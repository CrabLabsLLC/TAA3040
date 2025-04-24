/**
 * @file taa3040_types.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef TAA3040_TYPES_H
#define TAA3040_TYPES_H

#pragma once

#include <stdint.h>
#include <stdbool.h>

#define TAA3040_NUM_CHANNELS 4

/** Function pointer for I2C write operation */
typedef bool (*taa3040_i2c_write_t)(const uint8_t address, const uint8_t reg, const uint8_t data);

/** Function pointer for I2C read operation */
typedef bool (*taa3040_i2c_read_t)(const uint8_t address, const uint8_t reg, uint8_t *const data);

/** Function pointer for GPIO control (e.g., enable pin) */
typedef void (*taa3040_gpio_set_t)(const bool state);

/** Enum for filter types */
typedef enum {
    TAA3040_FILTER_LOW_PASS =   0x01,   ///< Blocks High Frequencies
    TAA3040_FILTER_HIGH_PASS =  0x02,   ///< Blocks Low Frequencies
    TAA3040_FILTER_BAND_PASS =  0x03,   ///< Allows Frequencies in a limited band
    TAA3040_FILTER_BAND_STOP =  0x04    ///< Allows all frequencies except for a limited band
} taa3040_filter_type_t;

typedef enum {
    TAA3040_OUTPUT_MODE_TDM = 0x0,  ///< Time Division Multiplexing the Channels
    TAA3040_OUTPUT_MODE_I2S = 0x1,  ///< Inter-IC Sound (I2S) Output
    TAA3040_OUTPUT_MODE_LJ  = 0x2,  ///< Left Justified Mode
    TAA3040_OUTPUT_MODE_RESERVED
} taa3040_output_mode_t;

typedef enum {
    TAA3040_OUTPUT_LENGTH_16BITS = 0x0, ///< 16 bit words 
    TAA3040_OUTPUT_LENGTH_20BITS = 0x1, ///< 20 bit words
    TAA3040_OUTPUT_LENGTH_24BITS = 0x2, ///< 24 bit words
    TAA3040_OUTPUT_LENGTH_32BITS = 0x3, ///< 32 bit words 
} taa3040_output_length_t;

typedef enum {
    TAA3040_CHANNEL_MODE_ANALOG_DIFF    = 0x0,  ///< Differential Analog Mode
    TAA3040_CHANNEL_MODE_ANALOG_SE      = 0x1,  ///< Single Ended Analog Mode
    TAA3040_CHANNEL_MODE_DIGITAL_PDM    = 0x2,  ///< Digital PDM Mode
    TAA3040_CHANNEL_MODE_RESERVED       = 0x3
} taa3040_channel_mode_t;

typedef enum {
    TAA3040_CHANNEL_IMPEDANCE_2K5   = 0x0,  ///< 2.5k Ohm Input Impedance
    TAA3040_CHANNEL_IMPEDANCE_10K   = 0x1,  ///< 10k Ohm Input Impedance
    TAA3040_CHANNEL_IMPEDANCE_20K   = 0x2,  ///< 20k Ohm Input Impedance
    TAA3040_CHANNEL_IMPEDANCE_RESERVED 
} taa3040_channel_impedance_t;

typedef enum {
    TAA3040_REFERENCE_VOLTAGE_2V75  = 0x0,  ///< 2.75 Volt Reference
    TAA3040_REFERENCE_VOLTAGE_2V5   = 0x1,  ///< 2.5 Volt Reference
    TAA3040_REFERENCE_VOLTAGE_1V375 = 0x2,  ///< 1.375 Volt Reference
    TAA3040_REFERENCE_VOLAGE_RESERVED
} taa3040_reference_voltage_t;

typedef enum {
    TAA3040_MIC_BIAS_VREF           = 0x0,  ///< Mic Bias is Same as reference voltage
    TAA3040_MIC_BIAS_VREF_SCALED    = 0x1,  ///< Mic Bias is reference voltage * 1.096
    TAA3040_MIC_BIAS_AVDD           = 0x6,  ///< Mic Bias is analog input voltage
    TAA3040_MIC_BIAS_RESERVED       = 0x7
} taa3040_mic_bias_t;

typedef enum {
    TAA3040_HIGHPASS_CUTOFF_PROGRAMMABLE  = 0x0,    ///< IIR Filter coefficients need to be set and used 
    TAA3040_HIGHPASS_CUTOFF_FS_DIV_4000   = 0x1,    ///< Cutoff at sampling frequency divided by 4000
    TAA3040_HIGHPASS_CUTOFF_FS_DIV_500    = 0x2,    ///< Cutoff at sampling frequency divided by 500
    TAA3040_HIGHPASS_CUTOFF_FS_DIV_125    = 0x3,    ///< Cutoff at sampling frequency divided by 125
} taa3040_highpass_cutoff_t;

typedef enum {
    TAA3040_BIQUAD_FILTER_MODE_DISABLED = 0x0,  ///< Biquads disabled
    TAA3040_BIQUAD_FILTER_MODE_SINGLE   = 0x1,  ///< One Biquad filter per channel
    TAA3040_BIQUAD_FILTER_MODE_DUAL     = 0x2,  ///< Two Biquad filters per channel
    TAA3040_BIQUAD_FILTER_MODE_TRIPLE   = 0x3,  ///< Three Biquad filters per channel
} taa3040_biquad_filter_mode_t;

typedef enum {
    TAA3040_CHANNEL_SUMMING_DISABLED = 0x0,     ///< Channel Summing Disabled
    TAA3040_CHANNEL_SUMMING_DOUBLE   = 0x1,     ///< Sum and Average 2 channels (1, 2), (3, 4), (5, 6)
    TAA3040_CHANNEL_SUMMING_QUAD     = 0x2,     ///< Sum and Average 4 channels (1, 2, 3, 4)
    TAA3040_CHANNEL_RESERVED
} taa3040_channel_summing_t;

typedef enum {
    TAA3040_DECIMATION_MODE_LINEAR_PHASE        = 0x0,
    TAA3040_DECIMATION_MODE_LOW_LATENCY         = 0x1,
    TAA3040_DECIMATION_MODE_VERY_LOW_LATENCY    = 0x2,
    TAA3040_DECIMATION_MODE_RESERVED            
} taa3040_decimation_mode_t;

typedef enum {
    TAA3040_GPIO_MODE_FLOATING      = 0x0,  ///< GPIO1 is high impedance
    TAA3040_GPIO_MODE_PUSH_PULL     = 0x1,  ///< GPIO1 is push pull output
    TAA3040_GPIO_MODE_OPEN_DRAIN_PU = 0x2,  ///< GPIO1 is open drain with a pull up resistor
    TAA3040_GPIO_MODE_OPEN_DRAIN    = 0x3,  ///< GPIO1 is either floating or zero
    TAA3040_GPIO_MODE_OPEN_SOURCE_PD= 0x4,  ///< GPIO1 is either strong up or weak down
    TAA3040_GPIO_MODE_OPEN_SOURCE   = 0x5,  ///< GPIO1 is either strong high or floating
    TAA3040_GPIO_MODE_RESERVED
} taa3040_gpio_config_t;

/** Device context structure */
typedef struct {
    const taa3040_i2c_write_t i2c_write;
    const taa3040_i2c_read_t i2c_read;
    const taa3040_gpio_set_t enable_pin;
} taa3040_hal_t;

typedef struct {


} taa3040_config_t;

typedef struct {



} taa3040_channel_config_t;

typedef struct taa3040
{
    taa3040_config_t config;
#ifndef TAA3040_MINIMAL_RAM
    taa3040_channel_config_t channel_configs[TAA3040_NUM_CHANNELS];
#endif
} taa3040_t;

#endif