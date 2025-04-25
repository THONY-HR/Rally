#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

int main() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
        con->setSchema("rallye");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM table_name");

        while (res->next()) {
            std::cout << "Column 1: " << res->getString(1) << std::endl;
            std::cout << "Column 2: " << res->getString(2) << std::endl;
            // Ajoutez d'autres colonnes si nécessaire
        }

        delete res;
        delete stmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cout << "SQLException: " << e.what() << std::endl;
    }

    return 0;
}

// g++ connexion.cpp -o rallye.exe -I "C:\MySQL\MySQL Connector C++ 8.1\include\jdbc" -L "C:\MySQL\MySQL Connector C++ 8.1\lib64" 
// g++ connexion.cpp -o rallye.exe -I "C:\MySQL\MySQL Connector C++ 8.1\include\jdbc" -L "C:\MySQL\MySQL Connector C++ 8.1\lib64" -lmysqlcppconn 
