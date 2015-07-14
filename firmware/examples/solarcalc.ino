  //Wire is just used on arduino, comment out using spark core
  #include "Wire.h"
  //Arduino statement
  #include <solarcalc.h>
  //Spark core statement
  //#include "solarcalc/solarcalc.h"
  
  float latitude = -34.9290;
  float longitude = 138.6010;
  float zenith = 90.833;
  float timezone = 9.5;
  
  int second=0;
  int minute=0;
  int hour=12;
  int dayOfMonth=14;
  int month=7;
  int year=2015;
 
  //Arduino
  solarcalc solardata = solarcalc(latitude, longitude, zenith, timezone);
 
  //Spark Core
  //solarcalc solardata(latitude, longitude, zenith, timezone);
  
  void setup() {
  //Wire is just used on arduino, comment out using spark core
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
