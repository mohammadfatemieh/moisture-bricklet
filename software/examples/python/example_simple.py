#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_moisture import Moisture

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    m = Moisture(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Get current moisture value
    moisture = m.get_moisture_value()

    print('Moisture Value: ' + str(moisture))

    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()