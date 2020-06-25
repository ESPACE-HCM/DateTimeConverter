#include "./Date.h"
#include "LunarConverter.h"
using namespace Espace;

uint8_t month;
uint16_t year;
void setup() {
    Serial.begin(115200);
    month = 1;
    year = 2018;
    Date date = Date(1, month,year);
    Serial.print("DL : ");
    Serial.print(date.DayInMonth);
    Serial.print("/");
    Serial.print(date.Month);
    Serial.print("/");
    Serial.print(date.Year);
   
    Serial.println();
    LunarConverter converter = LunarConverter();
    Date lunarDate = converter.Convert(date);
    for ( year = 2017; year <= 2020; year++)
    {
        for (uint8_t month = 1; month < 13; month++)
        {
            Date date = Date(1, month,year);
            Serial.print("DL : ");
            Serial.print(date.DayInMonth);
            Serial.print("/");
            Serial.print(date.Month);
            Serial.print("/");
            Serial.print(date.Year);
            if(date.IsLeafMonth){
                Serial.print(" N");
            }
            Serial.println();
            LunarConverter converter = LunarConverter();
            Date lunarDate = converter.Convert(date);
        
            Serial.print("AL : ");
            Serial.print(lunarDate.DayInMonth);
            Serial.print("/");
            Serial.print(lunarDate.Month);
            Serial.print("/");
            Serial.print(lunarDate.Year);
            if(lunarDate.IsLeafMonth){
                Serial.print(" N");
            }
            Serial.println();
        }
    }
}

void loop() {
    delay(1000);
}
