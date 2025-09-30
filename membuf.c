/* create a memory file
   input: filename string
   output: pointer to memory file structure,
           NULL on failure
 */
#include <string.h>
#include "membuf.h"
struct mem_file *mem_open(char *fn)
{
    struct mem_file *mem_new;
    time_t now;

    /* error checking */
    if( fn==NULL )
        return(NULL);

    /* allocate storage for memory file structure */
    mem_new = malloc( sizeof(struct mem_file) );
    if( mem_new==NULL )
        return(NULL);

    /* populate structure */
    mem_new->address = malloc( DEFAULT_SIZE );
    if( mem_new->address==NULL )
        return(NULL);
    mem_new->name=fn;        /* set memory file name */
    mem_new->size = 0;        /* set size */
    mem_new->offset = 0;    /* offset/file pointer */
        /* create timestemp */
    time(&now);
    mem_new->timestamp = ctime(&now);

    return(mem_new);
}
/*
   close memory file, free memory
   input: mem_file structure of an open
           memory file
 */
void mem_close(struct mem_file *m)
{
    free(m->address);
    free(m);
}
/* put a character to a memory file
   input- single character, memory file handle
   output- character written or
           EOF on failure
 */
int mem_putc(int c, struct mem_file *m)
{
    int *index;

    if( m->address==NULL )
        return(EOF);

    index = m->address+m->size;
    *index = c;

    m->size++;
    /* check for overflow */
    if( (m->size % DEFAULT_SIZE) == 0 )
    {
        m->address=realloc(m->address,m->size-1+DEFAULT_SIZE);
        if( m->address==NULL )
            return(EOF);
    }

    return(c);
}
/* fetch a character from a memory file
   input- memory file handle
   output- character retrieved or
           EOF on failure
 */
int mem_getc(struct mem_file *m)
{
    int *index;

    if( m->address==NULL )
        return(EOF);

    if( m->offset>m->size )
        return(EOF);

    index = m->address+m->offset;
    m->offset++;

    return( *index );
}
/* move the memory offset index
   input- memory file handle, offset, whence
   output- current offset or -1
   whence:  SEEK_SET (start)
            SEEK_CUR (current)
            SEEK_END (end)
 */
int mem_seek(struct mem_file *m, long position, int whence)
{
    /* return -1 on various errors */
    if( m->address==NULL )
        return(-1);

    /* adjust m->offset value */
    if( whence==SEEK_SET )
    {
        if( position<0 )
            return(-1);
        /* no negative offsets! */
        if( position>m->size )
            return(-1);
        /* set offset from the start */
        m->offset = position;
        return(m->offset);
    }
    else if( whence==SEEK_CUR )
    {
        if( m->offset+position<0 || m->offset+position > m->size )
            return(-1);
        m->offset+=position;
        return(m->offset);
    }
    else if( whence==SEEK_END )
    {
        if( position<0 || m->size-position<0 )
            return(-1);
        m->offset = m->size-position;
        return(m->offset);
    }
    else
        return(-1);
}

char * mem_putstr(char *s,struct mem_file *m){
	int i;
	for(i=0; i<strlen(s);i++)
		mem_putc(s[i],m);
	return s;
}

char * mem_getline(char *s, struct mem_file *m){
	int i=0;s=(char *)malloc(1);s[0]='\0';
	char v;
	v=mem_getc(m);
	while((v!='\n')&&(v!=EOF)){
		//printf("s[%d] = %c (%d) ",i,v,v);
		if ((v==-1)||(v==0)) break;
		s[i++]=v;
		v=mem_getc(m);
	}
	if (v!=EOF) s[i]='\n';
	return s;
}
