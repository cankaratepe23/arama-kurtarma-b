Encoder encoderLeft(18, 19);
Encoder encoderRight(20, 21);

const double perimeterOfWheel = 4.687 * PI;
const double shaftConstant = 297.92;
const int magneticPoles = 12;
const double step2cmConstant = perimeterOfWheel / (shaftConstant * magneticPoles);

void testEncoder()
{
  Serial.print(encoderLeft.read());
  Serial.print(" | ");
  Serial.println(encoderRight.read());
}

double distanceMeasure(char wheel) {
  double distanceTravelled;
  if (wheel == 'l') {
    distanceTravelled = encoderLeft.read() * step2cmConstant;
  }
  else if (wheel == 'r') {
    distanceTravelled = encoderRight.read() * step2cmConstant;
  }
  return distanceTravelled;
}

void resetEncoders()
{
  encoderLeft.write(0);
  encoderRight.write(0);
}

void go(double dist)
{
  while (distanceMeasure('l') < dist)
  {
    executeEncoderPid();
  }
  stopMotors();
  resetEncoders();
}
