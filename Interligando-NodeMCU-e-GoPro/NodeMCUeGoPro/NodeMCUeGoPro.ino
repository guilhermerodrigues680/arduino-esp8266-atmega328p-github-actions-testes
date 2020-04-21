/*
   Este sketch criar um WebServer Simples (HTTP-like)
   Este serve muda o estado do LED_BUILTIN
*/

#include <ESP8266WiFi.h>//Biblioteca que gerencia o WiFi.
#error "Meu erro 1"
#error  Meu erro 2
#error "Meu erro 3"
#error  Meu erro 4
#error "Meu erro 5"
#error  Meu erro 6
#error "Meu erro 7"
#error  Meu erro 8
#error "Meu erro 9"
#include <WiFiUDP.h> //Biblioteca necessaria para Wake On Lan
const char* ssid = "Gui__GoPro"; //Rede
const char* password = "99982965"; //Senha
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Conectar na rede WiFi
  Serial.print("\n\n Conectando em "); Serial.print(ssid);
  WiFi.mode(WIFI_STA); //Habilita o modo STATION.
  WiFi.begin(ssid, password);//Conecta no WiFi

  uint8_t tentativa = 0;
  while (WiFi.status() != WL_CONNECTED && tentativa++ < 100) {
    delay(500);
    Serial.print("\n Tentativa ");
    Serial.print(tentativa);
    for (int i = 0; i < tentativa; i++) {
      Serial.print(".");
    }
  }
  if (tentativa >= 100) {
    Serial.print("Impossivel conectar em"); Serial.println(ssid);
    Serial.println("Reinicie o NodeMCU e tente Novamente");
    while (true) {
      delay(500);
    }
  }

  Serial.println("\n WiFi connected");

  server.begin(); // Inicia o servidor
  Serial.print(" Servidor Iniciado, IP: ");
  Serial.println(WiFi.localIP()); // Imprimir o endereço IP do NodeMCU

  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
}

void loop() {
  //http();
  comandoGoPro();
}

void comandoGoPro() {
  delay(8000);
  Serial.println("******************************");
  const char* host = "10.5.5.9";

  Serial.print(" Realizando conexao com o host da GoPro: "); Serial.println(host);

  WiFiClient client; // Use WiFiClient class to create TCP connections
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println(" Falha na conexão");
    ligarGoPro();
    return;
  }
  Serial.println(" Conexao OK!");

  // We now create a URI for the request
  String url = "";
  //url += "/gp/gpControl/setting/2/1"; //Resolucao video 4K
  //url += "/gp/gpControl/status"; //Obter Status Camera
  url += "/gp/gpControl/command/system/sleep";
  /*url += "/input/";
    url += streamId;
    url += "?private_key=";
    url += privateKey;
    url += "&value=";
    url += value;*/

  Serial.print(" Requesting URL: "); Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  //Aguarda retorno do cliente
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(" >>> Client Timeout !");
      client.stop();
      return;
    }
  }

  //Le todas as linha de resposta que o servidor envia (Response Headers) e printa no serial
  Serial.print("\n Retorno do cliente: \n  | \n \\/ \n......................\n");
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
    lerStatusGoPro(line);
  }
  Serial.println("......................");

  Serial.println("\nFechando Conexao\n");
}

void lerStatusGoPro(String leitura){
  
  int indexBateria = leitura.indexOf("\"1\":"); //O indexBateria pode ser ultilizado com verficador inicial tambem
  
  if ( indexBateria != -1) { //0 = Nao tem bateria, 1 = Bateria Disponivel
    Serial.print("Status Bateria GoPro: ");
    Serial.print((leitura.substring(indexBateria + 1,indexBateria + 2).toInt()) == 0 ? "Sem Bateria\n" : "Bateria Disponivel\n");
  }

  int indexModoP = leitura.indexOf("\"43\":");
  if ( indexBateria != -1 && indexModoP != -1) { //0 = Video, 1 = Foto, 2 = Timelapse
    Serial.print((leitura.substring(indexModoP + 1,indexModoP + 2).toInt()) == 0 ? "Video\n" : (leitura.substring(indexModoP + 1,indexModoP + 2).toInt()) == 2 ? "Foto\n" : "MultiShot\n");
  }
}

void ligarGoPro() {
  //Wake on lan GoPro
  WiFiUDP UDP;
  IPAddress computer_ip(255, 255, 255, 0); //Subnet Mask GoPro '255.255.255.0'
  byte mac[] = { 0xD4, 0xD9, 0x19, 0xB9, 0xAC, 0x63 }; //Endereco MAC GoPro 'd4d919b9ac63'

  Serial.println("\t** Ligando GoPro **");
  UDP.begin(9); //start UDP client, not sure if really necessary.
  for (int i = 1; i <= 10; i++) {
    Serial.print(i); Serial.print("º Pacote. \tEnviando pacote WOL...\t");
    sendWOL(computer_ip, UDP, mac, sizeof mac);
    Serial.println("Pacote Enviado.");
    delay(250);
  }
}

void sendWOL(IPAddress addr, WiFiUDP udp, byte * mac,  size_t size_of_mac) {

  byte preamble[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  byte i;

  udp.beginPacket(addr, 9); //sending packet at 9,
  
  udp.write(preamble, sizeof preamble);
  
  for (i = 0; i < 16; i++)
  {
    udp.write(mac, size_of_mac);
  }
  udp.endPacket();
}

void http() {
  WiFiClient client = server.available(); //Checa se tem um Cliente conectado
  if (!client) {
    return;
  }
  Serial.println("------------------------------");
  Serial.println("Novo Cliente!");

  while (!client.available()) {// Wait until the client sends some data
    delay(1);
  }
  String req = client.readStringUntil('\r'); //Read the first line of the request
  Serial.print("Request: ");  Serial.println(req);
  client.flush();

  //Analisando o request
  int val;
  //Verifica se existe o trecho de texto no request, se não, retorna -1
  if (req.indexOf("/gpio/0") != -1) {
    val = 0;
  } else if (req.indexOf("/gpio/1") != -1) {
    val = 1;
  } else {
    Serial.println("invalid request");
    client.flush();
    client.print(urlError());
    //client.stop();
    return;
  }

  digitalWrite(LED_BUILTIN, val); // Set LED_BUILTIN according to the request
  client.flush();
  client.print(urlStatus(val)); // Send the response to the client
  delay(1);
  //cliente.stop();//Encerra a conexao.
  Serial.println("Cliente desconectado\n");
  /*
     Chega no final do loop e o cliente é desconectado
     devido o loop retornar para o inicio automaticamente
     e o Objeto 'client ser destruido'
  */
}

String urlStatus(boolean onOff) { // Montan a resposta em HTML
  /*String s = "";
    s += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
    s += (val) ? "high" : "low";
    s += "</html>\n"; */

  String url = "";
  //Inicio e identificação do codigo HTML
  url += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";//Identificaçao do HTML.
  url += "<!DOCTYPE html><html><head><title>ESP8266 Gui - WebServer</title>";//Identificaçao e Titulo.
  url += "<meta name='viewport' content='user-scalable=no'>";//Desabilita o Zoom.
  url += "<style>h1{font-size:18px;color:red;}</style></head>";//Cria uma nova fonte de tamanho e cor X.
  //Corpo do codigo HTML
  url += "<body bgcolor='ffffff'><center><h1>O led da placa esta: ";
  url += (onOff == 1) ? "HIGH" : "LOW";
  url += "</h1></center></body></html>"; //Fechamento das TAG's
  /*
    s += "<form action='/LED' method='get'>";//Cria um botao GET para o link /LED
    s += "<input type='submit' value='LED' id='frm1_submit'/></form>";

    s += "</h1></center></body></html>";//Termino e fechamento de TAG`s do HTML. Nao altere nada sem saber!
  */

  return url;
}

String urlError() { //Essa função gera uma String para quando o usuario acessar uma Url não configurada
  String url = "";
  //Inicio e identificação do codigo HTML
  url += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";//Identificaçao do HTML.
  url += "<!DOCTYPE html><html><head><title>ESP8266 Gui - WebServer</title>";//Identificaçao e Titulo.
  url += "<meta name='viewport' content='user-scalable=no'>";//Desabilita o Zoom.
  url += "<style>h1{font-size:18px;color:red;}</style></head>";//Cria uma nova fonte de tamanho e cor X.
  //Corpo do codigo HTML
  url += "<body bgcolor='ffffff'><center><h1>Link quebrado :( <br> Por favor verifique o endereco procurado.";
  url += "</h1></center></body></html>"; //Fechamento das TAG's

  return url;
}
