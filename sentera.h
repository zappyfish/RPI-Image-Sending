#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define IP "192.168.143.141"
#define PORT "8080"

#define HEADER_ZERO 0x46
#define HEADER_ONE 0x57
#define GENERATOR_POLYNOMIAL 0x87 // This might have to be 0x07??

class sentera {
public:
  void sentera()
  void ~sentera()
  void startCaptureAndTransmit();
private:
  void startCapture();
  std::string getCaptureUrl();
  void getImageAndTransmit();

  uint8_t* assemblePacket(uint8_t type, uint16_t length, uint8_t *payload);

  transmit transmitter;

}
