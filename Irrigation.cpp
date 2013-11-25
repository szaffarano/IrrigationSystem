#include "Irrigation.h"

Irrigation::Irrigation(IrrigationEvent** schedule, DHT* dht, RTC_DS1307* rtc) {
  this->dht = dht;
  this->rtc = rtc;
  this->schedule = schedule;
}

boolean Irrigation::windowOpen() {    
    DateTime now = rtc->now();
    int secondsNow = now.hour() * 60 * 60 + now.minute() * 60 + now.second();

    int i = 0;
    while(schedule[i] != NULL) {
      Instant* start = schedule[i]->getStart();
      Instant* end = schedule[i++]->getEnd();
      int secondsStart = start->getHour() * 60 * 60 + start->getMinutes() * 60 + start->getSeconds();
      int secondsEnd = end->getHour() * 60 * 60 + end->getMinutes() * 60 + end->getSeconds();
      
      if (secondsNow >= secondsStart && secondsNow <= secondsEnd) {
        return true;
      }
    }
    return false;
}

String Irrigation::dateToDisplay() {
  String str;
  DateTime now = rtc->now();
  if (now.day() < 10) str += "0";
  str += now.day();
  
  str += ".";
  
  if (now.month() < 10) str += "0";
  str += now.month();
  
  str += ".  ";
  
  if (now.hour() < 10) str += "0";
  str += now.hour();
  
  str += ":";
  
  if (now.minute() < 10) str += "0";
  str += now.minute();
  
  str += ":";
  
  if (now.second() < 10) str += "0";
  str += now.second();

  return str;
}

String Irrigation::weatherToDisplay() {
  String str;
  float h = dht->readHumidity();
  float t = dht->readTemperature();

  str += floatToString(h, 2);
  str += "%  ";
  str += floatToString(t, 2);
  str += " *C";
  
  return str;
}

// fuente: http://playground.arduino.cc/Main/FloatToString
// conalgunas modificaciones para simplificar en este caso de uso
String Irrigation::floatToString(float value, int places) {
    int minwidth=0;
    boolean rightjustify=false;
    
    // this is used to write a float value to string, outstr.  oustr is also the return value.
    char outstr[25]; 
    int digit;
    float tens = 0.1;
    int tenscount = 0;
    int i;
    float tempfloat = value;
    int c = 0;
    int charcount = 1;
    int extra = 0;
    // make sure we round properly. this could use pow from <math.h>, but doesn't seem worth the import
    // if this rounding step isn't here, the value  54.321 prints as 54.3209

    // calculate rounding term d:   0.5/pow(10,places)  
    float d = 0.5;
    if (value < 0)
        d *= -1.0;
    // divide by ten for each decimal place
    for (i = 0; i < places; i++)
        d/= 10.0;    
    // this small addition, combined with truncation will round our values properly 
    tempfloat +=  d;

    // first get value tens to be the large power of ten less than value    
    if (value < 0)
        tempfloat *= -1.0;
    while ((tens * 10.0) <= tempfloat) {
        tens *= 10.0;
        tenscount += 1;
    }

    if (tenscount > 0)
        charcount += tenscount;
    else
        charcount += 1;

    if (value < 0)
        charcount += 1;
    charcount += 1 + places;

    minwidth += 1; // both count the null final character
    if (minwidth > charcount){        
        extra = minwidth - charcount;
        charcount = minwidth;
    }

    if (extra > 0 and rightjustify) {
        for (int i = 0; i< extra; i++) {
            outstr[c++] = ' ';
        }
    }

    // write out the negative if needed
    if (value < 0)
        outstr[c++] = '-';

    if (tenscount == 0) 
        outstr[c++] = '0';

    for (i=0; i< tenscount; i++) {
        digit = (int) (tempfloat/tens);
        itoa(digit, &outstr[c++], 10);
        tempfloat = tempfloat - ((float)digit * tens);
        tens /= 10.0;
    }

    // if no places after decimal, stop now and return

    // otherwise, write the point and continue on
    if (places > 0)
    outstr[c++] = '.';


    // now write out each decimal place by shifting digits one by one into the ones place and writing the truncated value
    for (i = 0; i < places; i++) {
        tempfloat *= 10.0; 
        digit = (int) tempfloat;
        itoa(digit, &outstr[c++], 10);
        // once written, subtract off that digit
        tempfloat = tempfloat - (float) digit; 
    }
    if (extra > 0 and not rightjustify) {
        for (int i = 0; i< extra; i++) {
            outstr[c++] = ' ';
        }
    }

    outstr[c++] = '\0';
    return String(outstr);
}
