#include <LiquidCrystal_I2C.h>
#include <Key.h>
#include <Keypad.h>
#include <Wire.h>


const byte pinRele = 10;
const byte ranks = 4;
const byte columns = 4;

int passRobert[4] = {'1','5','4','2'};
int passControl = 0;

char key;
int number = key - 48;

byte pinRanks[ranks] = {9, 8, 7, 6};
byte pinColumns[columns] = {5, 4, 3, 2};

char keys[ranks][columns] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
  };

Keypad myKeyboard = Keypad(makeKeymap(keys),pinRanks, pinColumns, ranks, columns);

LiquidCrystal_I2C lcd(0x27, 20,4);



void setup() {
  Serial.begin(9600);
  pinMode(pinRele, OUTPUT);

 /* lcd.begin(20,4);
  for(int i = 0; i<3; i++){
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
    }

  lcd.backlight();*/
  
}

void loop() {
  char pulseKey = myKeyboard.getKey();
  if (pulseKey == passRobert[passControl]){
    passControl++;    
    }
  if (passControl == 4){
    digitalWrite(pinRele, HIGH);
    delay(1500);
    digitalWrite(pinRele, LOW);
    }
  if (pulseKey == '*'){
    passControl = 0;
    }
   
}
