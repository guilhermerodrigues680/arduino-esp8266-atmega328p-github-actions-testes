FROM debian:stretch-slim

# Instalar arduino IDE
# apt-get -qq
RUN apt-get -q update && apt-get install -q -y wget xz-utils && \
    wget -q https://downloads.arduino.cc/arduino-1.8.12-linux64.tar.xz -P /opt && \
    tar -xf /opt/arduino-1.8.12-linux64.tar.xz -C /opt && \
    rm -rf /opt/arduino-1.8.12-linux64.tar.xz && \
    sh /opt/arduino-1.8.12/install.sh && \
    command -v arduino && ls -lah /usr/local/bin/arduino && \
    apt-get -q purge -y wget xz-utils && \
    apt-get -q clean -y && apt-get -q autoremove -y && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /root/Arduino/hardware/esp8266com/esp8266
# > /dev/null 2>&1
RUN apt-get -q update && apt-get install -q -y git python3 && \
    git clone https://github.com/esp8266/Arduino.git . && \
    git checkout 2.6.3 && \
    git submodule update --init && \
    (cd tools && python3 get.py) && \
    apt-get -q clean -y && apt-get -q autoremove -y && \
    rm -rf /var/lib/apt/lists/*

# Return WORKDIR to /
WORKDIR /

# Print Sketchbook Default Location
SHELL ["/bin/bash", "-o", "pipefail", "-c"]
RUN arduino --get-pref | grep 'ske'

# CMD [ "bash" ]

# Copia o arquivo de código do repositório de ação para o WORKDIR atual
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Arquivo de código a ser executado quando o contêiner do docker é iniciado (`entrypoint.sh`)
ENTRYPOINT ["/entrypoint.sh"]