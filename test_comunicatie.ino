char chr;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void mainComunication() {  //Used to talk with an other devise
  while(!Serial.available()){}  //Waits for a message

  String str = Serial.readString();
  str.trim();  //Takes away junk such as \n or \r\n
  chr = str.charAt(0);  //Saves the first character of the string in chr.
  str.remove(0, 1);  //Removes the first character from str.
  if(chr >= 'A' && chr <= 'Z'){
    procesCommand(chr, str);
  }
  chr = '0';
}

void procesCommand(char chr, String str){
  switch(chr){
    case 'A':
      Serial.print(str);
      break;
  }
  return;
}




int whatChar() {
  while(!Serial.available()){}

  int chr = Serial.read();

  
}


void loop() {
  mainComunication();
}
