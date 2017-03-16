//Assign components to digital I/O pins on arduino
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
  
  //Writing the trig pin low then high is what sends out the sonic burst (the sound wave that will be reflected back to the sensor if there is an object in its path)
  //Need to have delays so that the sensor has time to process the data
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

//The echo pin uses the command pulseIn to determine the amount of time it took for the sound wave to be reflected back to the sensor
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

   //Turns the green LED on if an object more than 10 inches away from the sensor
  if(inches > 10)
  digitalWrite(greenLED, HIGH);
  else
  digitalWrite(greenLED, LOW);

  //Turns the orange LED on if an object is between 10 and 5 inches from the sensor
  if(inches <= 10 && inches >= 5)
  digitalWrite(orangeLED, HIGH);
  else
  digitalWrite(orangeLED, LOW);

  //Turns the red LED on if an object is less than 5 inches from the sensor
  //The piezo speaker is turned on and emits a noise at a frequency of 2000Hz divided by 2 times the distance that the object is from the sensor
  //This causes the speaker to emit a higher pitched noise as the object gets closer to the sensor
  if(inches < 5 && inches > 0){
  digitalWrite(redLED, HIGH);
  tone(alarm, 2000/(2*inches));
  }
  else{
  digitalWrite(redLED, LOW);
  noTone(alarm);
 }

 //Prints the distance in inches and centimeters on the serial monitor
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}

//converts the amount of time it takes the sound wave to travel into distance
//sound travels at approximately 1 inch every 74 microseconds
//need to divide this value by 2 to get the distance to the object that was detected
long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

//sound travels at 1 centimeter every 29 microseconds
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
