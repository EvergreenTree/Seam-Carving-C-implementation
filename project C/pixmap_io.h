static unsigned char *alloc_pixmap(long size);

unsigned char *load_pixmap(char *filename, int *width, int *height);

int load_RGB_pixmap(char *filename, int *width, int *height,
	unsigned char**R_data, unsigned char**G_data, unsigned char**B_data);

void store_pixmap(char *filename, unsigned char *data, int width, int height);

void store_RGB_pixmap(char *filename,
	unsigned char *R_data, unsigned char *G_data, unsigned char *B_data,
	int width, int height);

