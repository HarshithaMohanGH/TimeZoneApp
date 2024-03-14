#include "Globaltimezone.h"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <time.h>
#include <cppconn/driver.h>
#include <mysql_connection.h>
#include <mysql_error.h>
#include <cppconn/prepared_statement.h>
#include "../../TimeZoneApplication2/DatabaseManager.h"


using namespace std;
using namespace sql;


void Globaltimezone::logInteraction(const std::string& interaction) {
	std::ofstream logfile("user_interaction.txt", std::ios::app);
	if (logfile.is_open()) {
		time_t now;
		struct tm timeinfo;
		char timestamp[20];

		time(&now); // Get current system time

		// Convert to local time using localtime_s
		if (localtime_s(&timeinfo, &now) == 0) {
			strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);
			logfile << "[" << timestamp << "] " << interaction << std::endl; // Log interaction with timestamp
			logfile.close();

			// Create an instance of DatabaseManager and pass the connection
			DatabaseManager dbManager;
			dbManager.dbLogInteraction(interaction, std::string(timestamp));
		}
		else {
			std::cerr << "Failed to get local time.\n";
		}
	}
	else {
		std::cout << "Failed to open and store details." << std::endl;
	}
}




void Globaltimezone::displayMenu() {
	cout << "\nWelcome to the Global Time Zone Application\n"
		<< " 1. View current time in different time zones \n "
		<< " 2. Convert time between different time zones \n"
		<< " 3. Toggle daylight savings time on or off. \n"
		<< " 4. Manage fav time zones \n"
		<< " 5. Help and info \n"
		<< " 6. Exit .\n\n"
		<< "Enter your choice";
}

void Globaltimezone::executeChoice(int choice) {
	switch (choice) {
	case 1:
		viewCurrentTime(); break;
	case 2:
		convertTime(); break;
	case 3:
		toggleDayLight(); break;
	case 4:
		manageFavoriteTimeZones();
		break;
	case 5:
		displayHelp();
		break;
	case 6:
		exit(1);
	default:
		cout << "invalid choice\n";
	}
}

void Globaltimezone::viewCurrentTime() {
	string timezone;
	cout << "Enter the name of the timezone\n";
	cin >> timezone;
	if (!timezone.empty() && find_if(timezone.begin(), timezone.end(), [](char c) {
		return isdigit(c);	}) == timezone.end()) {
		if (converter.timeZoneOffsets.find(timezone) != converter.timeZoneOffsets.end()) {
			cout << "Current time in " << timezone << ":" << converter.getCurrentTime(timezone) << "\n\n";
		}
		else {
			cout << "Invalid timezone.\n";
		}
	}
	else {
		cout << "Invalid Input.Please input a valid time zone";

	}
}


void Globaltimezone::convertTime() {
	string sourceTimeZone, targetTimeZone;
	string currentTime = getCurrentSystemTime(); // Get current system time

	// Input for source and target time zones
	cout << "Enter the source time zone: ";
	cin >> sourceTimeZone;
	cout << "Enter the target time zone: ";
	cin >> targetTimeZone;

	// Perform time zone conversion
	cout << "Converted time in " << targetTimeZone << ": " << converter.convertTime(sourceTimeZone, targetTimeZone, currentTime) << "\n\n";
}

std::string Globaltimezone::getCurrentSystemTime() {
	// Get current system time
	time_t now = time(nullptr);
	struct tm timeinfo;
	char currentTime[20];

	// Convert to local time using localtime_s
	if (localtime_s(&timeinfo, &now) == 0) {
		strftime(currentTime, sizeof(currentTime), "%Y-%m-%d %H:%M:%S", &timeinfo);
		return std::string(currentTime);
	}
	else {
		// Handle error
		std::cerr << "Failed to get current system time.\n";
		return "";
	}
}


void Globaltimezone::toggleDayLight() {
	string timezonename, choice;
	cout << "Enable or diable DST?(on/off) ";
	cin >> choice;
	cout << "DST " << choice << " for the time zone\n\n ";
}



void Globaltimezone::manageFavoriteTimeZones() {
	int choice;
	cout << "1. Add fav time zone. \n"
		<< "2. Remove fav time zone. \n"
		<< "3. View fav time zone \n"
		<< "4. to main menu. \n"
		<< "5. Enter choice \n";
	cin >> choice;
	cout << "\n";

	switch (choice) {
	case 1:
		addFavTimeZ(); break;
	case 2:
		removeFavTimeZone(); break;
	case 3:
		viewFavTimeZone(); break;
	case 4:
		break;

	}

}

void Globaltimezone::addFavTimeZ() {
	string timezone;
	cout << " Enter the name of the timezone\n";
	cin >> timezone;
	favoriteTimeZones.insert(pair<int, string>(favoriteTimeZones.size() + 1, timezone));
	cout << "Time zone added to favorites.\n\n";

}

void Globaltimezone::removeFavTimeZone() {
	int index;
	cout << "Enter the index of the time zone to be removed:\n";
	cin >> index;

	if (index > 0 && index <= favoriteTimeZones.size()) {
		auto it = favoriteTimeZones.begin();
		std::advance(it, index - 1);

		cout << "Removed " << it->second << " successfully.\n";
		favoriteTimeZones.erase(it); // Remove the element
	}
	else {
		cout << "Invalid index.\n\n";
	}
}


void Globaltimezone::viewFavTimeZone() {
	cout << "Favourite timezones are: ";
	for (const auto& pair : favoriteTimeZones) {
		cout << pair.first << "." << pair.second << "\n";
	}
	cout << "\n";
}
void Globaltimezone::displayHelp() {
	cout << "Help & Information:\n"
		<< "- This application allows you to view current time in different time zones, convert time between time zones, toggle daylight savings time adjustments, and manage favorite time zones.\n"
		<< "- When converting time between time zones, please enter the time in the format: YYYY-MM-DD HH:MM:SS\n"
		<< "- You can add or remove time zones from your favorites for quick access.\n\n";
}

int main() {
	Globaltimezone app;
	int choice;

	while (true) {
		app.displayMenu();
		//cout << "Enter your choice: ";
		cin >> choice;
		cout << "\n";

		// Log user interaction
		string interaction = "User selected choice " + to_string(choice);
		//app.logInteraction(interaction);
		app.logInteraction(interaction);

		app.executeChoice(choice);
	}

	return 0;
}

