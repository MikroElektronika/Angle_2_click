/*
    __angle2_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__angle2_driver.h"
#include "__angle2_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __ANGLE2_DRV_I2C__
static uint8_t _slaveAddress;
#endif

const double _ANGLE2_DEG_LSB = 0.08789;

const uint8_t _ANGLE2_WRITE_CMD                          = 0x20;
const uint8_t _ANGLE2_READ_CMD                           = 0x10;
const uint8_t _ANGLE2_DUMMY_BYTE                         = 0x00;
const uint8_t _ANGLE2_REG_ADDR_MASK                      = 0x0F;

const uint8_t _ANGLE2_BIAS_CURR_TRIMM_REG_3              = 0x03;
const uint8_t _ANGLE2_ZERO_POS_MSB_REG_4                 = 0x04;
const uint8_t _ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5      = 0x05;
const uint8_t _ANGLE2_FLASH_N_REG_9                      = 0x09;

const uint8_t _ANGLE2_X_AXIS_TRIMM_EN                    = 0x10;
const uint8_t _ANGLE2_Y_AXIS_TRIMM_EN                    = 0x20;
const uint8_t _ANGLE2_AXIS_TRIMM_DIS                     = 0x00;

const uint8_t _ANGLE2_FLASH_REG_3                        = 0x08;
const uint8_t _ANGLE2_FLASH_REG_4                        = 0x10;
const uint8_t _ANGLE2_FLASH_REG_5                        = 0x20;
const uint8_t _ANGLE2_NO_FLASH                           = 0x00;

const T_ANGLE2_DEG_VAL _ANGLE2_MAX_SCALE_359_91_DEG      = 359.91211;
const T_ANGLE2_DEG_VAL _ANGLE2_MIN_SCALE_0_DEG           = 0;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static T_ANGLE2_DEG_VAL _calAngle( T_ANGLE2_DIG_VAL angleDig );

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static T_ANGLE2_DEG_VAL _calAngle( T_ANGLE2_DIG_VAL angleDig )
{
    T_ANGLE2_DEG_VAL retRes;
    
    retRes = angleDig;
    retRes *= _ANGLE2_DEG_LSB;
    
    return retRes;
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __ANGLE2_DRV_SPI__

void angle2_spiDriverInit(T_ANGLE2_P gpioObj, T_ANGLE2_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    hal_gpio_csSet( 1 );
}

#endif
#ifdef   __ANGLE2_DRV_I2C__

void angle2_i2cDriverInit(T_ANGLE2_P gpioObj, T_ANGLE2_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __ANGLE2_DRV_UART__

void angle2_uartDriverInit(T_ANGLE2_P gpioObj, T_ANGLE2_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

/* ----------------------------------------------------------- IMPLEMENTATION */

T_ANGLE2_DEG_VAL angle2_writeReg( uint8_t regAddr, uint8_t dataIn )
{
    uint8_t buffIn[ 2 ];
    uint8_t buffOut[ 2 ];
    T_ANGLE2_DIG_VAL angleData;
    T_ANGLE2_DEG_VAL retVal;
    
    buffIn[ 0 ] = regAddr & _ANGLE2_REG_ADDR_MASK;
    buffIn[ 0 ] |= _ANGLE2_WRITE_CMD;
    buffIn[ 1 ] = dataIn;
    
    hal_gpio_csSet( 0 );
    hal_spiTransfer( buffIn, buffOut, 2 );
    hal_gpio_csSet( 1 );
    
    angleData = buffOut[ 0 ];
    angleData <<= 4;
    angleData |= buffOut[ 1 ] >> 4;
    
    retVal = _calAngle( angleData );
    
    return retVal;
}

T_ANGLE2_DEG_VAL angle2_readReg( uint8_t regAddr, uint8_t *dataOut )
{
    uint8_t buffIn[ 2 ];
    uint8_t buffOut[ 2 ];
    T_ANGLE2_DIG_VAL angleData;
    T_ANGLE2_DEG_VAL retVal;
    
    buffIn[ 0 ] = regAddr & _ANGLE2_REG_ADDR_MASK;
    buffIn[ 0 ] |= _ANGLE2_READ_CMD;
    buffIn[ 1 ] = _ANGLE2_DUMMY_BYTE;
    
    hal_gpio_csSet( 0 );
    hal_spiTransfer( buffIn, buffOut, 2 );
    hal_gpio_csSet( 1 );
    
    *dataOut = buffOut[ 1 ];
    angleData = buffOut[ 0 ];
    angleData <<= 4;
    
    retVal = _calAngle( angleData );
    
    return retVal;
}

T_ANGLE2_DEG_VAL angle2_getAngle( void )
{
    uint8_t buffIn[ 2 ];
    uint8_t buffOut[ 2 ];
    T_ANGLE2_DIG_VAL angleData;
    T_ANGLE2_DEG_VAL retVal;
    
    buffIn[ 0 ] = _ANGLE2_DUMMY_BYTE;
    buffIn[ 1 ] = _ANGLE2_DUMMY_BYTE;
    
    hal_gpio_csSet( 0 );
    hal_spiTransfer( buffIn, buffOut, 2 );
    hal_gpio_csSet( 1 );
    
    angleData = buffOut[ 0 ];
    angleData <<= 4;
    angleData |= buffOut[ 1 ] >> 4;
    
    retVal = _calAngle( angleData );
    
    return retVal;
}

T_ANGLE2_DEG_VAL angle2_getAngleWithTimeIndex( uint8_t *timeIndx )
{
    uint8_t buffIn[ 3 ];
    uint8_t buffOut[ 3 ];
    T_ANGLE2_DIG_VAL angleData;
    T_ANGLE2_DEG_VAL retVal;
    
    buffIn[ 0 ] = _ANGLE2_DUMMY_BYTE;
    buffIn[ 1 ] = _ANGLE2_DUMMY_BYTE;
    buffIn[ 2 ] = _ANGLE2_DUMMY_BYTE;
    
    hal_gpio_csSet( 0 );
    hal_spiTransfer( buffIn, buffOut, 3 );
    hal_gpio_csSet( 1 );
    
    *timeIndx = buffOut[ 2 ];
    angleData = buffOut[ 0 ];
    angleData <<= 4;
    angleData |= buffOut[ 1 ] >> 4;
    
    retVal = _calAngle( angleData );
    
    return retVal;
}

void angle2_setZeroScale( T_ANGLE2_DEG_VAL zeroDeg )
{
    T_ANGLE2_DEG_VAL res;
    T_ANGLE2_DIG_VAL zeroData;
    uint8_t dataSend[ 2 ];
    
    if (zeroDeg > _ANGLE2_MAX_SCALE_359_91_DEG)
    {
        res = _ANGLE2_MAX_SCALE_359_91_DEG;
    }
    else
    {
        res = zeroDeg;
    }
    
    res /= _ANGLE2_DEG_LSB;
    zeroData = res;
    
    angle2_readReg( _ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5, &dataSend[0] );
    dataSend[ 0 ] &= 0x30;
    dataSend[ 0 ] |= zeroData & 0x000F;
    dataSend[ 1 ] = zeroData >> 4;
    
    angle2_writeReg( _ANGLE2_ZERO_POS_MSB_REG_4, dataSend[1] );
    angle2_writeReg( _ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5, dataSend[0] );
}

void angle2_enableTrimming( uint8_t state )
{
    uint8_t dataSend;
    
    angle2_readReg( _ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5, &dataSend );
    
    dataSend &= 0xCF;
    dataSend |= state & 0x30;
    
    angle2_writeReg( _ANGLE2_AXIS_TRIMM_AND_ZERO_LSB_REG_5, dataSend );
}

void angle2_flashReg( uint8_t regSel )
{
    uint8_t dataSend;
    
    dataSend = regSel & 0x38;
    
    angle2_writeReg( _ANGLE2_FLASH_N_REG_9, dataSend );
}

/* -------------------------------------------------------------------------- */
/*
  __angle2_driver.c

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