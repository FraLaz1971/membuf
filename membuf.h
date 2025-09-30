#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_SIZE 2048

struct mem_file {
	void *address;
	char *name;
	int size;
	int offset;
	char *timestamp;
};

struct mem_file *mem_open(char *fn);

void mem_close(struct mem_file *m);

/* put a character to a memory file
   input- single character, memory file handle
   output- character written or
           EOF on failure
 */
int mem_putc(int c, struct mem_file *m);

/* fetch a character from a memory file
   input- memory file handle
   output- character retrieved or
           EOF on failure
 */
int mem_getc(struct mem_file *m);
/* move the memory offset index
   input- memory file handle, offset, whence
   output- current offset or -1
   whence:  SEEK_SET (start)
               SEEK_CUR (current)
            SEEK_END (end)
 */
int mem_seek(struct mem_file *m, long position, int whence);

char * mem_putstr(char *s,struct mem_file *m);

char * mem_getline(char *s,struct mem_file *m);
