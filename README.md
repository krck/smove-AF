<h1> smove-AF (ATMEL Firmware) </h1>

<b> About </b> <br>
This Firmware is used to control an ATMEL Atmega1284P on the MELZI V2.0 Board. <br>
It can be used with the corresponding Desktop Application smove <br>
https://github.com/krck/smove <br>

The Firmware is written in C and uses the AVR Libraries. <br>
It accepts the standard G and M codes and is planned to <br>
give 3D-Printers a from CNC-Machines known very direct <br>
programming Interface, when used together with smove. <br>

<b> TODO </b>
- [ ] “goto_MACHINE_ZERO” function: move axis simultaneously
- [x] Add an “arc_motion” function
- [ ] Debug "arc_motion" function
- [ ] Fix Z-Axis height bug (Can not move higher than 50mm)
- [x] Add function / logic to set the feed-rate
- [ ] Implement the main loop (Change between direct and automated control)
- [ ] Set and check system states
- [ ] Add the error handling in the main loop
- [ ] Implement System functions like "reset()"
