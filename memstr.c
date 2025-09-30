#include "membuf.h"
#include <string.h>
int writemf(struct mem_file * mf){
	int i;
	char ins[128];
	strcpy(ins,"This is the line n. 1\n");
	mem_putstr(ins, mf);
	for(i=2; i<12; i++){
	  snprintf(ins, 128, "This is the line n. %d\n", i);
	  mem_putstr(ins, mf);
	}
	return 0;
}
int readmf(struct mem_file * mf){
	int i=0;
	char extr[128]="\0";
	for(i=0;i<10;i++)
		printf("%s",mem_getline(extr,mf));
	return 0;
}
int main(){
	static char name1[] = "memfile1";
    struct mem_file *mfp1;
    int i, res;
    mfp1 = mem_open(name1);
    if( mfp1==NULL )
    {
        fprintf(stderr,"Unable to create %s\n",name1);
        exit(1);
    }
    printf("Memory file '%s' created\n",name1);
    printf("Timestamp = %s\n",mfp1->timestamp);
    res = writemf(mfp1);
    res = readmf(mfp1);
    mem_close(mfp1);
	return 0;
}
