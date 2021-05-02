String stringOfBits = "0000";//binary to show

int pins[] = {6, 7, 8, 9};//array of actual pin numbers LEDs are connected to. Length of this array should should be equal to lengh of stringOfBits
int lengthOfDelay = 500;//time to show current binary in miliseconds 
int lengthOfInBetweenBlink = 100;//set this to 0 to avoid inbetween blink


void showInBetweenBlink() {
  for (int i=sizeof(pins)/sizeof(int) - 1; i > -1; i--) {
    digitalWrite(pins[i], LOW);
  }
  delay(lengthOfInBetweenBlink/2);
  for (int i=sizeof(pins)/sizeof(int) - 1; i > -1; i--) {
    digitalWrite(pins[i], HIGH);
  }  
  delay(lengthOfInBetweenBlink/2);
  for (int i=sizeof(pins)/sizeof(int) - 1; i > -1; i--) {
    digitalWrite(pins[i], LOW);
  }
}



void showCurrentBinaryOnLEDs(int duration){
  int pin_index = 0;
  for (int i=sizeof(pins)/sizeof(int) - 1; i > -1; i--) {
    if (stringOfBits[pin_index]== '1') {
      digitalWrite(pins[i], HIGH);
    }
    pin_index++;
  }
  
  delay(duration);
  for (int i=sizeof(pins)/sizeof(int) - 1; i > -1; i--) {
    digitalWrite(pins[i], LOW);
  }
}

void getNextStringOfBits() {
  int dragDigit = 0;
  for (int i = stringOfBits.length()-1; i > -1; i--) {
    if (dragDigit == 0) {
      if (stringOfBits[i] == '0') {
        stringOfBits[i] = '1';
        dragDigit = 0;
        return;
      } else {
        stringOfBits[i] = '0';
        dragDigit = 1;
      }
    } else {
      if (stringOfBits[i] == '0') {
        stringOfBits[i] = '1';
        dragDigit = 0;
        return;
      } else {
        stringOfBits[i] = '0';
        dragDigit = 1;
      }
    }
  }
  return;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Prepearing pins: ");
  //Serial.println(test.length());
  for (int i = 0; i < sizeof(pins)/sizeof(int); i++){
    pinMode(pins[i], OUTPUT);
    Serial.print(pins[i]);
    Serial.println(" is set to OUTPUT");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  getNextStringOfBits();
  Serial.println("Showing: "+stringOfBits);
  showInBetweenBlink();
  showCurrentBinaryOnLEDs(lengthOfDelay);
}
