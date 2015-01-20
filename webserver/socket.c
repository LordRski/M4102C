#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "socket.h"

/* Utilisation de socket, bind, listen */
int creer_serveur(int port) {
	int socket_serveur;
	int socket_client;
	struct sockaddr_in saddr;
	const char* welcome_message = "======================================\nBienvenue sur le serveur de La 7 Production\nAuteurs: Edouard CATTEZ - Melvin CLAVEL\nVous pouvez me parler\nSoyez créatif\nJe vous répondrez votre message tant que vous ne vous déconnectez pas.\n======================================\n";
	
	/* Création de la socket serveur */
	socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_serveur == -1)
	{
		perror("socket_serveur");
		return -1;
	}
	
	/* Attachement de la socket serveur sur toutes les interfaces */
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(socket_serveur, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
	{
		perror("bind socket_serveur");
		return -1;
	}
	
	
	/* Lancer l'attente de connexion */
	if (listen(socket_serveur, 10) == -1)
	{
		perror("listen socket_serveur");
		return -1;
	}
	
	/* Accepter une connexion */
	socket_client = accept(socket_serveur, NULL, NULL);
	if (socket_client == -1)
	{
		perror("accept");
		return -1;
	}
	
	/* Attente d'une seconde avant l'envoi du message de bienvenue */
	sleep(1);
	
	/* Message de bienvenue envoyé */
	write(socket_client, welcome_message, strlen(welcome_message));
	
	return socket_client;
}
