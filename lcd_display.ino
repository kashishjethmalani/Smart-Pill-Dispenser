
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial btSerial(3,4); //Rx/Tx
String msg

LiquidCrystal_I2C lcd(0x27,  16, 2);

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.print("How U Doin'?");
  lcd.autoscroll();
  btSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (btSerial.available()){
    delay(10);
    char ch = btSerial.read();
    msg = msg + ch;
  }
  if (msg.length() > 0){
    lcd.clear();
    lcd.print(msg);
    lcd.autoscroll();
  }
  msg = "";
}
