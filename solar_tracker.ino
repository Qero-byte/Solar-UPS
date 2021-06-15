#include <Servo.h>
#include <RTClib.h>
#include <Wire.h>
#include <SoftwareSerial.h>

RTC_DS1307 RTC;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

float latitude = 56.42234;
float longitude = 58.50577;
float correction_fac = 180.0;
int yearT = 0;
int monthT = 0;
int dayT = 0;
int hourT = 0;
int minuteT = 0;
float localTime = 0.0;
float timeZone = 5.0; //Arti, +5:00
float GMT = 0.0;
int d = 0;
float w = 0.0;
float e = 0.0;
float M = 0.0;
float oblecl = 0.0;
float L = 0.0;
float E = 0.0;
float x = 0.0;
float y = 0.0;
float z = 0.0;
float r = 0.0;
float v = 0.0;
float lon = 0.0;
float xequat = 0.0;
float yequat = 0.0;
float zequat = 0.0;
float RA = 0.0;
float Decl = 0.0;
float GMST0 = 0.0;
float SIDTIME = 0.0;
float HA = 0.0;
float xhor = 0.0;
float yhor = 0.0;
float zhor = 0.0;
float azimuth = 0.0;
float altitude = 0.0;
float azimuth_servo = 0.0;
float altitude_servo = 0.0;

Servo horizontal;
Servo vertical;

float aboba(float x) {
  int rv = x - floor(x / 360) * 360;
  if (rv < 0) {
    rv += 360;
  }
  return (rv);
}

void setup() {
  Serial.begin(9600);
  RTC.begin();
  horizontal.attach(3);
  vertical.attach(2);
  horizontal.write(90);
  vertical.write(0);
}

void loop() {
  DateTime now = RTC.now();
  yearT = now.year();
  monthT = now.month();
  dayT = now.day();
  hourT = now.hour();
  minuteT = now.minute();
  localTime = float(now.hour()) + (float(now.minute()) / 100.0); //Hour + (Minutes / 60)
  GMT = localTime - timeZone;
  d = round(367 * yearT - (7 * (yearT + ((monthT + 9) / 12))) / 4 + (275 * monthT) / 9 + dayT - 730530);
  w = 282.9404 + 4.70935E-5 * d;   // longitude of perihelion (degrees)
  e = 0.016709 - 1.151E-9 * d;     // eccentricity
  M = 356.0470 + 0.9856002585 * d; // mean anomaly (degrees)
  M = aboba(M);
  oblecl = 23.4393 - 3.563E-7 * d; // obliquity of the ecliptic
  L = aboba(w + M); // Sun's mean longitude
  E = M + (180 / PI) * e * sin(radians(M)) * (1 + e * cos(radians(M)));
  x = cos(radians(E)) - e;
  y = sin(radians(E)) * sqrt(1 - e * e);
  r = sqrt(x * x + y * y); // Heliocentric distance: the planet's distance from the Sun
  v = degrees(atan2(y, x));
  lon = aboba(v + w);
  x = r * cos(radians(lon));
  y = r * sin(radians(lon));
  xequat = x;
  yequat = y * cos(radians(oblecl));
  zequat = y * sin(radians(oblecl));
  RA = degrees(atan2(yequat, xequat)) / 15;
  Decl = degrees(atan2(zequat, sqrt(xequat * xequat + yequat * yequat)));
  GMST0 = L / 15 + 12;
  SIDTIME = GMST0 + GMT + longitude / 15;
  HA = (SIDTIME - RA) * 15;
  x = cos(radians(HA)) * cos(radians(Decl));
  y = sin(radians(HA)) * cos(radians(Decl));
  z = sin(radians(Decl));
  xhor = x * sin(radians(latitude)) - z * cos(radians(latitude));
  yhor = y;
  zhor = x * cos(radians(latitude)) + z * sin(radians(latitude));
  azimuth = degrees(atan2(yhor, xhor)) + 180;
  altitude = degrees(atan2(zhor, sqrt(xhor * xhor + yhor * yhor)));
  if (azimuth < 0) {
    azimuth += 360;
  }
  if (azimuth != 0 and azimuth >= 180) {
    azimuth_servo = azimuth - correction_fac;
  } else {
    if (azimuth == 0) {
      azimuth_servo = 180;
    } else {
      azimuth_servo = 0;
    }
  }
  if (altitude <= 90) {
    altitude_servo = altitude;
  } else {
    altitude_servo = 0;
  }
  horizontal.write(azimuth_servo);
  vertical.write(altitude_servo);
  Serial.println("Azimuth:" + String(azimuth));
  Serial.println("Height:" + String(altitude));
  Serial.println("Year:" + String(yearT));
  Serial.println("Month:" + String(monthT));
  Serial.println("Day:" + String(dayT));
  Serial.println("Hour:" + String(hourT));
  Serial.println("Minute:" + String(minuteT));
  Serial.println("GMT:" + String(GMT));
  Serial.println("Local time:" + String(localTime));
  Serial.println("Servo height:" + String(altitude_servo));
  Serial.println("-----------------------------------------------------------------"); 
}
