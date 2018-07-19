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
    while ((url = getCaptureUrl()_ == nullptr);
    getImageAndTransmit(url);
  }
}

uint8_t* sentera::assemblePacket(uint8_t type, uint16_t length, uint8_t *payload) {

}
