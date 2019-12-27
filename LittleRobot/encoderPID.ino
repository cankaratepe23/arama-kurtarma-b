double encoderKp = 0, encoderKd = 0, encoderKi = 0;
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
}

void executeEncoderPid()
{
  computeEncoderInput();
  encoderPID.Compute();
  setMotors(leftBaseSpeed + encoderOutput, rightBaseSpeed - encoderOutput);
}
