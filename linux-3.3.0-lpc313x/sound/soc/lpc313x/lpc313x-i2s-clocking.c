/*
 * sound/soc/lpc313x/lpc313x-i2s-clocking.c
 *
 * Author: Kevin Wells <kevin.wells@nxp.com>
 *
 * Copyright (C) 2009 NXP Semiconductors
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

/*
 * Note: Fractional clock divider domains are defined in the bootloader
 * code. As of the time this driver was developed, the fractional
 * divider groupings are mapped as follows:
 *     Group 17 -> TX0 WS, TX1, WS, RX0 WS, RX1 WS
 *     Group 18 -> TX0 BCK, TX1 BCK
 *     Group 19 -> CLK_256FS, TX_CLK0
 *     Group 20 -> RX0 BCK, RX1 BCK
 *
 * The driver supports the following sample rates and FS clock
 * multipliers. These rates are dependent on an external 12MHz
 * oscillator input. All these rates are generated from a small set of
 * PLL frequencies and a fractional divider. Some of the rates can be
 * generated by more than 1PLL frequency.
 *            8K  11.025K 12K 16K 22.05K 24K 32K 44.1K 48K
 *  128FS     Yes Yes     Yes Yes Yes    Yes Yes Yes   Yes
 *  256FS     Yes Yes     Yes Yes Yes    Yes Yes Yes   Yes
 *  384FS     Yes Yes     Yes Yes Yes    Yes Yes Yes   Yes
 *  512FS     Yes Yes     Yes Yes Yes    Yes Yes Yes   Yes
 *  768FS     Yes Yes     Yes Yes Yes    Yes Yes Yes   Yes
 *  1024FS    Yes Yes     Yes Yes Yes    Yes Yes Yes   Yes
 */

#include <linux/io.h>

#include <mach/board.h>
#include <mach/registers.h>
#include "lpc313x-i2s-clocking.h"

struct i2s_clk_setup {
	u32 target_codec_rate;
	u32 real_fs_codec_rate;
};
static struct i2s_clk_setup i2s_clk_state;

/*
 * clock setup enable/disable selection arrays - these clocks are enabled as a group
 * for a specific I2S channel
 */
static CGU_CLOCK_ID_T rx0clks[] = {
	CGU_SB_I2SRX_IF_0_PCLK_ID,
	CGU_SB_I2SRX_FIFO_0_PCLK_ID,
	CGU_SB_I2SRX_BCK0_N_ID,
	CGU_SB_I2SRX_WS0_ID,
	CGU_SB_I2SRX_BCK0_ID,
	CGU_SB_INVALID_CLK_ID
};
static CGU_CLOCK_ID_T tx0clks[] = {
	CGU_SB_I2STX_IF_0_PCLK_ID,
	CGU_SB_I2STX_FIFO_0_PCLK_ID,
	CGU_SB_I2STX_BCK0_N_ID,
	CGU_SB_I2STX_WS0_ID,
	CGU_SB_INVALID_CLK_ID
};
static CGU_CLOCK_ID_T rx1clks[] = {
	CGU_SB_I2SRX_IF_1_PCLK_ID,
	CGU_SB_I2SRX_FIFO_1_PCLK_ID,
	CGU_SB_I2SRX_BCK1_N_ID,
	CGU_SB_I2SRX_WS1_ID,
	CGU_SB_I2SRX_BCK1_ID,
	CGU_SB_INVALID_CLK_ID
};
static CGU_CLOCK_ID_T tx1clks[] = {
	CGU_SB_I2STX_IF_1_PCLK_ID,
	CGU_SB_I2STX_FIFO_1_PCLK_ID,
	CGU_SB_I2STX_BCK1_N_ID,
	CGU_SB_I2STX_WS1_ID,
	CGU_SB_INVALID_CLK_ID
};

typedef CGU_CLOCK_ID_T * P_CGU_CLOCK_ID_T;
static P_CGU_CLOCK_ID_T clkarray[CLK_TX_1 + 1] = {
	rx0clks,
	tx0clks,
	rx1clks,
	tx1clks
};

/* 48K*1024 sysclk rate settings (12M oscillator input),
   49152000Hz FS clock, error .003999Hz
   used for the following rates with the following dividers:
 *            8K  11.025K 12K 16K 22.05K 24K 32K 44.1K 48K
 *  128FS     48          32  24         16  12        8
 *  256FS     24          16  12         8   6         4
 *  384FS     16              8              4
 *  512FS     12          8              4   3         2
 *  768FS     8               4              2
 *  1024FS    6           4   3          2             1
*/
static CGU_HPLL_SETUP_T pllsetup_48K_1024 = {
	CGU_FIN_SELECT_FFAST, 514, 21708, 5, 0, 44, 21, 0, (48000 * 1024)
};

/* 48K*768 sysclk rate settings (12M oscillator input),
   36864000Hz FS clock, error .003999Hz
   used for the following rates with the following dividers:
 *            8K  11.025K 12K 16K 22.05K 24K 32K 44.1K 48K
 *  128FS     36          24  18         12            6
 *  256FS     18          12  9          6             3
 *  384FS     12          8   6          4   3         2
 *  512FS     9           6
 *  768FS     6           4              2             1
 *  1024FS
*/
static CGU_HPLL_SETUP_T pllsetup_48K_768 = {
	CGU_FIN_SELECT_FFAST, 514, 21299, 21, 0, 44, 22, 0, (48000 * 768)
};

/* 44.1K*1024 sysclk rate settings (12M oscillator input),
   45158400Hz FS clock, error .0131999Hz
   used for the following rates with the following dividers:
 *            8K  11.025K 12K 16K 22.05K 24K 32K 44.1K 48K
 *  128FS         32              16              8
 *  256FS         16              8               4
 *  384FS
 *  512FS         8               4               2
 *  768FS
 *  1024FS        4               2               1
*/
static CGU_HPLL_SETUP_T pllsetup_44_1K_1024 = {
	CGU_FIN_SELECT_FFAST, 770, 8191, 2, 0, 16, 8, 0, (44100 * 1024)
};

/* 44.1K*768 sysclk rate settings (12M oscillator input),
   33868800Hz FS clock, error .0099Hz
   used for the following rates with the following dividers:
 *            8K  11.025K 12K 16K 22.05K 24K 32K 44.1K 48K
 *  128FS         24              12              6
 *  256FS         12              6               3
 *  384FS         8               4               2
 *  512FS         6               3
 *  768FS         4               2               1
 *  1024FS        3
*/
static CGU_HPLL_SETUP_T pllsetup_44_1K_768 = {
	CGU_FIN_SELECT_FFAST, 514, 19660, 11, 0, 48, 23, 0, (44100 * 768)
};

/* 32K*1024 sysclk rate settings (12M oscillator input),
   32768000Hz FS clock, error .01638Hz
   used for the following rates with the following dividers:
 *            8K  11.025K 12K 16K 22.05K 24K 32K 44.1K 48K
 *  128FS     32              16             8
 *  256FS     16              8              4
 *  384FS
 *  512FS     8               4              2
 *  768FS
 *  1024FS                                   1
*/
static CGU_HPLL_SETUP_T pllsetup_32K_1024 = {
	CGU_FIN_SELECT_FFAST, 770, 32765, 21, 0, 20, 10, 0, (32000 * 1024)
};

static CGU_HPLL_SETUP_T *ppll_list[] = {
	&pllsetup_32K_1024,
	&pllsetup_44_1K_768,
	&pllsetup_44_1K_1024,
	&pllsetup_48K_768,
	&pllsetup_48K_1024,
	NULL
};

#if defined(CONFIG_SND_LPC315X_SOC)
/* For LPC315X Analog CODEC 128FS clock has to be used */
static const u32 fsdiv =
#if defined (CONFIG_SND_CODEC_FS128)
	128;
#endif
#endif

#if defined(CONFIG_SND_LPC313X_SOC)
static const u32 fsdiv =
#if defined (CONFIG_SND_CODEC_FS256)
	256;
#elif defined (CONFIG_SND_CODEC_FS384)
	384;
#elif defined (CONFIG_SND_CODEC_FS512)
	512;
#elif defined (CONFIG_SND_CODEC_FS768)
	768;
#elif defined (CONFIG_SND_CODEC_FS1024)
	1024;
#endif
#endif

static u32 lpc313x_set_best_rate(u32 freq)
{
	CGU_FDIV_SETUP_T clk_div;
	u32 diff;
	int i = 0;

	clk_div.stretch = 1;

	while (ppll_list[i] != NULL)
	{
		/* Find match divider based on current FS divider and rate */
		diff = ppll_list[i]->freq / fsdiv;
		clk_div.m = diff / freq;
		diff = diff - (freq * clk_div.m);

		if (diff == 0)
		{
			if (clk_div.m <= 1)
			{
				clk_div.n = 0;
				clk_div.m = 0;
			}
			else
			{
				clk_div.n = 1;
			}

			/* Set PLL rate and divider for CODEC clock */
			i2s_clk_state.real_fs_codec_rate = ppll_list[i]->freq;
			cgu_hpll_config(CGU_HPLL0_ID, ppll_list[i]);
			cgu_fdiv_config(19, clk_div, 1);
			return freq;
		}

		i++;
	}

	return 0;
}

/*
 * Sets up the audio PLL to generate a frequency as close as possible to
 * the target clkrate frequency
 */
static u32 lpc313x_set_codec_freq(u32 freq)
{
	if (freq == 0)
	{
		/* Disable the required audio CODEC clocks */
		cgu_clk_en_dis(CGU_SB_CLK_256FS_ID, 0);
		cgu_clk_en_dis(CGU_SB_I2S_EDGE_DETECT_CLK_ID, 0);
	}
	else if (freq != i2s_clk_state.target_codec_rate)
	{
		/* Disable the required audio CODEC clocks during frequency change */
		cgu_clk_en_dis(CGU_SB_CLK_256FS_ID, 0);
		cgu_clk_en_dis(CGU_SB_I2S_EDGE_DETECT_CLK_ID, 0);

		freq = lpc313x_set_best_rate(freq);
		if (freq > 0)
		{
#if !defined (CONFIG_SND_CODEC_NO_FS256_NEEDED)
			/* Enable clock */
			cgu_clk_en_dis(CGU_SB_CLK_256FS_ID, 1);
#endif
			cgu_clk_en_dis(CGU_SB_I2S_EDGE_DETECT_CLK_ID, 1);
		}
	}

	i2s_clk_state.target_codec_rate = freq;

	return freq;
}

/*
 * Start or stop a channel's clocks
 */
static void lpc313x_ch_clk_disen(enum i2s_supp_clks chclk, int en)
{
	int i = 0;
	P_CGU_CLOCK_ID_T pclks = (P_CGU_CLOCK_ID_T) clkarray[chclk];

	while (pclks[i] != CGU_SB_INVALID_CLK_ID)
	{
		cgu_clk_en_dis(pclks[i], en);
		i++;
	}
}

/*
 * Sets up the channel bit clock to generate a rate as close as possible
 * to the target clkrate frequency
 */
static u32 lpc313x_set_ch_freq(enum i2s_supp_clks chclk, u32 ws_freq, u32 bit_freq)
{
	CGU_FDIV_SETUP_T ch_div;

	if (ws_freq == 0)
	{
		/* Turn channel clock off */
		lpc313x_ch_clk_disen(chclk, 0);
		bit_freq = 0;
	}
	else
	{
		/* Stop channel clocks for the change */
		lpc313x_ch_clk_disen(chclk, 0);

		ch_div.stretch = 1;
		ch_div.n = 1;

		/* Find divider to generate target WS frequency from PLL */
		ch_div.m = i2s_clk_state.real_fs_codec_rate / ws_freq;
		cgu_fdiv_config(17, ch_div, 1);

		/* Find divider to generate target bck frequency from PLL */
		ch_div.m = i2s_clk_state.real_fs_codec_rate / bit_freq;

		if ((chclk == CLK_RX_0) || (chclk == CLK_RX_1)) {
			cgu_fdiv_config(20, ch_div, 1);
		}
		if ((chclk == CLK_TX_0) || (chclk == CLK_TX_1)) {
			cgu_fdiv_config(18, ch_div, 1);
		}

		/* Enable channel clock */
		lpc313x_ch_clk_disen(chclk, 1);
	}

	return ws_freq;
}

/*
 * Set the audio CODEC clock rate or 0 to disable the clock, returns
 * the actual programmed clock rate. The programmed rate is generated on
 * the FS256 pin has a rate of (256 * clkrate).
 */
u32 lpc313x_main_clk_rate(u32 freq)
{
	u32 ret = 0;
	/* Compute and set proper divider */
	ret = lpc313x_set_codec_freq(freq);
#if defined (CONFIG_SND_DEBUG_VERBOSE)
	pr_info("LPC313x ASOC main clock : %d (%d)\n",
		i2s_clk_state.target_codec_rate,
		i2s_clk_state.real_fs_codec_rate);
#endif
	return ret;
}

/*
 * Set a specific channel's bit clock and word select rates. his applies
 * to the channel's WS and BCLK signals. Returns the actual programmed
 * WS clock rate.
 */
u32 lpc313x_chan_clk_enable(enum i2s_supp_clks chclk, u32 ws_freq, u32 bit_freq)
{
	/* Compute and set proper divider */
	return lpc313x_set_ch_freq(chclk, ws_freq, bit_freq);
}
