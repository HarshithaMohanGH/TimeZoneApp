#pragma once
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <string>
using namespace std;
using namespace sql;

class DatabaseManager
{
private:
    string server = "tcp://localhost:3307";
    string username = "root";
    string password = "1234";

public:
    Connection* conn;
    Driver* driver;
    DatabaseManager() {
        try {
            driver = get_driver_instance();
            conn = driver->connect(server, username, password);
        }
        catch (SQLException e) {
            cerr << "Could not connect to server. Error message: " << e.what() << endl;
            exit(1);
        }
    }

     ~DatabaseManager() {
        delete conn;
    }

    Connection* getConnection() {
        return conn;
    }

    void dbLogInteraction(const string& interaction, const string& time);
};

