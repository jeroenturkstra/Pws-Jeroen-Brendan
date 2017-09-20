//Let the arduino send back the axact amounth of degrees he has turned so the py can 
//adjust acordingly.
// !!! voor getallen gebruiken we punten, geen comma's
//

char chr;
String str;
boolean error;

void setup() {
  //Put your setup code here, to run once:
  Serial.begin(9600);
  
}



void loop() {
  mainComunication();
  if (error == false){ //No error has occured, send OK
    Serial.print('O');Serial.println('K');
  }
  else{  //An error has occcured, end RR
    Serial.print('R');Serial.println('R');
  }
}




void mainComunication() {  //Used to talk with an other devise
  while(!Serial.available()){}  //Waits for a message
  error = false;

  str = Serial.readString();
  str.trim();  //Takes away junk such as \n or \r\n
  while(str.length() > 0){
    char chr = str.charAt(0);  //Saves the first character of the string in chr.
    str.remove(0, 1);  //Removes the first character from str.
    if(chr >= 'A' && chr <= 'Z'){
      procesCommand(chr);
      if(error){
        return;
      }
    }
  }
  chr = '0';
}



void procesCommand(char chr){  //Check what command he has to execute and does it.
  switch(chr){
    case 'M':  //Move
      Serial.println(str);

      
      break;
    case 'R':  //Rotate
      float var;
      var = stringToVariable();
      if(error){
        return;
      }
      Serial.println(var);

    
      break;
    case 'T':  //Test


      break;
    default:
    
    return;
  }
  str.remove(0);
  return;
}



float stringToVariable(){
  float returnVal = 0;  //Make a return value variable
  boolean decimalPoint = false;
  int decimalPlace = 1;
  
  while(str.length() > 0){  //A weird way to convert our string into an interger we want
    
    if(str.charAt(0) == '.'){  //Tests for decimal points, one means do a diferent 'algorithm' a second one means an error
      if(decimalPoint == false){  //if this is the first decimal point decimalPoint becomes true, else there is something wrong cause 2 points
        decimalPoint = true;
      }
      else{
        error = true;
        return;
      } 
    }

    
    if( !(  (str.charAt(0) > '0' && str.charAt(0) < '9') || str.charAt(0) == '.'  )  ){  //Gives an error if the character isn't valid(between 0 and 9 or a decimal point)
      error = true;
      return;
    }
    
    if(decimalPoint == false){  //Checks if a decimal point has been found and acts acordingly
      returnVal = returnVal*10 + int(str.charAt(0))-int('0');  //A simple way to convert our string to an interger
    }
    else{
      if(str.charAt(0) != '.'){
        returnVal = returnVal + ( int(str.charAt(0))-int('0') )/pow(10, decimalPlace); //Devides the new character by 10 to the power n where n is grows the more it is called
        decimalPlace += 1;
      }
    }
    
    str.remove(0,1);
    
  }
  return returnVal;
}
