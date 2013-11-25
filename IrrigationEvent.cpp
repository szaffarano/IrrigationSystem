#include "IrrigationEvent.h"

Instant::Instant(int hour, int minutes, int seconds) {
  this->hour = hour;
  this->minutes = minutes;
  this->seconds = seconds;
}

int Instant::getHour() {
  return this->hour;
}

int Instant::getMinutes() {
  return this->minutes;
}

int Instant::getSeconds() {
  return this->seconds;
}

IrrigationEvent::IrrigationEvent(Instant* start, Instant* end) {
  this->start = start;
  this->end = end;
}

IrrigationEvent::IrrigationEvent(String start, String end) {
  this->start = fromString(start);
  this->end = fromString(end);
}

IrrigationEvent::IrrigationEvent(char* start, char* end) {
  this->start = fromString(String(start));
  this->end = fromString(String(end));
}

Instant* IrrigationEvent::getStart() {
  return this->start;
}

Instant* IrrigationEvent::getEnd() {
  return this->end;
}

Instant* IrrigationEvent::fromString(String instant) {
  int idxHour = instant.indexOf(":");
  int idxMinutes = instant.indexOf(":", idxHour+1);
  int hour = instant.substring(0, idxHour+1).toInt();
  int minutes = instant.substring(idxHour+1, idxMinutes).toInt();
  int seconds = instant.substring(idxMinutes+1, instant.length()).toInt();

  return new Instant(hour, minutes, seconds);
}

String IrrigationEvent::toString() {
  String str = "";
  str += "Event [Inicio= ";
  
  str += start->getHour();
  str += ":";
  str += start->getMinutes();
  str += ":";
  str += start->getSeconds();

  str += " Fin= ";
  
  str += end->getHour();
  str += ":";
  str += end->getMinutes();
  str += ":";
  str += end->getSeconds();
  str += "]";
  
  return str;
}
