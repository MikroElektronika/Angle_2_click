/*
    __angle2_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __angle2_driver.h
@brief    Angle_2 Driver
@mainpage Angle_2 Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   ANGLE2
@brief      Angle_2 Click Driver
@{

| Global Library Prefix | **ANGLE2** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Oct 2018.**      |
| Developer             | **Nemanja Medakovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _ANGLE2_H_
#define _ANGLE2_H_

/** 
 * @macro T_ANGLE2_P
 * @brief Driver Abstract type 
 */
#define T_ANGLE2_P    const uint8_t*
#define T_ANGLE2_DEG_VAL    double
#define T_ANGLE2_DIG_VAL    uint16_t

/** @defgroup ANGLE2_COMPILE Compilation Config */              /** @{ */

   #define   __ANGLE2_DRV_SPI__                            /**<     @macro __ANGLE2_DRV_SPI__  @brief SPI driver selector */
//  #define   __ANGLE2_DRV_I2C__                            /**<     @macro __ANGLE2_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __ANGLE2_DRV_UART__                           /**<     @macro __ANGLE2_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup ANGLE2_VAR Variables */                           /** @{ */

/** Register Addresses */
extern const uint8_t _ANGLE2_BIAS_CURR_TRIMM_REG_3          ;
extern const uint8_t _ANGLE2_ZERO_POS_MSB_REG_4             ;
extern const uint8_t _ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5  ;
extern const uint8_t _ANGLE2_FLASH_N_REG_9                  ;

/** Settings for trimming control */
extern const uint8_t _ANGLE2_X_AXIS_TRIMM_EN                ;
extern const uint8_t _ANGLE2_Y_AXIS_TRIMM_EN                ;
extern const uint8_t _ANGLE2_AXIS_TRIMM_DIS                 ;

/** Settings for registers flash control */
extern const uint8_t _ANGLE2_FLASH_REG_3                    ;
extern const uint8_t _ANGLE2_FLASH_REG_4                    ;
extern const uint8_t _ANGLE2_FLASH_REG_5                    ;
extern const uint8_t _ANGLE2_NO_FLASH                       ;

/** MIN and MAX angle value in degrees */
extern const T_ANGLE2_DEG_VAL _ANGLE2_MAX_SCALE_359_91_DEG  ;
extern const T_ANGLE2_DEG_VAL _ANGLE2_MIN_SCALE_0_DEG       ;

                                                                       /** @} */
/** @defgroup ANGLE2_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup ANGLE2_INIT Driver Initialization */              /** @{ */

#ifdef   __ANGLE2_DRV_SPI__
void angle2_spiDriverInit(T_ANGLE2_P gpioObj, T_ANGLE2_P spiObj);
#endif
#ifdef   __ANGLE2_DRV_I2C__
void angle2_i2cDriverInit(T_ANGLE2_P gpioObj, T_ANGLE2_P i2cObj, uint8_t slave);
#endif
#ifdef   __ANGLE2_DRV_UART__
void angle2_uartDriverInit(T_ANGLE2_P gpioObj, T_ANGLE2_P uartObj);
#endif

                                                                       /** @} */
/** @defgroup ANGLE2_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Generic Write function
 *
 * @param[in] regAddr  Address where data be written
 * @param[in] dataIn  Data to be written
 *
 * @returns Angle value in degrees with 12-bit resolution [0 - 359.91]
 *
 * Function writes one byte data to the register.
 */
T_ANGLE2_DEG_VAL angle2_writeReg( uint8_t regAddr, uint8_t dataIn );

/**
 * @brief Generic Read function
 *
 * @param[in] regAddr  Address which from data be read
 * @param[out] dataOut  Memory where data be stored
 *
 * @returns Angle value in degrees with 8-bit resolution [0 - 359.91]
 *
 * Function reads one byte data from the register.
 */
T_ANGLE2_DEG_VAL angle2_readReg( uint8_t regAddr, uint8_t *dataOut );

/**
 * @brief Angle Getting function
 *
 * Function returns angle value in degrees with a range from 0 to 359.91.
 * @note Angle value is calculated with 12-bit resolution.
 */
T_ANGLE2_DEG_VAL angle2_getAngle( void );

/**
 * @brief Angle and Time Index Getting function
 *
 * @param[out] timeIndx  Memory where Time Index data be stored
 *
 * Function returns angle value in degrees, with a range from 0 to 359.91,
 * and also returns a Time Index value via output parameter.
 * @note Angle value is calculated with 12-bit resolution.
 */
T_ANGLE2_DEG_VAL angle2_getAngleWithTimeIndex( uint8_t *timeIndx );

/**
 * @brief Zero Scale Setting function
 *
 * @param[in] zeroDeg  Zero position value in degrees [0 - 359.91]
 *
 * Function sets a zero position value in degrees with 12-bit resolution.
 */
void angle2_setZeroScale( T_ANGLE2_DEG_VAL zeroDeg );

/**
 * @brief Trimming Enable function
 *
 * @param[in] state  0x10 - x axis, 0x20 - y axis
 *
 * Function selects which axis will be enabled for trimming.
 */
void angle2_enableTrimming( uint8_t state );

/**
 * @brief Flash Register function
 *
 * @param[in] regSel  0x08 - reg3, 0x10 - reg4, 0x20 - reg5
 *
 * Function stores the content of an entire selected register in the OTP memory.
 */
void angle2_flashReg( uint8_t regSel );

                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Angle_2_STM.c
    @example Click_Angle_2_TIVA.c
    @example Click_Angle_2_CEC.c
    @example Click_Angle_2_KINETIS.c
    @example Click_Angle_2_MSP.c
    @example Click_Angle_2_PIC.c
    @example Click_Angle_2_PIC32.c
    @example Click_Angle_2_DSPIC.c
    @example Click_Angle_2_AVR.c
    @example Click_Angle_2_FT90x.c
    @example Click_Angle_2_STM.mbas
    @example Click_Angle_2_TIVA.mbas
    @example Click_Angle_2_CEC.mbas
    @example Click_Angle_2_KINETIS.mbas
    @example Click_Angle_2_MSP.mbas
    @example Click_Angle_2_PIC.mbas
    @example Click_Angle_2_PIC32.mbas
    @example Click_Angle_2_DSPIC.mbas
    @example Click_Angle_2_AVR.mbas
    @example Click_Angle_2_FT90x.mbas
    @example Click_Angle_2_STM.mpas
    @example Click_Angle_2_TIVA.mpas
    @example Click_Angle_2_CEC.mpas
    @example Click_Angle_2_KINETIS.mpas
    @example Click_Angle_2_MSP.mpas
    @example Click_Angle_2_PIC.mpas
    @example Click_Angle_2_PIC32.mpas
    @example Click_Angle_2_DSPIC.mpas
    @example Click_Angle_2_AVR.mpas
    @example Click_Angle_2_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __angle2_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */