# fan
by kim timoth engh

## Preamble
fan is a Arduino based project which is short for "fire alarm notifier". The goal of the project is to make a device which can detect if a fire alarm is triggered and then send a text message through gsm to the respective owner.

This is GPL code.

## Current implemented features
* serial interface which can handle strings.
* a function to check for valid strings.
* a function to execute commands.

## Planned features
* GSM implementation to take commands and to send SMS.
* A system to detect fire alarms.

## Current commands
* set.id xxxx: sets id for the device
* set.# xxxx: sets the phone number which the device will communicate to.
* start: allows the device to send SMS.
* stop : prohibits the device to send SMS.
* status: reports status, device id and phone number.
