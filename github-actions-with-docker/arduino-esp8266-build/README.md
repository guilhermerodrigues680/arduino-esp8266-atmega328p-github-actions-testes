### Exemplos

```sh
# A ultima versao da imagem
docker run guilhermerodrigues680/arduino-esp8266-build "guilhermerodrigues680/Interligando-NodeMCU-e-GoPro" "NodeMCUeGoPro" "NodeMCUeGoPro.ino"
docker run guilhermerodrigues680/arduino-esp8266-build:latest "guilhermerodrigues680/Interligando-NodeMCU-e-GoPro" "NodeMCUeGoPro" "NodeMCUeGoPro.ino"
# Versao especifica da imagem
docker run guilhermerodrigues680/arduino-esp8266-build:v1 "guilhermerodrigues680/Interligando-NodeMCU-e-GoPro" "NodeMCUeGoPro" "NodeMCUeGoPro.ino"
docker run guilhermerodrigues680/arduino-esp8266-build:v1.1 "guilhermerodrigues680/Interligando-NodeMCU-e-GoPro" "NodeMCUeGoPro" "NodeMCUeGoPro.ino"
```

```sh
# ERROR
docker run guilhermerodrigues680/arduino-esp8266-build "guilhermerodrigues680/atmega328p-arduino-python-html-websocker-led13" "src" "main.c"
```

```sh
docker run guilhermerodrigues680/arduino-esp8266-build:v1.2 "guilhermerodrigues680/Arduino-Pre-Processador-C" "arduino_pre_processador" "arduino_pre_processador.ino" "esp8266com:esp8266:nodemcu"

docker run guilhermerodrigues680/arduino-esp8266-build:v1.2 "guilhermerodrigues680/Arduino-Pre-Processador-C" "arduino_pre_processador" "arduino_pre_processador.ino" "arduino:avr:uno"

docker run guilhermerodrigues680/arduino-esp8266-build:v1.2 "guilhermerodrigues680/Arduino-Pre-Processador-C" "arduino_pre_processador" "arduino_pre_processador.ino" "arduino:avr:nano:cpu=atmega168"
```

```sh
docker run guilhermerodrigues680/arduino-esp8266-build:v1.2 "arduino/tutorials" "Arduino101HeartRateMonitor" "Arduino101HeartRateMonitor.ino" "arduino:avr:uno"
```

### VERSAO 1.2

```Dockerfile
FROM guilhermerodrigues680/arduino-esp8266-build:v1.1
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
```

```sh
#!/bin/bash

# Set Sketchbook Default Location
cd /root/Arduino

echo "\$0 = $0"
echo "\$1 = $1"
echo "\$2 = $2"
echo "\$3 = $3"
echo "\$4 = $4"

time=$(date)
echo "::set-output name=time::$time"

# repository_github="$1"
# path_ino_file="$2"
# ino_file="$3"
# board="$3"

git clone "https://github.com/$1.git" repository
cd "repository/$2"

arduino -v --board $4 --verify $3
```