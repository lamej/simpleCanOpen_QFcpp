This program has three active objects:

Application Core: This will run the application and handle the main functionalities.
CANopen: This handles the CANopen protocol.
System Integrity: This ensures the program is running smoothly. If it detects an issue, a watchdog will be triggered.
To get an idea about this project, please refer to the class diagram.

The main role of this project is to collect data from the I/O and send it via a serial can communication. This project will be used as a kind of GPIO expander that utilizes CANopen, LCDs, and a keypad for configuration.
to do :
 implement SDO and heart beat.
 implement crypto ( is laready in the class diagram.

 Hardware Requirements:

This is a simple CANopen communication running on the evaluation board NUCLEO-F091RC. For more information, please refer to this link.
For CANopen, I use the board SHIELD CAN-BUS 13262 to interface with the STM32 board. More details can be found in the hookup guide.
Keypad from SparkFun.
Any LCD that works either serially or parallelly.
Compiler:

The compiler used is IAR Workbench.
The project is based on QP/C++ (see here for more information).
https://www.state-machine.com/products/qp
To refresh your understanding of how CANopen is structured, please refer to:
https://www.ni.com/en/shop/seamlessly-connect-to-third-party-devices-and-supervisory-system/the-basics-of-canopen.html
How to Test:

Use two pairs of NUCLEO-F091RC and SHIELD CAN-BUS 13262 boards connected via CANBus.
Ensure they do not have the same EXT_CARD1CAB_ID_.
Modify bsp.hpp according to your connection.
Remap PDO with your input and output GPIOs.
Any message that comes from any board will be displayed according to the LCD you choose.

Any modification that occurs at any input will be sent to a peer board.
