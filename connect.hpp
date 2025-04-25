#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include "mysql.h"

class DatabaseConnector {
private:
    MYSQL* connection;

public:
    DatabaseConnector(const std::string& server, const std::string& user, const std::string& password, const std::string& database) {
        connection = mysql_init(NULL);
        if (connection == NULL) {
            std::cerr << "Error initializing MySQL: " << mysql_error(connection) << std::endl;
            exit(1);
        }

        if (!mysql_real_connect(connection, server.c_str(), user.c_str(), password.c_str(), database.c_str(), 0, NULL, 0)) {
            std::cerr << "Error connecting to MySQL: " << mysql_error(connection) << std::endl;
            mysql_close(connection);
            exit(1);
        }

        std::cout << "Connected successfully" << std::endl;
    }

    ~DatabaseConnector() {
        mysql_close(connection);
    }

    MYSQL* getConnection() {
        return connection;
    }
};

class Concurrent {
private:
    DatabaseConnector connector;

public:
    Concurrent(const std::string& server, const std::string& user, const std::string& password, const std::string& database) : connector(server, user, password, database) {}

    void insertIntoTable(const std::string& data) {
        MYSQL* conn = connector.getConnection();

        std::string query = "INSERT INTO concurrent(nom_concurrent) VALUES('" + data + "')";

        if (mysql_query(conn, query.c_str())) {
            std::cerr << "Error in inserting data: " << mysql_error(conn) << std::endl;
            return;
        }

        std::cout << "Data inserted successfully" << std::endl;
    }
};

int main() {
    Concurrent concurrent("localhost", "root", "root", "rallye");
    concurrent.insertIntoTable("SomeData");

    return 0;
}