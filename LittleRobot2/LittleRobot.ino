#include <PID_v1.h>
#include <Encoder.h>

// Straight speeds when going forwards: 200 / 170
#include <SoftwareSerial.h>

bool stopped = false;
bool remoteMode = false;
bool crooked = false;

SoftwareSerial mySerial(10, 11); // RX, TX
int qtrValues[] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  defineQtr();
  defineMotors();
  setDirection('f');
  initQtrPid();
  initEncoderPid();
  delay(100); // QTR reads 11111111 if read immediately after the robot is turned on. Delay prevents that.
}

void loop() {
  if (!crooked) {
    setMotors(100, 240);
    delay(2000);
    crooked = true;
  }
  printEncoderPidValues();
  executeEncoderPid();
  /*
    readQtrConstantsFromSerial();
    if (stopped) {
      return;
    }
    readQtr();
    executeQtrPid();
    if (isLineCompletelyWhite())
    {
      stopMotors();
      stopped = true;
    }
  */
  /*
    straightTest();
    mySerial.println("done");
    delay(10000);
  */
}
