#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, X, X); // CAMBIAR A LA IP DESEAD
EthernetServer server(X); // CAMBIAR AL PUERTO DESEADO
const int pinRELE = 7;

void setup()
{
  // Conecto Arduino
  Serial.begin(9600);

  // Conecto red
  Ethernet.begin(mac, ip);
  server.begin();

  // Conecto rele
  pinMode(pinRELE, OUTPUT);

  // Desactivo rele
  digitalWrite(pinRELE, HIGH);
}

void loop()
{
  EthernetClient client = server.available();
  if (client)
  {
    // Envio respuesta
    client.println(F("HTTP/1.1 200 OK\nContent-Type: text/plain"));

    // Cierro conexion
    client.stop();

    // Activo rele
    digitalWrite(pinRELE, LOW);

    // Espero
    delay(500);

    // Desactivo rele
    digitalWrite(pinRELE, HIGH);
  }
}
