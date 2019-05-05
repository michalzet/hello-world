#include <LiquidCrystal.h>
#include <Arduino.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int Trig = 2;  //pin 2 Arduino połączony z pinem Trigger czujnika
int Echo = 3;  //pin 3 Arduino połączony z pinem Echo czujnika
int CM;        //odległość w cm
long CZAS;     //długość powrotnego impulsu w uS

void setup()
{
  Serial.begin(9600);                        //inicjalizaja monitora szeregowego
  pinMode(Trig, OUTPUT);                     //ustawienie pinu 2 w Arduino jako wyjście
  pinMode(Echo, INPUT);                      //ustawienie pinu 3 w Arduino jako wejście
  lcd.begin(16, 2);
  lcd.print("testing...");

  Serial.println("Test czujnika odleglosci");
}

void loop()
{
  pomiar_odleglosci();              //pomiar odległości
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Odleglosc: ");      //wyświetlanie wyników na ekranie w pętli co 200 ms
  lcd.print(CM);
  lcd.println(" cm");
  delay(200);
}

void pomiar_odleglosci ()
{
  digitalWrite(Trig, HIGH);       //ustawienie stanu wysokiego na 10 uS - impuls inicjalizujacy - patrz dokumentacja
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  CZAS = pulseIn(Echo, HIGH);
  CM = CZAS / 58;                //szerokość odbitego impulsu w uS podzielone przez 58 to odleglosc w cm - patrz dokumentacja
}
