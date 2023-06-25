# Grill-Thermometer
Using the G070 board and the class PCB, created a grill thermometer that can measure from just above freezing to 150DegC minimum.

Using the PCB mounted thermistor for cold junction measurement from -10DegC to 50DegC and the meat probe Thermocouple for internal temperature, ensured calibration and used the PCB mounted EEPROM for storage of the calibration constants.

Created a UI to select target temperatures, display current temperature/settings, and context for grill thermometer such as meat type and target "doneness" along with Temp. 

Calibration done through the UI, serial port, or debugger (debugger will require some way to write to EEPROM through code execution).

Used the beeper when the food is "done" and any "advanced functions" (e.g. "rest anticipation" where "done" assumes some temperature increase) are optional.
