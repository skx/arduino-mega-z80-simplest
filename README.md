# Z80 Retroshield code

The [RetroShield](http://www.8bitforce.com/projects/retroshield/) comes in a Z80 flavour, complete with a small amount of [sample code](https://gitlab.com/8bitforce/retroshieldz80).

However the sample code mixes the actual Z80-usage with some unrelated things, such as button-scanning, LCD display, and SPI-RAM access which makes it harder to use as a standalone "thing".

This repository aims to make the retro-shield easier to deal with, by abstracting the CPU-driving into a single standalone class.  Allowing you to use it in your arduino-sketch along with whatever else you wish to do.

There are currently two pieces of sample-code for the Z80 retroshield, one uses the `loop()`-based approach this repository contains, the other uses a timer-function to drive the processor.  Using a timer is cleaner since it gives you more speed and predictability, however the execution becomes more complex because you can't do things like invoke `Serial.read()`/`Serial.write()` inside an interrupt-handler - though you can disable the time for the duration of your "stuff".

In short running things in `loop()` is more predictable, but slower.


## Overview

Create a `Z80` object, and pass it handlers for:

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

The retroshield itself:

* [http://www.8bitforce.com/projects/retroshield/](http://www.8bitforce.com/projects/retroshield/)

Now some Z80 links

* Sample Z80 code:
  * [https://github.com/skx/z80-examples](https://github.com/skx/z80-examples)
* Sample Z80 emulator:
  * [https://github.com/skx/z80emulater/](https://github.com/skx/z80emulater/).
* My blog posts on the topic of creating Z80-based computer:
  * [https://blog.steve.fi/tags/z80/](https://blog.steve.fi/tags/z80/)
