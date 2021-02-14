#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);
const int SW_PIN=8;
const int X_PIN=0;
const int Y_PIN=1;

int X_POS=0;
int Y_POS=0;
bool MOVE_ENABLED=true;

char EDIT_CHARS[] = { ' ','A','B','C','D','E','F','G','H','I' };
int EDIT_POS=0;
bool EDIT = false;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(SW_PIN, INPUT);
  digitalWrite(SW_PIN, HIGH);
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("Liam was here!");
  lcd.setCursor(X_POS,Y_POS);
}

void blink(){
  //delay(1000);
  lcd.blink();
  /*delay(1000);
  lcd.noBlink();*/
}

void tran_pos(char pos){
  switch(pos){
    case 'U':
      Y_POS--;
      break;
    case 'D':
      Y_POS++;
      break;
    case 'L':
      X_POS--;
      break;
    case 'R':
      X_POS++;
      break;
  }
  lcd.setCursor(X_POS,Y_POS);
}

void edit_mode(){
  
}

void loop() {
  // put your main code here, to run repeatedly:
  blink();
  Serial.print("Switch: ");
  Serial.print(digitalRead(SW_PIN));
  
  Serial.print("\n");
  Serial.print("X-Axis: ");
  Serial.print(analogRead(X_PIN));
  
  Serial.print("\n");
  Serial.print("Y-Axis: ");
  Serial.print(analogRead(Y_PIN));

  Serial.print("\n\n");
  if(MOVE_ENABLED){
    if(analogRead(Y_PIN)<=300 && Y_POS> 0){
      tran_pos('U');
    }
    if(analogRead(Y_PIN)>=700 && Y_POS<1){
      tran_pos('D');
    }
    if(analogRead(X_PIN)<=300 && X_POS<15){
      tran_pos('R');
    }
    if(analogRead(X_PIN)>=700 && X_POS> -1){
      tran_pos('L');
    }
  }
  if(digitalRead(SW_PIN)==0){
    EDIT=true;
    while(EDIT && ((Y_PIN<=300 || Y_PIN>=700))){
      MOVE_ENABLED=false;
      while(analogRead(Y_PIN)<=10 && EDIT_POS > -1){
        EDIT_POS--;
        //lcd.print(EDIT_CHARS[EDIT_POS]);
        delay(500);
      }
      while(analogRead(Y_PIN)>=1000 && EDIT_POS < 51){
        EDIT_POS++;
        //lcd.print(EDIT_CHARS[EDIT_POS]);
        delay(500);
      }
      lcd.print(EDIT_CHARS[EDIT_POS]);
      delay(1000);
      if(digitalRead(SW_PIN)==1){
        delay(1000);
        if(digitalRead(SW_PIN)==1){
          EDIT=false;
          MOVE_ENABLED=true;
          break;
        }
      }
      EDIT_POS=0;
    }
  }
  delay(100);
}
