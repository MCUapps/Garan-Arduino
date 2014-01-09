Garan-Arduino
=============

This is my unofficial library and exmaple code to drive [Garan Audio Module](http://www.seeedstudio.com/depot/garan-audio-module-p-1607.html).

It's not perfect, but it's working.

SoftwareSerial works great as the communication channel with Garan. Just assign a pair of RX/TX, store some MP3 files in the micro-SD card, and your are ready to go.

Compatibilites
--------------

I tested the code mainly on Seeeduino V3.0 (Atmega 328P). The board is claimed to be based on Duemilanove Schematic, 100% compatible to its existing programs.

It also works PARTIALLY on MSP430 Value Line G2 Launchpad using msp430g2553 with Energia according to my rough tests. It seems that those commands with music names would cause Launchpad to reset itself. I guess it's caused by buffer overflow of SoftwareSerial driver, but I am not sure about the root cause.

Examples
--------

There are 2 examples for now.

* Garan_Console -- Use Serial Monitor and your keyboard to test some commands. It also prints the feedback bytes in hex format.
* UltraSonicRanger_Reading -- Report the reading from an Ultra Sonic Ranger every 3 second.

Audio Tools
-----------

There is only a Ruby script inside this folder. I used it to connect [http://tts-api.com](http://tts-api.com) to download voice files counting from 1 to 1000. Should be useful for reading type applications.
