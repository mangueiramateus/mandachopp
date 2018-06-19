#!/usr/bin/env python

from lib_oled96 import ssd1306
from PIL import ImageFont
from smbus import SMBus


i2cbus = SMBus(1)        # 1 = Raspberry Pi but NOT early REV1 board

oled = ssd1306(i2cbus)   # create oled object, nominating the correct I2C bus, default address

# we are ready to do some output ...

# put border around the screen:
oled.canvas.rectangle((0, 0, oled.width-1, oled.height-2), outline=1, fill=0)

# Write two lines of text.
font = ImageFont.truetype('FreeMonoBold.ttf', 16)
oled.canvas.text((10,0),    'MANDA CHOPP', fill=1, font = font)
font = ImageFont.truetype('FreeSans.ttf', 20)
oled.canvas.text((0,12),   'T', fill=1, font = font)
oled.canvas.text((0,28),   'T', fill=1, font = font)
oled.canvas.text((0,44),   'T', fill=1, font = font)


# now display that canvas out to the hardware
oled.display()
