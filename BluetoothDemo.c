/*
###  Bluetooth Home Control Automation ###
Master class on Embedded system using Arm Cortex M4
=================================================================================================
⚫ Advantages of Bluetooth

 • Advantages
 ✔Bluetooth: interoperable
 ✔IrDA: line of sight needed, point-to-point
 ✔WLAN: higher power consumption

 • Disadvantages
 ✔Bluetooth: only up to 1 Mbps
 ✔IrDA: much cheaper, faster (up to 16 Mbps)
 ✔WLAN: faster (up to 11 Mbps)
 
 =================================================================================================
 
⚫ HC-05 Default Settings

 - Default Bluetooth Name: "HC-05"
 - Default Password: 1234 or 0000
 - Default Communication: Slave
 - Default Mode: Data Mode
 - Data Mode Baud Rate: 9600, 8, N, 1
 - Command Mode Baud Rate: 38400, 8, N, 1
 - Default firmware: LINVOR
=================================================================================================

⚫ Tech Specifications
 • Serial Bluetooth module for arduino other microcontrollers
 • Operating Voltage: 4V to 6V (Typically +5V)
 • Operating Current: 30mA.
 • Range: <100m
 • Works with Serial communication (USART) and TTL compatible
 • Follows IEEE 802.15.1 standardized protocol • Uses Frequency-Hopping Spread spectrum (FHSS)
 • Can operate in Master, Slave or Master/Slave mode
 • Can be easily interfaced with Laptop or Mobile phones with Bluetooth
 • Supported baud rate: 9600,19200,38400,57600,115200,230400,460800.
 =================================================================================================
 ⚫ What is a Relay

• A relay is an electrically operated switch. 
 It consists of a set of input terminals for a single or multiple 
 control signals, and a set of operating contact terminals.

• The traditional form of a relay uses an electromagnet to close or 
 open the contacts, but other operating principles have been invented, 
 such as in solid-state relays which use semiconductor properties 
 for control without relying on moving parts.
=================================================================================================
⚫ BLOCK DIAGRAM

|-----------|  |-----------|
|           |  |           |>>|---------|>>|------|
| BLUETOOTH |>>|STM32F411  |>>|  RELAYS |>>| FAN  |
|           |>>|           |  |---------|  |------|
|           |  |           |>>|---------|  |------|
|           |  |           |>>|  RELAYS |>>|LIGHT |
|           |  |           |  |---------|>>|------|
|-----------|  |-----------|    
 
 =================================================================================================
⚫ Serial Data

|---------|-------------|------------------|
|         |   DATA      |   OPERATION      |
|---------|-------------|------------------|
| Fan on  |    A        |   Fan Turned ON  |
|---------|-------------|------------------|
| Fan off |    B        |   Fan Turned OFF |
|---------|-------------|------------------|

 =================================================================================================
⚫ UART Parameters
 • Baud Rate           (9600, 19200, 115200, others)
 • Number of Data Bits (7, 8)
 • Parity Bit          (On, Off)
 • Stop Bits           (0, 1, 2)
 • Flow Control        (None, On, Hardware)
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


=================================================================================================

*/

/*
SCHEMATIC DESIGN
[From Alternate Function Table 9]
PB6 >> TX   
PB7 >> RX -> BLUETOOTH TX
RELAY >>PA5

*/

/*
=================================================================================================
⚫⚫⚫ UART WRITE ⚫⚫⚫

 void uart2_write(int ch) 
 {
	  //Make sure the transmit data register is empty 
	  while(!("USART2 SR & 0x0080))(){} 
	  //write to transmit data register 
	  *USART2_DR =(ch&0xFF);

 }
=================================================================================================
### Status register (USART SR) ###

 Address offset: 0x00
 Reset value: 0x0000 0000
 
 TXE : Transmit data register empty
 This bit is set by hardware when the content of the 
 TDR register has been transferred into the shift register.
 An interrupt is generated if the TXEIE bit =1 
 in the USART CR1 register. It is cleared by a write to 
 the USART DR register 0: Data is not transferred to the 
 shift register.
 0: Data is not transferred to the shift register.
 1: Data is transferred to the shift register)
=================================================================================================



=================================================================================================




=================================================================================================




=================================================================================================


*/