# Controls

* Potentiometers
 - B10K
 - D Shaft
 - 6mm diameter
 - 7mm diameter hole
 - Vertical (not right-angle) orientation
 - https://www.mouser.com/ProductDetail/Alpha-Taiwan/RD901F-40-15F-B10K-00DL1?qs=1mbolxNpo8eEwO1hUJUOSQ%3D%3D
 - only available in q's of 1000+... fuckers

* Encoder
 - https://www.mouser.com/ProductDetail/Bourns/PEC11R-4215F-N0024?qs=Zq5ylnUbLm5g22exZGkf6w%3D%3D

* Buttons
 - https://www.mouser.com/ProductDetail/CK/D6C90F1LFS?qs=%2Fha2pyFadujMQpIh4h5pAhSY17avLfzRYcm%252BAJ9v%2FMtXgrU6ZAUxRw%3D%3D

* Knobs
 - https://www.thonk.co.uk/shop/1900h-d/
 - 16mm tall
 - 12mm diameter at base
 
 - These seem better https://www.thonk.co.uk/shop/intellijel-black-knobs/
 

* Displays
 - https://www.adafruit.com/product/938
 - PCB dimensions: 35.6mm/33mm
 - Display dimensions 1.3"/0.9"
 - Usable screen
 
 
 
 - Maybe this is better: https://www.digikey.com/product-detail/en/dfrobot/DFR0650/1738-DFR0650-ND/12324929
 - PCB dimensions: 30x30mm
 - Display dimensions: 0.86” x 0.42”
 
* Power Switch 
  - One of these guys, doesn't really matter I think:
	- https://www.mouser.com/Search/Refine?Keyword=R1966ABLKBLKA

* Status LEDs:
 - https://www.adafruit.com/product/778
 - 3mm diameter
 - 3.5mm hole?

* Chassis
  - https://www.circuitspecialists.com/rackmount-enclosure-37-2u.html


Front panel part counts:
  * Rotary Encoders: 2x
  * Potentiometers: 15x
	* https://www.thonk.co.uk/shop/alpha-9mm-pots-dshaft/
	* B25K - D shaft - Alpha Vertical 9mm Potentiometer
  * Volume Potentiometer: 1x
	* https://www.thonk.co.uk/shop/alpha-9mm-pots-dshaft/
	* A10K - DUAL GANG - D shaft - Alpha Vertical 9mm Potentiometer
  * Momentary Buttons: 14x
  * LEDs: 11x
  * Displays: 5x

Potentiometer Demux:
	- https://www.ti.com/lit/ds/symlink/cd74hct4067-q1.pdf?ts=1593413308238&ref_url=https%253A%252F%252Fwww.google.com%252F
	- Actually, should probably use 3x8 demux. 2 for buttons, 2 for pots, and share address line between all muxe's. means we can read 4 inputs per select => faster

Shift Register for driving LEDs:
	- https://media.digikey.com/pdf/Data%20Sheets/ST%20Microelectronics%20PDFS/STP16C596A.pdf
	- SPI interface... that's okay though
