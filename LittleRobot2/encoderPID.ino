double encoderKp = 6, encoderKd = 1, encoderKi = 2;
// 23 7 8
double encoderInput, encoderOutput, encoderSetpoint = 0;

PID encoderPID(&encoderInput, &encoderOutput, &encoderSetpoint, encoderKp, encoderKi, encoderKd, DIRECT);

void initEncoderPid()
{
  encoderPID.SetMode(AUTOMATIC);
  encoderPID.SetOutputLimits(-200, 200);
}

void computeEncoderInput()
{
  encoderInput = encoderLeft.read() - encoderRight.read();
  encoderInput /= 4;
//  if (abs(encoderInput) < 200) {
//    encoderInput = 0;
//  }
}

void executeEncoderPid()
{
  computeEncoderInput();
  encoderPID.Compute();
  setMotors(leftBaseSpeed + encoderOutput, rightBaseSpeed - encoderOutput);
}

void printEncoderPidValues()
{
  Serial.print("Encoder Input: ");
  Serial.print(encoderInput);
  Serial.print(" | Output: ");
  Serial.println(encoderOutput);
}
