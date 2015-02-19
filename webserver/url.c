#include "url.h"

char * rewrite_url(char * url)
{
	char *rewritten;
	int i;
	
	i = 0;
	while (url[i] != '\0' && url[i] != '?')
	{
		i++;
	}
	
	/* url[i] == '\0' ou url[i] == '?' */
	rewritten = (char *)malloc(i+1);
	
	if (rewritten == NULL)
		return NULL;
	
	strncpy(rewritten, url, i);
	rewritten[i] = '\0';
	
	return rewritten;
}

int check_and_open(const char * url, const char * document_root)
{
	int fd;
	char *path;
	
	path = (char*)malloc(strlen(url)+strlen(document_root)+1);
	
	strcpy(path, document_root);
	strcat(path, url);
	fd = open(path, O_RDONLY);
	
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	
	return fd;
}

int get_file_size(int fd)
{
	struct stat buf;
	
	if (fstat(fd, &buf) == -1)
	{
		perror("fstat");
		return -1;
	}
	
	return buf.st_size;
}

int copy(int in, int out)
{
	int towrite;
	char buf[8000];

	towrite = read(in,buf,sizeof(buf));
	while (towrite > 0)
	{
		write(out,buf,towrite);
		towrite = read(in,buf,sizeof(buf));
	}	
	return out;
}
