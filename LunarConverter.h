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
#define ROOTYEAR = 2000

namespace Espace
{
    const uint8_t LUT2K16[] = { 44,6,147,    // 2000
				192,74,155,  // 2001
				100,5,43,    // 2002
				12,10,91,    // 2003
				176,42,174,  // 2004
				76,5,106,    // 2005
				232,117,229, // 2006
				140,11,165,  // 2007
				60,13,73,    // 2008
				208,93,85,   // 2009
				116,10,149,  // 2010
				28,5,45,     // 2011
				184,69,93,   // 2012
				84,10,181,   // 2013
				248,155,170, // 2014
				156,5,210,   // 2015
				68,13,165,   // 2016
				226,110,138, // 2017
				132,14,74,   // 2018
				44,12,150, // 2019
				200,76,158, // 2020
				100,5,86, // 2021
				12,10,181, // 2022
				176,42,218, // 2023
				84,6,210, // 2024
				232,103,101, // 2025
				140,7,37, // 2026
				52,6,75, // 2027
				208,86,87, // 2028
				108,4,171, // 2029
				20,5,91, // 2030
				186,53,106, // 2031
				92,11,106, // 2032
				248,191,82, // 2033
				156,11,146, // 2034
				68,11,37, // 2035
				226,109,11, // 2036
				124,10,77, // 2037
				36,4,173, // 2038
				192,84,187, // 2039
				100,5,173, // 2040
				12,11,170, // 2041
				176,45,170, // 2042
				84,13,146, // 2043
				240,126,165, // 2044
				140,13,37, // 2045
				52,10,85, // 2046
				210,90,77, // 2047
				116,4,182, // 2048
				20,6,181, // 2049
				186,54,210, // 2050
				92,14,202, // 2051
				12,135,146, // 2052
				148,14,147, // 2053
				68,13,42, // 2054
				226,101,22, // 2055
				124,10,91, // 2056
				36,5,90, // 2057
				194,69,101, // 2058
				100,11,85, // 2059
				20,7,74, // 2060
				168,55,75, // 2061
				76,10,147, // 2062
				232,122,171, // 2063
				140,5,43, // 2064
				44,10,155, // 2065
				208,90,186, // 2066
				116,5,106, // 2067
				28,11,101, // 2068
				184,75,170, // 2069
				92,13,74, // 2070
				248,141,149, // 2071
				156,12,149, // 2072
				60,9,45, // 2073
				216,101,109, // 2074
				124,10,181, // 2075
				44,5,170, // 2076
				192,70,213, // 2077
				100,14,165, // 2078
				20,13,74, // 2079
				176,62,141, // 2080
				76,12,150, // 2081
				232,124,214, // 2082
				140,5,86, // 2083
				52,10,181, // 2084
				210,91,84, // 2085
				116,6,212, // 2086
				28,14,165, // 2087
				192,71,74, // 2088
				84,6,139, // 2089
				240,138,151, // 2090
				148,4,171, // 2091
				60,9,91, // 2092
				218,101,90, // 2093
				124,11,106, // 2094
				44,7,84, // 2095
				200,75,149, // 2096
				100,11,69, // 2097
				12,10,139, // 2098
				168,42,151, // 2099};	// 2k29
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
