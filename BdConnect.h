# 1 "Bdconnect.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "Bdconnect.cpp"






using namespace std;

class BdConnect
{
private:
    OCI_Connection* connection;

public:
    BdConnect() : connection(nullptr)
    {}

    ~BdConnect()
    {
        disconnect();
    }

    void connect()
    {
        if (!OCI_Initialize(nullptr, nullptr, OCI_ENV_DEFAULT))
        {
            throw runtime_error("Erreur d'initialisation OCI");
        }


        connection = OCI_ConnectionCreate(
            "orcl",
            "rallye",
            "nilo",
            OCI_SESSION_DEFAULT);
        if (connection == nullptr)
        {
            handleOCIError();
        }
        cout << "Connexion réussie à la base de données Oracle" << endl;
    }

    void disconnect()
    {
        if (connection != nullptr)
        {
            OCI_ConnectionFree(connection);
            connection = nullptr;
            cout << "Déconnexion de la base de données Oracle" << endl;
        }
    }

    OCI_Resultset* executeQuery(const char* query)
    {
        OCI_Statement* statement = OCI_StatementCreate(connection);
        if (statement == nullptr)
        {
            handleOCIError();
        }

        OCI_ExecuteStmt(statement, query);
        return OCI_GetResultset(statement);
    }

private:
    void handleOCIError()
    {
        OCI_Error* error = OCI_GetLastError();
        if (error != nullptr)
        {
            throw runtime_error(OCI_ErrorGetString(error));
        } else
        {
            throw runtime_error("Erreur OCI inconnue");
        }
    }
};
