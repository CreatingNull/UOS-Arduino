Version 0.7.0
-------------

:Date: TBC

* Restructuring device definition to capture pin indices, state and specs.
  This allows the device to communicate its capabilities.
* Adding the ``IO_NONE`` state to allow for ignoring pins.
* Sanity check pin compatibility before executing IO actions.
* Adding a systems test case against the get_firmware_details functionality.
* Updating firmware_details command to use 2 byte identity and API version codes.
* Setting identities based on device.
* Changed ``Devices.ino`` definitions to be a header file so we can mandate the import order.

Version 0.6.0
-------------

:Date: 8-January-2023

* Updating for redesigned UOS protocol.
* Redesigned the supported device hardware to be defined in a more concise manner.
* Redesigned IO handling to reduce wasted memory.
* Removing 16-bit types being used for loop variables.
* Ensuring pins are defined before trying to use them.
* Remove non-binary search array lookup as all our definition arrays will be sorted.
* Fixing the arduino uno definition. This device has fewer ADC pins than the nano.
* Set globals to use a tailing underscore for convention to differentiate them from locals.
* Fixed a bug where switching from output high state to input would leave pull-ups enabled.
