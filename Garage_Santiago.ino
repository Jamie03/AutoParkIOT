#include <Servo.h>

// for Sound Sensor
const int sensorPin = 2;
int val = 0; // just a bool checker

// for Servo
const int servoPin = 3;
Servo garage;

// for LEDs
const int GL = 13;
const int PL = 12;

// for Ultrasonic Sensor
const int trigPin = 4;
const int echoPin = 5;
long duration; // Stores duration for sensor
int distance; // Stores distace for sensor

// for Button
const int buttonPin = 6;

// for Buzzer
const int buzzerPin = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Connects to Serial 9600
  pinMode(sensorPin, INPUT); // Sets sensorPin as an Input
  garage.attach(servoPin); // Sets to designated pin
  pinMode(GL, OUTPUT); // Sets the GL LED as an Output
  pinMode(PL, OUTPUT); // Sets the PL LED as an Output
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buttonPin, INPUT_PULLUP); // INPUT_PULLUP to always check state
  // need to hold button to read input
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(sensorPin);

  if (val == HIGH) { 
    garage.write(90); // Turns the servo 90
    Serial.println("Servo turn 90!");
    digitalWrite(GL, HIGH); // Turns on garage light
    Serial.println("Garage light on!");
    while (true){ // Loops while checking distance of car for BEEP & LIGHT
      digitalWrite(trigPin, LOW); 
      delayMicroseconds(2); // Clears the trigPin
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); // Sets the trigPin HIGH for 10 micro seconds
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH); // Returns sound wave travel duration
      distance = duration * 0.034 / 2; // Calculating the distance

      if (distance > 0 && distance < 50){ // Limits distance of detection to 50
        tone(buzzerPin, 750); // Activates sound if car is nearby
        digitalWrite(PL, HIGH); // Activates parking light
        delay(distance*12); // Delays next BEEP and LIGHT based on distance

        noTone(buzzerPin); // Turns off buzzer after delay
        digitalWrite(PL, LOW); // Turns off parking light after delay

        Serial.print("Distance of car: ");
        Serial.println(distance); // Prints the distance of the car

        delay(distance*12); // Delays next BEEP & LIGHT for better effect
      }
      
      if (digitalRead(buttonPin) == LOW){ // Gets out of loop of checking car
        Serial.println("Button Pressed!");
        Serial.println("Servo is set back to 0!"); 
        Serial.println("Garage lights off!");
        break;
      }
    }
  }
  else { 
    garage.write(0);
    digitalWrite(GL, LOW);
  }
}
