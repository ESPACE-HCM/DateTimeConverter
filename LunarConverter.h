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

#ifndef LunarConverter_h
#define LunarConverter_h
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif
#include "Date.h"

namespace Espace
{
    const uint8_t LUT2K16[] = {68, 13, 165,   // 2k16
								 226, 110, 138, // 2k17
								 132, 14, 74,   // 2k18
								 44, 12, 150,   // 2k19
								 200, 12, 150,  // 2k20
								 100, 5, 86,	// 2k21
								 12, 10, 181,   // 2k22
								 176, 42, 218,  // 2k23
								 84, 6, 210,	// 2k24
								 232, 103, 101, // 2k25
								 140, 7, 37,	// 2k26
								 52, 6, 75,		// 2k27
								 208, 86, 87,   // 2k28
								 104, 0, 0};	// 2k29
    class LunarConverter
    {
    private:
        uint8_t GetMaxDay(uint8_t lunarMonth, uint8_t byte1, uint8_t byte2, uint8_t byte3);
    public:
        LunarConverter();
        ~LunarConverter();
        Date Convert(Date date);
    };
}
#endif