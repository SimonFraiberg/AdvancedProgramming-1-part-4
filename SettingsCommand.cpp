#include "SettingsCommand.h"

SettingsCommand::SettingsCommand(SocketIO socket, multimap<vector<double>, string> &database,
                                 int &k, string &distanceMatric) : socket(socket),
                                                                   database(database),
                                                                   k(k),
                                                                   distanceMatric(distanceMatric)

{
}

void SettingsCommand::execute()
{
    this->description = "The current KNN parameters are: K = " + to_string(this->k) + ", DISTANCE METRIC = " + this->distanceMatric + "\n";
    send(socket.getSock(), description.c_str(), description.size(), 0);

    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    // Receive the file size
    int bytes = recv(socket.getSock(), buffer, sizeof(buffer), 0);

    string input = string(buffer, bytes);

    bool invaild = false;
    int tempK;
    string distanceFunc;
    string error;
    stringstream stream(input);
    stream >> tempK;
    stream >> distanceFunc;

    if (tempK <= 0)
    {
        invaild = true;
        error = "invaild value for K\n";
    }
    // CHECK: If K is greater than the number of vectors in the database we define him to be the size of the database.
    if (tempK > database.size())
    {
        invaild = true;
        error = "invaild value for K\n";
    }

    // CHECK: if the user entered a non-existent distance function - not one of the existing options.
    vector<double> v1 = {1, 2};
    vector<double> v2 = {2, 3};

    double tempDistance = Distance::distanceAcorddingTo(v1, v2, distanceFunc);
    if (tempDistance == -1)
    {
        invaild = true;
        error += "invalid value for metric\n";
    }

    if (!invaild)
    {
        this->distanceMatric = distanceFunc;
        this->k = tempK;
        string changed = "changed";
        send(socket.getSock(), changed.c_str(), changed.size(), 0);
    }
    else
    {
        send(socket.getSock(), error.c_str(), error.size(), 0);
    }
}
