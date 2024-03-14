#pragma once

#pragma once

// Globaltimezone.h

#ifndef GLOBALTIMEZONE_H
#define GLOBALTIMEZONE_H

#include <string>
#include <map>
#include "TimeZoneConverter.h" // Include the header file for TimeZoneConverter class
#include "../../TimeZoneApplication2/DatabaseManager.h"

class Globaltimezone {
private:
    Connection* conn;
public:
    TimeZoneConverter converter;
    std::map<int, std::string> favoriteTimeZones;

    //static void logInteraction(const std::string& interaction);
    Globaltimezone() : conn(nullptr) {}

    Globaltimezone(Connection* connection) : conn(connection) {}
    void logInteraction(const std::string& interaction); //, Connection* conn
    void displayMenu();
    void executeChoice(int choice);
    void viewCurrentTime();
    void convertTime();
    std::string getCurrentSystemTime();
    bool isValidTimeFormat(const std::string& time);
    void toggleDayLight();
    void manageFavoriteTimeZones();
    void addFavTimeZ();
    void removeFavTimeZone();
    void viewFavTimeZone();
    void displayHelp();
};

#endif // GLOBALTIMEZONE_H


