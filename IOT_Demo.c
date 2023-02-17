/*
=================================================================================================
Master class on Embedded system using Arm Cortex M4
⚫⚫⚫ INTERNET OF THINGS ⚫⚫⚫
=================================================================================================
*/


/*
=================================================================================================
 ⚫ What is Internet of Things ?
 Connecting everyday things embedded with electronics, software and sensors 
 to the internet enabling them to collect and exchange data
================================================================================================= 
 ⚫SOFTWARE REQUIRED
• STM2CUBE IDE
• SALEA LOGIC ANALYZER
• Thingspeak
=================================================================================================
 ⚫ What is Thingspeak

 • Analytic loT platform
 -Collect data from sensors, "things"
 -Visualize data instantly
 -Has more than 60,000 users

 • Analyze data
 -MATLAB integration allows users to run scheduled code 
  on data coming into ThingSpeak.

 • Act on data
 -Eg. send a tweet when the temperature in your backyard 
  reaches 32 degrees
 
 =================================================================================================
⚫ SCHEMATIC DESIGN
  PB6 >> TX   
  PB7 >> RX -> ESP8266 TX
  RELAY >>PA5
  
=================================================================================================
⚫ BLOCK DIAGRAM

|------------|  |-----------|  |-----------|
|            |  |           |  |           |>>|---------|>>|---------|
| Thingspeak |>>| ESP8266   |>>|STM32F411  |>>|  ADC    |>>| SENSOR  |
|            |  |           |>>|           |  |---------|  |---------|
|            |  |           |  |           |>>|---------|  |---------|
|            |  |           |  |           |>>|  RELAYS |>>|  LIGHT  |
|------------|  |           |  |           |  |---------|>>|---------|
                |-----------|  |-----------| 
				
=================================================================================================
⚫ UART Parameters
 • Baud Rate           (115200)
 • Number of Data Bits (7, 8)
 • Parity Bit          (On, Off)
 • Stop Bits           (0, 1, 2)
 • Flow Control        (None, On, Hardware)
=================================================================================================
⚫ AT COMMANDS
 AT commands used for data transmission

 • AT+RST
 • AT+CWJAP="WIFINAME", "Password"
 • AT+CIPSTART="TCP","184.106.153.149",80
 • AT+CIPSEND=49 
 • GET /update?api_key=XXXXXX XXXX&field1-000
 • AT+CLOSE
=================================================================================================
⚫ STEPS FOR UART TRANSMIT

 //Enable clock access to GPIOA
 //SET PA2,PA3 MODE TO Alternate function Mode
 //SET PA2,PA3 Alternative function type to UART_TX (AF07)
 //CONFIGURE UART MODULE
 //ENABLE CLOCK ACCESS TO UART2
 //CONFIGURE BAUDRATE
 //CONFIGURE TRANSFER DIRECTION
 //ENABLE UART MODULE
=================================================================================================
⚫ BAUD RATE CALCULATION
 • Peripheral Clock=16000000
 • BAUDRATE=9600
 • BRR =((16000000+(9600/2))/9600)
 • BRR=1667
 • HEX VALUE OF BRR=0X0683

 • BAUDRATE=115200
 • BRR =((16000000+(115200/2))/115200)
 • BRR=139
 • HEX VALUE OF BRR=0X008B


=================================================================================================

=================================================================================================










=================================================================================================




=================================================================================================
*/