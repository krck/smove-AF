smove-AF (ATMEL Firmware)
========

This is a small (work in progress) 3D Printer Firmware, designed for an ATMEL Atmega1284P on the MELZI V2.0 Board. 
It can be controlled with the corresponding Desktop Application [smove](https://github.com/krck/smove).

About
--------

The Firmware is written in C with the Atmel Studio 7.0 and uses the AVR Libraries.
It accepts the standard G and M codes and is planned to give 3D-Printers a, from CNC-Machines known, very direct 
programming Interface, when used together with the smove desktop application.

TODO (next few steps)
--------

- [ ] “goto_MACHINE_ZERO” function: move axis simultaneously
- [x] Add an “arc_motion” function
- [ ] Debug "arc_motion" function
- [ ] Fix Z-Axis height bug (Can not move higher than 50mm)
- [x] Add function / logic to set the feed-rate
- [ ] Implement the main loop (Change between direct and automated control)
- [ ] Set and check system states
- [ ] Add the error handling in the main loop
- [ ] Implement System functions like "reset()"
