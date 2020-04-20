import os
import re

CMD_COMPILAR_INO = 'arduino --board esp8266com:esp8266:nodemcu --verify Interligando-NodeMCU-e-GoPro/NodeMCUeGoPro/NodeMCUeGoPro.ino 2>&1'
output = os.popen(CMD_COMPILAR_INO).read()

# output = (
#     "Picked up JAVA_TOOL_OPTIONS: \n"
#     "Loading configuration...\n"
#     "Initializing packages...\n"
#     "Preparing boards...\n"
#     "Verifying...\n"
#     'NodeMCUeGoPro:7:2: error: #error "erro aqu"\n'
#     '#error "erro aqu"\n'
#     '^\n'
#     "NodeMCUeGoPro:7:62: fatal error: WiFiUDP.h: No such file or directory\n"
#     "#include <WiFiUDP.h> //Biblioteca necessaria para Wake On Lan\n"
#     "                                                            ^\n"
#     "compilation terminated.\n"
#     "exit status 1\n"
# )

print("Output: ")
print(output)

# matchs = re.findall(r'(.*):(.*):(.*):(.*):(.*)', output, re.M|re.I)
matchs = re.findall(r'(.*):([0-9]*):([0-9]*): (.*error:) (.*)', output)

if matchs:
    # print(matchs.group(2))
    print('Matchs: ')
    for match in matchs:
        print(match)
else:
    print('Sem resultados')