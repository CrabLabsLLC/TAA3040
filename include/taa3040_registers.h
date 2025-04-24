/**
 * @file taa3040_registers.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#ifndef TAA3040_REGISTERS_H
#define TAA3040_REGISTERS_H

#include <stdint.h>


/**
 * @brief Page 0 Registers
 * 
 */
typedef enum {
    TAA3040_P0_PAGE_CFG         = 0x00, ///< Device page select (R/W) 
    TAA3040_P0_SW_RESET         = 0x01, ///< Software reset (self-clearing)
    TAA3040_P0_SLEEP_CFG        = 0x02, ///< Regulator, VREF, I2C broadcast, sleep 
    // 0x03–0x04 reserved 
    TAA3040_P0_SHDN_CFG         = 0x05, ///< Shutdown configuration 
    // 0x06 reserved
    TAA3040_P0_ASI_CFG0         = 0x07, ///< ASI format, word length, polarity
    TAA3040_P0_ASI_CFG1         = 0x08, ///< ASI LSB, keeper, offset 
    TAA3040_P0_ASI_CFG2         = 0x09, ///< ASI daisy, error detect, auto-resume 
    // 0x0A reserved 
    TAA3040_P0_ASI_CH1          = 0x0B, ///< ASI channel 1 slot/output 
    TAA3040_P0_ASI_CH2          = 0x0C, ///< ASI channel 2 slot/output 
    TAA3040_P0_ASI_CH3          = 0x0D, ///< ASI channel 3 slot/output 
    TAA3040_P0_ASI_CH4          = 0x0E, ///< ASI channel 4 slot/output 
    TAA3040_P0_ASI_CH5          = 0x0F, ///< ASI channel 5 slot/output 
    TAA3040_P0_ASI_CH6          = 0x10, ///< ASI channel 6 slot/output 
    TAA3040_P0_ASI_CH7          = 0x11, ///< ASI channel 7 slot/output 
    TAA3040_P0_ASI_CH8          = 0x12, ///< ASI channel 8 slot/output 
    TAA3040_P0_MST_CFG0         = 0x13, ///< Master/slave, auto clock, PLL disable 
    TAA3040_P0_MST_CFG1         = 0x14, ///< FS_RATE and BCLK/FSYNC ratio 
    TAA3040_P0_ASI_STS          = 0x15, ///< ASI clock monitor status 
    TAA3040_P0_CLK_SRC          = 0x16, ///< Clock source config 
    // 0x17–0x1E reserved 
    TAA3040_P0_PDMCLK_CFG       = 0x1F, ///< PDM clock divider 
    TAA3040_P0_PDMIN_CFG        = 0x20, ///< PDM DIN edge config 
    TAA3040_P0_GPIO_CFG0        = 0x21, ///< GPIO1 config and drive 
    TAA3040_P0_GPO_CFG0         = 0x22, ///< GPO1 config and drive 
    TAA3040_P0_GPO_CFG1         = 0x23, ///< GPO2 config and drive 
    TAA3040_P0_GPO_CFG2         = 0x24, ///< GPO3 config and drive 
    TAA3040_P0_GPO_CFG3         = 0x25, ///< GPO4 config and drive
    // 0x26–0x28 reserved 
    TAA3040_P0_GPO_VAL          = 0x29, ///< GPIO/GPO output values 
    TAA3040_P0_GPIO_MON         = 0x2A, ///< GPIO input monitor 
    TAA3040_P0_GPI_CFG0         = 0x2B, ///< GPI1/2 config 
    TAA3040_P0_GPI_CFG1         = 0x2C, ///< GPI3/4 config
    // 0x2D–0x2E reserved 
    TAA3040_P0_GPI_MON          = 0x2F, ///< GPI1–4 input monitor 
    // 0x30–0x31 reserved 
    TAA3040_P0_INT_CFG          = 0x32, ///< Interrupt config 
    // 0x33 INT_MASK0 
    TAA3040_P0_INT_MASK0        = 0x33, ///< Interrupt mask 0 
    // 0x34–0x35 reserved 
    TAA3040_P0_INT_LTCH0        = 0x36, ///< Latched interrupt status /
    // 0x37–0x3A reserved 
    TAA3040_P0_BIAS_CFG         = 0x3B, ///< Bias and ADC config 
    TAA3040_P0_CH1_CFG0         = 0x3C, ///< Channel1 input config 
    TAA3040_P0_CH1_CFG1         = 0x3D, ///< Channel1 volume/gain 
    TAA3040_P0_CH1_CFG2         = 0x3E, ///< Channel1 phase cal 
    TAA3040_P0_CH1_CFG3         = 0x3F, ///< Channel1 IIR select 
    TAA3040_P0_CH1_CFG4         = 0x40, ///< Channel1 decimation 
    TAA3040_P0_CH2_CFG0         = 0x41, ///< Channel2 input config 
    TAA3040_P0_CH2_CFG1         = 0x42, ///< Channel2 volume/gain 
    TAA3040_P0_CH2_CFG2         = 0x43, ///< Channel2 phase cal 
    TAA3040_P0_CH2_CFG3         = 0x44, ///< Channel2 IIR select 
    TAA3040_P0_CH2_CFG4         = 0x45, ///< Channel2 decimation 
    TAA3040_P0_CH3_CFG0         = 0x46, ///< Channel3 input config 
    TAA3040_P0_CH3_CFG1         = 0x47, ///< Channel3 volume/gain 
    TAA3040_P0_CH3_CFG2         = 0x48, ///< Channel3 phase cal 
    TAA3040_P0_CH3_CFG3         = 0x49, ///< Channel3 IIR select 
    TAA3040_P0_CH3_CFG4         = 0x4A, ///< Channel3 decimation 
    TAA3040_P0_CH4_CFG0         = 0x4B, ///< Channel4 input config 
    TAA3040_P0_CH4_CFG1         = 0x4C, ///< Channel4 volume/gain 
    TAA3040_P0_CH4_CFG2         = 0x4D, ///< Channel4 phase cal 
    TAA3040_P0_CH4_CFG3         = 0x4E, ///< Channel4 IIR select 
    TAA3040_P0_CH4_CFG4         = 0x4F, ///< Channel4 decimation 
    // 0x50–0x51 reserved 
    TAA3040_P0_CH5_CFG2         = 0x52, ///< Channel5 PDM config 
    TAA3040_P0_CH5_CFG3         = 0x53, ///< Channel5 PDM gain 
    TAA3040_P0_CH5_CFG4         = 0x54, ///< Channel5 decimation 
    // 0x55–0x56 reserved */
    TAA3040_P0_CH6_CFG2         = 0x57, ///< Channel6 PDM config 
    TAA3040_P0_CH6_CFG3         = 0x58, ///< Channel6 PDM gain 
    TAA3040_P0_CH6_CFG4         = 0x59, ///< Channel6 decimation 
    // 0x5A reserved 
    TAA3040_P0_CH7_CFG2         = 0x5C, ///< Channel7 PDM config 
    TAA3040_P0_CH7_CFG3         = 0x5D, ///< Channel7 PDM gain 
    TAA3040_P0_CH7_CFG4         = 0x5E, ///< Channel7 decimation
    // 0x5B reserved
    TAA3040_P0_CH8_CFG2         = 0x61, ///< Channel8 PDM config 
    TAA3040_P0_CH8_CFG3         = 0x62, ///< Channel8 PDM gain 
    TAA3040_P0_CH8_CFG4         = 0x63, ///< Channel8 decimation 
    // 0x60 reserved 
    TAA3040_P0_DSP_CFG0         = 0x6B, ///< DSP processing config 
    TAA3040_P0_DSP_CFG1         = 0x6C, ///< DSP additional settings 
    // 0x6D–0x6F reserved 
    TAA3040_P0_AGC_CFG0         = 0x70, ///< AGC config 
    // 0x71–0x72 reserved 
    TAA3040_P0_IN_CH_EN         = 0x73, ///< Input channel enable 
    TAA3040_P0_ASI_OUT_CH_EN    = 0x74, ///< ASI output channel enable 
    TAA3040_P0_PWR_CFG          = 0x75, //< Power-up config 
    TAA3040_P0_DEV_STS0         = 0x76, ///< Channel power status 
    TAA3040_P0_DEV_STS1         = 0x77, ///< Device mode status 
    // 0x78–0x7D reserved
    TAA3040_P0_I2C_CKSUM        = 0x7E  ///< I2C checksum register 
} taa3040_page0_reg_t;
    

/**
 * @brief Page 2 Registers
 * 
 */
typedef enum {
    TAA3040_P2_PAGE_CFG        = 0x00,
    // Biquad 1 
    TAA3040_P2_BQ1_N0_BYT1     = 0x08,
    TAA3040_P2_BQ1_N0_BYT2     = 0x09,
    TAA3040_P2_BQ1_N0_BYT3     = 0x0A,
    TAA3040_P2_BQ1_N0_BYT4     = 0x0B,
    TAA3040_P2_BQ1_N1_BYT1     = 0x0C,
    TAA3040_P2_BQ1_N1_BYT2     = 0x0D,
    TAA3040_P2_BQ1_N1_BYT3     = 0x0E,
    TAA3040_P2_BQ1_N1_BYT4     = 0x0F,
    TAA3040_P2_BQ1_N2_BYT1     = 0x10,
    TAA3040_P2_BQ1_N2_BYT2     = 0x11,
    TAA3040_P2_BQ1_N2_BYT3     = 0x12,
    TAA3040_P2_BQ1_N2_BYT4     = 0x13,
    TAA3040_P2_BQ1_D1_BYT1     = 0x14,
    TAA3040_P2_BQ1_D1_BYT2     = 0x15,
    TAA3040_P2_BQ1_D1_BYT3     = 0x16,
    TAA3040_P2_BQ1_D1_BYT4     = 0x17,
    TAA3040_P2_BQ1_D2_BYT1     = 0x18,
    TAA3040_P2_BQ1_D2_BYT2     = 0x19,
    TAA3040_P2_BQ1_D2_BYT3     = 0x1A,
    TAA3040_P2_BQ1_D2_BYT4     = 0x1B,
    // Biquad 2 /
    TAA3040_P2_BQ2_N0_BYT1     = 0x1C,
    TAA3040_P2_BQ2_N0_BYT2     = 0x1D,
    TAA3040_P2_BQ2_N0_BYT3     = 0x1E,
    TAA3040_P2_BQ2_N0_BYT4     = 0x1F,
    TAA3040_P2_BQ2_N1_BYT1     = 0x20,
    TAA3040_P2_BQ2_N1_BYT2     = 0x21,
    TAA3040_P2_BQ2_N1_BYT3     = 0x22,
    TAA3040_P2_BQ2_N1_BYT4     = 0x23,
    TAA3040_P2_BQ2_N2_BYT1     = 0x24,
    TAA3040_P2_BQ2_N2_BYT2     = 0x25,
    TAA3040_P2_BQ2_N2_BYT3     = 0x26,
    TAA3040_P2_BQ2_N2_BYT4     = 0x27,
    TAA3040_P2_BQ2_D1_BYT1     = 0x28,
    TAA3040_P2_BQ2_D1_BYT2     = 0x29,
    TAA3040_P2_BQ2_D1_BYT3     = 0x2A,
    TAA3040_P2_BQ2_D1_BYT4     = 0x2B,
    TAA3040_P2_BQ2_D2_BYT1     = 0x2C,
    TAA3040_P2_BQ2_D2_BYT2     = 0x2D,
    TAA3040_P2_BQ2_D2_BYT3     = 0x2E,
    TAA3040_P2_BQ2_D2_BYT4     = 0x2F,
    // Biquad 3 /
    TAA3040_P2_BQ3_N0_BYT1     = 0x30,
    TAA3040_P2_BQ3_N0_BYT2     = 0x31,
    TAA3040_P2_BQ3_N0_BYT3     = 0x32,
    TAA3040_P2_BQ3_N0_BYT4     = 0x33,
    TAA3040_P2_BQ3_N1_BYT1     = 0x34,
    TAA3040_P2_BQ3_N1_BYT2     = 0x35,
    TAA3040_P2_BQ3_N1_BYT3     = 0x36,
    TAA3040_P2_BQ3_N1_BYT4     = 0x37,
    TAA3040_P2_BQ3_N2_BYT1     = 0x38,
    TAA3040_P2_BQ3_N2_BYT2     = 0x39,
    TAA3040_P2_BQ3_N2_BYT3     = 0x3A,
    TAA3040_P2_BQ3_N2_BYT4     = 0x3B,
    TAA3040_P2_BQ3_D1_BYT1     = 0x3C,
    TAA3040_P2_BQ3_D1_BYT2     = 0x3D,
    TAA3040_P2_BQ3_D1_BYT3     = 0x3E,
    TAA3040_P2_BQ3_D1_BYT4     = 0x3F,
    TAA3040_P2_BQ3_D2_BYT1     = 0x40,
    TAA3040_P2_BQ3_D2_BYT2     = 0x41,
    TAA3040_P2_BQ3_D2_BYT3     = 0x42,
    TAA3040_P2_BQ3_D2_BYT4     = 0x43,
    // Biquad 4 /
    TAA3040_P2_BQ4_N0_BYT1     = 0x44,
    TAA3040_P2_BQ4_N0_BYT2     = 0x45,
    TAA3040_P2_BQ4_N0_BYT3     = 0x46,
    TAA3040_P2_BQ4_N0_BYT4     = 0x47,
    TAA3040_P2_BQ4_N1_BYT1     = 0x48,
    TAA3040_P2_BQ4_N1_BYT2     = 0x49,
    TAA3040_P2_BQ4_N1_BYT3     = 0x4A,
    TAA3040_P2_BQ4_N1_BYT4     = 0x4B,
    TAA3040_P2_BQ4_N2_BYT1     = 0x4C,
    TAA3040_P2_BQ4_N2_BYT2     = 0x4D,
    TAA3040_P2_BQ4_N2_BYT3     = 0x4E,
    TAA3040_P2_BQ4_N2_BYT4     = 0x4F,
    TAA3040_P2_BQ4_D1_BYT1     = 0x50,
    TAA3040_P2_BQ4_D1_BYT2     = 0x51,
    TAA3040_P2_BQ4_D1_BYT3     = 0x52,
    TAA3040_P2_BQ4_D1_BYT4     = 0x53,
    TAA3040_P2_BQ4_D2_BYT1     = 0x54,
    TAA3040_P2_BQ4_D2_BYT2     = 0x55,
    TAA3040_P2_BQ4_D2_BYT3     = 0x56,
    TAA3040_P2_BQ4_D2_BYT4     = 0x57,
    // Biquad 5 /
    TAA3040_P2_BQ5_N0_BYT1     = 0x58,
    TAA3040_P2_BQ5_N0_BYT2     = 0x59,
    TAA3040_P2_BQ5_N0_BYT3     = 0x5A,
    TAA3040_P2_BQ5_N0_BYT4     = 0x5B,
    TAA3040_P2_BQ5_N1_BYT1     = 0x5C,
    TAA3040_P2_BQ5_N1_BYT2     = 0x5D,
    TAA3040_P2_BQ5_N1_BYT3     = 0x5E,
    TAA3040_P2_BQ5_N1_BYT4     = 0x5F,
    TAA3040_P2_BQ5_N2_BYT1     = 0x60,
    TAA3040_P2_BQ5_N2_BYT2     = 0x61,
    TAA3040_P2_BQ5_N2_BYT3     = 0x62,
    TAA3040_P2_BQ5_N2_BYT4     = 0x63,
    TAA3040_P2_BQ5_D1_BYT1     = 0x64,
    TAA3040_P2_BQ5_D1_BYT2     = 0x65,
    TAA3040_P2_BQ5_D1_BYT3     = 0x66,
    TAA3040_P2_BQ5_D1_BYT4     = 0x67,
    TAA3040_P2_BQ5_D2_BYT1     = 0x68,
    TAA3040_P2_BQ5_D2_BYT2     = 0x69,
    TAA3040_P2_BQ5_D2_BYT3     = 0x6A,
    TAA3040_P2_BQ5_D2_BYT4     = 0x6B,
    // Biquad 6 */
    TAA3040_P2_BQ6_N0_BYT1     = 0x6C,
    TAA3040_P2_BQ6_N0_BYT2     = 0x6D,
    TAA3040_P2_BQ6_N0_BYT3     = 0x6E,
    TAA3040_P2_BQ6_N0_BYT4     = 0x6F,
    TAA3040_P2_BQ6_N1_BYT1     = 0x70,
    TAA3040_P2_BQ6_N1_BYT2     = 0x71,
    TAA3040_P2_BQ6_N1_BYT3     = 0x72,
    TAA3040_P2_BQ6_N1_BYT4     = 0x73,
    TAA3040_P2_BQ6_N2_BYT1     = 0x74,
    TAA3040_P2_BQ6_N2_BYT2     = 0x75,
    TAA3040_P2_BQ6_N2_BYT3     = 0x76,
    TAA3040_P2_BQ6_N2_BYT4     = 0x77,
    TAA3040_P2_BQ6_D1_BYT1     = 0x78,
    TAA3040_P2_BQ6_D1_BYT2     = 0x79,
    TAA3040_P2_BQ6_D1_BYT3     = 0x7A,
    TAA3040_P2_BQ6_D1_BYT4     = 0x7B,
    TAA3040_P2_BQ6_D2_BYT1     = 0x7C,
    TAA3040_P2_BQ6_D2_BYT2     = 0x7D,
    TAA3040_P2_BQ6_D2_BYT3     = 0x7E,
    TAA3040_P2_BQ6_D2_BYT4     = 0x7F
} taa3040_page2_reg_t;
    

/**
 * @brief Registers in Page 3
 * 
 */
typedef enum {
    TAA3040_P3_PAGE_CFG        = 0x00,
    // Biquad 7 /
    TAA3040_P3_BQ7_N0_BYT1     = 0x08,
    TAA3040_P3_BQ7_N0_BYT2     = 0x09,
    TAA3040_P3_BQ7_N0_BYT3     = 0x0A,
    TAA3040_P3_BQ7_N0_BYT4     = 0x0B,
    TAA3040_P3_BQ7_N1_BYT1     = 0x0C,
    TAA3040_P3_BQ7_N1_BYT2     = 0x0D,
    TAA3040_P3_BQ7_N1_BYT3     = 0x0E,
    TAA3040_P3_BQ7_N1_BYT4     = 0x0F,
    TAA3040_P3_BQ7_N2_BYT1     = 0x10,
    TAA3040_P3_BQ7_N2_BYT2     = 0x11,
    TAA3040_P3_BQ7_N2_BYT3     = 0x12,
    TAA3040_P3_BQ7_N2_BYT4     = 0x13,
    TAA3040_P3_BQ7_D1_BYT1     = 0x14,
    TAA3040_P3_BQ7_D1_BYT2     = 0x15,
    TAA3040_P3_BQ7_D1_BYT3     = 0x16,
    TAA3040_P3_BQ7_D1_BYT4     = 0x17,
    TAA3040_P3_BQ7_D2_BYT1     = 0x18,
    TAA3040_P3_BQ7_D2_BYT2     = 0x19,
    TAA3040_P3_BQ7_D2_BYT3     = 0x1A,
    TAA3040_P3_BQ7_D2_BYT4     = 0x1B,
    // Biquad 8 /
    TAA3040_P3_BQ8_N0_BYT1     = 0x1C,
    TAA3040_P3_BQ8_N0_BYT2     = 0x1D,
    TAA3040_P3_BQ8_N0_BYT3     = 0x1E,
    TAA3040_P3_BQ8_N0_BYT4     = 0x1F,
    TAA3040_P3_BQ8_N1_BYT1     = 0x20,
    TAA3040_P3_BQ8_N1_BYT2     = 0x21,
    TAA3040_P3_BQ8_N1_BYT3     = 0x22,
    TAA3040_P3_BQ8_N1_BYT4     = 0x23,
    TAA3040_P3_BQ8_N2_BYT1     = 0x24,
    TAA3040_P3_BQ8_N2_BYT2     = 0x25,
    TAA3040_P3_BQ8_N2_BYT3     = 0x26,
    TAA3040_P3_BQ8_N2_BYT4     = 0x27,
    TAA3040_P3_BQ8_D1_BYT1     = 0x28,
    TAA3040_P3_BQ8_D1_BYT2     = 0x29,
    TAA3040_P3_BQ8_D1_BYT3     = 0x2A,
    TAA3040_P3_BQ8_D1_BYT4     = 0x2B,
    TAA3040_P3_BQ8_D2_BYT1     = 0x2C,
    TAA3040_P3_BQ8_D2_BYT2     = 0x2D,
    TAA3040_P3_BQ8_D2_BYT3     = 0x2E,
    TAA3040_P3_BQ8_D2_BYT4     = 0x2F,
    // Biquad 9 /
    TAA3040_P3_BQ9_N0_BYT1     = 0x30,
    TAA3040_P3_BQ9_N0_BYT2     = 0x31,
    TAA3040_P3_BQ9_N0_BYT3     = 0x32,
    TAA3040_P3_BQ9_N0_BYT4     = 0x33,
    TAA3040_P3_BQ9_N1_BYT1     = 0x34,
    TAA3040_P3_BQ9_N1_BYT2     = 0x35,
    TAA3040_P3_BQ9_N1_BYT3     = 0x36,
    TAA3040_P3_BQ9_N1_BYT4     = 0x37,
    TAA3040_P3_BQ9_N2_BYT1     = 0x38,
    TAA3040_P3_BQ9_N2_BYT2     = 0x39,
    TAA3040_P3_BQ9_N2_BYT3     = 0x3A,
    TAA3040_P3_BQ9_N2_BYT4     = 0x3B,
    TAA3040_P3_BQ9_D1_BYT1     = 0x3C,
    TAA3040_P3_BQ9_D1_BYT2     = 0x3D,
    TAA3040_P3_BQ9_D1_BYT3     = 0x3E,
    TAA3040_P3_BQ9_D1_BYT4     = 0x3F,
    TAA3040_P3_BQ9_D2_BYT1     = 0x40,
    TAA3040_P3_BQ9_D2_BYT2     = 0x41,
    TAA3040_P3_BQ9_D2_BYT3     = 0x42,
    TAA3040_P3_BQ9_D2_BYT4     = 0x43,
    // Biquad 10 /
    TAA3040_P3_BQ10_N0_BYT1    = 0x44,
    TAA3040_P3_BQ10_N0_BYT2    = 0x45,
    TAA3040_P3_BQ10_N0_BYT3    = 0x46,
    TAA3040_P3_BQ10_N0_BYT4    = 0x47,
    TAA3040_P3_BQ10_N1_BYT1    = 0x48,
    TAA3040_P3_BQ10_N1_BYT2    = 0x49,
    TAA3040_P3_BQ10_N1_BYT3    = 0x4A,
    TAA3040_P3_BQ10_N1_BYT4    = 0x4B,
    TAA3040_P3_BQ10_N2_BYT1    = 0x4C,
    TAA3040_P3_BQ10_N2_BYT2    = 0x4D,
    TAA3040_P3_BQ10_N2_BYT3    = 0x4E,
    TAA3040_P3_BQ10_N2_BYT4    = 0x4F,
    TAA3040_P3_BQ10_D1_BYT1    = 0x50,
    TAA3040_P3_BQ10_D1_BYT2    = 0x51,
    TAA3040_P3_BQ10_D1_Byt3    = 0x52,
    TAA3040_P3_BQ10_D1_Byt4    = 0x53,
    TAA3040_P3_BQ10_D2_BYT1    = 0x54,
    TAA3040_P3_BQ10_D2_BYT2    = 0x55,
    TAA3040_P3_BQ10_D2_BYT3    = 0x56,
    TAA3040_P3_BQ10_D2_BYT4    = 0x57,
    // Biquad 11 /
    TAA3040_P3_BQ11_N0_BYT1    = 0x58,
    TAA3040_P3_BQ11_N0_BYT2    = 0x59,
    TAA3040_P3_BQ11_N0_BYT3    = 0x5A,
    TAA3040_P3_BQ11_N0_BYT4    = 0x5B,
    TAA3040_P3_BQ11_N1_BYT1    = 0x5C,
    TAA3040_P3_BQ11_N1_BYT2    = 0x5D,
    TAA3040_P3_BQ11_N1_BYT3    = 0x5E,
    TAA3040_P3_BQ11_N1_BYT4    = 0x5F,
    TAA3040_P3_BQ11_N2_BYT1    = 0x60,
    TAA3040_P3_BQ11_N2_BYT2    = 0x61,
    TAA3040_P3_BQ11_N2_BYT3    = 0x62,
    TAA3040_P3_BQ11_N2_BYT4    = 0x63,
    TAA3040_P3_BQ11_D1_BYT1    = 0x64,
    TAA3040_P3_BQ11_D1_BYT2    = 0x65,
    TAA3040_P3_BQ11_D1_BYT3    = 0x66,
    TAA3040_P3_BQ11_D1_BYT4    = 0x67,
    TAA3040_P3_BQ11_D2_BYT1    = 0x68,
    TAA3040_P3_BQ11_D2_BYT2    = 0x69,
    TAA3040_P3_BQ11_D2_BYT3    = 0x6A,
    TAA3040_P3_BQ11_D2_BYT4    = 0x6B,
    // Biquad 12 
    TAA3040_P3_BQ12_N0_BYT1    = 0x6C,
    TAA3040_P3_BQ12_N0_BYT2    = 0x6D,
    TAA3040_P3_BQ12_N0_BYT3    = 0x6E,
    TAA3040_P3_BQ12_N0_BYT4    = 0x6F,
    TAA3040_P3_BQ12_N1_BYT1    = 0x70,
    TAA3040_P3_BQ12_N1_BYT2    = 0x71,
    TAA3040_P3_BQ12_N1_BYT3    = 0x72,
    TAA3040_P3_BQ12_N1_BYT4    = 0x73,
    TAA3040_P3_BQ12_N2_BYT1    = 0x74,
    TAA3040_P3_BQ12_N2_BYT2    = 0x75,
    TAA3040_P3_BQ12_N2_BYT3    = 0x76,
    TAA3040_P3_BQ12_N2_BYT4    = 0x77,
    TAA3040_P3_BQ12_D1_BYT1    = 0x78,
    TAA3040_P3_BQ12_D1_BYT2    = 0x79,
    TAA3040_P3_BQ12_D1_BYT3    = 0x7A,
    TAA3040_P3_BQ12_D1_BYT4    = 0x7B,
    TAA3040_P3_BQ12_D2_BYT1    = 0x7C,
    TAA3040_P3_BQ12_D2_BYT2    = 0x7D,
    TAA3040_P3_BQ12_D2_BYT3    = 0x7E,
    TAA3040_P3_BQ12_D2_BYT4    = 0x7F
} taa3040_page3_reg_t;
    

typedef enum {
    TAA3040_P4_PAGE_CFG        = 0x00,
    // Mixer 1 coefficients /
    TAA3040_P4_MIX1_CH1_BYT1   = 0x08,
    TAA3040_P4_MIX1_CH1_BYT2   = 0x09,
    TAA3040_P4_MIX1_CH1_BYT3   = 0x0A,
    TAA3040_P4_MIX1_CH1_BYT4   = 0x0B,
    TAA3040_P4_MIX1_CH2_BYT1   = 0x0C,
    TAA3040_P4_MIX1_CH2_BYT2   = 0x0D,
    TAA3040_P4_MIX1_CH2_BYT3   = 0x0E,
    TAA3040_P4_MIX1_CH2_BYT4   = 0x0F,
    TAA3040_P4_MIX1_CH3_BYT1   = 0x10,
    TAA3040_P4_MIX1_CH3_BYT2   = 0x11,
    TAA3040_P4_MIX1_CH3_BYT3   = 0x12,
    TAA3040_P4_MIX1_CH3_BYT4   = 0x13,
    TAA3040_P4_MIX1_CH4_BYT1   = 0x14,
    TAA3040_P4_MIX1_CH4_BYT2   = 0x15,
    TAA3040_P4_MIX1_CH4_BYT3   = 0x16,
    TAA3040_P4_MIX1_CH4_BYT4   = 0x17,
    // Mixer 2 /
    TAA3040_P4_MIX2_CH1_BYT1   = 0x18,
    TAA3040_P4_MIX2_CH1_BYT2   = 0x19,
    TAA3040_P4_MIX2_CH1_BYT3   = 0x1A,
    TAA3040_P4_MIX2_CH1_BYT4   = 0x1B,
    TAA3040_P4_MIX2_CH2_BYT1   = 0x1C,
    TAA3040_P4_MIX2_CH2_BYT2   = 0x1D,
    TAA3040_P4_MIX2_CH2_BYT3   = 0x1E,
    TAA3040_P4_MIX2_CH2_BYT4   = 0x1F,
    TAA3040_P4_MIX2_CH3_BYT1   = 0x20,
    TAA3040_P4_MIX2_CH3_BYT2   = 0x21,
    TAA3040_P4_MIX2_CH3_BYT3   = 0x22,
    TAA3040_P4_MIX2_CH3_BYT4   = 0x23,
    TAA3040_P4_MIX2_CH4_BYT1   = 0x24,
    TAA3040_P4_MIX2_CH4_BYT2   = 0x25,
    TAA3040_P4_MIX2_CH4_BYT3   = 0x26,
    TAA3040_P4_MIX2_CH4_BYT4   = 0x27,
    // Mixer 3 /
    TAA3040_P4_MIX3_CH1_BYT1   = 0x28,
    TAA3040_P4_MIX3_CH1_BYT2   = 0x29,
    TAA3040_P4_MIX3_CH1_BYT3   = 0x2A,
    TAA3040_P4_MIX3_CH1_BYT4   = 0x2B,
    TAA3040_P4_MIX3_CH2_BYT1   = 0x2C,
    TAA3040_P4_MIX3_CH2_BYT2   = 0x2D,
    TAA3040_P4_MIX3_CH2_BYT3   = 0x2E,
    TAA3040_P4_MIX3_CH2_BYT4   = 0x2F,
    TAA3040_P4_MIX3_CH3_BYT1   = 0x30,
    TAA3040_P4_MIX3_CH3_BYT2   = 0x31,
    TAA3040_P4_MIX3_CH3_BYT3   = 0x32,
    TAA3040_P4_MIX3_CH3_BYT4   = 0x33,
    TAA3040_P4_MIX3_CH4_BYT1   = 0x34,
    TAA3040_P4_MIX3_CH4_BYT2   = 0x35,
    TAA3040_P4_MIX3_CH4_BYT3   = 0x36,
    TAA3040_P4_MIX3_CH4_BYT4   = 0x37,
    // Mixer 4 fills from 0x38 /
    TAA3040_P4_MIX4_CH1_BYT1   = 0x38,
    TAA3040_P4_MIX4_CH1_BYT2   = 0x39,
    TAA3040_P4_MIX4_CH1_BYT3   = 0x3A,
    TAA3040_P4_MIX4_CH1_BYT4   = 0x3B,
    TAA3040_P4_MIX4_CH2_BYT1   = 0x3C,
    TAA3040_P4_MIX4_CH2_BYT2   = 0x3D,
    TAA3040_P4_MIX4_CH2_BYT3   = 0x3E,
    TAA3040_P4_MIX4_CH2_BYT4   = 0x3F,
    TAA3040_P4_MIX4_CH3_BYT1   = 0x40,
    TAA3040_P4_MIX4_CH3_BYT2   = 0x41,
    TAA3040_P4_MIX4_CH3_BYT3   = 0x42,
    TAA3040_P4_MIX4_CH3_BYT4   = 0x43,
    TAA3040_P4_MIX4_CH4_BYT1   = 0x44,
    TAA3040_P4_MIX4_CH4_BYT2   = 0x45,
    TAA3040_P4_MIX4_CH4_BYT3   = 0x46,
    TAA3040_P4_MIX4_CH4_BYT4   = 0x47, 
    // First-order IIR
    TAA3040_P4_IIR_N0_BYT1     = 0x48,
    TAA3040_P4_IIR_N0_BYT2     = 0x49,
    TAA3040_P4_IIR_N0_BYT3     = 0x4A,
    TAA3040_P4_IIR_N0_BYT4     = 0x4B,
    TAA3040_P4_IIR_N1_BYT1     = 0x4C,
    TAA3040_P4_IIR_N1_BYT2     = 0x4D,
    TAA3040_P4_IIR_N1_BYT3     = 0x4E,
    TAA3040_P4_IIR_N1_BYT4     = 0x4F,
    TAA3040_P4_IIR_D1_BYT1     = 0x50,
    TAA3040_P4_IIR_D1_BYT2     = 0x51,
    TAA3040_P4_IIR_D1_BYT3     = 0x52,
    TAA3040_P4_IIR_D1_BYT4     = 0x53
} taa3040_page4_reg_t;

typedef struct {
    
    uint8_t page: 2;
    union {
        taa3040_page0_reg_t page0;
        taa3040_page2_reg_t page2;
        taa3040_page3_reg_t page3;
        taa3040_page4_reg_t page4;
    };

} taa3040_reg_t;
    
#endif /* TAA3040_REGS_H */