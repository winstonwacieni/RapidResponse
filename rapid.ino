#include <Stepper.h> // include the stepper library

#define POWER_PIN  7
#define SIGNAL_PIN A5
#define GREEN 3
#define BLUE 4
#define RED1 5
#define RED2 6
#define BigRED 8
#define buzzer 9

// Define the number of steps per revolution (should be 2048 for your motor)
const int stepsPerRevolution = 2048;

// Initialize the stepper motor with the appropriate pins and number of steps
Stepper myStepper(stepsPerRevolution, 10, 11, 12, 13);

int value = 0; // variable to store the sensor value

void setup() {
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
  pinMode(SIGNAL_PIN, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(BigRED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  myStepper.setSpeed(15); // set the motor speed (RPM)
}

void loop() {
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF
  
  if (value > 0 && value < 100 ) {
    digitalWrite(GREEN, HIGH);
    noTone(buzzer);
  } else if (value > 101 && value < 300) {
    digitalWrite(BLUE, HIGH);
    digitalWrite(BigRED, LOW);
    digitalWrite(RED1, LOW);
    digitalWrite(RED2, LOW);
    noTone(buzzer);
  } else if (value > 301) {
    digitalWrite(RED1, HIGH);
    digitalWrite(RED2, HIGH);
    digitalWrite(BigRED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    tone(buzzer, 3000); // buzzer max
    delay(500);
    noTone(buzzer);
    tone(buzzer, 2000);
    delay(1000);
    myStepper.step(2048); // rotate the motor one full revolution (clockwise)
    delay(1000); // wait for 5 seconds
    myStepper.step(-2048); // rotate the motor back to the original position (counterclockwise)
  } else {
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED1, LOW);
    digitalWrite(RED2, LOW);
    digitalWrite(BigRED, LOW);
    noTone(buzzer);
  }
  
  // Serial
  Serial.print("Sensor value: ");
  Serial.println(value);
  delay(1000);

  // reaction
}
