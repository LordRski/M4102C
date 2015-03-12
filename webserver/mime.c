#include "headers/mime.h"

struct ext_to_mime supported_mimes[] = {
	{ ".jpg", "image/jpeg" },
	{ ".css", "text/css" },
	{ ".html", "text/html" },
	{ NULL, NULL }
};

const char * get_ext(char * url)
{
	return strrchr(url, '.');
}

const char * get_mime(const char * ext)
{
	int i;
	for (i = 0; supported_mimes[i].ext != NULL; i++)
	{
		if (strcmp(ext, supported_mimes[i].ext) == 0)
			return supported_mimes[i].mime;
	}
	return "text/plain";
}
