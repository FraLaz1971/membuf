/* test the memory file functions */
#include <stdio.h>
#include "membuf.h"
int main()
{
    static char name1[] = "memory_file";
    struct mem_file *mfp1, *mfp2;
    int a,r;

    mfp1 = mem_open(name1);
    if( mfp1==NULL )
    {
        fprintf(stderr,"Unable to create %s\n",name1);
        exit(1);
    }
    printf("Memory file '%s' created\n",name1);
    printf("Timestamp = %s\n",mfp1->timestamp);
    /* write the alphabet to the memory-file */
    for( a='A'; a<='Z'; a++ )
        mem_putc(a,mfp1);

    /* read back in the entire alphabet */
    printf("Reading the entire file: ");
    r = mem_seek(mfp1,0,SEEK_SET);
    if( r==-1)
    {
        fprintf(stderr,"Position error\n");
        exit(1);
    }
    for( a=0; a<26; a++ )
        putchar( mem_getc(mfp1) );
    putchar('\n');

    /* read the last ten characters */
    printf("Reading the last ten characters: ");
    r = mem_seek(mfp1,10,SEEK_END);
    if( r==-1)
    {
        fprintf(stderr,"Position error\n");
        exit(1);
    }
    for( a=0; a<10; a++ )
        putchar( mem_getc(mfp1) );
    putchar('\n');

    /* read the middle ten characters */
    printf("Reading the middle ten characters: ");
        /* position is at the end of the file */
    r = mem_seek(mfp1,-18,SEEK_CUR);
    if( r==-1)
    {
        fprintf(stderr,"Position error\n");
        exit(1);
    }
    for( a=0; a<10; a++ )
        putchar( mem_getc(mfp1) );
    putchar('\n');
	printf("Press Enter: ");
    getchar();
    mem_close(mfp1);
    printf("Memory file '%s' closed\n",name1);

    return(0);
}
