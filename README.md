# STM32duino-Composite

This library aims to generate a decent monochrome video signal using a run of the mill STM32F103C8T6 "bluepill" board.

The code I wrote is by no means good and the video signal randomly jumps because I haven't gotten the vertical sync perfect.

The code relies on the STM32's software timers to create a series of sync pulses every 64µS

# Considerations
This only works with PAL. I have not managed to get a progressive NTSC scan to work. If you know how to achieve one please open an issue or make a pull request.

It is pretty much required to use the -O3 optimizer with this code and to overclock the board to 128Mhz.

If you opt to leave all the settings at their defaults then you can go into the header file and uncomment the "SLOW_MODE" definition. This will give you very chunky pixels but it will work.

This library uses timer 1 on the STM32. Any PWM signals on pins which rely on timer 1 will probably not function. Those are pins PA8, PA9, and PA10.