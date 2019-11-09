#include "cachelab.h"
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
	int timeStamp;
	int valid;
	long long int tag;
} eachLine;


FILE *pFile;

int main(int argc, char** argv)
{
    arg_input inputs;
    char letter;
    eachLine **linePointer;
    int totalSets;

    //hold the readings from the trace file
    char operation;
    unsigned long int address;
    int size;
    unsigned long int tag;
    unsigned long int set;

    int hitCounter =0;
    int missCounter = 0;
    int evictionCounter =0;

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
    int counter =0;
    //getting hte space for lines
    for(i =0; i<totalSets;i++){
	    linePointer[i] = malloc(inputs.lines* sizeof(eachLine));
    }

    while(fscanf(pFile, " %c %lx,%d", &operation, &address, &size)== 3)
    {
	    tag = (address>>inputs.set)>>inputs.blocks;
	    int tagSize = 64 - inputs.set - inputs.blocks;
	    set = (address<< tagSize)>>(64-inputs.set);
	    printf("I wanted to print this .............\n tag = %lx, set = %lx", tag, set); //tested and found its working properly

	    i = 0;
	    int isHit = 0;
	    int isValidLine = 0;
	    int isEviction =0;
	    int oldestLine = -1;
	    int m =0;
	    while(i<inputs.lines){
		    if((linePointer[set][i]).valid == 0 && isValidLine ==0 ){
			    isValidLine = 1;
			    counter = i +1;
		    } else if ((linePointer[set][i]).valid ==1 && (linePointer[set][i]).tag == tag){
			    isHit = 1;
			    for(m = 0; m< inputs.lines; m++){
				    if(m == i){
					    (linePointer[set][m]).timeStamp = 0;
				    } else {
					    (linePointer[set][m]).timeStamp = (linePointer[set][m]).timeStamp +1;
				    }
			    }
		    }
		    i++;
	    }
		    if(isHit==0){
			    if(isValidLine == 1 ){
					(linePointer[set][counter-1]).valid = 1;
					(linePointer[set][counter-1]).tag = tag;
					 for(m = 0; m< inputs.lines; m++){
                                    		if(m == counter-1){
                                            		(linePointer[set][m]).timeStamp = 0;
                                    		} else {
                                            		(linePointer[set][m]).timeStamp = (linePointer[set][m]).timeStamp +1;
                                    		}
					 }
					 isEviction = 0;

                            } else if (isValidLine == 0){
				    int k  =0;
				    int lru =0;
				    for( k=0; k<inputs.lines;k++){
					    if(linePointer[set][k].timeStamp >oldestLine){
						    oldestLine = (linePointer[set][k]).timeStamp;
						    lru = k;
					    }
				    }
				    for(m = 0; m< inputs.lines; m++){
                                                if(m == lru){
                                                        (linePointer[set][m]).timeStamp = 0;
                                                } else {
                                                        (linePointer[set][m]).timeStamp = (linePointer[set][m]).timeStamp +1;
						}
				    }
				    isEviction  =1;
			    }
		    }
		    if (isHit){
			    hitCounter += 1;
		    } else if(isEviction){
			    missCounter +=1;
			    evictionCounter +=1;
		    } else {
			    missCounter +=1;
		    }

		    if(operation == 'M'){
			    hitCounter +=1;
		    }

    }

    fclose(pFile);
    int f = 0;
    for(f = 0; f<totalSets;f++){
	    free(linePointer[f]);
    }
    //printSummary(0,0,0);
    printSummary(hitCounter, missCounter, evictionCounter);
    return 0;
}
