#pragma once
// TimeZoneConverter.h

#ifndef TIMEZONECONVERTER_H
#define TIMEZONECONVERTER_H

#include <map>
#include <string>

class TimeZoneConverter {
public:
    std::map<std::string, int> timeZoneOffsets;
    bool isDaylightSavingsActive;

public:
    TimeZoneConverter();
    int getTimeZoneOffset(const std::string& timeZone);
    std::string getCurrentTime(const std::string& timeZone);
    std::string convertTime(const std::string& sourceTimeZone, const std::string& targetTimeZone, const std::string& sourceTime);
    void enableDaylightSavings();
    void disableDaylightSavings();
};

#endif // TIMEZONECONVERTER_H

