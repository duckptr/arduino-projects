#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char myKeys[ROWS][COLS]=
{
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};

byte rowPins[ROWS] = {5,4,3,2};
byte colPins[COLS] = {8,9,10,11};

Keypad customKeypad = Keypad (makeKeymap(myKeys), rowPins, colPins, ROWS, COLS);

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  char customKey = customKeypad.getKey();
  if(customKey)
  {
    Serial.println(customKey);
  }

}
