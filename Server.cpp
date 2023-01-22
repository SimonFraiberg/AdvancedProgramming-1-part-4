#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include "Distance.h"
#include "InputValidation.h"
#include "DataBase.h"
#include "KNN.h"
#include "UploadCommand.h"

using namespace std;
/*
 *creating a TCP server to accept from client vector, distance function and K for KNN algorithem. returning KNN result to client.
 *wating for clients to connet in infinite loop.
 */
int main(int argc, char *argv[])
{
    string classification;
    if (argc != 3)
    {
        cout << "wrong number of arguments. there should be 3 arguments" << endl;
        return 0;
    }
    // create the data base
    multimap<vector<double>, string> dataBase;
    dataBase = DataBase::createDataBaseFromFIle(argv[1]); // argv[1] should be file name of the data base.
    if (dataBase.empty())
    {
        cout << "an error has occurred in the data base" << endl;
        return 0;
    }
    int temp = 0;
    try
    {
        temp = stoi(argv[2]); // argv[2] should be the port to listen to.
    }
    catch (...)
    {
        cout << "port number is not valid \n";
        return 0;
    }

    const int server_port = temp;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("error binding socket");
    }
    if (listen(sock, 5) < 0)
    {
        perror("error listening to a socket");
    }
    while (true)
    {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *)&client_sin, &addr_len);
        if (client_sock < 0)
        {
            perror("error accepting client");
        }
        while (true)
        {

            char buffer[4096];
            memset(buffer, 0, sizeof(buffer));
            bool invalidFlag = false;
            string classification = "invalid input";

            int expected_data_len = sizeof(buffer);
            int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
            if (read_bytes == 0)
            {
                break;
            }
            else if (read_bytes < 0)
            {
                invalidFlag = true;
                classification = "invalid input";
            }
            else
            {

                if (strlen(buffer) == 1 && buffer[0] == '1')
                {

                    memset(buffer, 0, sizeof(buffer));
                    SocketIO socket(client_sock);
                    UploadCommand command(socket);
                    command.execute();
                }
            }
        }
        close(client_sock);
    }
    close(sock);
    return 0;
}
