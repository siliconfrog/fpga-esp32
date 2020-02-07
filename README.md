Contains the verilog code to demonstrate the capabilities of the Silicon Frog
fpga-384 when connected to an ESP32 with the following projects:

# Blink

The simplest example with flashing LEDs.

# PWM

Fading the LED brightness using PWM.

# Gates

The ESP32 cycles the FPGA through a set of logic gates (AND, OR, XOR, NOT)
and the LEDs will show the result of the inputs.

The gate type is chosen dependent upon a bit pattern selection, and the output is the
logical gate application of the input.

# Adder

The ESP32 shows the FPGA as a simple one bit full adder taking in a
single bit and a carry bit and producing the result bit and a new carry bit.

Resulting bit and carry bit are shown on the leds.

# Parity

The ESP32 cycles the FPGA through a sequence where four bits are used as an
input to find the even parity, which is shown on an led.

# Rand

The FPGA will provide a running Pseudo Random Number Generator using a Linear Feedback
Shift Register.

A single bit is shown on an led which should flash with an unpredictable pattern.

# Pattern

Shows the application of an internal state machine. A binary pattern is fed into an
input which changes the internal state. The green LED lights when the full pattern is
correctly received.

# BCD

This shows Binary Coded Decimal logic.

# Decoder

Shows how to generate specific binary output, given a binary input. Can be used to
create a 3-8 decoder, for example.

# SPI

Shows reception and transmission of SPI data at 4MHz speeds.

# I2C

Shows how to create a device with a programmable I2C address.

# Serial

Implements a serial encoder / decoder, which has been tested at 115200 baud.

