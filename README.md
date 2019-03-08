![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Angle_2 Click

- **CIC Prefix**  : ANGLE2
- **Author**      : Nemanja Medakovic
- **Verison**     : 1.0.0
- **Date**        : Oct 2018.

---

### Software Support

We provide a library for the Angle_2 Click on our [LibStock](https://libstock.mikroe.com/projects/view/2629/angle-2-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library can perform a control of the Angle 2 Click board.
Also can measure the angle value in degrees with a range of 0 deg to 359.91 deg.
Zero position setting also can be performed by using this library.
The library offers a choice to save content of an entire selected register in OTP memory.
For more details check documentation.

Key functions :

- ``` T_ANGLE2_DEG_VAL angle2_writeReg( uint8_t regAddr, uint8_t dataIn ) ``` - Function writes one byte data to the register.
- ``` T_ANGLE2_DEG_VAL angle2_getAngle( void ) ``` - Function returns angle value in degrees with a range from 0 to 359.91.
- ``` void angle2_setZeroScale( T_ANGLE2_DEG_VAL zeroDeg ) ``` - Function sets a zero position value in degrees with 12-bit resolution.

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes peripherals and pins.
- Application Initialization - Initializes SPI interface in Mode 3 and performs a device
  configuration for properly working.
- Application Task - (code snippet) - Reads angle value in degrees and logs results on uart terminal.


```.c
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
```

Additional Functions :

- void floatCut() - Makes float value to be rounded on two decimal places.

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2629/angle-2-click) page.

Other mikroE Libraries used in the example:

- Conversions
- SPI
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
