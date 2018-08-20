/*void Encoder()
{
aState = digitalRead(outputA); // Reads the "current" state of the outputA

   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState)
   {  
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) 
     { 
       counter ++;
     } 
     else 
     {
       counter --;
     }
   }
//     DeltaCounter = counter - LastCounter; 
     LastCounter = counter;   
     aLastState = aState; // Updates the previous state of the outputA with the current state

}*/
