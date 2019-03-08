/*
Example for Angle_2 Click

    Date          : Oct 2018.
    Author        : Nemanja Medakovic

Test configuration PIC :
    
    MCU             : P18F87K22
    Dev. Board      : EasyPIC PRO v7
    PIC Compiler ver : v7.2.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes peripherals and pins.
- Application Initialization - Initializes SPI interface in Mode 3 and performs a device
  configuration for properly working.
- Application Task - (code snippet) - Reads angle value in degrees and logs results on uart terminal.

Additional Functions :

- void floatCut() - Makes float value to be rounded on two decimal places.

*/

#include "Click_Angle_2_types.h"
#include "Click_Angle_2_config.h"

T_ANGLE2_DEG_VAL angle;
char text[ 100 ];

void floatCut()
{
    uint8_t count;
    uint8_t conCnt = 0;
    uint8_t conVar = 0;

    for (count = 0; count < 100; count++)
    {
        if (text[ count ] == '.')
        {
            conVar = 1;
        }
        if (conVar == 1)
        {
            conCnt++;
        }
        if (conCnt > 3)
        {
            if ((text[ count ] == 'e') || (conVar == 2))
            {
                text[ count - (conCnt - 4) ] = text[ count ];
                text[ count ] = 0;
                conVar = 2;
            }
            else
            {
                text[ count ] = 0;
            }
        }
    }
}

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );

    mikrobus_spiInit( _MIKROBUS1, &_ANGLE2_SPI_CFG[0] );

    mikrobus_logInit( _LOG_USBUART, 9600 );
    mikrobus_logWrite( "*** Initializing... ***", _LOG_LINE );

    Delay_ms( 100 );
}

void applicationInit()
{
    angle2_spiDriverInit( (T_ANGLE2_P)&_MIKROBUS1_GPIO, (T_ANGLE2_P)&_MIKROBUS1_SPI );
    Delay_ms( 300 );
    
    angle2_writeReg( _ANGLE2_BIAS_CURR_TRIMM_REG_3, 0x00 );
    angle2_enableTrimming( _ANGLE2_X_AXIS_TRIMM_EN | _ANGLE2_Y_AXIS_TRIMM_EN );
    angle2_setZeroScale( 44 );
    Delay_ms( 200 );
    
    mikrobus_logWrite( "** Angle 2 is initialized **", _LOG_LINE );
    mikrobus_logWrite( "", _LOG_LINE );
}

void applicationTask()
{
    angle = angle2_getAngle();
    
    FloatToStr( angle, text );
    floatCut();
    
    mikrobus_logWrite( "Angle is: ", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_TEXT );
    mikrobus_logWrite( " deg", _LOG_LINE );

    Delay_ms( 200 );
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}
