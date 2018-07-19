#include "sentera.h"

void sentera::sentera() {
  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset((char *)&address, 0, sizeof(address));

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(IP); // this is address of host which I want to send the socket
	address.sin_port = htons(atoi(PORT));


	printf("handle: %d\n", sock); // prints number greater than 0 so I assume handle is initialized properly

	if (bind(sock, (const struct sockaddr*) &address, sizeof(struct sockaddr_in)) < 0)
	{
		printf("failed to bind socket (%s)\n", strerror(errno)); // Cannot assign requested address
	}
}

void sentera::~sentera() {

}

// Send start capture command
void sentera::startCapture() {

}

// Return null if no data available yet, url otherwise
std::string sentera::getCaptureUrl() {

}

// Using url, grab the image then transmit it
void sentera::getImageAndTransmit() {

}

// Capture and transmit loop
void sentera::startCaptureAndTransmit() {
  while (1) {
    startCapture();
    std::string url = nullptr;
    while ((url = getCaptureUrl()) == nullptr);
    getImageAndTransmit(url);
  }
}

uint8_t* sentera::assemblePacket(uint8_t type, uint16_t length, uint8_t *payload) {
  uint8_t *packet = new packet[length + 2 + 2 + 1 + 1];
  packet[0] = HEADER_ZERO;
  packet[1] = HEADER_ONE;
  packet[2] = type;
  packet[3] = (length & 0xff);
  packet[4] = (length >> 8) & 0xff;

  uint8_t crc = 0;

  for (int i = 0; i < length; ++i) {
    uint8_t b = payload[i];
    packet[5 + i] = b;
    for (int bit = 7; bit >= 0; --bit) {
      if ((crc & 0x80) != 0) {   /* MSB set, shift it out of the register */
          crc = (uint8_t)(crc << 1);
          /* shift in next bit of input stream:
           * If it's 1, set LSB of crc to 1.
           * If it's 0, set LSB of crc to 0. */
          crc = ((uint8_t)(b & (1 << i)) != 0) ? (byte)(crc | 0x01) : (byte)(crc & 0xFE);
          /* Perform the 'division' by XORing the crc register with the generator polynomial */
          crc = (uint8_t)(crc ^ GENERATOR_POLYNOMIAL);
      } else {   /* MSB not set, shift it out and shift in next bit of input stream. Same as above, just no division */
          crc = (uint8_t)(crc << 1);
          crc = ((uint8_t)(b & (1 << i)) != 0) ? (byte)(crc | 0x01) : (byte)(crc & 0xFE);
      }
    }
  }
  packet[length + 2 + 2 + 1] = crc;
  return packet;
}
