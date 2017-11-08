
#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif

#ifdef sun
extern char *sys_errlist[];
char *strerror(int err)
{
    return sys_errlist[err];
}
#endif

#define MAGIC_PGM    "P5\n"
#define MAGIC_PPM    "P6\n"


static unsigned char *alloc_pixmap(long size);

unsigned char *load_pixmap(char *filename, int *width, int *height);

int load_RGB_pixmap(char *filename, int *width, int *height,
	unsigned char**R_data, unsigned char**G_data, unsigned char**B_data);

void store_pixmap(char *filename, unsigned char *data, int width, int height);

void store_RGB_pixmap(char *filename,
	unsigned char *R_data, unsigned char *G_data, unsigned char *B_data,
	int width, int height);

