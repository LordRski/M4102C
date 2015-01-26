#include "socket.h"

/* Attend la connexion d'un utilisateur et retourne la socket client */
int ecouter_connexion(int socket_serveur)
{
	int socket_client;
	const char* welcome_message = "======================================\nBienvenue sur le serveur de La 7 Production\nAuteurs: Edouard CATTEZ - Melvin CLAVEL\nVous pouvez me parler\nSoyez créatif\nJe vous répondrez votre message tant que vous ne vous déconnectez pas.\n======================================\n";	
	/* Accepte une connexion */
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

	/* Notification de connexion pour le serveur */
	printf("Connexion d'un client... ID: %d\n", socket_client);
	
	return socket_client;
}

/* Crée un serveur et retourne sa socket */
int creer_serveur(int port) {
	int optval = 1;
	int socket_serveur;
	struct sockaddr_in saddr;
	
	/* Création de la socket serveur */
	socket_serveur = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_serveur == -1)
	{
		perror("socket_serveur");
		exit(1);
	}
	
	/* Attachement de la socket serveur sur toutes les interfaces */
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = INADDR_ANY;
	
	/* Activation de l'option SO_REUSEADDR */
	if (setsockopt(socket_serveur, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1)
	{
		perror("Can not set SO_REUSEADDR option");
		exit(1);
	}
	
	if (bind(socket_serveur, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
	{
		perror("bind socket_serveur");
		exit(1);
	}
	
	/* Lancer l'attente de connexion */
	if (listen(socket_serveur, 10) == -1)
	{
		perror("listen socket_serveur");
		return -1;
	}
	
	return socket_serveur;
}
