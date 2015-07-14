# solarcalc
===========
Library to calculate solar data

## Synopsis

**Solarcalc** is an Spark core / arduino library created to calculate sunrise, sunset, solar noon and solar position at any place on earth based on NOAA Solar Calculator. These equations are base on Astronomical Algorithms by Jean Meeus.
http://www.esrl.noaa.gov/gmd/grad/solcalc/calcdetails.html

The Calculation of Julian Date is based on the formula found on wikipedia.
https://en.wikipedia.org/wiki/Julian_day

## Code Example
  
see file solarcalc.ino

## Motivation

This project was created to automate a fishtank led lights. I was really tired of turning it on/off manually.
I use this library in conjuction with a DS3231 High Precision Real-Time Clock Module to keep the time. The code for this is not included in the example.

## Contributors

NOAA: http://www.esrl.noaa.gov/gmd/grad/solcalc/calcdetails.html
wikipedia: https://en.wikipedia.org/wiki/Julian_day

## License

Release into the public domain.
