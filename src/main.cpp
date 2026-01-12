#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ----- LCD -----
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ----- Contador de 48h -----
unsigned long totalSeconds = 48UL * 60UL * 60UL; // 48 horas
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // 1 segundo

bool calibracaoFinalizada = false;

// ----- Controle MOSFET e LED -----
#define PIN_MOSFET 7
#define LED_CALIB  8

void setup() {
  // Inicializa LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Calibrando MQ");

  // Inicializa pinos
  pinMode(PIN_MOSFET, OUTPUT);
  pinMode(LED_CALIB, OUTPUT);

  // Liga sensores e LED de status
  digitalWrite(PIN_MOSFET, HIGH);
  digitalWrite(LED_CALIB, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();

  // --- Atualiza contador ---
  if (!calibracaoFinalizada && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (totalSeconds > 0) {
      totalSeconds--;

      // Converte para horas, minutos e segundos
      unsigned int hours   = totalSeconds / 3600;
      unsigned int minutes = (totalSeconds % 3600) / 60;
      unsigned int seconds = totalSeconds % 60;

      lcd.setCursor(0, 1);

      // Formatação HH:MM:SS sem usar String
      if (hours < 10) lcd.print('0');
      lcd.print(hours);
      lcd.print(':');

      if (minutes < 10) lcd.print('0');
      lcd.print(minutes);
      lcd.print(':');

      if (seconds < 10) lcd.print('0');
      lcd.print(seconds);
      lcd.print("   "); // Limpa resíduos de digitos anteriores
    } 
    else {
      // Finaliza calibração
      calibracaoFinalizada = true;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Calibracao OK");

      lcd.setCursor(0, 1);
      lcd.print("Sensor pronto");

      // Desliga sensores e LED
      digitalWrite(PIN_MOSFET, LOW);
      digitalWrite(LED_CALIB, LOW);
    }
  }
}
