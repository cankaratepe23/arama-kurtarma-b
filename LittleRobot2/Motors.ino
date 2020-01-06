#define in1 38
#define in2 39
#define in3 40
#define in4 41

#define enA 44 // Sağ Motor
#define enB 45 // Sol Motor

#define leftBaseSpeed 200
#define rightBaseSpeed 170

void defineMotors()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(enA, OUTPUT);
}

void setDirection(char dir)
{
  if (dir == 'f')
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if (dir == 'b')
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if (dir == 'r')
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else if (dir == 'l')
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}

void setMotors(int left, int right)
{
  if (left < 0)
  {
    left = 0;
  }
  if (right < 0)
  {
    right = 0;
  }
  if (left > 255)
  {
    left = 255;
  }
  if (right > 255)
  {
    right = 255;
  }
  analogWrite(enB, left);
  analogWrite(enA, right);
  //printMotorStatus(left, right);
}

void printMotorStatus(int left, int right)
{
  mySerial.print("Set motors left: ");
  mySerial.print(left);
  mySerial.print(" right: ");
  mySerial.println(right);
}

void stopMotors()
{
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
