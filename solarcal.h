/*
	Solar calculations
	solarcal.h - Library to calculated solar data
	Created by Orlando Aguirre, July 27, 2015
	Release into the public domain.
*/


#ifndef solarcalc_h
#define solarcalc_h

#include "Arduino.h"

class solarcalc
{
  public:
    solarcalc(float, float, float, float);
    void time (int, int, int, int, int, int);
    void calculations();

    float current_time();
    float julian_date();
    float julian_century();
    float solar_noon();
    float sunrise_time();
    float sunset_time();
    float equation_of_time();
    float solar_elevation_atm();    
    float solar_declination();
    float solar_elevation_angle();

  private:
    float latitude, longitude, zenith, timezone;

    int year, month, day, hour, minute, second;

    float current_hour;
    float y, m, a, JD, JC;
    float GMLS, GMAS, EEO, EMoC, STL, STA, SRV, SAL, MOE, OC, SRA;
    float SDec, var_y, EoT, HA, Snoon, Sunrise, Sunset;
    float SDur, TST, HAng, SZA, SEA, AAR, SEAtmR, SAzA;
};

#endif
