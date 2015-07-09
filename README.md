# solarcalc
Library to calculate solar data

## Synopsis

**Solarcalc** is an arduino library created to calculate sunrise, sunset, solar noon and solar position at any place on earth based on NOAA Solar Calculator. These equations are base on Astronomical Algorithms by Jean Meeus.
http://www.esrl.noaa.gov/gmd/grad/solcalc/calcdetails.html

The Calculation of Julian Date is based on the formula found on wikipedia.
https://en.wikipedia.org/wiki/Julian_day

## Code Example
  
  #include "Wire.h"
  #include <solarcalc.h>
  
  int second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  
  void setup() {
    Wire.begin();
    Serial.begin(9600);
  }
 void loop() { 
  solardata.time(year, month, dayOfMonth, hour, minute, second);
  solardata.calculations();
  Serial.println("-----------------------");
  Serial.println(solardata.current_time());
  Serial.println(solardata.julian_date());
  Serial.println(solardata.solar_noon());
  Serial.println(solardata.sunrise_time());
  Serial.println(solardata.sunset_time());
  Serial.println(solardata.equation_of_time());
  Serial.println(solardata.solar_elevation_atm());
  Serial.println(solardata.solar_declination());
  Serial.println(solardata.solar_elevation_angle());
}

## Motivation

This project was created to automate a fishtank led lights. I was really tired of turning it on/off manually.
I use this library in conjuction with a DS3231 High Precision Real-Time Clock Module to keep the time. The code for this is not included in the example.

## Contributors

NOAA: http://www.esrl.noaa.gov/gmd/grad/solcalc/calcdetails.html
wikipedia: https://en.wikipedia.org/wiki/Julian_day

## License

Release into the public domain.
