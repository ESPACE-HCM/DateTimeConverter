#include "Date.h"
#include "LunarConverter.h"

void setup() {
    Serial.begin(9600);
    Espace::Date date = Espace::Date(1,12,2019);
    Espace::LunarConverter converter = Espace::LunarConverter();
    Espace::Date lunarDate = converter.Convert(date);
    Serial.print(lunarDate.DayInMonth);
    Serial.print("/");
    Serial.print(lunarDate.Month);
    Serial.print("/");
    Serial.print(lunarDate.Year);
}

void loop() {
  // put your main code here, to run repeatedly:
    delay(1000);
}
