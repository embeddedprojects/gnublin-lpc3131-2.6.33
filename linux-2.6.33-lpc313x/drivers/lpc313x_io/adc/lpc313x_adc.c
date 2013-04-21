/* 
 * lpc313x_adc.c
 * 
 * * LAST CHANGE: 2013-04-02 by Christian Karsch
 * 
 *  Authors:    Christian Karsch <contact@Christiankarsch.de> (c) 2013                                  - completely rewrite
 *              Nils Stec, "krumeltee", <info@fi-no.de>, (c) 2011,2012     - the kernel module on top of the adc code
 *              Michael Schwarz, (c) 2011                                  - the adc code itself
 *              some module parts are by LKMPG                             - taken from version "2007-05-18 ver 2.6.4"
 *
 * ADC driver for LPC313x (gnublin)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <asm/io.h>
#include <asm/uaccess.h>
#include <mach/registers.h>

#include <linux/init.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/fs.h>

#include <linux/cdev.h>       /* Support for /sys/class */
#include <linux/device.h>


#include "lpc313x_adc.h"

static dev_t driv_number;
static struct cdev *driv_object;
static struct class *driv_class;
static struct device *driv_dev;


#define DRIVER_AUTHOR "2013 Christian Karsch <contact@Christiankarsch.de>,  2011 Nils Stec \"krumeltee\" <info@fi-no.de>, 2011 Michael Schwarz"
#define DRIVER_DESC   "lpc313x adc driver for gnublin"

/* ################################################################################################################# */
/* ## Hardware handling ############################################################################################ */
/* ################################################################################################################# */

//#define ADC_CON_REG            __REG (ADC_PHYS + 0x20)
//#define ADC_R0_REG             __REG (ADC_PHYS + 0x00)
//#define ADC_R1_REG             __REG (ADC_PHYS + 0x04)
//#define ADC_R2_REG             __REG (ADC_PHYS + 0x08)
//#define ADC_R3_REG             __REG (ADC_PHYS + 0x0C)
//#define ADC_CSEL_REG           __REG (ADC_PHYS + 0x24)
//#define ADC_INT_ENABLE_REG     __REG (ADC_PHYS + 0x28)
//#define ADC_INT_STATUS_REG     __REG (ADC_PHYS + 0x2C)
//#define ADC_INT_CLEAR_REG      __REG (ADC_PHYS + 0x30)
#define ADC_INT_ENABLE  1
#define ADC_Rx_DATA     1023
#define ADC_ENABLE      (1 << 1)
#define ADC_CSCAN       (1 << 2)
#define ADC_SSCAN       (~ADC_CSCAN)
#define ADC_START       (1 << 3)
#define ADC_STOP        (~ADC_START)
#define ADC_STATUS      (1 << 4)
#define ADC_INT_STATUS  1
#define ADC_INT_CLEAR   1

#define ADC_CON_DEFAULT          0
#define ADC_CSEL_DEFAULT         0
#define ADC_INT_ENABLE_DEFAULT   0
#define ADC_INT_STATUS_DEFAULT   0
#define ADC_INT_CLEAR_DEFAULT    0

#define ADC_CALC_CSEL(ch, res) ((res) << ((ch) * 4))
#define ADC_DATA_MASK(res) ((1 << (res)) - 1)

#define ADC_POWERSAVE_AUTO 666
#define ADC_POWERSAVE_ON  1
#define ADC_POWERSAVE_OFF 0

int LPC313X_ADC_powerOn( void ) {
	int dummy;
	u32 timeout;

	SYS_ADC_PD = 0;

	/* enable clock for ADC */
	cgu_clk_en_dis( CGU_SB_ADC_CLK_ID, 1 );
	cgu_clk_en_dis( CGU_SB_ADC_PCLK_ID, 1 );

	/* reset to default */

	ADC_CON_REG = ADC_CON_DEFAULT;
	ADC_CSEL_REG = ADC_CSEL_DEFAULT;
	ADC_INT_ENABLE_REG = ADC_INT_ENABLE_DEFAULT;
	ADC_INT_CLEAR_REG = ADC_INT_CLEAR_DEFAULT;

	/* dummy interupt status register read */
	/** TODO: here we have to use a timeout, find out why and change, if neccessary.
	 if you re-enable the adc the whole board freezes without this timeout. **/
	dummy = ADC_INT_STATUS_REG ;
	timeout = 0x2ffff; // if timeout is too high, we have to wait a bit (system freezes for this time)
// for the driver while reenabling the adc. use 0x2fff.
	while ( ( ADC_INT_STATUS_REG & 1 ) && timeout-- )
	;

	/* enable ADC interrupt */
	ADC_INT_ENABLE_REG |= ADC_INT_ENABLE;

	/* set ADC power up */
	ADC_CON_REG |= ADC_ENABLE;

	return 0;
}

int LPC313X_ADC_powerOff( void ) {
	/* wait while there is a conversion */
	while ( ADC_INT_STATUS_REG & 0x10 )
	;

	/* set ADC to default state */
	ADC_CON_REG = ADC_CON_DEFAULT;
	ADC_CSEL_REG = ADC_CSEL_DEFAULT;
	ADC_INT_ENABLE_REG = ADC_INT_ENABLE_DEFAULT;
	ADC_INT_CLEAR_REG = ADC_INT_CLEAR_DEFAULT;

	/* disable clock for ADC */
	cgu_clk_en_dis( CGU_SB_ADC_CLK_ID, 0 );
	cgu_clk_en_dis( CGU_SB_ADC_PCLK_ID, 0 );

	return 0;
}

u16 LPC313X_ADC_readold( int channel, int resolution ) {
	u16 result = 0xffff;
	int timeout = 0xffffff;

	if ( ( ADC_INT_STATUS_REG & 1 ) ) {			// wait if there is a conversion
		while ( ADC_INT_STATUS_REG & 1 )
		ADC_INT_CLEAR_REG |= ( ADC_INT_CLEAR );
	}

	ADC_INT_ENABLE_REG |= ADC_INT_ENABLE;		// enable ADC interrupt

	if ( ( ADC_INT_STATUS_REG & 1 ) ) {		// wait until interrupt is cleared
		while ( ADC_INT_STATUS_REG & 1 )
		ADC_INT_CLEAR_REG |= ( ADC_INT_CLEAR );
	}

	ADC_CSEL_REG = ADC_CALC_CSEL(channel & 3, resolution);// select channel and resolution
	ADC_CON_REG &= ADC_SSCAN;				// single conversion mode
	ADC_CON_REG |= ADC_START;				// start
	while ( ( ADC_INT_STATUS_REG == 0 ) && timeout-- )
	;		// wait until a conversion is done

	if ( timeout == 0 )
		return 0xffff;

	ADC_INT_CLEAR_REG |= ADC_INT_CLEAR;		// wait until a conversion is done

	switch ( channel ) {	// read in the 10 bit value of the converted channel
	case 0:
		result = (u16) ADC_R0_REG & ADC_Rx_DATA;
		break;
		case 1:
		result = (u16) ADC_R1_REG & ADC_Rx_DATA;
		break;
		case 2:
		result = (u16) ADC_R2_REG & ADC_Rx_DATA;
		break;
		case 3:
		result = (u16) ADC_R3_REG & ADC_Rx_DATA;
		break;
	}
	ADC_CON_REG &= ADC_STOP;	// read in the 10 bit value of the converted channel
	while ( ADC_INT_STATUS_REG & 1 )
	ADC_INT_CLEAR_REG |= ADC_INT_CLEAR;	// wait until the interrupt status bit is cleared
	return result;
}

/* ################################################################################################################# */
/* ################################################################################################################# */
/* ################################################################################################################# */

static LPC313X_ADC_CONFIG config = { 0 };

u16 LPC313X_ADC_get( void ) {
	u16 result = 0;
	if ( config.flags.power == LPC313X_ADC_OFF ) {
		config.flags.errorcode = LPC313X_ADC_IS_OFF;
		return 0;
	}

	if ( config.flags.power == LPC313X_ADC_AUTO ) {
		LPC313X_ADC_powerOn();
	}

	if ( config.average[config.channel] == 0 ) {
		result = LPC313X_ADC_readold( config.channel,
				config.resulution[config.channel] );
	} else {
		u32 sum = 0;
		u8 loop = config.average[config.channel];
		while ( loop-- ) {
			sum += LPC313X_ADC_readold( config.channel,
					config.resulution[config.channel] );
		}
		result = sum / config.average[config.channel];
	}

	if ( config.flags.power == LPC313X_ADC_AUTO ) {
		LPC313X_ADC_powerOff();
	}
	config.flags.errorcode = LPC313X_ADC_OK;
	return result;
}

void LPC313X_ADC_conertToString( u16 val, char* s ) {
	sprintf( s, "0x%03x\n", val );
}

/* ################################################################################################################# */
/* ## Devicefile handling ########################################################################################## */
/* ################################################################################################################# */

static int isDeviceOpen = 0;

static int LPC313X_ADC_deviceOpen( struct inode* inode, struct file* file ) {
	if ( isDeviceOpen ) {
		return -EBUSY;
	}
	isDeviceOpen++;
	try_module_get( THIS_MODULE );
	return 0;
}

static int LPC313X_ADC_deviceRelease( struct inode* inode, struct file* file ) {
	isDeviceOpen--;
	module_put( THIS_MODULE );
	return 0;
}

long LPC313X_ADC_deviceIoctl( struct file* file, unsigned int cmd,
		unsigned long arg ) {
	LPC313X_ADC_VALUE result0 = { 0 };
	LPC313X_ADC_RESULUTION result1 = { 0 };
	LPC313X_ADC_AVERAGE result2 = { 0 };

	switch ( cmd ) {
	case LPC313X_ADC_GET_VALUE:
		result0.value = LPC313X_ADC_get();
		result0.channel = config.channel;
		result0.flags = config.flags;
		return result0.vint;
	case LPC313X_ADC_GET_RESULUTION:
		result1.resulution[0] = config.resulution[0];
		result1.resulution[1] = config.resulution[1];
		result1.resulution[2] = config.resulution[2];
		result1.resulution[3] = config.resulution[3];
		return result1.vint;
	case LPC313X_ADC_GET_AVERAGE:
		result2.average[0] = config.average[0];
		result2.average[1] = config.average[1];
		result2.average[2] = config.average[2];
		result2.average[3] = config.average[3];
		return result2.vint;
	case LPC313X_ADC_SET_CHANNEL:
		config.channel = (u8) arg & 0x03;
		break;
	}
	return 0;
}

static ssize_t LPC313X_ADC_deviceRead( struct file* file, char* buffer,
		size_t length, loff_t* offset ) {
	unsigned long ignore; // prevent -Wunused-result
	u16 val;
	if ( length == sizeof(LPC313X_ADC_READ) && !config.flags.legacy ) { // read exactly 12 Bytes
		LPC313X_ADC_READ data;
		data.value = LPC313X_ADC_get();
		data.config = config;

		ignore = copy_to_user( buffer, (unsigned char *) &data, length );
		return length;
	} else if ( length == 7 && !config.flags.legacy ) { // read exactly 7 Bytes
		char sVal[7]; /* { '0' , 'x' , '3 ' , 'F' , 'F' , '\n' ,'\0' } */
		val = LPC313X_ADC_get();
		sprintf( sVal, "0x%03x\n", val );
		ignore = copy_to_user( buffer, (unsigned char *) sVal, length );
		return length;
	} else {
		static char msg[7] = { 0 }; /* { '0' , 'x' , '3 ' , 'F' , 'F' , '\n' ,'\0' } */
		static char* msgPtr = msg;
		static int sendEOF = 1;

		int bytes_read = 0;
		if ( *msgPtr == '\0' ) {
			if ( sendEOF ) {
				sendEOF = 0;
				val = LPC313X_ADC_get();
				sprintf( msg, "0x%03x\n", val );
				msgPtr = msg;
			} else {
				sendEOF = 1;
				return 0;
			}
		}
		while ( length && *msgPtr ) {
			put_user( *( msgPtr++ ), buffer++ );
			length--;
			bytes_read++;
		}
		return bytes_read;
	}
}

static ssize_t LPC313X_ADC_deviceWrite( struct file* file, const char* buff,
		size_t len, loff_t* off ) {
	if ( len == sizeof(LPC313X_ADC_CONFIG) ) { // 10 Bytes
		unsigned long ignore; // prevent -Wunused-result
		ignore = copy_from_user( &config, buff, len );
		if ( config.channel > 3 ) {
			config.channel = 0;
		}
		if ( config.resulution[0] > 10 || config.resulution[0] < 1 ) {
			config.resulution[0] = 10;
		}
		if ( config.resulution[1] > 10 || config.resulution[1] < 1 ) {
			config.resulution[1] = 10;
		}
		if ( config.resulution[2] > 10 || config.resulution[2] < 1 ) {
			config.resulution[2] = 10;
		}
		if ( config.resulution[3] > 10 || config.resulution[3] < 1 ) {
			config.resulution[3] = 10;
		}
		if ( config.flags.power > 2 ) {
			config.flags.power = LPC313X_ADC_AUTO;
		}
		if ( config.flags.power == LPC313X_ADC_ON ) {
			LPC313X_ADC_powerOn();
		} else {
			LPC313X_ADC_powerOff();
		}
		return len;
	} else { // len <= 9
		/**
		 * BIT 31 if '1' print status in KERN_INFO and exit
		 *     30 if '1' print status in KERN_INFO and exit
		 *     29 if '1' print status in KERN_INFO and exit
		 *     28 if '1' print status in KERN_INFO and exit
		 *
		 *     11 average
		 *     10 average
		 *      9 powersave
		 *      8 powersave
		 *      7 debug
		 *
		 *      5 resolution
		 *      4 resolution
		 *
		 *      1 channel
		 * BIT  0 channel
		 */
		char message_from_user[5]; /* 5 Bytes 'FFFF\0'*/
		long ltemp;
		u16 config_word;

		config_word = 0;

		if ( copy_from_user( message_from_user, buff,
				( len < sizeof( message_from_user ) ) ?
						len : sizeof( message_from_user ) ) ) {
			return -EINVAL;
		}
		message_from_user[4] = '\0';
		ltemp = simple_strtol( message_from_user, NULL, 16 );

		config_word = (u16) ( ltemp & 0xffff );

		/* DEBUG [BIT 7] */
		if ( config_word & 0x0080 ) {
			config.flags.debug = 1;
		} else {
			config.flags.debug = 0;
		}

		if ( config.flags.debug )
			printk(
					KERN_INFO "[lpc313x adc] got config word 0x%04x, setting up adc:\n",
					config_word );

		/* Print Status [BIT 31:28] */
		// first of all, check if user want's to see status, if, print it and exit
		if ( ( ( config_word >> 12 ) & 0x0003 ) > 0 ) {
			printk(
					KERN_INFO "[lpc313x adc] channel:'%d', resolution:'%d', averaging:'%d'loops\n",
					config.channel, config.resulution[config.channel],
					config.average[config.channel] );
			switch ( config.flags.power ) {
			case LPC313X_ADC_ON:
				printk(
						KERN_INFO "[lpc313x adc] powersave off, adc always on\n" );
				break;
			case LPC313X_ADC_OFF:
				printk(
						KERN_INFO "[lpc313x adc] powersave on, adc always off\n" );
				break;
			case LPC313X_ADC_AUTO:
				printk( KERN_INFO "[lpc313x adc] powersave auto (default)\n" );
				break;
			}
			return len;
		}

		/* CHANNEL [BIT 1:0]*/
		config.channel = config_word & 0x0003;	// get adc channel config

		/* RESOLUTION [BIT 5:4] */
		switch ( ( ( config_word >> 4 ) & 0x0003 ) ) {	// get resolution config
		case 0:
			//printk( KERN_INFO "set res to 10\n" );
			config.resulution[config.channel] = 10;
			break;
		case 1:
			//printk( KERN_INFO "set res to 8\n" );
			config.resulution[config.channel] = 8;
			break;
		case 2:
			//printk( KERN_INFO "set res to 4\n" );
			config.resulution[config.channel] = 4;
			break;
		default:
			//printk( KERN_INFO "set res to 10\n" );
			config.resulution[config.channel] = 10;
			break;
		}

		/* AVERAGE [BIT 11:10]*/
		switch ( ( ( config_word >> 10 ) & 0x0003 ) ) { // get averaging config
		case 0:
			config.average[config.channel] = 0;
			break;
		case 1:
			config.average[config.channel] = 10;
			break;
		case 2:
			config.average[config.channel] = 75;
			break;
		case 3:
			config.average[config.channel] = 150;
			break;
		default:
			config.average[config.channel] = 0;
			break;
		}

		/*powersave [BIT 9:8]*/
		switch ( ( ( config_word >> 8 ) & 0x0003 ) ) { // get adc powersave mode config
		case 0:
			config.flags.power = LPC313X_ADC_ON; // adc powersave off, adc always on
			LPC313X_ADC_powerOn();			// turn on adc
			break;
		case 1:
			config.flags.power = LPC313X_ADC_OFF;// adc powersave auto, on/off when needed, takes more time, saves power (default)
			LPC313X_ADC_powerOff();			// turn off adc
			break;
		case 2:
			config.flags.power = LPC313X_ADC_ON;	// adc always off
			LPC313X_ADC_powerOn();			// turn off adc
			break;
		default:
			config.flags.power = LPC313X_ADC_AUTO;	// default behaviour, AUTO
			LPC313X_ADC_powerOff();			// turn off adc
			break;
		}

		if ( config.flags.debug ) {
			printk(
					KERN_INFO "[lpc313x adc] channel:'%d', resolution:'%d', averaging:'%d'loops\n",
					config.channel, config.resulution[config.channel],
					config.average[config.channel] );
			switch ( config.flags.power ) {
			case LPC313X_ADC_ON:
				printk(
						KERN_INFO "[lpc313x adc] powersave off, adc always on\n" );
				break;
			case LPC313X_ADC_OFF:
				printk(
						KERN_INFO "[lpc313x adc] powersave on, adc always off\n" );
				break;
			case LPC313X_ADC_AUTO:
				printk( KERN_INFO "[lpc313x adc] powersave auto (default)\n" );
				break;
			}
		}
		return len;
	}
}

/* ################################################################################################################# */
/* ## Module handling  ############################################################################################# */
/* ################################################################################################################# */

static struct file_operations moduleFO = { .owner = THIS_MODULE, .read =
		LPC313X_ADC_deviceRead, .write = LPC313X_ADC_deviceWrite,
		.unlocked_ioctl = LPC313X_ADC_deviceIoctl, .open =
				LPC313X_ADC_deviceOpen, .release = LPC313X_ADC_deviceRelease };

static int moduleMajor;

int LPC313X_ADC_moduleInit( void ) {
	config.channel = 0;
	config.resulution[0] = 10;
	config.resulution[1] = 10;
	config.resulution[2] = 10;
	config.resulution[3] = 10;
	config.average[0] = 0;
	config.average[1] = 0;
	config.average[2] = 0;
	config.average[3] = 0;
	config.flags.power = LPC313X_ADC_AUTO;
	config.flags.legacy = 0;
	config.flags.debug = 0;
 
	/* Driver loading with Sysfs support --BN */
        if(alloc_chrdev_region(&driv_number,0,1,"lpc313x_adc_dev") < 0 ) return -EIO;
        driv_object = cdev_alloc();

        if( driv_object==NULL)
        goto free_device_number;

        driv_object->owner = THIS_MODULE;
        driv_object->ops   = &moduleFO;

        if( cdev_add(driv_object,driv_number,1))
        goto free_cdev;

        driv_class = class_create(THIS_MODULE, "lpc313x_adc");
        if( IS_ERR(driv_class) ) {
        pr_err( "[lpc313x_adc] no sysfs support\n");
        goto free_cdev;
        }

        driv_dev = device_create(driv_class, NULL, driv_number, NULL, "%s", "lpc313x_adc");

/*
	moduleMajor = register_chrdev( 0, LPC313X_ADC_DEVNAME, &moduleFO );
	if ( moduleMajor < 0 ) {
		printk(
				KERN_ALERT "[lpc313x adc] registering char device failed with %d\n",
				moduleMajor );
		return moduleMajor;
	}
*/
	switch ( config.flags.power ) {
	case LPC313X_ADC_ON:
		LPC313X_ADC_powerOn();
		break;
	default:
		LPC313X_ADC_powerOff();
		break;
	}

        dev_info(driv_dev, "[lpc313x_adc] driver loaded\n");

	return 0;



free_cdev:
        kobject_put(&driv_object->kobj);
free_device_number:
        unregister_chrdev_region(driv_number, 1);
        return -EIO;

}

void LPC313X_ADC_moduleExit( void ) {
	LPC313X_ADC_powerOff();
       
        device_release_driver(driv_dev);
        device_destroy(driv_class,driv_number);
        class_destroy(driv_class);
        cdev_del(driv_object);
        unregister_chrdev_region(driv_number,1);

        dev_info(driv_dev, "[lpc313x_adc] driver unloaded\n");

//	unregister_chrdev( moduleMajor, LPC313X_ADC_DEVNAME );
//	printk( KERN_INFO "[lpc313x adc] DRIVER UNLOADED\n" );
}

module_init( LPC313X_ADC_moduleInit )
;
module_exit( LPC313X_ADC_moduleExit )
;

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( DRIVER_AUTHOR );
MODULE_DESCRIPTION( DRIVER_DESC );
MODULE_SUPPORTED_DEVICE( "lpc313x adc on gnublin" );
/* EOF */

