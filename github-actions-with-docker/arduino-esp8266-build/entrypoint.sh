#!/bin/bash

# Set Sketchbook Default Location
cd /root/Arduino

echo "\$0 = $0"
echo "\$1 = $1"
echo "\$2 = $2"
echo "\$3 = $3"

time=$(date)
echo "::set-output name=time::$time"

# repository_github="$1"
# path_ino_file="$2"
# ino_file="$3"

git clone "https://github.com/$1.git" repository
cd "repository/$2"

arduino -v --board esp8266com:esp8266:nodemcu --verify $3