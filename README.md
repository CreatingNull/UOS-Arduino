#![NullTek Documentation](resources / NullTekDocumentationLogo.png) \
                              UART - Arduino - Operating - System

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](LICENSE.md)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/29433b61b58d4841b29bf7957f6eb0e7)](https://www.codacy.com/gh/CreatingNull/UART-Arduino-Operating-System/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=CreatingNull/UART-Arduino-Operating-System&amp;utm_campaign=Badge_Grade)

The UART AOS is a project that allows dynamic run-time control over embedded systems operation, 
using the Null Packet Comms Protocol. 
See the [official project documentation](https://nulltek.xyz/wiki/doku.php?id=uart_aos).

**Recomended Versions:**

*   **[0.2.0](https://github.com/CreatingNull/UART-Arduino-Operating-System/releases/tag/0.2.0)** - Functional development release, contains basic functionality but there are still a lot of features missing. 

It is recommended to use the latest stable release for deployment purposes. 
Development versions may be buggy and have incomplete functionality. 

## Getting Started

This operating system is optimised for ATMega328 hardware, but it should work across multiple Arduino architectures, however pin mappings may change and the is no guarantee of stability provided.

It is recommended you use:
*   Arduino Nano
*   Arduino Uno 

For the best results.

### Installing from Source

This method is aimed at users familiar with the arduino IDE and / or users who need to make modifications to the project.

1.  Download the latest source from [tags](https://github.com//CreatingNull/UART-Arduino-Operating-System/tags).
2.  Included in the source is a zipped library for serial communications, this needs to be added through the arduino IDE. 
3.  Select the hardware and programming method through the IDE and then compile / upload the code to the target device. 

***

## Contributing

If this project ever gets to any sort of usable state, it would be great to get any community additions.

### Built using

*   [Arduino 1.8.13](https://github.com/arduino/Arduino) - Primary Compiler and IDE
*   [Processing](https://processing.org/) - Operating System Loop / Handler Language
*   [C++](https://isocpp.org/) - For the NPC serial communications libraries.

This project uses: 

*   clang-format to format it's C++ and C code using google styleing.
    ``` sudo apt-get install clang-format ```

***

## Authors

*   **Steve Richardson** - *Project Concept and Initial Development* - [CreatingNull](https://github.com/CreatingNull)

***

## Donations

I just do this stuff for fun, but if you found any of my work helpful a little tip would be very much appreciated. 

[![Support via buymeacoffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/nulltek)

***

## License

This repo uses the MIT open-source license, for details on the current licensing see LICENSE.md or click the badge above. 
*   Copyright 2020 © <a href="https://nulltek.xyz" target="_blank">NullTek</a>.