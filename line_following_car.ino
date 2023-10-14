// Define motor pins
#define M1 3  // Right Motor MA1
#define M2 4  // Right Motor MA2
#define M3 5  // Left Motor MB1
#define M4 6  // Left Motor MB2
#define E1 2  // Right Motor Enable Pin EA
#define E2 7  // Left Motor Enable Pin EB

// Define IR sensor pins
#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3
#define IR5 A4

// Define motor speed
#define MOTOR_SPEED 150

void setup() {
  // Set up motor and IR sensor pins
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
}

void moveRobot(int motor1, int motor2, int motor3, int motor4) {
  digitalWrite(M1, motor1);
  digitalWrite(M2, motor2);
  digitalWrite(M3, motor3);
  digitalWrite(M4, motor4);
}

void loop() {
  // Reading sensor values
  int s1 = digitalRead(IR1);
  int s2 = digitalRead(IR2);
  int s3 = digitalRead(IR3);
  int s4 = digitalRead(IR4);
  int s5 = digitalRead(IR5);

  // Helper function to simplify motor control
  auto go = [](int motor1, int motor2, int motor3, int motor4) {
    analogWrite(E1, MOTOR_SPEED);
    analogWrite(E2, MOTOR_SPEED);
    moveRobot(motor1, motor2, motor3, motor4);
  };

  // Conditions for line following
  if (s2 == 1 && s3 == 0 && s4 == 1) {
    go(HIGH, LOW, LOW, HIGH); // Forward
  } else if (s1 == 1 && s3 == 1 && s4 == 1 && s5 == 0) {
    go(LOW, HIGH, LOW, LOW); // Right
  } else if (s1 == 0 && s2 == 1 && s3 == 1 && s4 == 1) {
    go(LOW, LOW, LOW, HIGH); // Right
  } else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 1) {
    go(LOW, LOW, LOW, HIGH); // Left
  } else if (s1 == 1 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 1) {
    go(LOW, HIGH, LOW, LOW); // Right
  } else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 1) {
    go(LOW, LOW, LOW, HIGH); // Right
  } else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 0) {
    go(LOW, LOW, LOW, HIGH); // Left
  } else if (s1 == 0 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 0) {
    go(LOW, HIGH, LOW, LOW); // Right
  } else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 0) {
    go(LOW, LOW, LOW, HIGH); // Right
  } else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0) {
    moveRobot(LOW, LOW, LOW, LOW); // Stop
  }
}
