import os

g = os.popen('arduino --board esp8266com:esp8266:nodemcu --verify Interligando-NodeMCU-e-GoPro/NodeMCUeGoPro/NodeMCUeGoPro.ino').read()

print("G é: ")
print(g)