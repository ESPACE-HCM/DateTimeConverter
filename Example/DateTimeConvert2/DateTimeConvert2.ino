#include "Date.h"
#include "LunarConverter.h"
using namespace Espace;
void setup() {
    Serial.begin(9600);
    Date date = Date(1,12,2019);
    LunarConverter converter = LunarConverter();
    Date lunarDate = converter.Convert(date);
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
