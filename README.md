# hand-grip-heart-rate-monitor
This repo contains an Arduino program to calculate heart rate from the analog signal of a Vernier hand grip sensor.  
This is part of the final project of the *Electronic Devices for Biomedical Design* course (HCMIU VNU-HCMC, Sep 2020 - Jan 2021).  
Tutorial at https://www.vernier.com/engineering/arduino/arduino-online-guide/connecting-vernier-sensors-to-arduino/  

What the program does:
1. Take analog input from the Vernier sensor
2. Detect peaks
3. Calculate heart rate (is the mean period between each peak) with filtering and dampening to smoothen results
4. Output heart rate