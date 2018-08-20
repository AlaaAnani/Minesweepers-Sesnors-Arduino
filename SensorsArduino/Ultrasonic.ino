

void UltrasonicSensorR()
{
  if (millis() >= ping1Timer) 
  {  
    ping1Timer += ping1Speed;      
    sonar1.ping_timer(echo1Check); 
  }
  
}
void UltrasonicSensorL()
{

  if (millis() >= ping2Timer) {   
    ping2Timer += ping2Speed;      
    sonar2.ping_timer(echo2Check);
  }

}
void echo1Check() 
{ 
  if (sonar1.check_timer()) 
  { 
   distanceR = sonar1.ping_result / US_ROUNDTRIP_CM;
  }

}
void echo2Check() 
{ 
  if (sonar2.check_timer()) 
  { 
   distanceL = sonar2.ping_result / US_ROUNDTRIP_CM;
  }

}
