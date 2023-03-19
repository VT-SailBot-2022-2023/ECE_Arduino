void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  Serial3.begin(115200);
}

void loop() { // run over and over
  if (Serial3.available()) {
    Serial.write(Serial3.read());
  }
}
