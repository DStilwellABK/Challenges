#include <iostream>
#include <thread>
#include <fstream>
#include <conio.h>
#include <list>
#include <enet/enet.h>

using namespace std;

//void CreateClient();

void ConnectToServer(string name);
void DisconnectFromServer();
void GetMessageFromServer();
void UpdateClientConsole();
void SendMessageToServer(string name);
void CreateClient();

list<string> messages;
ENetHost* client;
string currentInput;

int main()
{

    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        cout << "An error occurred while initializing ENet.\n" << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);
    client = nullptr;
    
    CreateClient();

    string name = "";

    cout << "Please enter a name: ";
    cin >> name;

    ConnectToServer(name);

    
    return EXIT_SUCCESS;
}

void CreateClient() {

    client = enet_host_create(NULL /* create a client host */,
        1 /* only allow 1 outgoing connection */,
        2 /* allow up 2 channels to be used, 0 and 1 */,
        0 /* assume any amount of incoming bandwidth */,
        0 /* assume any amount of outgoing bandwidth */);
    if (client == nullptr)
    {
        fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
        exit(EXIT_FAILURE);
    }
}


void ConnectToServer(string name) {
    ENetAddress address;
    ENetEvent event;
    ENetPeer* peer;
    
    /* Connect to some.server.net:1234. */
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;

    /* Initiate the connection, allocating the two channels 0 and 1. */
    peer = enet_host_connect(client, &address, 2, 0);

    if (peer == NULL)
    {
        fprintf(stderr,
            "No available peers for initiating an ENet connection.\n");
        exit(EXIT_FAILURE);
    }
    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        cout << "Connection to 127.0.0.1:1234 succeeded." << endl;
    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(peer);
        cout << "Connection to 127.0.0.1:1234 failed." << endl;
    }



    system("cls");
    // Thread off the client sending messages while on the main thread we'll be checking if the client should be getting any messages 
    // and have both run at the same time.
    thread SendAMessage(SendMessageToServer, name);
    thread UpdateConsoleThread(UpdateClientConsole);
    GetMessageFromServer();

    SendAMessage.join();
    UpdateConsoleThread.join();
}


void GetMessageFromServer() {
    ENetEvent event;
    string message;
    while (true) {
        while (enet_host_service(client, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_RECEIVE:
                message = (char*)event.packet->data;
                messages.push_back(message);
                //cout << message << endl;
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);
            }
        }
    }
}

void SendMessageToServer(string name) {
    cout << endl;
    cout << endl;
    cout << "Enter a message or type quit to leave: " << endl;
    
    list<string> chatHistory = list<string>();
    while (currentInput != "quit") {

        currentInput = "";
        char key;
        int keyStrokeChecker;
        //while (testKeyStroke != Enter key, what ever number that was again)
        while (true) {
            keyStrokeChecker = _getch();
            // If we didn't hit enter yet, then display what the user is type into the console for the user.
            if (keyStrokeChecker != 130) {
                if (keyStrokeChecker != 8) {
                    key = _getch();
                    currentInput += key;
                }
                else if (currentInput.length() > 0) {
                    currentInput.erase(currentInput.length() - 1);
                }
            }

            //UpdateClientConsole();
            //cout << currentInput;

        }
        if (currentInput != "quit" && currentInput.length()>0) {
            
            string message = name + ": " + currentInput;
            ENetPacket* packet = enet_packet_create(message.c_str(),
                message.length() + 1,
                ENET_PACKET_FLAG_RELIABLE);

            enet_host_broadcast(client, 0, packet);

            enet_host_flush(client);
        }

    }
}

void ClearScreen() {
    int x = 0, y = 0;
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void UpdateClientConsole() {
    while (true) {
        ClearScreen();
        for (string message : messages) {
            cout << message << endl;
        }

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "Say (hit enter to send a message): " << currentInput;
    }

}


void DisconnectFromServer() {

}