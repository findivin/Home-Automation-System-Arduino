#include <Servo.h>
#include <LiquidCrystal.h>

#define buton1 6
#define buton2 7
#define buton3 8
#define pompa 9 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo servo_hrana;

unsigned long timpinceput_apa = 0;//
unsigned long timpinceput_hrana = 0;

short intervaludare = 2;// intervalul de udare in ore
short intervalhranire = 3;//intervalul de hranire in ore

bool apasat1 = 0;  
bool apasat2 = 0;
bool apasat3 = 0;

short contor_meniu = 1;// 1. Principal 2. Udat 3. Hranit

void timp(bool ah, short &minute, short &ore){//1.apa 0.hrana
  if(ah){
    unsigned minutetotal = (intervaludare - (millis()/3600000 - timpinceput_apa/3600000))*60 - (millis()/60000 - timpinceput_apa/60000);
    ore = minutetotal/60;
    minute = minutetotal%60;
  }
  else{
    unsigned minutetotal = (intervalhranire - (millis()/3600000 - timpinceput_hrana/3600000))*60 - (millis()/60000 - timpinceput_hrana/60000);
    ore = minutetotal/60;
    minute = minutetotal%60;
  }
  
}

void verifbutoane(){
  apasat1 = digitalRead(buton1);
  apasat2 = digitalRead(buton2);
  apasat3 = digitalRead(buton3);
}

void udare(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Udare...");
  digitalWrite(pompa, HIGH);
  delay(2500);
  digitalWrite(pompa, LOW);

}

void hranire(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hranire...");
  servo_hrana.write(0);
  delay(500);
  servo_hrana.write(90);
  
}

void schimba_meniu(){
  if( contor_meniu < 4)
        contor_meniu++;
  else  contor_meniu = 1; 
}

void meniu_principal(){
  short minute, ore;
  if(apasat2){
    timp(1,minute,ore);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print ("Countdown Apa");
    lcd.setCursor(0, 1);
    lcd.print(ore);
    lcd.print("h ");
    lcd.print(minute);
    lcd.print("m");
    delay(5000);
    lcd.clear();
    apasat2=0;
    meniu_principal();
  }
  else if (apasat3){
    timp(0,minute,ore);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print ("Countdown Hrana");
    lcd.setCursor(0, 1);
    lcd.print (ore);
    lcd.print("h ");
    lcd.print (minute);
    lcd.print("m");
    delay(5000);
    lcd.clear();
    apasat3=0;
    meniu_principal();
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("1. Alte meniuri");
    lcd.setCursor(0, 1);
    lcd.print("2. Apa  3. Hrana");
  }
}

void meniu_udare(){
  apasat1 = 0;
  lcd.clear();
  bool a = false;
  while(!apasat1){
    verifbutoane();
    lcd.setCursor(0,0); 
    lcd.print("Set timp apa");
    lcd.setCursor(0,1); 
    lcd.print("2.- 3.+ t=");
    lcd.print(intervaludare);
    lcd.print("h");
    if (apasat2 && intervaludare > 1){
      intervaludare--;
      delay(250);
      lcd.clear();
      a = true;
    }
    else if (apasat3){
      intervaludare++;
      delay(250);
      lcd.clear();
      a = true;
    }
  }
  lcd.clear();
  if(a) timpinceput_apa = millis();
}

void meniu_hranire(){
  apasat1 = 0;
  lcd.clear();
  bool a = false;
  while(!apasat1){
    verifbutoane();
    lcd.setCursor(0,0); 
    lcd.print("Set timp hrana");
    lcd.setCursor(0,1); 
    lcd.print("2.- 3.+ t=");
    lcd.print(intervalhranire);
    lcd.print("h");
    if (apasat2 && intervalhranire > 1){
      intervalhranire--;
      delay(250);
      lcd.clear();
      a = true;
    }
    else if (apasat3){
      intervalhranire++;
      delay(250);
      lcd.clear();
      a = true;
    }
  }
  lcd.clear();
  if(a) timpinceput_hrana = millis();
}

void meniu_fa_ceva(){
  apasat1 = 0;
  lcd.clear();
  while(!apasat1){
    verifbutoane();
    lcd.setCursor(0, 0);
    lcd.print("Meniu rapid");
    lcd.setCursor(0, 1);
    lcd.print("2.Apa 3.Hrana");
    if(apasat2)
      udare();
    else if(apasat3)
      hranire();
  }

}

void setup() {
  lcd.begin(16, 2);
  servo_hrana.attach(10);

  pinMode(buton1, INPUT);
  pinMode(buton2, INPUT);
  pinMode(buton3, INPUT);
  pinMode(pompa, OUTPUT);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Bine ai venit! ");
  lcd.setCursor(0, 1);
  lcd.print("Proiect atestat");
  delay(2500);
  lcd.clear();

  timpinceput_apa = millis();
  timpinceput_hrana = millis();
}

void loop() {
  verifbutoane();
  if (apasat1) {
    schimba_meniu();
    delay(500);
  }
  switch(contor_meniu){
    case 2:
      meniu_udare();
      break; 
    case 3:
      meniu_hranire();
      break;
    case 4:
      meniu_fa_ceva();
      break;
    default:
      meniu_principal();
      break;
  }
  short minute, ore;
    timp(0, minute, ore);
    if(minute < 1 && ore == 0)
      udare();
    timp(1, minute, ore);
    if(minute < 1 && ore == 0)
      hranire();
 delay(10);
}