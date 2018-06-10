# OpenHAB
This repository contains configuration files for my OpenHAB2 home automation system.

Included in this repository are details about my custom alarm system which integrates the ESP32 chipset with OpenHAB.  Included information contains all hardware and software schematics.  
  
  
  
How to make custom sound effects:  
In my my alarmController.rules file you may have noticed that I have several sound files which I reference.  These files are contained within my "sounds" folder in my OpenHAB configuration on my Raspberry Pi.  These files are a combination of sound effects I complied using a YouTube to MP3 converter and Siri text-to-speech using the "say" function through Terminal on my Mac.  I cannot upload the sound files here due to copyright restrictions, however, you would likely want to make your own custom sound effects anyways.  Here are what mine are:  
chime.mp3 - A mellow single-tone "blip" noise  
incorrect.mp3 - Agressive error noise  
armed.mp3 - A mellow 2-tone "bing" noise followed by "Hello, system is armed"  
welcome.mp3 - A mellow 2-tone "bing" noise followed by "Hello, system disarmed"  
alarm triggered.mp3 - "Danger" followed by agressive siren alert tone  
