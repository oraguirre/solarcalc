/*
	Solar calculations
	solarcal.cpp - Library to calculated solar data
	Created by Orlando Aguirre, July 27, 2015
	Release into the public domain.
*/
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <solarcalc.h>
#elif defined(SPARK)
#include "application.h"
#include "solarcalc/solarcalc.h"
#endif

#include <math.h>
#define pi 3.14159265358979323846
#define Radians 0.017453292519943295769 // (pi/180)
#define Degrees 57.295779513082320877  // (180/pi)

solarcalc::solarcalc(float _latitude, float _longitude, float _zenith, float _timezone) {

  latitude   = _latitude;
  longitude  = _longitude;
  zenith     = _zenith;
  timezone   = _timezone;
}

void solarcalc::time(int _year, int _month, int _day, int _hour, int _minute, int _second) {

  year = _year;
  month = _month;
  day = _day;
  hour = _hour;
  minute = _minute;
  second = _second;

}

void solarcalc::calculations() {

  current_hour = float(hour) + (float(minute) / 60) + (float(second) / 3600);
  a = floor((14 - month) / 12);
  y = year + 4800 - a;
  m = month - 12 * a - 3;
  //Julian Date
  JD = (day + floor((153 * m + 2) / 5) + 365 * y + floor(y / 4) - floor(y / 100) + floor(y / 400) - 32045) + (current_hour - 12) / 24;
  //Julian Century
  JC = (JD - 2451545) / 36525;
  //Geom Mean Long Sun (deg)
  GMLS = fmod(280.46646 + JC * (36000.76983 + JC * 0.0003032),360);
  //Geom Mean Anom Sun (deg)
  GMAS = 357.52911 + JC * (35999.05029 - 0.0001537 * JC);
  //Eccent Earth Orbit
  EEO = 0.016708634 - JC * (0.000042037 + 0.0000001267 * JC);
  //Sun Eq of Ctr
  EMoC = sin(Radians * (GMAS)) * (1.914602 - JC * (0.004817 + 0.000014 * JC)) + sin(Radians * (2 * GMAS)) * (0.019993 - 0.000101 * JC) + sin(Radians * (3 * GMAS)) * 0.000289;
  //Sun True Long (deg)
  STL = GMLS + EMoC;
  //Sun True Anom (deg)
  STA = GMAS + EMoC;
  //Sun Rad Vector (AUs)
  SRV = (1.000001018 * (1 - EEO * EEO)) / (1 + EEO * cos(Radians * (STA)));
  //Sun App Long (deg)
  SAL = STL - 0.00569 - 0.00478 * sin(Radians * (125.04 - 1934.136 * JC));
  //Mean Obliq Ecliptic (deg)
  MOE = 23 + (26 + ((21.448 - JC * (46.815 + JC * (0.00059 - JC * 0.001813)))) / 60) / 60;
  //Obliq Corr (deg)
  OC = MOE + 0.00256 * cos(Radians * (125.04 - 1934.136 * JC));
  //Sun Rt Ascen (deg)
  SRA = Degrees * (atan2(cos(Radians * (SAL)), cos(Radians * (OC)) * sin(Radians * (SAL))));
  //Sun Declin (deg)
  SDec = Degrees * (asin(sin(Radians * (OC)) * sin(Radians * (SAL))));
  //var y
  var_y = tan(Radians * (OC / 2)) * tan(Radians * (OC / 2));
  //Eq of Time (minutes)
  EoT = 4 * Degrees * (var_y * sin(2 * Radians * (GMLS)) - 2 * EEO * sin(Radians * (GMAS)) + 4 * EEO * var_y * sin(Radians * (GMAS)) * cos(2 * Radians * (GMLS)) - 0.5 * var_y * var_y * sin(4 * Radians * (GMLS)) - 1.25 * EEO * EEO * sin(2 * Radians * (GMAS)));
  //HA Sunrise (deg)
  HA = Degrees * (acos(cos(Radians * (90.833)) / (cos(Radians * (latitude)) * cos(Radians * (SDec))) - tan(Radians * (latitude)) * tan(Radians * (SDec))));
  //Solar Noon (LST)
  Snoon = (720 - 4 * longitude - EoT + timezone * 60) / 1440 * 24;
  //Sunrise Time (LST)
  Sunrise = Snoon - HA * 4 / 1440 * 24;
  //Sunset Time (LST)
  Sunset = Snoon + HA * 4 / 1440 * 24;
  //Sunlight Duration (minutes)
  SDur = 8 * HA;
  //True Solar Time (min)
  TST = fmod(current_hour * 1440 + EoT + 4 * longitude - 60 * timezone,1440);
  //Hour Angle (deg)
  if (TST / 4 < 0) {
    HAng = TST / 4 + 180;
  }
  else {
    HAng = TST / 4 - 180;
  }
  //Solar Zenith Angle (deg)
  SZA = Degrees * (acos(sin(Radians * (latitude)) * sin(Radians * (SDec)) + cos(Radians * (latitude)) * cos(Radians * (SDec)) * cos(Radians * (HAng))));
  //Solar Elevation Angle (deg)
  SEA = 90 - SZA;
  //Approx Atmospheric Refraction (deg)
  if (SEA > 85) {
    AAR = 0;
  }
  else {
    if (SEA > 5) {
      AAR = (58.1 / tan(Radians * (SEA)) - 0.07 / pow(tan(Radians * (SEA)), 3) + 0.000086 / pow(tan(Radians * (SEA)), 5)) / 3600;
    }
    else {
      if (SEA > -0.575) {
        AAR = (1735 + SEA * (-518.2 + SEA * (103.4 + SEA * (-12.79 + SEA * 0.711)))) / 3600;
      }
      else {
        AAR = (-20.772 / tan(Radians * (SEA))) / 3600;
      }
    }
  }
  //Solar Elevation corrected for atm refraction (deg)
  SEAtmR = SEA + AAR;
  //Solar Azimuth Angle (deg cw from N)
  if (HAng > 0) {
    SAzA = fmod(Degrees * (acos(((sin(Radians * (latitude)) * cos(Radians * (SZA))) - sin(Radians * (SDec))) / (cos(Radians * (latitude)) * sin(Radians * (SZA))))) + 180,360);
  }
  else {
    SAzA = fmod(540 - Degrees * (acos(((sin(Radians * (latitude)) * cos(Radians * (SZA))) - sin(Radians * (SDec))) / (cos(Radians * (latitude)) * sin(Radians * (SZA))))),360);
  }

}

float solarcalc::current_time() {
  return current_hour;
}

float solarcalc::julian_date() {
  return JD;
}

float solarcalc::julian_century() {
  return JC;
}

float solarcalc::solar_noon() {
  return Snoon;
}

float solarcalc::sunrise_time() {
  return Sunrise;
}

float solarcalc::sunset_time() {
  return Sunset;
}

float solarcalc::solar_elevation_atm() {
  return SEAtmR;
}

float solarcalc::equation_of_time() {
  return EoT;
}

float solarcalc::solar_declination() {
  return SDec;
}

float solarcalc::solar_elevation_angle() {
  return SAzA;
}
