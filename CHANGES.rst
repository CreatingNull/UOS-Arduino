Version 0.6.0
-------------

:Date: TBC

* Redesigned the supported device hardware to be defined in a more concise manner.
* Redesigned IO handling to reduce wasted memory.
* Removing 16-bit types being used for loop variables.
* Ensuring pins are defined before trying to use them.
* Remove non-binary search array lookup as all our definitiuon arrays will be sorted.
* Fixing the arduino uno definition. This device has fewer ADC pins than the nano.
