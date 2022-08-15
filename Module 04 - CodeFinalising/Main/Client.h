#pragma once
#include <enet/enet.h>
#include <thread>
#include <iostream>

using namespace std;

// TODO: Setup client functions to this so we can manage the two.
class Client {
	//int health;
	bool success;
	thread* PacketThread = nullptr;

	ENetHost* NetHost;
public:
	Client() :
		success(true)
	{
		NetHost = enet_host_create(NULL /* create a client host */,
			1 /* only allow 1 outgoing connection */,
			2 /* allow up 2 channels to be used, 0 and 1 */,
			0 /* assume any amount of incoming bandwidth */,
			0 /* assume any amount of outgoing bandwidth */);


		if (!NetHostSuccess()) {
			fprintf(stderr,
				"An error occurred while trying to create an ENet client host.\n");
			exit(EXIT_FAILURE);
		}

		if (!AttemptConnectToServer())
		{
			fprintf(stderr,
				"No available peers for initiating an ENet connection.\n");
			exit(EXIT_FAILURE);
		}
		PacketThread = new thread(ClientProcessPackets);


		if (PacketThread)
		{
			PacketThread->join();
		}
		delete PacketThread;
	}

	bool NetHostSuccess()
	{
		return NetHost != nullptr;
	}

	bool AttemptConnectToServer()
	{
		ENetAddress address;
		/* Connect to some.server.net:1234. */
		enet_address_set_host(&address, "127.0.0.1");
		address.port = 1234;
		/* Initiate the connection, allocating the two channels 0 and 1. */
		Peer = enet_host_connect(NetHost, &address, 2, 0);
		return Peer != nullptr;
	}

	void ClientProcessPackets()
	{
		while (1)
		{
			ENetEvent event;
			/* Wait up to 1000 milliseconds for an event. */
			while (enet_host_service(NetHost, &event, 1000) > 0)
			{
				switch (event.type)
				{
				case  ENET_EVENT_TYPE_CONNECT:
					cout << "Connection succeeded " << endl;
					break;
				case ENET_EVENT_TYPE_RECEIVE:
					HandleReceivePacket(event);
					break;
				}

			}
		}
	}

};