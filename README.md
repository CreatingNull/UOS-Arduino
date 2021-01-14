# ![NullTek Documentation](resources/NullTekDocumentationLogo.png) UART - Arduino - Operating - System

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](LICENSE.md)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/29433b61b58d4841b29bf7957f6eb0e7)](https://www.codacy.com/gh/CreatingNull/UART-Arduino-Operating-System/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=CreatingNull/UART-Arduino-Operating-System&amp;utm_campaign=Badge_Grade)
![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/CreatingNull/UART-Arduino-Operating-System)

The UART AOS is a project that allows dynamic run-time control over embedded systems operation, 
using the Null Packet Comms Protocol. 
See the [official project documentation](https://wiki.nulltek.xyz/projects/uos/).

## Getting Started

This operating system is optimised for ATMega328P hardware. 
It should work across multiple Arduino architectures, however pin mappings may change, and there is no guarantee of stability.

It is tested on:
*   Arduino Nano
*   Arduino Uno 

For the best results.

### Installing from Source

This method is aimed at users familiar with the arduino IDE and / or users who need to make modifications to the project.

1.  Download the latest source from [tags](https://github.com//CreatingNull/UART-Arduino-Operating-System/tags).
2.  Included in the source is a zipped library for serial communications, this needs to be added through the arduino IDE. 
3.  Select the hardware and programming method through the IDE and then compile / upload the code to the target device. 

***

### Built using

*   [Arduino 1.8.13](https://github.com/arduino/Arduino) - Primary Compiler and IDE.
*   [Processing](https://processing.org/) - Operating System Loop / Handler Language.
*   [C++](https://isocpp.org/) - For the NPC serial communications libraries.

This project uses: 

*   clang-format to format it's C++ and C code using google styling.
    ``` sudo apt-get install clang-format ```

***

## Donations

I just do this stuff for fun in my spare time, but feel free to:

[![Support via buymeacoffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/nulltek)

***

## License

The source of this repo uses the MIT open-source license, for details on the current licensing see LICENSE.md or click the badge above. 
*   Copyright 2021 © <a href="https://nulltek.xyz" target="_blank">NullTek</a>.
