# UOS-Arduino Systems Test

This repository includes a pytest suite which aims to verify functionality on physical hardware.
This can be thought of as system functional testing, so that a developer can use to verify basic functionality against the UOS specification.

This test suite can be built to execute in an automated fashion, but it should not be considered part of the main CI pipeline due to its reliance on application hardware.

## Running Tests

Current the suite is built to run on Python 3.11 using the uos-hardware library.
Configure a development environment for the project and install requirements from `.resources\requirements-development.txt`.

### Device Under Test Configuration

This test suite requires a modified arduino nano 3 or compatible clone.

The modifications to be made are:

 * A 10k resistor between D2 and D5 - this is for testing digital input / output.
 * A 10k resistor between 5V and A7 and a 10k resistor between A7 and GND - divider for testing ADC input.

### Launching the test suite.

To run the test suite you need to provide pytest the port to your modified arduino nano device.

`python -m pytest .tests/ --port=/dev/ttyUSB0`
