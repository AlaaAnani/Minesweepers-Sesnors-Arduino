/*void UltrasonicSensorR()
{
  // Clears the trigPin
digitalWrite(trig1Pin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig1Pin, HIGH);
delayMicroseconds(10);
digitalWrite(trig1Pin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
 pinMode(echo1Pin, INPUT);
duration1 = pulseIn(echo1Pin, HIGH);
// Calculating the distance
distanceR= duration1*0.034/2;
// Prints the distance on the Serial Monitor
}
void UltrasonicSensorL()
{
  // Clears the trigPin
digitalWrite(trig2Pin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trig2Pin, HIGH);
delayMicroseconds(10);
digitalWrite(trig2Pin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
//digitalWrite(echo1Pin, LOW);
duration2 = pulseIn(echo2Pin, HIGH,10000);
// Calculating the distance
distanceL= duration2*0.034/2;
// Prints the distance on the Serial Monitor
}*/

void UltrasonicSensorR()
{
// Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distance pings.
  if (millis() >= ping1Timer) {   // pingSpeed milliseconds since last ping, do another ping.
    ping1Timer += ping1Speed;      // Set the next ping time.
    sonar1.ping_timer(echo1Check); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
  }
  // Do other stuff here, really. Think of it as multi-tasking.
}
void UltrasonicSensorL(){
// Notice how there's no delays in this sketch to allow you to do other processing in-line while doing distance pings.
  if (millis() >= ping2Timer) {   // pingSpeed milliseconds since last ping, do another ping.
    ping2Timer += ping2Speed;      // Set the next ping time.
    sonar2.ping_timer(echo2Check); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
  }
  // Do other stuff here, really. Think of it as multi-tasking.
}
void echo1Check() 
{ // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!
  if (sonar1.check_timer()) { // This is how you check to see if the ping was received.
    // Here's where you can add code.
   // Serial.print("Ping: ");
   // Serial.print(sonar.ping_result / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
   // Serial.println("cm");
   distanceR = sonar1.ping_result / US_ROUNDTRIP_CM;
  }
  // Don't do anything here!
}
void echo2Check() 
{ // Timer2 interrupt calls this function every 24uS where you can check the ping status.
  // Don't do anything here!
  if (sonar2.check_timer()) 
  { // This is how you check to see if the ping was received.
    // Here's where you can add code.
   // Serial.print("Ping: ");
   // Serial.print(sonar.ping_result / US_ROUNDTRIP_CM); // Ping returned, uS result in ping_result, convert to cm with US_ROUNDTRIP_CM.
   // Serial.println("cm");
   distanceL = sonar2.ping_result / US_ROUNDTRIP_CM;
  }
  // Don't do anything here!
}
