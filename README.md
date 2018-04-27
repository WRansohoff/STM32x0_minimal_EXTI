# Overview

This is a minimal project to demonostrate how to use a hardware interrupt for listening to either a button press, or incremental rotary encoder input. Behavior depends on the contents of the interrupt handler in `src/nvic.c`.

If a simple button is connected to pin B1, the LED can be set to toggle each time it is pressed.

If an incremental rotary encoder dial is connected to pins B1 and B0, the LED can be set to turn on or off depending on the direction of the last 'click' on the dial.

In both cases, pin B3 is used to control the LED. On the 'Nucleo' boards sold by ST, there is an on-board LED connected to this pin.

# Uploading and Debugging

This project targets either an STM32F031K6 or STM32L031K6 chip, depending on the 'MCU' option in the Makefile.

I've tested the program with 'Nucleo-32' boards for both chips. To upload the resulting program, you can use your choice of uploader/debugger. I use GDB and Texane's "stlink" project:

https://github.com/texane/stlink

It's a fairly simple process to upload and debug a program:

1. Plug your board in - for ST's Nucleo boards, you can just use an ordinary micro-USB cable.

2. Enter 'st-util' in a terminal window after installing the utilities linked above. You should see some general information printed about your chip.

3. Run `arm-none-eabi-gdb main.elf` (or whatever your file is called, if it's not 'main.elf')

4. Point GDB to the port opened by 'st-util' - usually 4242: `target extended-remote :4242`

5. Enter `load` to upload your program.

6. You're code is uploaded! Enter `continue` to start it running, and if you need to pause for debugging you can hit `ctrl+C` a few times (followed by 'y' for 'yes') to interrupt it once it's started.

Once the code is uploaded, you can more or less treat the GDB debugging session like you would any other C/C++ program in GDB. You can set breakpoints, step through the code with `s`/`si`/`n`/`ni`/etc, inspect variables or memory addresses, and so on.
