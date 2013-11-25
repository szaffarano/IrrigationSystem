#ifndef _IRRIGATION_H_
#define _IRRIGATION_H_

#include <DHT.h>
#include <RTClib.h>
#include "IrrigationEvent.h"

class Irrigation {
  public:
    Irrigation(IrrigationEvent** schedule, DHT* dht, RTC_DS1307* rtc);
    boolean windowOpen();
    String dateToDisplay();
    String weatherToDisplay();
  private:
    DHT* dht;
    RTC_DS1307* rtc;
    IrrigationEvent** schedule;
    String floatToString(float value, int places);
};

#endif // _IRRIGATION_H_
