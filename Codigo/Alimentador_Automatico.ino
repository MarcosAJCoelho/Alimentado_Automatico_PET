#include <SimpleTimer.h>
#include <LiquidCrystal.h>
#include "Stepper_28BYJ_48.h"

const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Stepper_28BYJ_48 stepper(6,5,4,3);
SimpleTimer temporizador;

int ajuste = 2;
int pino_adjt = A0;
int pino_adjq = A1;
long valor_tempo = 60000;
long valor_qtde = 10;

void setup() {
  pinMode(ajuste,INPUT_PULLUP);
  temporizador.setInterval(valor_tempo);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Alimentador Auto");
  lcd.setCursor(0,1);
  lcd.write("Tempo: ");
  lcd.print(valor_tempo/1000);
  stepper.step(50);
  stepper.step(-50);
  delay(1000);
}

void loop() {
  if ( digitalRead(ajuste) == LOW ) {
    lcd.setCursor(0,0);
    lcd.write("  Ajustes       ");
    valor_tempo = analogRead(pino_adjt);
    valor_tempo = map(valor_tempo, 0, 1023, 20000, 60000);
    temporizador.setInterval(valor_tempo);
    temporizador.reset();
    valor_qtde = analogRead(pino_adjq);
    valor_qtde = map(valor_qtde, 0, 1023, 1, 21);
    lcd.setCursor(0,1);
    lcd.print(valor_tempo/1000);
    lcd.print(" seg. ");
    lcd.print(valor_qtde);
    lcd.print(" porc.");
  }
  else {
    lcd.setCursor(0,0);
    lcd.write("Alimentador Auto");
    lcd.setCursor(0,1);
    lcd.write("Tempo: ");
    lcd.print(valor_tempo/1000);
    lcd.print(" s     ");
  }
  if (temporizador.isReady()) {          
    stepper.step(500*valor_qtde);
    stepper.step(-100);
    temporizador.reset();   
  }
} 
