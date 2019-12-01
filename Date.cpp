
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

#include "Date.h"
namespace Espace
{
Date::Date()
{
	DayInWeek = 1;
	DayInMonth = 24;
	Month = 9;
	Year = 18;
}

Date::Date(uint8_t date, uint8_t month, uint16_t year)
{
	DayInMonth = date;
	Month = month;
	Year = year;
	DayInWeek = getDayOfWeek();
	IsLeafYear = isLeafYear();
}

uint8_t Date::getDayOfWeek()	
{
	uint16_t y = Year + 2000;
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	y -= Month < 3;
	return (y + y/4 - y/100 + y/400 + t[Month-1] + DayInMonth) % 7;
}

bool Date::isLeafYear()
{
	int realyear = 2000 + Year;
	return (realyear % 4 == 0) && ((realyear % 400 == 0) || (realyear % 100 != 0));
}

uint8_t Date::GetNumberOfDaysInMonth()
{
	char number;
	switch (Month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
	{
		number = 31;
		break;
	}
	case 2:
	{
		if (isLeafYear())
		{
			number = 29;
		}
		else
		{
			number = 28;
		}
		break;
	}
	default:
	{
		number = 30;
		break;
	}
	}
	return number;
}

bool Date::operator>(const Date d2)
{
	return (Year > d2.Year) || 
		(Year == d2.Year && Month > d2.Month) ||
		(Year == d2.Year && Month == d2.Month && DayInMonth > d2.DayInMonth);
}

bool Date::operator<(const Date d2)
{
	return (Year < d2.Year) || 
	(Year == d2.Year && Month < d2.Month) ||
	(Year == d2.Year && Month == d2.Month && DayInMonth < d2.DayInMonth);
}

bool Date::operator=(const Date d2)
{
	return (Year == d2.Year && Month == d2.Month && DayInMonth == d2.DayInMonth);
}

Date Date::operator+(const uint8_t b)
{
	Date addedDate(DayInMonth + b, Month, Year);
	while (addedDate.DayInMonth > addedDate.GetNumberOfDaysInMonth())
	{
		addedDate.DayInMonth = addedDate.DayInMonth - addedDate.GetNumberOfDaysInMonth();
		addedDate.Month++;
		if (addedDate.Month == 13)
		{
			addedDate.Year++;
			addedDate.Month = 1;
		}
	}
	return addedDate;
}
}