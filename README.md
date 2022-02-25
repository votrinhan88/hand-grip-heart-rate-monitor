# hand-grip-heart-rate-monitor
 Arduino code for Vernier Hand grip Heart rate Monitor sensor

This repo is a final project of the course Electronic Devices for Biomedical Design (Sep 2020 - Jan 2021).
Tutorial at https://www.vernier.com/engineering/arduino/arduino-online-guide/connecting-vernier-sensors-to-arduino/

What the program does:
- Take analog input from the Vernier sensor
- Detect peaks
- Calculate heart rate (is the mean period between each peak) with filtering and dampening to smoothen signal
- Output heart rate and graph of analog signal