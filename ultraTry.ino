#define NOTE_C4 262
#include <Servo.h> 

const int trigPin = 11;
const int echoPin = 12;
const int greenLED = 10;
const int orangeLED = 9;
const int redLED = 8;
const int alarm = 7;


void setup() {
  Serial.begin(9600);
}

void loop()
{
  long duration, inches, cm;
  pinMode(greenLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(alarm, OUTPUT);
  pinMode(trigPin, OUTPUT);
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
   
  if(inches > 10)
  digitalWrite(greenLED, HIGH);
  else
  digitalWrite(greenLED, LOW);
  
  if(inches <= 10 && inches >= 5)
  digitalWrite(orangeLED, HIGH);
  else
  digitalWrite(orangeLED, LOW);
  
  if(inches < 5 && inches > 0){
  digitalWrite(redLED, HIGH);
  tone(alarm, 2000/(2*inches));
  }
  else{
  digitalWrite(redLED, LOW);
  noTone(alarm);
 }
 
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
