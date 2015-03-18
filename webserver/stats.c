#include "headers/stats.h"

static shared_data *data;

void send_stats(FILE * client)
{
	char msg[400];
	snprintf(msg, 400,"served_connections: %d\r\nserved_requests: %d\r\n200: %d\r\n400: %d\r\n403: %d\r\n404: %d\r\n",
			data->stats.served_connections,
			data->stats.served_requests,
			data->stats.ok_200,
			data->stats.ko_400,
			data->stats.ko_403,
			data->stats.ko_404);
	send_status(client, 200, "OK");
	fprintf(client, "Content-Length: %d\r\n\r\n", (int)strlen(msg));
	fprintf(client, "%s", msg);
	fflush(client);
}

int init_stats(void)
{
	data = mmap(NULL, sizeof(data), PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_init(&(data->semaphore), 0, 1);
	data->stats.served_connections = 0;
	data->stats.served_requests = 0;
	data->stats.ok_200 = 0;
	data->stats.ko_400 = 0;
	data->stats.ko_403 = 0;
	data->stats.ko_404 = 0;
	return 0;
}

web_stats * get_stats(void)
{
	sem_wait(&(data->semaphore));
	return &(data->stats);
}

int release_stats(void) {
	return sem_post(&(data->semaphore));
}
