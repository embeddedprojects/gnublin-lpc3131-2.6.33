#define LPC313X_ADC_DEVNAME "lpc313x_adc"

enum LPC313X_ADC_POWER_ENUM {
	LPC313X_ADC_OFF = 0, LPC313X_ADC_ON = 1, LPC313X_ADC_AUTO = 2
};
typedef enum LPC313X_ADC_POWER_ENUM LPC313X_ADC_POWER;

enum LPC313X_ADC_ERRORCODE_ENUM {
	LPC313X_ADC_OK = 0, LPC313X_ADC_UNKNOWN = 1, LPC313X_ADC_IS_OFF = 2
};
typedef enum LPC313X_ADC_ERRORCODE_ENUM LPC313X_ADC_ERRORCODE;

struct LPC313X_ADC_FLAGS_STRUCT {
	uint8_t errorcode :4;
	uint8_t power :2;
	uint8_t legacy :1;
	uint8_t debug :1;
};
typedef struct LPC313X_ADC_FLAGS_STRUCT LPC313X_ADC_FLAGS;

struct LPC313X_ADC_CONFIG_STRUCT {
	uint8_t channel;
	uint8_t resulution[4];
	uint8_t average[4];
	LPC313X_ADC_FLAGS flags;
};
typedef struct LPC313X_ADC_CONFIG_STRUCT LPC313X_ADC_CONFIG;
typedef LPC313X_ADC_CONFIG LPC313X_ADC_WRITE;

#define LPC313X_ADC_CONFIG_DEFAULT {0,{10,10,10,10},{0,0,0,0},{0,2,0,0}}

struct LPC313X_ADC_READ_STRUCT {
	uint16_t value;
	union {
		struct {
			uint8_t channel;
			uint8_t resulution[4];
			uint8_t average[4];
			LPC313X_ADC_FLAGS flags;
		};
		LPC313X_ADC_CONFIG config;
	};
};
typedef struct LPC313X_ADC_READ_STRUCT LPC313X_ADC_READ;

/* IOCTRL */

enum LPC313x_ADC_CMD_ENUM {
	LPC313X_ADC_GET_VALUE = 0,
	LPC313X_ADC_GET_RESULUTION = 1,
	LPC313X_ADC_GET_AVERAGE = 2,
	LPC313X_ADC_SET_CHANNEL = 3
};
typedef enum LPC313X_ADC_CMD_ENUM LPC313X_ADC_CMD;

union LPC313X_ADC_VALUE_UNION {
	int32_t vint;
	struct {
		uint16_t value;
		uint8_t channel;
		LPC313X_ADC_FLAGS flags;
	};
};
typedef union LPC313X_ADC_VALUE_UNION LPC313X_ADC_VALUE;

union LPC313X_ADC_RESULUTION_UNION {
	int32_t vint;
	uint8_t resulution[4];
};
typedef union LPC313X_ADC_RESULUTION_UNION LPC313X_ADC_RESULUTION;

union LPC313X_ADC_AVERAGE_UNION {
	int32_t vint;
	uint8_t average[4];
};
typedef union LPC313X_ADC_AVERAGE_UNION LPC313X_ADC_AVERAGE;

/*EOF*/

