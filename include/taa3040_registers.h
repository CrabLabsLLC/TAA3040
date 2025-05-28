/**
 * @file taa3040_registers.h'
 * @author Orion Serup (orion@crablabs.io)
 * @brief The register and bitmask definitions for the TAA3040 driver
 * @version 0.1
 * @date 2025-04-29
 * 
 * @license MIT
 * @copyright Copyright (c) Crab Labs LLC 2025
 * 
 */

#ifndef TAA3040_REGISTERS_H
#define TAA3040_REGISTERS_H

#include <stdint.h>

/* === Core Registers (Page 0) === */
#define TAA3040_REG_PAGE_SELECT                     0x00 ///< Page selection register
#define TAA3040_REG_SW_RESET                        0x01 ///< Software reset
#define TAA3040_REG_SLEEP_CFG                       0x02 ///< Sleep configuration
#define TAA3040_REG_SHUTDOWN_CFG                    0x05 ///< Shutdown configuration

/* === ASI Interface Registers (Page 0) === */
#define TAA3040_REG_ASI_CONFIG0                     0x07 ///< ASI/I2S/TDM basic configuration
#define TAA3040_REG_ASI_CONFIG1                     0x08
#define TAA3040_REG_ASI_CONFIG2                     0x09

#define TAA3040_REG_ASI_CHANNEL_BASE                0x0B ///< Per channel config, mirrored 

/* === Master Config Registers (Page 0)* === */
#define TAA3040_REG_MASTER_CONFIG0                  0x13
#define TAA3040_REG_MASTER_CONFIG1                  0x14

/* === ASI Status Register (Page 0) === */
#define TAA3040_REG_ASI_STATUS                      0x15

/* === Clock Configuration (Page 0) === */
#define TAA3040_REG_CLOCK_SOURCE                    0x16

/* === PDM Configuration  (Page 0) === */
#define TAA3040_REG_PDMCLK_CONFIG                   0x1F
#define TAA3040_REG_PDMIN_CONFIG                    0x20

/* === GPIO and Interrupt Registers (Page 0) === */
#define TAA3040_REG_GPIO1_CONFIG                    0x21
#define TAA3040_REG_GPO_CONFIG_BASE                 0x22  ///< GPO configuration start
#define TAA3040_REG_GPO_VALUE                       0x29  ///< Output states of GPO
#define TAA3040_REG_GPIO1_MONITOR                   0x2A  ///< Reads values at GPI Pin
#define TAA3040_REG_GPI_CONFIG_BASE                 0x2B  ///< GPI configuration start
#define TAA3040_REG_GPI_MONITOR                     0x2F  ///< Reads GPI Pins

#define TAA3040_REG_INTERRUPT_CONFIG                0x32  ///< Interrupt config
#define TAA3040_REG_INTERRUPT_MASK                  0x33  ///< Which events trigger interrupts
#define TAA3040_REG_INTERRUPT_LATCH                 0x34  ///< Details which interrupts occurred

/* === Bias Configuration (Page 0) === */
#define TAA3040_REG_BIAS_CONFIG                     0x3B

/* === Channel Specific Registers (Page 0) === */
#define TAA3040_REG_CHANNEL_CONFIG_BASE             0x3C ///< AGC enable
#define TAA3040_REG_CHANNEL_GAIN_BASE               0x3D /// Gain
#define TAA3040_REG_CHANNEL_VOLUME_BASE             0x3E ///< Digital volume control
#define TAA3040_REG_CHANNEL_GAIN_CAL_BASE           0x3F    
#define TAA3040_REG_CHANNEL_PHASE_CAL_BASE          0x40

#define TAA3040_CHANNEL_REGISTER_ENTRIES            5

/* === DSP Configuration (Page 0) === */
#define TAA3040_REG_DSP_CONFIG0                     0x6B  ///< Filtering 
#define TAA3040_REG_DSP_CONFIG1                     0x6C

/* === AGC Config (Page 0) === */
#define TAA3040_REG_AGC_CONFIG                      0x70

/* === Channel Enable (Page 0) === */
#define TAA3040_REG_IN_CHANNEL_EN                   0x73  ///< Input channel enabling 
#define TAA3040_REG_ASI_OUT_CHANNEL_EN              0x74  ///< ASI channel out enabling

/* === Power Configuration (Page 0) === */
#define TAA3040_REG_POWER_CONFIG                    0x75

/* === Status Registers (Page 0) === */
#define TAA3040_REG_STATUS0                         0x76
#define TAA3040_REG_STATUS1                         0x77

/** === I2C Checksum (Page 0) === */
#define TAA3040_REG_I2C_CHECKSUM                    0x7E

/* === Page 2: Biquad Filter Set 1 === */
#define TAA3040_PAGE_BIQUAD_FILTER_1                0x02
#define TAA3040_REG_BIQUAD_COEFF_BASE               0x00

/* === Page 3: Biquad Filter Set 2 === */
#define TAA3040_PAGE_BIQUAD_FILTER_2                0x03

#define TAA3040_BIQUAD_COEFF_WORDS_PER_SECTION      (5) ///< b0, b1, b2, a1, a2
#define TAA3040_BIQUAD_CHANNEL_STRIDE               (5)

/* === Page 4: Mixer Matrix === */
#define TAA3040_PAGE_MIXER_CONTROL                  0x04
#define TAA3040_REG_MIXER_MATRIX_BASE               0x00

/* === Mixer Matrix Helper Constants === */
#define TAA3040_MIXER_MATRIX_ENTRIES_PER_CHANNEL    (8)
#define TAA3040_MIXER_COEFF_WORDS_PER_ENTRY         (1)
#define TAA3040_MIXER_CHANNEL_STRIDE                (8)

/* === Page 4: First Order IIR Filter === */
#define TAA3040_PAGE_IIR_COEFF                      0x04
#define TAA3040_REG_IIR_COEFF_START                 0x48
#define TAA3040_REG_IIR_N0                          0x48 ///< n0 coefficient
#define TAA3040_REG_IIR_N1                          0x4C ///< n1 coefficient
#define TAA3040_REG_IIR_D1                          0x50 ///< d1 coefficient

#define TAA3040_IIR_COEFF_WORDS_PER_SECTION         (3)

/* === Bit Masks and Field Definitions === */

/* --- SW_RESET (0x01) --- */
#define TAA3040_SW_RESET_MASK                       (0x01)

/* --- Sleep Config (0x02) --- */
#define TAA3040_SLEEP_DISABLE_SHIFT                 (0x0)
#define TAA3040_SLEEP_DISABLE_MASK                  (0x01 << TAA3040_SLEEP_DISABLE_SHIFT)
#define TAA3040_I2C_BROADCAST_SHIFT                 (0x2)
#define TAA3040_I2C_BROADCAST_MASK                  (0x01 << TAA3040_SLEEP_ENABLE_SHIFT)
#define TAA3040_VREF_QCHRG_SHIFT                    (0x3)
#define TAA3040_VREF_QCHRG_MASK                     (0x3 << TAA3040_VREF_QCHRG_SHIFT)
#define TAA3040_AREG_SELECT_SHIFT                   (0x7)
#define TAA3040_AREG_SELECT_MASK                    (0x01 << TAA3040_AREG_SELECT_SHIFT)

/* -- Shutdown Config (0x05) --- */
#define TAA3040_DREG_KA_TIME_SHIFT                  (0)
#define TAA3040_DREG_KA_TIME_MASK                   (0x3 << TAA3040_DREG_KA_TIME_SHIFT)
#define TAA3040_SHDNZ_CFG_SHIFT                     (2)
#define TAA3040_SHDNZ_CFG_MASK                      (0x3 << TAA3040_SHDNZ_CFG_SHIFT)
#define TAA3040_INCAP_QCHG_SHIFT                    (4)
#define TAA3040_INCAP_QCHG_MASK                     (0x3 << TAA3040_INCAP_QCHG_SHIFT)

/* --- ASI Config (0x7) --- */
#define TAA3040_ASI_FORMAT_SHIFT                    (6)
#define TAA3040_ASI_FORMAT_MASK                     (0x03 << TAA3040_ASI_FORMAT_SHIFT) ///< Bits 1:0
#define TAA3040_ASI_WORD_LENGTH_SHIFT               (4)
#define TAA3040_ASI_WORD_LENGTH_MASK                (0x3 << TAA3040_ASI_WORD_LENGTH_SHIFT) ///< Bits 3:2
#define TAA3040_FSYNC_POLARITY_SHIFT                (3)
#define TAA3040_FSYNC_POLARITY_MASK                 (0x01 << TAA3040_FSYNC_POLARITY_SHIFT)
#define TAA3040_BCLK_POLARITY_SHIFT                 (2)
#define TAA3040_BLCK_POLARITY_MASK                  (0x01 << TAA3040_BCLK_POLARITY_SHIFT)
#define TAA3040_TRANSMIT_EDGE_SHIFT                 (1)
#define TAA3040_TRANSMIT_EDGE_MASK                  (0x1 << TAA3040_TRANSMIT_EDGE_SHIFT)
#define TAA3040_TRANSMIT_FILL_SHIFT                 (0)
#define TAA3040_TRANSMIT_FILL_MASK                  (0x1 << TAA3040_TRANSMIT_FILL_SHIFT)

/* --- ASI Config 1 (0x8) --- */
#define TAA3040_TRANSMIT_LSB_SHIFT                  (0x7)
#define TAA3040_TRANSMIT_LSB_MASK                   (0x1 << TAA3040_TRANSMIT_LSB_SHIFT)
#define TAA3040_TRANSMIT_KEEPER_SHIFT               (0x5)
#define TAA3040_TRANSMIT_KEEPER_MASK                (0x3 << TAA3040_TRANSMIT_KEEPER_SHIFT)
#define TAA3040_TRANSMIT_OFFSET_SHIFT               (0)
#define TAA3040_TRANSMIT_OFFSET_MASK                (0xF << TAA3040_TRANSMIT_OFFSET_SHIFT)

/* --- ASI Config 2 (0x9) --- */
#define TAA3040_ASI_DAISY_SHIFT                     (7)
#define TAA3040_ASI_DAISY_MASK                      (0x1 << TAA3040_ASI_DAISY_SHIFT)
#define TAA3040_ASI_ERROR_SHIFT                     (5)
#define TAA3040_ASI_ERROR_MASK                      (0x1 << TAA3040_ASI_ERROR_SHIFT)
#define TAA3040_ASI_ERROR_RECOVERY_SHIFT            (4)
#define TAA3040_ASI_ERROR_RECOVERY_MASK             (0x1 << TAA3040_ASI_ERROR_RECOVERY_SHIFT)

/* --- ASI Channels  --- */
#define TAA3040_ASI_CHANNEL_SLOT_SHIFT              (0)
#define TAA3040_ASI_CHANNEL_SLOT_MASK               (0x3F << TAA3040_ASI_CHANNEL_SLOT_SHIFT)
#define TAA3040_ASI_CHANNEL_OUTPUT_SHIFT            (6)
#define TAA3040_ASI_CHANNEL_OUTPUT_MASK             (0x1 << TAA3040_ASI_CHANNEL_OUTPUT_SHIFT)

/* --- Master Config (0x13-14) --- */
#define TAA3040_MCLK_FREQ_SELECT_SHIFT              (0)
#define TAA3040_MCLK_FREQ_SELECT_MASK               (0x7 << TAA3040_MCLK_FREQ_SELECT_SHIFT)
#define TAA3040_SAMPLE_RATE_SHIFT                   (3)
#define TAA3040_SAMPLE_RATE_MASK                    (0x1 << TAA3040_SAMPLE_RATE_SHIFT)
#define TAA3040_BCLK_FSYNC_GATE_SHIFT               (4)
#define TAA3040_BCLK_FSYNC_GATE_MASK                (0x1 << TAA3040_BCLK_FSYNC_GATE_SHIFT)
#define TAA3040_AUTO_MODE_PLL_SHIFT                 (5)
#define TAA3040_AUTO_MODE_PLL_MASK                  (0x1 << TAA3040_AUTO_MODE_PLL_SHIFT)
#define TAA3040_AUTO_CLOCK_CONFIG_SHIFT             (6)
#define TAA3040_AUTO_CLOCK_CONFIG_MASK              (0x1 << TAA3040_AUTO_CLOCK_CONFIG_SHIFT)
#define TAA3040_MASTER_SLAVE_CONFIG_SHIFT           (7)
#define TAA3040_MASTER_SLAVE_CONFIG_MASK            (0x1 << TAA3040_MASTER_SLAVE_CONFIG_SHIFT)

#define TAA3040_FSYNC_BCLK_RATIO_SHIFT              (0)
#define TAA3040_FSYNC_BCLK_RATIO_MASK               (0xF << TAA3040_FSYNC_BCLK_RATIO_SHIFT)
#define TAA3040_FSYNC_RATE_SHIFT                    (4)
#define TAA3040_FSYNC_RATE_MASK                     (0xF << TAA3040_FSYNC_RATE_SHIFT)

/* --- ASI Status (0x15) --- */
#define TAA3040_FSYNC_RATIO_STATUS_SHIFT            (4)
#define TAA3040_FSYNC_RATIO_STATUS_MASK             (0xF << TAA3040_FSYNC_RATIO_STATUS_SHIFT)
#define TAA3040_FSYNC_RATE_STATUS_SHIFT             (0)
#define TAA3040_FSYNC_RATE_STATUS_MASK              (0xF << TAA3040_FSYNC_RATE_SHIFT)

/* --- Clock Source (0x16) --- */
#define TAA3040_MCLK_RATIO_SEL_SHIFT                (3)
#define TAA3040_MCLK_RATIO_SEL_MASK                 (0x7 <<  TAA3040_MCLK_RATIO_SEL_SHIFT)
#define TAA3040_MCLK_FREQ_SEL_SHIFT                 (6)
#define TAA3040_MCLK_FREQ_SEL_MASK                  (0x1 << TAA3040_MCLK_FREQ_SELECT_SHIFT)
#define TAA3040_SLAVE_CLOCK_SOURCE_SHIFT            (7)
#define TAA3040_SLAVE_CLOCK_SOURCE_MASK             (0x1 << TAA3040_SLAVE_CLOCK_SOURCE_SHIFT)

/* --- PDM Clock Config (0x1F) --- */
#define TAA3040_PDMCLK_DIVIDER_SHIFT                (0)
#define TAA3040_PDMCLK_DIVIDER_MASK                 (0x3 << TAA3040_PDMCLK_DIVIDER_SHIFT)

/* --- PDM Config (0x20) --- */
#define TAA3040_PDMDIN1_EDGE_SHIFT                  (7)
#define TAA3040_PDMDIN1_EDGE_MASK                   (0x1 << TAA3040_PDMDIN1_EDGE_SHIFT)
#define TAA3040_PDMDIN2_EDGE_SHIFT                  (6)
#define TAA3040_PDMDIN2_EDGE_MASK                   (0x1 << TAA3040_PDMDIN2_EDGE_SHIFT)
#define TAA3040_PDMDIN3_EDGE_SHIFT                  (5)
#define TAA3040_PDMDIN3_EDGE_MASK                   (0x1 << TAA3040_PDMDIN3_EDGE_SHIFT)
#define TAA3040_PDMDIN4_EDGE_SHIFT                  (4)
#define TAA3040_PDMDIN4_EDGE_MASK                   (0x1 << TAA3040_PDMDIN4_EDGE_SHIFT)

/* --- GPIO1 Config (0x21) --- */
#define TAA3040_GPIO_CONFIG_SHIFT                   (4)
#define TAA3040_GPIO_CONFIG_MASK                    (0xF << TAA3040_GPIO_CONFIG_SHIFT) ///< Bits 7:4
#define TAA3040_GPIO_DRIVE_MODE_SHIFT               (0)
#define TAA3040_GPIO_DRIVE_MODE_MASK                (0x7 << TAA3040_GPIO_DRIVE_MODE_SHIFT) ///< Bits 0:2

/* --- GPO Config (0x23-0x25) --- */
#define TAA3040_GPO_CONFIG_SHIFT                    (4)
#define TAA3040_GPO_CONFIG_MASK                     (0x0F << TAA3040_GPO_CONFIG_SHIFT) ///< Bits 3:0
#define TAA3040_GPO_DRIVE_MODE_SHIFT                (0)
#define TAA3040_GPO_DRIVE_MODE_MASK                 (0x7 << TAA3040_GPO_DRIVE_MODE_SHIFT) ///< Bits 7:4

/* --- GPO Value Register (0x29) --- */
#define TAA3040_GPO1_VALUE_SHIFT                    (0x7)
#define TAA3040_GPO1_VALUE_MASK                     (0x1 << TAA3040_GPO1_VALUE_SHIFT)
#define TAA3040_GPO2_VALUE_SHIFT                    (0x6)
#define TAA3040_GPO2_VALUE_MASK                     (0x1 << TAA3040_GPO2_VALUE_SHIFT)
#define TAA3040_GPO3_VALUE_SHIFT                    (0x5)
#define TAA3040_GPO3_VALUE_MASK                     (0x1 << TAA3040_GPO3_VALUE_SHIFT)
#define TAA3040_GPO4_VALUE_SHIFT                    (0x4)
#define TAA3040_GPO4_VALUE_MASK                     (0x1 << TAA3040_GPO4_VALUE_SHIFT)

/* --- GPIO Monitoring (0x2A) --- */
#define TAA3040_GPIO1_MON_SHIFT                     (7)
#define TAA3040_GPIO1_MON_MASK                      (0x1 << TAA3040_GPIO1_MON_SHIFT)

/* --- GPI Config 1 (0x2B) --- */
#define TAA3040_GPI1_CONFIG_SHIFT                   (0x4)
#define TAA3040_GPI1_CONFIG_MASK                    (0x7 << TAA3040_GPI1_CONFIG_SHIFT)
#define TAA3040_GPI2_CONFIG_SHIFT                   (0x0)
#define TAA3040_GPI2_CONFIG_MASK                    (0x7 << TAA3040_GPI2_CONFIG_SHIFT)

/* --- GPI Config 2 (0x2C) --- */
#define TAA3040_GPI3_CONFIG_SHIFT                   (4)
#define TAA3040_GPI3_CONFIG_MASK                    (0x7 << TAA3040_GPI3_CONFIG_SHIFT)
#define TAA3040_GPI4_CONFIG_SHIFT                   (0)
#define TAA3040_GPI4_CONFIG_MASK                    (0x7 << TAA3040_GPI4_CONFIG_SHIFT)

/* --- GPI Monitor Register (0x2F) --- */
#define TAA3040_GPI1_MONITOR_SHIFT                  (0x7)
#define TAA3040_GPI1_MONITOR_MASK                   (0x1 << TAA3040_GPI1_MONITOR_SHIFT)
#define TAA3040_GPI2_MONITOR_SHIFT                  (0x6)
#define TAA3040_GPI2_MONITOR_MASK                   (0x1 << TAA3040_GPI2_MONITOR_SHIFT)
#define TAA3040_GPI3_MONITOR_SHIFT                  (0x5)
#define TAA3040_GPI3_MONITOR_MASK                   (0x1 << TAA3040_GPI3_MONITOR_SHIFT)
#define TAA3040_GPI4_MONITOR_SHIFT                  (0x4)
#define TAA3040_GPI4_MONITOR_MASK                   (0x1 << TAA3040_GPI4_MONITOR_SHIFT)

/* --- Interrupt Config (0x32) --- */
#define TAA3040_INTERRUPT_POLARITY_SHIFT            (7)
#define TAA3040_INTERRUPT_POLARITY_MASK             (0x1 << TAA3040_INTERRUPT_POLARITY_SHIFT)
#define TAA3040_INTERRUPT_EVENT_SHIFT               (5)
#define TAA3040_INTERRUPT_EVENT_MASK                (0x7 << TAA3040_INTERRUPT_EVENT_SHIFT)
#define TAA3040_INTERRUPT_LATCH_SHIFT               (0x2)
#define TAA3040_INTERRUPT_LATCH_MASK                (0x1 << TAA3040_INTERRUPT_LATCH_SHIFT)

/* --- Interrupt Mask (0x33) --- */
#define TAA3040_INTERRUPT_ASI_ERROR_SHIFT           (7)
#define TAA3040_INTERRUPT_ASI_ERROR_MASK            (0x1 << TAA3040_INTERRUPT_ASI_ERROR_SHIFT)
#define TAA3040_INTERRUPT_PLL_ERROR_SHIFT           (6)
#define TAA3040_INTERRUPT_PLL_ERROR_MASK            (0x1 << TAA3040_INTERRUPT_PLL_ERROR_SHIFT)

/* --- Interrupt Latch (0x36) --- */


/* --- Bias Configuration (0x3B) --- */
#define TAA3040_MIC_BIAS_SHIFT                      (4)
#define TAA3040_MIC_BIAS_MASK                       (0x7 << TAA3040_MIC_BIAS_SHIFT)
#define TAA3040_ADC_SCALE_SHIFT                     (0)
#define TAA3040_ADC_SCALE_MASK                      (0x3 << TAA3040_ADC_SCALE_SHIFT)

/* --- Channel Config (0x3C-0x63) --- */
// Config 0
#define TAA3040_CHANNEL_AGC_EN_SHIFT                (0x0)
#define TAA3040_CHANNEL_AGC_EN_MASK                 (0x1 << TAA3040_CHANNEL_AGC_EN_SHIFT)
#define TAA3040_CHANNEL_IMPEDANCE_SHIFT             (0x2)
#define TAA3040_CHANNEL_IMPEDANCE_MASK              (0x3 << TAA3040_CHANNEL_IMPEDANCE_SHIFT)
#define TAA3040_CHANNEL_COUPLING_SHIFT              (4)
#define TAA3040_CHANNEL_COUPLING_MASK               (0x1 << TAA3040_CHANNEL_COUPLING_SHIFT)
#define TAA3040_CHANNEL_SOURCE_SHIFT                (5)
#define TAA3040_CHANNEL_SOURCE_MASK                 (0x3 << TAA3040_CHANNEL_SOURCE_SHIFT)
#define TAA3040_CHANNEL_INPUT_TYPE_SHIFT            (7)
#define TAA3040_CHANNEL_INPUT_TYPE_MASK             (0x1 << TAA3040_CHANNEL_INPUT_TYPE_SHIFT)

// Config 1
#define TAA3040_CHANNEL_GAIN_SHIFT                  (0x2)
#define TAA3040_CHANNEL_GAIN_MASK                   (0x3F << TAA3040_CHANNEL_GAIN_SHIFT)

// Config 2
#define TAA3040_CHANNEL_VOLUME_SHIFT                (0x0)
#define TAA3040_CHANNEL_VOLUME_MASK                 (0xFF << TAA3040_CHANNEL_VOLUME_SHIFT)

// Config 3
#define TAA3040_CHANNEL_GAIN_CAL_SHIFT              (0x4)
#define TAA3040_CHANNEL_GAIN_CAL_MASK               (0xF << TAA3040_CHANNEL_GAIN_CAL_SHIFT)

// Config 4
#define TAA3040_CHANNEL_PHASE_CAL_SHIFT             (0x0)
#define TAA3040_CHANNEL_PHASE_CAL_MASK              (0xFF << TAA3040_CHANNEL_PHASE_CAL_SHIFT) 

/* --- DSP Config (0x6B) --- */
#define TAA3040_DECIMATION_FILTER_SHIFT             (0x4)
#define TAA3040_DECIMATION_FILTER_MASK              (0x3 << TAA3040_DECIMATION_FILTER_SHIFT)
#define TAA3040_CHANNEL_SUM_MODE_SHIFT              (2)
#define TAA3040_CHANNEL_SUM_MODE_MASK               (0x3 << TAA3040_CHANNEL_SUM_MODE_SHIFT)
#define TAA3040_HIGH_PASS_FILTER_SHIFT              (0)
#define TAA3040_HIGH_PASS_FILTER_MASK               (0x3 << TAA3040_HIGH_PASS_FILTER_SHIFT)

/* --- DSP Config (0x6C) --- */
#define TAA3040_VOLUME_GANGED_SHIFT                 (7)
#define TAA3040_VOLUME_GANGED_MASK                  (0x1 << TAA3040_VOLUME_GANGED_SHIFT)
#define TAA3040_BIQUAD_COUNT_SHIFT                  (5)
#define TAA3040_BIQUAD_COUNT_MASK                   (0x3 << TAA3040_BIQUAD_COUNT_SHIFT)
#define TAA3040_SOFT_STEP_SHIFT                     (4)
#define TAA3040_SOFT_STEP_MASK                      (0x1 << TAA3040_SOFT_STEP_SHIFT)
#define TAA3040_AGC_SELECT_SHIFT                    (3)
#define TAA3040_AGC_SELECT_MASK                     (0x1 << TAA3040_AGC_SELECT_SHIFT)

/* --- AGC Config (0xE7) --- */
#define TAA3040_AGC_LEVEL_SHIFT                     (4)
#define TAA3040_AGC_LEVEL_MASK                      (0xF << TAA3040_AGC_LEVEL_SHIFT)
#define TAA3040_AGC_MAX_GAIN_SHIFT                  (0)
#define TAA3040_AGC_MAX_GAIN_MASK                   (0xF << TAA3040_AGC_MAX_GAIN_SHIFT)

/* --- Input Enable (0x73) --- */
#define TAA3040_CHANNEL1_ENABLE_SHIFT               (0x7)
#define TAA3040_CHANNEL1_ENABLE_MASK                (0x1 << TAA3040_CHANNEL1_ENABLE_SHIFT)
#define TAA3040_CHANNEL2_ENABLE_SHIFT               (0x6)
#define TAA3040_CHANNEL2_ENABLE_MASK                (0x1 << TAA3040_CHANNEL2_ENABLE_SHIFT)
#define TAA3040_CHANNEL3_ENABLE_SHIFT               (0x5)
#define TAA3040_CHANNEL3_ENABLE_MASK                (0x1 << TAA3040_CHANNEL3_ENABLE_SHIFT)
#define TAA3040_CHANNEL4_ENABLE_SHIFT               (0x4)
#define TAA3040_CHANNEL4_ENABLE_MASK                (0x1 << TAA3040_CHANNEL4_ENABLE_SHIFT)
#define TAA3040_CHANNEL5_ENABLE_SHIFT               (0x3)
#define TAA3040_CHANNEL5_ENABLE_MASK                (0x1 << TAA3040_CHANNEL5_ENABLE_SHIFT)
#define TAA3040_CHANNEL6_ENABLE_SHIFT               (0x3)
#define TAA3040_CHANNEL6_ENABLE_MASK                (0x1 << TAA3040_CHANNEL6_ENABLE_SHIFT)
#define TAA3040_CHANNEL7_ENABLE_SHIFT               (0x1)
#define TAA3040_CHANNEL7_ENABLE_MASK                (0x1 << TAA3040_CHANNEL7_ENABLE_SHIFT)
#define TAA3040_CHANNEL8_ENABLE_SHIFT               (0x0)
#define TAA3040_CHANNEL8_ENABLE_MASK                (0x1 << TAA3040_CHANNEL8_ENABLE_SHIFT)

/* --- Output Enable (0x74) --- */
#define TAA3040_ASI_CHANNEL1_ENABLE_SHIFT           (0x7)
#define TAA3040_ASI_CHANNEL1_ENABLE_MASK            (0x1 << TAA3040_ASI_CHANNEL1_ENABLE_SHIFT)
#define TAA3040_ASI_CHANNEL2_ENABLE_SHIFT           (0x6)
#define TAA3040_ASI_CHANNEL2_ENABLE_MASK            (0x1 << TAA3040_ASI_CHANNEL2_ENABLE_SHIFT)
#define TAA3040_ASI_CHANNEL3_ENABLE_SHIFT           (0x5)
#define TAA3040_ASI_CHANNEL3_ENABLE_MASK            (0x1 << TAA3040_ASI_CHANNEL3_ENABLE_SHIFT)
#define TAA3040_ASI_CHANNEL4_ENABLE_SHIFT           (0x4)
#define TAA3040_ASI_CHANNEL4_ENABLE_MASK            (0x1 << TAA3040_ASI_CHANNEL4_ENABLE_SHIFT)
#define TAA3040_ASI_CHANNEL5_ENABLE_SHIFT           (0x3)
#define TAA3040_ASI_CHANNEL5_ENABLE_MASK            (0x1 << TAA3040_ASI_CHANNEL5_ENABLE_SHIFT)
#define TAA3040_ASI_CHANNEL6_ENABLE_SHIFT           (0x3)
#define TAA3040_ASI_CHANNEL6_ENABLE_MASK            (0x1 << TAA3040_ASI_CHANNEL6_ENABLE_SHIFT)
#define TAA3040_ASI_CHANNEL7_ENABLE_SHIFT           (0x1)
#define TAA3040_ASI_CHANNEL7_ENABLE_MASK            (0x1 << TAA3040_ASI_CHANNEL7_ENABLE_SHIFT)
#define TAA3040_ASI_CHANNEL8_ENABLE_SHIFT           (0x0)
#define TAA3040_ASI_CHANNEL8_ENABLE_MASK            (0x1 << TAA3040_ASI_CHANNEL8_ENABLE_SHIFT)

/* --- Power Config (0x75) --- */
#define TAA3040_DYNAMIC_POWER_SHIFT                 (0x4)
#define TAA3040_DYNAMIC_POWER_MASK                  (0x1 << TAA3040_DYNAMIC_POWER_SHIFT)
#define TAA3040_DYNAMIC_POWER_CHANNELS_SHIFT        (0x2)
#define TAA3040_DYNAMIC_POWER_CHANNELS_MASK         (0x3 << TAA3040_DYNAMIC_POWER_SHIFT)
#define TAA3040_PLL_ENABLE_SHIFT                    (0x5)
#define TAA3040_PLL_ENABLE_MASK                     (0x1 << TAA3040_PLL_ENABLE_SHIFT)
#define TAA3040_ADC_ENABLE_SHIFT                    (0x6)
#define TAA3040_ADC_ENABLE_MASK                     (0x1 << TAA3040_ADC_ENABLE_SHIFT)
#define TAA3040_MIC_BIAS_ENABLE_SHIFT               (7)
#define TAA3040_MIC_BIAS_ENABLE_MASK                (0x1 << TAA3040_MIC_BIAS_ENABLE_SHIFT)

/* --- Input Status Register (0x76) ---*/
#define TAA3040_CHANNEL1_STATUS_SHIFT               (0x7)
#define TAA3040_CHANNEL1_STATUS_MASK                (0x1 << TAA3040_CHANNEL1_STATUS_SHIFT)
#define TAA3040_CHANNEL2_STATUS_SHIFT               (0x6)
#define TAA3040_CHANNEL2_STATUS_MASK                (0x1 << TAA3040_CHANNEL2_STATUS_SHIFT)
#define TAA3040_CHANNEL3_STATUS_SHIFT               (0x5)
#define TAA3040_CHANNEL3_STATUS_MASK                (0x1 << TAA3040_CHANNEL3_STATUS_SHIFT)
#define TAA3040_CHANNEL4_STATUS_SHIFT               (0x4)
#define TAA3040_CHANNEL4_STATUS_MASK                (0x1 << TAA3040_CHANNEL4_STATUS_SHIFT)
#define TAA3040_CHANNEL5_STATUS_SHIFT               (0x3)
#define TAA3040_CHANNEL5_STATUS_MASK                (0x1 << TAA3040_CHANNEL5_STATUS_SHIFT)
#define TAA3040_CHANNEL6_STATUS_SHIFT               (0x3)
#define TAA3040_CHANNEL6_STATUS_MASK                (0x1 << TAA3040_CHANNEL6_STATUS_SHIFT)
#define TAA3040_CHANNEL7_STATUS_SHIFT               (0x1)
#define TAA3040_CHANNEL7_STATUS_MASK                (0x1 << TAA3040_CHANNEL7_STATUS_SHIFT)
#define TAA3040_CHANNEL8_STATUS_SHIFT               (0x0)
#define TAA3040_CHANNEL8_STATUS_MASK                (0x1 << TAA3040_CHANNEL8_STATUS_SHIFT)

/* --- Device Status Register (0x77) --- */
#define TAA3040_MODE_STATUS_SHIFT                   (5)
#define TAA3040_MODE_STATUS_MASK                    (0x7 << TAA3040_MODE_STATUS_SHIFT)

/* --- IIR Config (Page 4, 0x10) --- */
#define TAA3040_IIR_ENABLE_MASK                     (0x01) ///< Bit 0
#define TAA3040_IIR_MODE_MASK                       (0x06) ///< Bits 2:1
#define TAA3040_IIR_MODE_SHIFT                      (1)

/* === Helper Macros === */
#define TAA3040_REG_CH_CONFIG(ch)                   (TAA3040_REG_CHANNEL_CONFIG_BASE + (ch * TAA3040_CHANNEL_REGISTER_ENTRIES))
#define TAA3040_REG_CH_VOLUME(ch)                   (TAA3040_REG_CHANNEL_VOLUME_BASE + (ch * TAA3040_CHANNEL_REGISTER_ENTRIES))
#define TAA3040_REG_CH_GAIN(ch)                     (TAA3040_REG_CHANNEL_GAIN_BASE + (ch * TAA3040_CHANNEL_REGISTER_ENTRIES))
#define TAA3040_REG_CH_GAIN_CAL(ch)                 (TAA3040_REG_CHANNEL_GAIN_CAL_BASE + (ch * TAA3040_CHANNEL_REGISTER_ENTRIES))
#define TAA3040_REG_CH_PHASE_CAL(ch)                (TAA3040_REG_CHANNEL_PHASE_CAL_BASE + (ch * TAA3040_CHANNEL_REGISTER_ENTRIES))


#endif /* TAA3040_REGISTERS_H */
