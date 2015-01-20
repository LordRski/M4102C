#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"

int main(int argc, char **argv)
{
	const char* welcome_message = "Bienvenue sur le serveur de La 7 Production\nAuteurs: Edouard CATTEZ - Melvin CLAVEL\nVous pouvez me parler\nSoyez créatif\nJe vous répondrez votre message tant que vous ne vous déconnectez pas.\n\n\n";
	int socket_client;
	socket_client = creer_serveur(8000);
	
	if (socket_client != -1)
	{
		write(socket_client, welcome_message, strlen(welcome_message));
		while(1)
		{
			
		
		}
	}
	
	return 0;
}
