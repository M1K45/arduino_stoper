#include<Arduino.h>
#include <LiquidCrystal.h> //Dołączenie bilbioteki
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Informacja o podłączeniu nowego wyświetlacza
#define LEWY 8
#define PRAWY 9
bool stopSet =0;
unsigned long czasStart, czasStop, diff;
float czas = 0;



void ekranStartowy(){
  lcd.clear();
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("    -STOPER-    "); //Wyświetlenie tekstu
  lcd.setCursor(0, 1); //Ustawienie kursora
  lcd.print("L-start   P-stop"); //Wyświetlenie tekstu
}

void start (){
  lcd.clear();
  lcd.setCursor(0, 0); //Ustawienie kursora 
  while(!stopSet){
    if (digitalRead(PRAWY) == LOW){
      stopSet = 1;
    }
    delay(10);
    lcd.clear();
    lcd.setCursor(0, 0); //Ustawienie kursora 
    czas += 0.01;
    lcd.print(czas);
  } 
}


void stop (){
  for(;;){
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Koniec pomiaru "); //Wyświetlenie tekstu 
  lcd.setCursor(0, 1); 
  lcd.print(czas);
  lcd.print(" s");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("L - mierz dalej"); //Wyświetlenie tekstu 
  lcd.setCursor(0, 1); 
  lcd.print("P - menu start");
  delay(4000);
  if (digitalRead(LEWY) == LOW){
    break; 
    start();
  }
}
}

void setup() {
  pinMode(LEWY, INPUT_PULLUP);
  pinMode(PRAWY, INPUT_PULLUP);
  ekranStartowy();
}
 
void loop() {

  if (digitalRead(LEWY) == LOW){
    start();
    stop();
  }
}