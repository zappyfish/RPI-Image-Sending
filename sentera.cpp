#include <stdio>

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
