#include <iostream>
#include <thread>
#include <enet/enet.h>

using namespace std;

bool quit = false;

string currentResponse = "";

void CreateServer();
string Lowercase(string input);
void BroadcastToAllUser(string message);

ENetAddress address;
ENetHost* server;

int main()
{

    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        cout << "An error occurred while initializing ENet.\n" << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    CreateServer();
    while (1)
    {
        ENetEvent event;
        string message;
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(server, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                cout << "A new client connected from "
                    << event.peer->address.host
                    << ":" << event.peer->address.port
                    << endl
                    << endl;
                /* Store any relevant client information here. */
                event.peer->data = (void*)("Client information");

                // THIS SENDS INFO TO THE CLIENTS

                break;
            case ENET_EVENT_TYPE_RECEIVE:
                 message = (char*)event.packet->data;
                cout << "User " << message << endl;
                //<< "was received from " << (char*)event.peer->data
                //<< " on channel " << event.channelID << endl;
            /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);
                BroadcastToAllUser(message);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                cout << (char*)event.peer->data << ": disconnected." << endl;
                /* Reset the peer's client information. */
                event.peer->data = NULL;
            }
        }
    }
    //string input;
    //while (1) {
    //    system("cls");
    //    cout << "Options: \n 1.) Enter check server to get the status of your server." << endl;
    //    cout << "Enter quit to end the server." << endl;
    //    if (currentResponse != "") {
    //        cout << currentResponse << endl;
    //    }
    //    cin >> input;
    //    input = Lowercase(input);
    //    if (input == "quit") {
    //        quit = true;
    //        break;
    //    }
    //    else if (input == "check server") {
    //        // TODO: Figure out how to ping the status of my newly created server.
    //        currentResponse = "Your server is currently running.";
    //    }
    //}

    //Server.join();
}

void CreateServer() {


    /* Bind the server to the default localhost.     */
    /* A specific host address can be specified by   */
    /* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = ENET_HOST_ANY;
    /* Bind the server to port 1234. */
    address.port = 1234;
    server = enet_host_create(&address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);
    if (server == nullptr)
    {
        fprintf(stderr,
            "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }
}

void BroadcastToAllUser(string message) {

    /* Create a reliable packet of size 7 containing "packet\0" */
    ENetPacket* packet = enet_packet_create(message.c_str(),
        message.length() + 1,
        ENET_PACKET_FLAG_RELIABLE);
    /* Extend the packet so and append the string "foo", so it now */
    /* contains "packetfoo\0"                                      */
    //enet_packet_resize(packet, strlen("packetfoo") + 1);
    //strcpy(&packet->data[strlen("packet")], "foo");
    /* Send the packet to the peer over channel id 0. */
    /* One could also broadcast the packet by         */
    enet_host_broadcast(server, 0, packet);
    //enet_peer_send(event.peer, 0, packet);

    /* One could just use enet_host_service() instead. */
    //enet_host_service();
    enet_host_flush(server);
}

string Lowercase(string input) {
    string lowerCasedString = "";
    for (char letter : input) {
        lowerCasedString += tolower(letter);
    }

    return lowerCasedString;
}
