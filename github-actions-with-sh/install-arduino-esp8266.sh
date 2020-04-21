#!/bin/bash

# Mesmo código do dockerfile, porem em SH

sudo apt-get -q update && sudo apt-get install -q -y wget xz-utils && \
sudo wget -q https://downloads.arduino.cc/arduino-1.8.12-linux64.tar.xz -P /opt && \
sudo tar -xf /opt/arduino-1.8.12-linux64.tar.xz -C /opt && \
sudo rm -rf /opt/arduino-1.8.12-linux64.tar.xz && \
sudo sh /opt/arduino-1.8.12/install.sh && \
command -v arduino && ls -lah /usr/local/bin/arduino

mkdir -p /root/Arduino/hardware/esp8266com/esp8266
cd /root/Arduino/hardware/esp8266com/esp8266

sudo apt-get -q update && apt-get install -q -y git python3 && \
git clone https://github.com/esp8266/Arduino.git . && \
git checkout 2.6.3 && \
git submodule update --init && \
(cd tools && python3 get.py) > /dev/null 2>&1

arduino --get-pref | grep 'ske'