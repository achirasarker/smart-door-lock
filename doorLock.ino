#include <Keypad.h>

int lock = 2;
int ledBlue = 3;
int ledRed = 4;
int count = 0;

const byte numRows = 4; 
const byte numCols = 3;

//Map out the keypad buttons in a 2D array
char keymap[numRows][numCols] = { 
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

//Store pins of arduino that keypad rows & cols are connected to within an array
byte rowPins[numRows] = {5,6,7,8};
byte colPins[numCols] = {9,10,11};

//Object myKeypad of class Keypad and pass all params of keypad in it
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup() {
  Serial.begin(9600); 
  pinMode(lock, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT);
  digitalWrite(lock, HIGH); //Set lock pin as high since we're using a logic low relay
}

void loop() {
  char keypressed = myKeypad.getKey();
  if(keypressed!=NO_KEY)
  {
    //Password is 444
    Serial.println(keypressed); 
    if (keypressed == '4')
      count = count + 1;
    if (count > 3)
      count = 0;
    if ((keypressed=='*')&&(count==3))
    {
      digitalWrite(lock, LOW); //open lock
      digitalWrite(ledBlue, HIGH);
      digitalWrite(ledRed, LOW);
      count = 0;
    }
    if (keypressed == '#')
    {
      digitalWrite(lock, HIGH); //close lock
      digitalWrite(ledRed, HIGH);
      digitalWrite(ledBlue, LOW);
      count = 0;
    }
  }

}
