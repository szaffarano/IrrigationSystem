#ifndef _EVENTO_H_
#define _EVENTO_H_

#include <Arduino.h>

class Instant {
  public:
    Instant(int hour, int minutes, int seconds);
    int getHour();
    int getMinutes();
    int getSeconds();
  private:
    int hour, minutes, seconds;
};

class IrrigationEvent {
  public:
    IrrigationEvent(String start, String end);
    IrrigationEvent(char* start, char* end);
    IrrigationEvent(Instant* start, Instant* end);
    String toString();
    Instant* getStart();
    Instant* getEnd();
  private:
    Instant* start;
    Instant* end;
    Instant* fromString(String instant);
};
#endif
