

class sentera {
public:
  void startCaptureAndTransmit();
private:
  void startCapture();
  std::string getCaptureUrl();
  void getImageAndTransmit();

  transmit transmitter;
}
