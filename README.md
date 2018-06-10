# OpenHAB
This repository contains configuration files for my OpenHAB2 home automation system.

Included in this repository are details about my custom alarm system which integrates the ESP32/ESP8266 chipset with OpenHAB.  Included information contains all hardware and software schematics.

## How it all works
My family has several [Bravo5 motion detectors](http://www.dsc.com/alarm-security-products/BV-500GB,%20BV-501GB,%20BV-502GB%20-%20Bravo%C2%AE%205%20360%C2%B0%20Ceiling-Mount%20PIR%20Motion%20Detectors/76) in our home which were prevoisly interfaced with a standard unmonitored alarm system.  4-conductor cabling was ran from each sensor to the control board as well as to 2 keypads on the main and second floor of our home.  The 4-conductor cable delivers 12V to each sensor with a pair of wires.  The remaining pair of wires is connected to the internal relay contact of the motion sensor which are electrically connected by the relay when motion is detected.  I have these sensors interfaced with my ESP8266 via optocouplers so that the 12V signal from the sensor does not fry the ESP which operates on 3.3V.  To replace the 2 keypads in our home I opted to use Amazon Fire tablets and HABPanel.  This solution proves cost-effective, simple to impliment, and elegant.  I used to 4-conductor cable going to these locations to pass 12V to these [USB charging adapters](https://smile.amazon.com/gp/product/B07121W7Q4/ref=oh_aui_search_detailpage?ie=UTF8&psc=1) to keep the tablets supplied with a charge.  I followed [this guide on YouTube](https://www.youtube.com/watch?v=DBfwKYFbbb8) to get the tablets running the HABPanel interface.  Beware, however, that Fire tablets don't allow you to unlock them via Tasker which basically means that you can't have the tablets automatically lock and unlock when there's motion.  I just have mine setup so that the screen is contantly on and never locks. The system logic occurs on the OpenHAB side, so the ESP8266 is simply reporting motion to OpenHAB and receiving commands when to trigger the siren relay.  Connected to the siren relay is this [Elk siren driver board](https://www.homecontrols.com/ELK-Two-Channel-Siren-Driver-Module-ELK101) which has a "chirp" and "constant" tone setting.

## HABPanel
- The passcode input is interfaced though the "Universal Keypad widget" which I have linked to the alarmKeypadInput item 
- Several "Attention with Button" widgets display the alarm status and zone status for each sensor.  
- "Selection" widiget with "Arm=Arm,Chime=Chime,Triggered=Manual Trip" as my list of comma-separated choices to control the alarm mode
- Button to control the lights on the main level of my home
- Button and "Attention with Button" to control and display the status of my garage  

## My PCB design files
The PCB files in this repository feature a board which can interface with up to 4 motion sensors and 1 relay.  The board takes a 12V 5A power supply via a standard DC power-jack.  The design features 4 M3 mounting holes, 1 power LED connected to the 3.3V line, 1 LED connected to D5, and a screw-terminal connected to 12V which I have used to connect to the 4-conductor cabling to run power to the tablets.  You can, obviously, modify the design to meet your own specifications.

## BOM for PCB (links to DigiKey and AmazonSmile)
For the PCB itself you will need:
 - [1x DC Jack](https://www.digikey.com/product-detail/en/cui-inc/PJ-102AH/CP-102AH-ND/408448)
 - [Non-stackable female headers](https://smile.amazon.com/Straight-Female-Header-Spacing-Connector/dp/B00TGOJE1W/ref=sr_1_7?ie=UTF8&qid=1528657475&sr=8-7&keywords=female+headers)
 - [1x ESP8266](https://smile.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B010O1G1ES/ref=sr_1_1_sspa?s=electronics&ie=UTF8&qid=1528657504&sr=1-1-spons&keywords=esp8266&psc=1)
 - [1x 2-pin 3.5mm screw terminal](https://www.digikey.com/product-detail/en/phoenix-contact/1984617/277-1721-ND/950849)
 - [1x 12V to 5V regulator](https://smile.amazon.com/DROK-Regulator-Converter-Step-down-Transformer/dp/B0758ZTS61/ref=sr_1_10?ie=UTF8&qid=1528657574&sr=8-10&keywords=12v+to+5v+converter)
 - [2x 68 ohm 0603 resistors](https://www.digikey.com/product-detail/en/rohm-semiconductor/ESR03EZPJ270/RHM27DCT-ND/4053754)
 - [2x 0805 leds](https://www.digikey.com/product-detail/en/lite-on-inc/LTST-C170KFKT/160-1413-1-ND/386774)
 
 
For each sensor you wish to interface with you will need:
 - [1x PCB screw terminal connector](https://smile.amazon.com/gp/product/B01M5FARN8/ref=oh_aui_search_detailpage?ie=UTF8&psc=1)
 - [1x PC817 optocoupler](https://smile.amazon.com/gp/product/B06X6M2NNY/ref=oh_aui_search_detailpage?ie=UTF8&psc=1)
 - [1x 0603 10k ohm resistor](https://www.digikey.com/product-detail/en/rohm-semiconductor/ESR03EZPJ103/RHM10KDCT-ND/1762925)
 - [1x 0603 1k ohm resistor](https://www.digikey.com/product-detail/en/rohm-semiconductor/ESR03EZPF1001/RHM1.00KADCT-ND/1983752)
 - [1x RB715S SMD diode](https://www.digikey.com/product-detail/en/rohm-semiconductor/RB751S-40TE61/RB751S-40TE61CT-ND/650794)
 
For each relay trigger you wish to interface with you will need:
 - [1x PC817 optocoupler](https://smile.amazon.com/gp/product/B06X6M2NNY/ref=oh_aui_search_detailpage?ie=UTF8&psc=1)
 - [2x 0603 100 resistor](https://www.digikey.com/product-detail/en/rohm-semiconductor/ESR03EZPJ101/RHM100DCT-ND/1983776)
 - [1x RB715S SMD diode](https://www.digikey.com/product-detail/en/rohm-semiconductor/RB751S-40TE61/RB751S-40TE61CT-ND/650794)
 - [1x 2N3904 transistor](https://smile.amazon.com/gp/product/B008IFYBWW/ref=oh_aui_search_detailpage?ie=UTF8&psc=1)
 - [1x relay](https://www.digikey.com/product-detail/en/omron-electronics-inc-emc-div/G5LE-1-DC5/Z1014-ND/280368)
 - [1x 2-pin 3.5mm screw terminal](https://www.digikey.com/product-detail/en/phoenix-contact/1984617/277-1721-ND/950849)


## How to make custom sound effects: 
In my my alarmController.rules file you may have noticed that I have several sound files which I reference.  These files are contained within my "sounds" folder in my OpenHAB configuration on my Raspberry Pi.  These files are a combination of sound effects I complied using a YouTube to MP3 converter and [Siri text-to-speech using the "say" function](https://www.lifewire.com/mac-say-command-with-talking-terminal-2260772) through Terminal on my Mac.  I cannot upload the sound files here due to copyright restrictions, however, you would likely want to make your own custom sound effects anyways.  Here are what mine are:  
- chime.mp3 - A mellow single-tone "blip" noise  
- incorrect.mp3 - Agressive error noise  
- armed.mp3 - A mellow 2-tone "bing" noise followed by "Hello, system is armed"  
- welcome.mp3 - A mellow 2-tone "bing" noise followed by "Hello, system disarmed"  
- alarm triggered.mp3 - "Danger" followed by agressive siren alert tone  
