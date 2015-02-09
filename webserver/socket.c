#include "socket.h"

/* Traitement du signal passé en paramètre */
void traitement_signal(int sig)
{
	int status;
	if (sig == SIGCHLD) {
		while (waitpid(-1, &status, WNOHANG) > 0)
			;
	}
}

/* Initialise les signaux des processus */
void initialiser_signaux(void)
{
	struct sigaction sa;
	
	sa.sa_handler = traitement_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction(SIGCHLD)");
	}
	
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
	}
}

/* Attend la connexion d'un utilisateur et retourne la socket client */
int ecouter_connexion(int socket_serveur)
{
	int pid;
	int socket_client;
	
	/* Accepte une connexion */
	socket_client = accept(socket_serveur, NULL, NULL);
	if (socket_client == -1)
	{
		perror("accept");
		return -1;
	}
	
	/* Création d'un client (processus fils)*/
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return -1;
	}
	else if (pid > 0)
	{
		close(socket_client);
		return 0;
	}
	else
	{	
		/* Notification de connexion pour le serveur */
		printf("Connexion d'un client... ID: %d\n", getpid());
	}
	
	return socket_client;
}


/* Crée un serveur et retourne sa socket */
int creer_serveur(int port)
{
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
	
	/* Configuration de la socket */
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
