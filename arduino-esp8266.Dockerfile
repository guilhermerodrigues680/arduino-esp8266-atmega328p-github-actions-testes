FROM ubuntu:18.04

WORKDIR /opt

RUN \
    apt update && apt install -y wget xz-utils git python3 vim nano htop && \
    wget https://downloads.arduino.cc/arduino-1.8.12-linux64.tar.xz && \
    tar -xf arduino-1.8.12-linux64.tar.xz && \
    rm -rf arduino-1.8.12-linux64.tar.xz && \
    cd arduino-1.8.12 && \
    ./install.sh && \
    which arduino && \
    ls -la $(which arduino) | grep 'arduino'

WORKDIR /root/Arduino

RUN \
    printf "\n Local do Sketchbook: \n" && \
    arduino --get-pref | grep 'ske' && \
    printf "\n" && \
    pwd && \
    mkdir hardware && cd hardware && mkdir esp8266com && cd esp8266com && \
    git clone https://github.com/esp8266/Arduino.git esp8266 && \
    cd esp8266 && \
    git checkout 2.6.3 && \
    git submodule update --init && \
    cd tools && \
    python3 get.py

WORKDIR /root

CMD [ "bash" ]

# Execute:
# docker build --tag ubuntu-arduino-compiler:0.1 .
# docker run -it --name ubc ubuntu-arduino-compiler:0.1