# UART-Arduino-Operating-System

The UART AOS is a project that allows dynamic run-time control over embedded systems operation, 
using the Null Packet Comms Protocol. 
See the [official project documentation](https://nulltek.xyz/wiki/doku.php?id=uart_aos).

**Recomended Versions:**
* **0.0.1** - Functional development release, contains basic functionality but there are still a lot of features missing. 

It is recommended to use the latest stable release for deployment purposes. 
Development versions may be buggy and have incomplete functionality. 

## Getting Started

This operating system is optimised for Nano/Uno hardware, but it should work across multiple Arduino architectures, however pin mappings may change and the is no guarantee it will work.

It is recommended you use:
* Arduino Nano
* Arduino Uno 

For the best results.

### Installing From Binary

This is the recommended method for production installs as it doesn't involve setting up libraries or any handling / manipulation of the source.
1. Download the latest binary for your hardware (/bin), in most cases use the version **without** bootloader as most arduino hardware comes pre-flashed with the bootloader. In addition programming the device over serial (instead of ISP) requires the bootloader to be present. 
2. Attach the target device to the computer, ensure the software serial port drivers install correctly. Take note of the port number. 
3. Using avrdude (Installs with Arduino IDE (/hardware/tools/avr/bin) or available [here](http://savannah.nongnu.org/projects/avrdude))
run the following cli command. ```
"Path\to\avrdude.exe" -C "path\to\avrdude.conf" -v -p part -c arduino -P COMPORT -b 57600 -D -U flash:w:C:Path\to\hex```
    * Where "Path\to\avrdude.exe" is the full path to the avrdude executable on your computer.
    * "Path\to\avrdude.conf" should be the full path to the arduino configuration file.
    * "part" should be set to the part number of the avr on your arduino. Eg: atmega328p for arduino nano.
    * COMPORT should be set to the serial port of the device you plugged in eg: COM4
    * finally "path\to\hex" should be set to the full path for the binary file in this repo. 
### Installing from Source

This method is aimed at users familiar with the arduino IDE and / or users who need to make modifications to the project.

1. Git clone the latest source files. 
2. Included in the source is a zipped libary for serial communications, this needs to be added through the arduino IDE. 
3. Select the hardware and programming method through the IDE and then compile / upload the code to the target device. 

## Built With

* [Arduino 1.8.10](https://github.com/arduino/Arduino) - Primary Compiler and IDE
* [Processing](https://processing.org/) - Operating System Loop / Handler Language
* [C++](https://isocpp.org/) - For the NPC serial communications libraries.

## Versioning
I am using [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com//CreatingNull/UART-Arduino-Operating-System/tags). 

## Authors

* **Steve Richardson** - *Project Concept and Initial Development* - [CreatingNull](https://github.com/CreatingNull)

## License

This project is licensed under the GNU GPLv3 License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* The NPC drivers were inspired by herkulex serial packet comms when I started this project in 2016, however the simularities are fairly distint now. 
