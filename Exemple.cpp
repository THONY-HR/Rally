#include "OracleDatabase.h"

int main() 
{
    try 
    {
        OracleDatabase db;
        db.connect();
        
        OCI_Resultset* resultSet = db.executeQuery("SELECT * FROM Stock");
        while (OCI_FetchNext(resultSet)) 
        {
            int id = OCI_GetInt(resultSet, 1);
            std::string name = OCI_GetString(resultSet, 2);
            std::cout << "ID: " << id << ", Name: " << name << std::endl;
        }

        db.disconnect();
    } catch (const std::exception& e) 
    {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
