  #include "Wire.h"
  #include <solarcalc.h>
  
  float latitude = -34.9290;
  float longitude = 138.6010;
  float zenith = 90.833;
  float timezone = 9.5;
  int second, minute, hour, dayOfWeek, dayOfMonth, month, year;
 
  solarcalc solardata = solarcalc(latitude, longitude, zenith, timezone);
 
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
