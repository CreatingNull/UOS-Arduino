# UART-Arduino-Operating-System

## Formatted Change Log

***
### *Version: 0.4.0, Release Date: TBC

*Note:*
*   Removed outdated info from the original NPC library. 
*   Removed redundant handling code from the top level.
*   Fixed a hidden-bug with the major version in addr 250.
*   Instantiated digital pins 0 and 1 as mapped by default.
*   Added instruction 251 for querying config on digital pins.
*   Removed redundant variables from NPC library.

***
### *Version: 0.3.0, Release Date: 8-October-2020*

*Note:*
*   Improved markdown formatting. 
*   Moved LICENSE.md to root to match GH conventions. 
*   Added version and device information as constants into the source.
*   Added UOS command 250 for returning a version and hardware information packet.

***
### *Version: 0.2.0, Release Date: 20-September-2020*

*Note:*
*   Added a .gitignore to allow for the removal of build / temp files.
*   Removed binary files, repo should just contain source until a better deployment pipeline is developed. 
*   Fixed a mistake where DIO volatile input should have been handled on the same address 64 instead of 65.
*   Switched to MIT license for more permissive use. 

***
### *Version: 0.1.0, Release Date: 8-December-2019*

*Note:*
*   Added a developer change log to allow for easy recording of changes as they are developed. 
*   Added in support for digital IO reads. For syntax see documentation. 
*   Completed the support for write IO to set input modes, for both pullup enabled and pullup disabled.
*   Refactored API code into its own .ino. 
*   Refactored API handling for IO reading to use common packet return / handling functionality.
*   Refactored commands with response packets into a common daq function to reduce code duplication. 
*   Fixed some bugs in the factory defaults and enabled all 12 digital IO and 8 analog IO pins. 
***
