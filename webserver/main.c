#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "socket.h"

int main(int argc, char **argv)
{
	int port;
	int socket_client;
	char buf[256];
	
	if (argc < 2) {
		printf("Usage: /l7pserv [port]\n");
		return -1;
	}
	
	port = atoi(argv[1]);
	
	if (port == 0) {
		printf("port must be an int > 0 !\n");
		return -1;
	}
	
	socket_client = creer_serveur(port);
	
	while(socket_client != -1)
	{
		if (read(socket_client, &buf, sizeof(buf)) != -1)
		{ 
			write(socket_client, &buf, strlen(buf));
		}
	}
	
	return 0;
}
