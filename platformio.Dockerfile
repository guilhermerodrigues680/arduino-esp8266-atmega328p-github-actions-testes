FROM python:3.7-slim-stretch

RUN \
    pip3 install -U platformio && \
    platformio update

# Instalar ferramentas basicas e ohmyzsh
RUN \
    apt update && apt install -y wget zsh git vim nano htop && \
    sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

WORKDIR /root

CMD [ "zsh" ]

# Execute:
# docker build --tag plarformio:0.1 --file platformio.Dockerfile .
# docker run -it --name pla platformio:0.1