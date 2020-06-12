/*
// Copyright 2019, Espcae Vietnam Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// 
// THIS SOURCE CIDE IS USED FOR STUDY PURPOSE ONLY.

*/

#include "LunarConverter.h"
namespace Espace
{    
/*
Luu am lich 3byte/nam
byte1:    [Ngay bat dau 1/1 AL - 5 bit][thang bat dau 1/1 AL - 1 bit][So ngay thang nhuan - 1 bit]
byte2:    [Thang nhuan - 4 bit][so ngay thang 12,11,10,9 - 4bit]
byte3:    [So ngay thang 8,7,6,5,4,3,2,1 - 8bit]

Ngay bat dau 1/1 AL  :  0x01->0x1F    1-31
thang bat dau 1/1 AL :  0             Thang 1
1             Thang 2
So ngay trong thang  :  0             29 ngay
1             30 ngay


*/
LunarConverter::LunarConverter(/* args */)
{
}

LunarConverter::~LunarConverter()
{
}
uint8_t LunarConverter::GetMaxDay(uint8_t lunarMonth, uint8_t byte1, uint8_t byte2, uint8_t byte3)
{
	uint8_t GetValue = 0;
	if (lunarMonth == 0)
		return 0;
	else if (lunarMonth == 1)
		GetValue = byte3 & 0x01;
	else if (lunarMonth == 2)
		GetValue = byte3 & 0x02;
	else if (lunarMonth == 3)
		GetValue = byte3 & 0x04;
	else if (lunarMonth == 4)
		GetValue = byte3 & 0x08;
	else if (lunarMonth == 5)
		GetValue = byte3 & 0x10;
	else if (lunarMonth == 6)
		GetValue = byte3 & 0x20;
	else if (lunarMonth == 7)
		GetValue = byte3 & 0x40;
	else if (lunarMonth == 8)
		GetValue = byte3 & 0x80;
	else if (lunarMonth == 9)
		GetValue = byte2 & 0x01;
	else if (lunarMonth == 10)
		GetValue = byte2 & 0x02;
	else if (lunarMonth == 11)
		GetValue = byte2 & 0x04;
	else if (lunarMonth == 12)
		GetValue = byte2 & 0x08;
	else if (lunarMonth == 13)
		GetValue = byte1 & 0x02; //leap month
	if (GetValue != 0x00)
		return 30;
	return 29;
}

Date LunarConverter::Convert(Date date)
{
	uint8_t sD, sM, lD, lM, lY, aM;
	/*
	sD: start day
	sM: start Month
	lD: lunar Date
	lM: Lunar Month
	lY: lunar year
	aM: number days in each lunar month
	*/
	uint16_t roottime = (ROOTYEAR - 2000);
	bool CNN = true;
	//Date Start;
	uint8_t byte1, byte2, byte3;
	if (date.Year < roottime)
		return Date(date.DayInMonth, date.Month, date.Year);
	// Get Lut 3 bytes
	byte1 = LUT2K16[(date.Year - roottime) * 3];
	byte2 = LUT2K16[(date.Year - roottime) * 3 + 1];
	byte3 = LUT2K16[(date.Year - roottime) * 3 + 2];
	lY = date.Year;
	//Get Start Day Start Month
	sD = byte1 >> 3;
	if ((byte1 & 0x04) == 0)
		sM = 1;
	else
		sM = 2;
	Date cmpDate(sD, sM, date.Year);
	Date currentDate(date.DayInMonth, date.Month, date.Year);
	//Get LUT for previous year if this Start Day < Current Day
	if (currentDate < cmpDate)
	{
		if (date.Year < 17)
			return Date(date.DayInMonth, date.Month, date.Year);
		byte1 = LUT2K16[(date.Year - roottime) * 3 - 3];
		byte2 = LUT2K16[(date.Year - roottime) * 3 - 2];
		byte3 = LUT2K16[(date.Year - roottime) * 3 - 1];
		lY = date.Year - 1;
		sD = byte1 >> 3;
		if ((byte1 & 0x04) == 0)
			sM = 1;
		else
			sM = 2;
	}
	CNN = (byte2 >> 4 != 0); 
	cmpDate.DayInMonth = sD;
	cmpDate.Month = sM;
	cmpDate.Year = lY;
	lM = 1;
	aM = GetMaxDay(lM, byte1, byte2, byte3);
	bool isLeafMonth = false;
	for (uint8_t i = 0; i < 13; i++)
	{
		Date TempDate = cmpDate + aM;
		if (TempDate > currentDate)
		{
			break;
		}
		else
		{
			if (lM == (byte2 >> 4) && CNN)
			{
				CNN = false;
				aM = GetMaxDay(13, byte1, byte2, byte3);
				isLeafMonth = true;
			}
			else
			{
				lM++;
				aM = GetMaxDay(lM, byte1, byte2, byte3);
			}
			cmpDate.DayInMonth = TempDate.DayInMonth;
			cmpDate.Month = TempDate.Month;
			cmpDate.Year = TempDate.Year;
		}
	}
	if (cmpDate.Month == date.Month)
	{
		lD = date.DayInMonth - cmpDate.DayInMonth + 1;
	}
	else
	{
		lD = date.DayInMonth + cmpDate.GetNumberOfDaysInMonth() - cmpDate.DayInMonth + 1;
	}
	return Date(lD, lM, date.Year);
}
}
