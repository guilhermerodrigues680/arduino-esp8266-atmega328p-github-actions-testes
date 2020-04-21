

sudo apt-get -q update && sudo apt-get install -q -y wget xz-utils && \
sudo wget -q https://downloads.arduino.cc/arduino-1.8.12-linux64.tar.xz -P /opt && \
sudo tar -xf /opt/arduino-1.8.12-linux64.tar.xz -C /opt && \
sudo rm -rf /opt/arduino-1.8.12-linux64.tar.xz && \
sudo sh /opt/arduino-1.8.12/install.sh && \
command -v arduino && ls -lah /usr/local/bin/arduino && \
apt-get -q purge -y wget xz-utils && \
apt-get -q clean -y && apt-get -q autoremove -y && \
rm -rf /var/lib/apt/lists/*