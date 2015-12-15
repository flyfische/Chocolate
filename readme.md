#Arduino Chocolate Tempering Machine
I created this to temper chocolate.  It uses a relay to power a crock pot (slow cooker) that is monitored via a temperature sensor.  It uses the following recipe, but can easily be configured:

Heat 2/3 of chocolate 120*F
Add last 1/3 of chocolate and cool to 82*F
Rewarm to at least 87* but not exceeding 89*

#Dependencies

This uses the LiquidCrystal library to print to a 16x2 lcd, indicating status and current temperature.

The DallasTemperature is used to communicate with the OneWire temperature sensor.

The temperature sensor used is a DS18b20.  It's covered in a waterproof sleeve.

I used an arduino uno and a standard relay.  It's all housed in a plastic junction box.