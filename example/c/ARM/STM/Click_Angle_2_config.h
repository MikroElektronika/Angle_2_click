#include "Click_Angle_2_types.h"

const uint32_t _ANGLE2_SPI_CFG[ 2 ] = 
{ 
        _SPI_FPCLK_DIV256, 
        _SPI_SECOND_CLK_EDGE_TRANSITION |
        _SPI_CLK_IDLE_HIGH |
        _SPI_MASTER | 
        _SPI_MSB_FIRST |
        _SPI_8_BIT | 
        _SPI_SSM_ENABLE | 
        _SPI_SS_DISABLE | 
        _SPI_SSI_1
};