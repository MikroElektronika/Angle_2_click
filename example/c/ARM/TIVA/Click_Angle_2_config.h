#include "Click_Angle_2_types.h"

const uint32_t _ANGLE2_SPI_CFG[ 3 ] = 
{ 
	1000000, 
	_SPI_MASTER, 
	_SPI_8_BIT | 
	_SPI_CLK_IDLE_HIGH |
	_SPI_SECOND_CLK_EDGE_TRANSITION 
};
