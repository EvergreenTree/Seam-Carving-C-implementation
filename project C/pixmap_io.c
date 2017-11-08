#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

//#ifdef unix
#include <unistd.h>
#include <sys/stat.h>
#define O_BINARY 0
#define IO_LEN    (1<<30)
//#endif

#if defined(THINK_C) || defined(__MWERKS__)
#include <unix.h>
#define IO_LEN    (1<<14)
#endif

#include "pixmap_io.h"

static int match_key(int fd, char *key)
{
  char buf[80];

  read(fd, buf, strlen(key));
  if( strncmp(buf, key, strlen(key)) != 0 )
    return FALSE;
  else
    return TRUE;
}

static void skip_comment(int fd, char code, char *c)
{
  while( *c == code )
    {
      while( (read(fd, c, 1) == 1 ) && (*c != '\n') ) ;
      read(fd, c, 1);
    }
}

static void read_header_line(int fd, char *buf)
{
  int i;

  i = 1;
  while( (read(fd, &buf[i], 1) == 1 ) && (buf[i] != '\n') && (buf[i] != '\r') && (i<79) )
    i++;
  buf[i] = 0;
}

static int get_pgm_header(int fd, char *magic, int *width, int *height)
{
  char buf[80];

  if( !match_key(fd, magic) )
    return FALSE;
  read(fd, buf, 1);
  skip_comment(fd, '#', buf);
  read_header_line(fd, buf);
  sscanf(buf, "%d %d", width, height);
  read(fd, buf, 1);
  skip_comment(fd, '#', buf);
  read_header_line(fd, buf);
  return TRUE;
}

static int open_read(char *filename)
{
  int fd;

  if( (fd = open(filename, O_BINARY|O_RDONLY)) < 0 )
    fprintf(stderr, "can't reset file `%s': %s\n", filename, strerror(errno));
  return fd;
}

static int open_read_pixmap(char *filename, char *magic, int *width, int *height)
{
  int fd;

  if( (fd = open_read(filename)) < 0)
    return fd;
  if( !get_pgm_header(fd, magic, width, height) )
    {
      fprintf(stderr, "can't read header of %s\n", filename);
      return -1;
    }
  return fd;
}

static unsigned char *alloc_pixmap(long size)
{
  unsigned char *data;

  if( (data = (unsigned char *)malloc(size)) == NULL )
    {
    fprintf(stderr, "malloc error\n");
    return NULL;
    }
  return data;
}

static void load_data(int fd, unsigned char *data, long size)
{
  char *buffer;
  long count;

  buffer = (char *)data;
  while( size > 0 )
    {
    count = IO_LEN;
    if( count > size )
      count = size;
    read(fd, buffer, count);
    buffer += count;
    size -= count;
    }
}

static void load_chunky(int fd, unsigned char *R_data, unsigned char *G_data, unsigned char *B_data, int width, int height)
{
  unsigned char *buffer, *buf, *buf_R, *buf_G, *buf_B;
  int count;

  buffer = alloc_pixmap(3L*width);
  buf_R = R_data;
  buf_G = G_data;
  buf_B = B_data;
  for( ; height > 0; height-- )
    {
    load_data(fd, buffer, 3L*width);
    count = width;
    buf = buffer;
    while( count-- > 0 )
      {
      *buf_R++ = *buf++;
      *buf_G++ = *buf++;
      *buf_B++ = *buf++;
      }
    }
  free(buffer);
}

unsigned char *load_pixmap(char *filename, int *width, int *height)
{
  int fd;
  long size;
  unsigned char *data;

  if( (fd = open_read_pixmap(filename, MAGIC_PGM, width, height)) < 0)
    return NULL;
  size = (long)*width * *height;
  data = alloc_pixmap(size);
  if( data != NULL )
    load_data(fd, data, size);
  close(fd);
  return data;
}

int load_RGB_pixmap(char *filename, int *width, int *height, unsigned char**R_data, unsigned char**G_data, unsigned char**B_data)
{
  int fd;
  long size;

  if( (fd = open_read_pixmap(filename, MAGIC_PPM, width, height)) < 0)
    return FALSE;
  size = (long)*width * *height;
  *R_data = alloc_pixmap(size);
  *G_data = alloc_pixmap(size);
  *B_data = alloc_pixmap(size);
  
  if( (*R_data != NULL) && (*G_data != NULL ) && (*B_data != NULL ))
    {
    load_chunky(fd, *R_data, *G_data, *B_data, *width, *height);
    close(fd);
    return TRUE;
    }

  close(fd);
  if( *R_data == NULL )
    return FALSE;
  free(*R_data);
  if( *G_data == NULL )
    return FALSE;
  free(*G_data);
  return FALSE;
}

static void put_header_line(int fd, char *buf)
{
  write(fd, buf, strlen(buf));
}

static void put_header_info(int fd, char *mark, char *filename)
{
  char buf[80];
  time_t now;

  sprintf(buf, "%sTitle: %s\n", mark, filename);
  put_header_line(fd, buf);
  now = time(NULL);
  sprintf(buf, "%sCreationDate: %s", mark, ctime(&now));
  put_header_line(fd, buf);
  sprintf(buf, "%sCreator: pixmap_io, P. Chassignet\n", mark);
  put_header_line(fd, buf);
}

static void put_pgm_header(int fd, char *magic, int width, int height, char *filename)
{
  char buf[80];

  put_header_line(fd, magic);
  put_header_info(fd, "# ", filename);
  sprintf(buf, "%d %d\n255\n", width, height);
  put_header_line(fd, buf);
}

static int open_write(char *filename)
{
  int fd;

#if defined(THINK_C) || defined(__MWERKS__)
  if( (fd = open(filename, O_BINARY|O_CREAT|O_TRUNC|O_RDWR)) < 0 )
#else
  if( (fd = open(filename, O_BINARY|O_CREAT|O_TRUNC|O_RDWR, S_IREAD|S_IWRITE)) < 0 )
#endif
    fprintf(stderr, "can't rewrite file `%s': %s\n", filename, strerror(errno));
  return fd;
}

static void store_data(int fd, unsigned char *data, long size)
{
  char *buffer;
  long count;
  
  buffer = (char *)data;
  while( size > 0 )
    {
    count = IO_LEN;
    if( count > size )
      count = size;
    write(fd, buffer, count);
    buffer += count;
    size -= count;
    }
}

static void store_chunky(int fd, unsigned char *R_data, unsigned char *G_data, unsigned char *B_data, int width, int height)
{
  unsigned char *buffer, *buf, *buf_R, *buf_G, *buf_B;
  int count;

  buffer = alloc_pixmap(3L*width);
  buf_R = R_data;
  buf_G = G_data;
  buf_B = B_data;
  for( ; height > 0; height-- )
    {
    count = width;
    buf = buffer;
    while( count-- > 0 )
      {
       *buf++ = *buf_R++;
       *buf++ = *buf_G++;
       *buf++ = *buf_B++;
      }
    store_data(fd, buffer, 3L*width);
    }
  free(buffer);
}

void store_pixmap(char *filename, unsigned char *data, int width, int height)
{
  int fd;
  
  if( (fd = open_write(filename)) < 0 )
    return;
  put_pgm_header(fd, MAGIC_PGM, width, height, filename);
  store_data(fd, data, (long)width*height);
  close(fd);
}

void store_RGB_pixmap(char *filename, unsigned char *R_data, unsigned char *G_data, unsigned char *B_data, int width, int height)
{
  int fd;
  
  if( (fd = open_write(filename)) < 0 )
    return;
  put_pgm_header(fd, MAGIC_PPM, width, height, filename);
  store_chunky(fd, R_data, G_data, B_data, width, height);
  close(fd);
}
