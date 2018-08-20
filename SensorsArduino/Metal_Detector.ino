void MetalDetector()
{
  int f = digitalRead(MetalDecetor_pin);
  RelayTimer = millis();
 if(RelayTimer - LastTimer < 1000)
 {
  digitalWrite(MMRelay_pin, HIGH);
  if(f)
   { 
    MineR = 1;
    digitalWrite(Sound_pin, HIGH);
     }
  else
    {MineR = 0;
     digitalWrite(Sound_pin, LOW);
    }
 }
  

   
  if(RelayTimer - LastTimer >= 1000)
  {
   digitalWrite(MMRelay_pin, LOW);
   if(f)
    {  MineL = 1;
       digitalWrite(Sound_pin, HIGH);
    
    }
    else{
      MineL = 0;
       digitalWrite(Sound_pin, LOW);
    }
      
      if(RelayTimer - LastTimer >= 2000)
         LastTimer = RelayTimer;
  }

}

