# ![NullTek Documentation](resources/UOSLogoSmall.png) UOS Arduino

[![License](https://img.shields.io/:license-mit-blue.svg?style=flat-square)](LICENSE.md)
[![Codacy grade](https://img.shields.io/codacy/grade/29433b61b58d4841b29bf7957f6eb0e7?logo=codacy&style=flat-square)](https://app.codacy.com/gh/CreatingNull/UOS-Arduino)
![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/CreatingNull/UOS-Arduino?style=flat-square)

The arduino implementation of the UOS remote control protocol.
This software allows run-time control over embedded systems operation.
See the [official project documentation](https://wiki.nulltek.xyz/projects/uos/).

Status: Under active development, unstable versions are available for testing.

---

## Getting Started

This operating system is optimised for ATMega328P hardware.
It should work across multiple Arduino architectures, however pin mappings may change, and there is no guarantee of stability.

It is tested on:
*   Arduino Nano
*   Arduino Uno

For the best results.

### Installing from Source

This method is aimed at users familiar with the arduino IDE and / or users who need to make modifications to the project.

1.  Download the latest source from [tags](https://github.com//CreatingNull/UOS-Arduino/tags).
2.  Include the latest [Null Packet Comms](https://github.com/CreatingNull/Null-Packet-Comms-Arduino) library.
3.  Select the hardware and programming method through the IDE and then compile / upload the code to the target device.

---

## Donations

I just do this stuff for fun in my spare time, but feel free to:

[![Support via buymeacoffee](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/nulltek)

---

## License

The source of this repo uses the MIT open-source license, for details on the current licensing see [LICENSE](LICENSE.md) or click the badge above.
