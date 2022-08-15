#include <enet/enet.h>
#include <string>
#include <list>
#include <iostream>
#include <thread>
#include <conio.h>
#include "Client.h"

using namespace std;

ENetHost* NetHost = nullptr;
ENetPeer* Peer = nullptr;
bool IsServer = false;
thread* PacketThread = nullptr;

enum PacketHeaderTypes
{
    PHT_Invalid = 0,
    PHT_IsDead,
    PHT_Position,
    PHT_Count
};

enum PacketSendingTypes {
    ADD_NEW_PLAYER,
    REMOVE_PLAYER
};

struct GamePacket
{
    GamePacket() {}
    PacketHeaderTypes Type = PHT_Invalid;
};

struct Player {
    Player(float health, string name, int id) {
        playerId = id;
        this->health = health;
        this->name = name;
        this->maxHealth = health;
    }

    void KillPlayer() {
        isDead = true;
    }

    void DamagePlayer(float dmg) {
        health -= dmg;
        if (health <= 0) KillPlayer();
    }

    void HealPlayer(float amnt) {
        if (health <= maxHealth) {
            health += amnt;
            if (health >= maxHealth) health = maxHealth;
        }
    }

    int playerId = 0;
    string name = "Guest";
    bool isDead = false;
    float maxHealth = 100;
    float health = 100;
};

struct GameCountPacket : public GamePacket {
    GameCountPacket(int maxAmount) {
        Type = PHT_Count;
        this->maxAmount = maxAmount;
        currentAmount = 0;
        players = list<Player>();
    }
    void AddNewPlayer() {
        currentAmount++;
    }

    list<Player> players;
    int currentAmount;
    int maxAmount;
};

struct IsDeadPacket : public GamePacket
{
    IsDeadPacket()
    {
        Type = PHT_IsDead;
    }

    int playerId = 0;
    bool IsDead = false;
};

struct PositionPacket : public GamePacket
{
    PositionPacket()
    {
        Type = PHT_Position;
    }

    int playerId = 0;
    int x = 0;
    int y = 0;
};

void GuessingGame() {
    // Generate a number for clients to guess
    // Send off asking for clients
}

//can pass in a peer connection if wanting to limit
bool CreateServer(int playersAmount)
{
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 1234;
    NetHost = enet_host_create(&address /* the address to bind the server host to */,
        playersAmount,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);

    return NetHost != nullptr;
}
// "\x1b[2K"
// "\r"

//bool CreateClient()
//{
//    NetHost = enet_host_create(NULL /* create a client host */,
//        1 /* only allow 1 outgoing connection */,
//        2 /* allow up 2 channels to be used, 0 and 1 */,
//        0 /* assume any amount of incoming bandwidth */,
//        0 /* assume any amount of outgoing bandwidth */);
//
//    return NetHost != nullptr;
//}
//
//bool AttemptConnectToServer()
//{
//    ENetAddress address;
//    /* Connect to some.server.net:1234. */
//    enet_address_set_host(&address, "127.0.0.1");
//    address.port = 1234;
//    /* Initiate the connection, allocating the two channels 0 and 1. */
//    Peer = enet_host_connect(NetHost, &address, 2, 0);
//    return Peer != nullptr;
//}

void HandleReceivePacket(const ENetEvent& event)
{
    GamePacket* RecGamePacket = (GamePacket*)(event.packet->data);
    if (RecGamePacket)
    {
     //   cout << "Received Game Packet " << endl;

        if (RecGamePacket->Type == PHT_IsDead)
        {
            cout << "u dead?" << endl;
            IsDeadPacket* DeadGamePacket = (IsDeadPacket*)(event.packet->data);
            if (DeadGamePacket)
            {
                string response = (DeadGamePacket->IsDead ? "yeah" : "no");
                cout << response << endl;
            }
        }



        if (RecGamePacket->Type == PHT_Count)
        {
            GameCountPacket* CountGamePacket = (GameCountPacket*)(event.packet->data);
            if (CountGamePacket)
            {
                cout << "CURRENNT AMOUNT IS AT: " << CountGamePacket->currentAmount << endl;
                string response = "ERROR";
                if (CountGamePacket->currentAmount >= CountGamePacket->maxAmount)
                    response = "Server is currently at max capacity. Re-enter 2 if you'd like to try again.";
                else if (CountGamePacket->currentAmount >= 2)
                    response = "Game is currently playing. Setting your team as: Spectator.";
                    // Set client to spectator
                else {

                    response = "Connected successfully, ";
                    //CountGamePacket->currentAmount++;

                    //PacketSendingTypes packetToSend = PacketSendingTypes::ADD_NEW_PLAYER;
                    ENetPacket* packet = enet_packet_create("ADD_NEW_PLAYER",
                        sizeof("ADD_NEW_PLAYER"),
                        ENET_PACKET_FLAG_RELIABLE);

                    //enet_host_broadcast(NetHost, 0, packet);
                    enet_host_broadcast(NetHost, 0, packet);

                    enet_host_flush(NetHost);

                    //enet_host_flush(NetHost);

                    if (CountGamePacket->currentAmount >= 2) {
                        response += "starting game, get ready!";
                    }
                    else {
                        response += "waiting for opponent";
                    }
                }
                cout << response << endl;
            }
        }
    }
    else
    {
        cout << "Invalid Packet " << endl;
    }

    /* Clean up the packet now that we're done using it. */
    enet_packet_destroy(event.packet);
    {
        enet_host_flush(NetHost);
    }
}

void BroadcastIsDeadPacket()
{
    IsDeadPacket* DeadPacket = new IsDeadPacket();
    DeadPacket->IsDead = true;
    ENetPacket* packet = enet_packet_create(DeadPacket,
        sizeof(IsDeadPacket),
        ENET_PACKET_FLAG_RELIABLE);

    /* One could also broadcast the packet by         */
    enet_host_broadcast(NetHost, 0, packet);
    //enet_peer_send(event.peer, 0, packet);

    /* One could just use enet_host_service() instead. */
    //enet_host_service();
    enet_host_flush(NetHost);
    delete DeadPacket;
}

void BroadcastServerInfoToClient(GameCountPacket* GameCountPacketSend) {
    //cout << GameCountPacketSend->currentAmount;
    ENetPacket* packet = enet_packet_create(GameCountPacketSend,
        sizeof(GameCountPacket),
        ENET_PACKET_FLAG_RELIABLE);

    /* One could also broadcast the packet by         */
    enet_host_broadcast(NetHost, 0, packet);
    //enet_peer_send(event.peer, 0, packet);

    /* One could just use enet_host_service() instead. */
    //enet_host_service();
    enet_host_flush(NetHost);
}

void HandleNewClientPacketInfo(GameCountPacket* GameCountPacketSend) {
    GameCountPacketSend->AddNewPlayer();

}

void ServerProcessPackets(GameCountPacket* GameCountPacketSend)
{
    while (1)
    {
        ENetEvent event;
        while (enet_host_service(NetHost, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                cout << "A new client connected from "
                    << event.peer->address.host
                    << ":" << event.peer->address.port
                    << endl;
                /* Store any relevant client information here. */
                event.peer->data = (void*)("Client information");
                //BroadcastIsDeadPacket();
                BroadcastServerInfoToClient(GameCountPacketSend);

                break;
            case ENET_EVENT_TYPE_RECEIVE:
                //HandleReceivePacket(event);
                //string input = (char*)event.packet->data;
                //cout << "RECEIVED CLIENT PACKET";
                //GameCountPacketSend->AddNewPlayer();
                cout << "I got a packet sent to me." << endl;
                HandleNewClientPacketInfo(GameCountPacketSend);
                //if (input == "ADD_NEW_PLAYER")
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                cout << (char*)event.peer->data << "disconnected." << endl;
                /* Reset the peer's client information. */
                event.peer->data = NULL;
                //notify remaining player that the game is done due to player leaving
            }
        }
    }
}


int main(int argc, char** argv)
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        cout << "An error occurred while initializing ENet." << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    cout << "1) Create Server " << endl;
    cout << "2) Create Client " << endl;
    int UserInput;
    ENetEvent event;
    cin >> UserInput;
    int amnt = 0;
    if (UserInput == 1)
    {
        //How many players?
        cout << "How many clients would you like to have on this server? ";
        while (amnt <= 0) {
            cin >> amnt;
        }

        if (!CreateServer(amnt))
        {
            fprintf(stderr,
                "An error occurred while trying to create an ENet server.\n");
            exit(EXIT_FAILURE);
        }

        IsServer = true;
        cout << "waiting for players to join..." << endl;
        cout << endl;
        GameCountPacket* GameCountPacketSend = new GameCountPacket(amnt);
        //cout << "Started a NEW game packet";
        PacketThread = new thread(ServerProcessPackets, GameCountPacketSend);
    }
    else if (UserInput == 2)
    {
        //if (!CreateClient())
        //{
        //    fprintf(stderr,
        //        "An error occurred while trying to create an ENet client host.\n");
        //    exit(EXIT_FAILURE);
        //}
        Client client = Client();

        //handle possible connection failure
        {
            //enet_peer_reset(Peer);
            //cout << "Connection to 127.0.0.1:1234 failed." << endl;
        }
    }
    else
    {
        cout << "Invalid Input" << endl;
    }


    if (PacketThread)
    {
        PacketThread->join();
    }
    delete PacketThread;
    if (NetHost != nullptr)
    {
        enet_host_destroy(NetHost);
    }

    return EXIT_SUCCESS;
}