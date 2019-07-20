# Z80 Retroshield code

The [RetroShield](http://www.8bitforce.com/projects/retroshield/) comes in a Z80 flavour, complete with a small amount of [sample code](https://gitlab.com/8bitforce/retroshieldz80).

However the sample code mixes the actual Z80-usage with some unrelated things, such as button-scanning, LCD display, and SPI-RAM access which makes it harder to use as a standalone "thing".

This repository aims to make the retro-shield easier to deal with, by abstracting the CPU-driving into a single standalone class.  Allowing you to use it in your arduino-sketch along with whatever else you wish to do.

**TODO** Make a note here about the design choice of tick vs. interrupt driving.


## Overview

Create a Z80-object, and pass it handlers for:

* Reading a byte of RAM from address XXX.
* Writing byte NN to address XXX of RAM.
* Reading a byte from I/O address NN.
* Writing byte NN to I/O address NN.

Once you've done that call `.Tick()`to run the processor regularly.

The [sample code](arduino-mega-z80-simplest.ino) should demonstrate the usage in a clean fashion, but questions are welcome!


## TODO

The code has been compile-tested only.

I'm still hazy on whether the I/O access will succeed, but we'll see ..


## Links

Sample Z80 code:

* [https://github.com/skx/z80-examples](https://github.com/skx/z80-examples)

Sample Z80 emulator:

* [https://github.com/skx/z80emulater/](https://github.com/skx/z80emulater/).

Blog posts on the topic:

* [https://blog.steve.fi/tags/z80/](https://blog.steve.fi/tags/z80/)
