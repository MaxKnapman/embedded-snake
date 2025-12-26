# embedded-snake
Snake game for Arduino

Current state:
- circuit prototype complete
- code is incomplete but getting there
- there's not a lot of ram to work with on the nano

TODO:
- make and upload circuit diagram
- what happens when we die?
- don't allow out of bounds
- figure out what to do about memory constraints

Notes:
- this runs on an arduino nano with an ssd1315 oled screen using i2c
- four buttons wired up to digital pins with the internal pullup resistor to control movement(pins in code comments)
