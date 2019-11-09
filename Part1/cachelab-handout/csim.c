//#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
typedef struct{
	int set;
	int lines;
	int blocks;
	char* trace;

} arg_input;


typedef struct{
	int hits;
	int misses;
	int evictions;
} results;


typedef struct{
	int recently_used;
	int valid;
	long long int tag;
} eachLine;


FILE *pFile;

int main(int argc, char** argv)
{
    arg_input inputs;
    //results output;
    //eachLine aline;
    char letter;
    eachLine **linePointer;
    int totalSets;

    //hold the readings from the trace file
    char operation;
    unsigned long int address;
    int size;
    unsigned long int tag;
    unsigned long int set;

    while((letter = getopt(argc, argv, "s:E:b:t:")) != -1)
    {
	    switch(letter)
	    {
		    case 's': inputs.set = atoi(optarg);
			      totalSets = pow(2, inputs.set);
		      	      break;
		    case 'E': inputs.lines = atoi(optarg);
			break;
		    case 'b': inputs.blocks = atoi(optarg);
			break;
		    case 't': inputs.trace = optarg;
			break;
		    default:
      			      printf("please give the valid input");
			exit(1);
	    }
    }
    
    printf("this is s = %d, E = %d, b = %d, file location =   %s",inputs.set,inputs.lines,inputs.blocks,inputs.trace);
    pFile = fopen(inputs.trace, "r");
    if(pFile== NULL){
	    printf("there is no trace file");
	    exit(1);
    }
    linePointer = malloc(totalSets *8);
    int i =0;
    for(i =0; i<totalSets;i++){
	    linePointer[i] = malloc(inputs.lines* sizeof(eachLine));
    }

    while(fscanf(pFile, " %c %lx,%d", &operation, &address, &size)>0)
    {
	    tag = (address>>inputs.set)>>inputs.blocks;
	    int tagSize = 64 - inputs.set - inputs.blocks;
	    set = (address<< tagSize)>>(64-inputs.set);
    }
    printf("reading file tag = %lx, set = %lx", tag, set);


   // printSummary(0, 0, 0);
    return 0;
}
