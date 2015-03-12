#include "headers/stats.h"

static web_stats stats;

void send_stats(FILE * client)
{
	char msg[400];
	snprintf(msg, 400,"served_connections: %d\r\nserved_requests: %d\r\n200: %d\r\n400: %d\r\n403: %d\r\n404: %d\r\n",
			stats.served_connections,
			stats.served_requests,
			stats.ok_200,
			stats.ko_400,
			stats.ko_403,
			stats.ko_404);
	send_status(client, 200, "OK");
	fprintf(client, "Content-Length: %d\r\n\r\n", (int)strlen(msg));
	fprintf(client, "%s", msg);
	fflush(client);
}

int init_stats(void)
{
	stats.served_connections = 0;
	stats.served_requests = 0;
	stats.ok_200 = 0;
	stats.ko_400 = 0;
	stats.ko_403 = 0;
	stats.ko_404 = 0;
	return 0;
}

web_stats * get_stats(void)
{
	return &stats;
}
