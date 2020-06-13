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
#include <Arduino.h>
#ifndef Date_h
#define Date_h
namespace Espace
{
class Date
{
  public:
		uint8_t DayInWeek;
		uint8_t DayInMonth;
		uint8_t Month;
		uint16_t Year;
		bool IsLeafMonth;
		bool IsLeafYear;
		Date();
		Date(uint8_t date, uint8_t month, uint16_t year);
		uint8_t GetNumberOfDaysInMonth();
		bool operator>(const Date d2);
		bool operator<(const Date d2);
		bool operator=(const Date d2);
		Date operator+(uint8_t b);
		Date getLunarDateMonth();
	private:
		uint8_t getDayOfWeek();
		bool isLeafYear();
};
}
#endif