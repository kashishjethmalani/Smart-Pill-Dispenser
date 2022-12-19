#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,  16, 2);
#define pin1  8  
#define pin2  9                
#define pin3  10
#define pin4  11
int buzzer = 7;
int period = 500;
unsigned long time_now = 0;
void stepper_moving(void);          //this function used to rotate stepper motor
void Step_A(void);                  //the following four functionts related to motion of stepper motor
void Step_B(void);
void Step_C(void);
void Step_D(void);
void forward(void);
volatile int counter=0;  

void Step_A(){
  digitalWrite(pin1, HIGH);//turn on coil 1 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}
void Step_B(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, HIGH);//turn on coil 2
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}
void Step_C(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, HIGH); //turn on coil 3
  digitalWrite(pin4, LOW); 
}
void Step_D(){
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, HIGH); //turn on coil 4
}
void step_OFF(){
  digitalWrite(pin1, LOW); //power all coils down
  digitalWrite(pin2, LOW); 
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
}

void forward(){//one tooth forward
  Step_A();
  delay(5);
  Step_B();
  delay(5);
  Step_C();
  delay(5);
  Step_D();
  delay(5);
}

 
void welcome_message(void){
  lcd.clear();
  lcd.print("Welcome to Pill");
  lcd.setCursor(3,1);
  lcd.print("Dispenser");
  
  delay(2000);
  
}

void pill_d(void){
  lcd.clear();
  lcd.print("Pill ");
  lcd.setCursor(3,1);
  lcd.print("Dispensed.");
  
  delay(500);
  
}

void buzzer_p(){
  delay(10000);
  tone(buzzer, 1000); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
  delay(500);
  tone(buzzer, 1000); // You can also use noTone() to stop the sound it takes 1 parametere which is the buzzer pin
  delay(500);
  noTone(buzzer);
}

void time_delay(){
  time_now = millis();
   
  while(millis() < time_now + period){
    //wait approx. [period] ms
  }
}


char Incoming_value = 0;

SoftwareSerial btSerial(3,4); //Rx/Tx
                
void setup() 
{
  btSerial.begin(9600);         
  pinMode(13, OUTPUT);       
}

void loop()
{
  if(btSerial.available() > 0)  
  {
    Incoming_value = btSerial.read();      
    btSerial.print(Incoming_value);        
    btSerial.print("\n");        
    if(Incoming_value == '1'){            
      digitalWrite(13, HIGH);
      time_delay();
      btSerial.print(Incoming_value);
      lcd.init();
      lcd.backlight();
      lcd.print("Smart Pill Dispenser...");
      for (int k = 0; k<4; k++){
        delay(2000);
        welcome_message();
        for(float counter=0; counter<26; counter++){
          forward();
        
        }
        time_delay();
        pill_d();
        time_delay();
        buzzer_p();
      }
    }  
    else if(Incoming_value == '0'){       
      digitalWrite(13, LOW);
      delay(200);
      btSerial.print(Incoming_value);   
  }                            
}
} 
