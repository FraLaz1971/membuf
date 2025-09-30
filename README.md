# membuf: use a memory buffer as a file
###
write and read to a memory buffer as you are reading and writing to a file.
It has the following programming interface:
###
`struct mem_file *mem_open(char *fn);

void mem_close(struct mem_file *m);

int mem_putc(int c, struct mem_file *m);

int mem_getc(struct mem_file *m);

int mem_seek(struct mem_file *m, long position, int whence);

char * mem_putstr(char *s,struct mem_file *m);

char * mem_getline(char *s,struct mem_file *m);`
###
There are 2 example programs:
### mainmb
and
### memstr
to compile them (on Linux):
###
`make`
###
to run them
###
`./mainmb`
###
`./memstr`
