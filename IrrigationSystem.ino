#include <LiquidCrystal.h>
#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>
#include "IrrigationEvent.h"
#include "Irrigation.h"

// sensor de temperatura y humedad
#define 	DHT_22	2
#define 	DHTTYPE DHT22

// reloj
#define 	RTC_SDA	A4
#define 	RTC_SCL	A5

// LCD
#define		LCD_RS	12
#define		LCD_E	11
#define		LCD_D4	6
#define		LCD_D5	5
#define		LCD_D6	4
#define		LCD_D7	3

// relay
#define		RELAY	10

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Irrigation* irrigation;

// schedule de riegos -> IrrigationEvent(HORA_INICIO, HORA_FIN)
// IMPORTANTE: terminar con una entrada nula
IrrigationEvent* schedule[] = {
    new IrrigationEvent("7:0:30", "7:1:0"),
    new IrrigationEvent("14:0:30", "14:01:0"),
    new IrrigationEvent("19:0:30", "19:0:45"),
    NULL
};

void setup() {
  DHT* dht = new DHT(DHT_22, DHTTYPE);
  RTC_DS1307* rtc = new RTC_DS1307();
  
  Wire.begin();
  rtc->begin();
  dht->begin();

  lcd.begin(16, 2);
  lcd.print("hello, world!");
  
  // setea la hora solo si el rtc esta no inicializado.
  if (! rtc->isrunning() ) {
    rtc->adjust(DateTime(__DATE__, __TIME__));
  }

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  
  irrigation = new Irrigation(schedule, dht, rtc);
}

void loop() {    
  if (irrigation->windowOpen()) {
    digitalWrite(RELAY, LOW);
    lcd.setCursor(0,0);
    lcd.print("Regando...      ");
  } else {
    lcd.setCursor(0, 0);
    lcd.print(irrigation->dateToDisplay());
    lcd.setCursor(0, 1);
    lcd.print(irrigation->weatherToDisplay());
    digitalWrite(RELAY, HIGH);
  }
}
