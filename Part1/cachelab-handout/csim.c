#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

/* defining the struct to store the commandline aruments*/
typedef struct{
	int set;
	int lines;
	int blocks;
	char* trace;

} arg_input;

/* struct to hold the timestamp, validity and tag for each line*/
typedef struct{
	int timeStamp;
	int valid;
	long long int tag;
} eachLine;

//file pointer
FILE *pFile;

int main(int argc, char** argv)
{
    arg_input inputs;     //used to store the command line arguments.
    char letter;          //this char is used to hold each parsed character from the command line.
    eachLine **linePointer;    //used to store the timestamp, validity and tag for each line
    int totalSets;         //holds the number of total sets represented by the s number of bits.

    //hold the readings from the trace file
    char operation;    //store the type of operation as a char read from the trace file

    unsigned long int address;    //this holds the parsed address from the trace file
    unsigned long int tag;         //this hold the tag value
    unsigned long int set;        //this holds the set value.
    int hitCounter =0;          //hitcounter holds the number of total hits.
    int missCounter = 0;       // holds the total number of misses.
    int evictionCounter =0;       //holds the total number of evictions.


    /* this loop gets the command line arguments stored in the corresponding variables.*/
    while((letter = getopt(argc, argv, "s:E:b:t:")) != -1)
    {
	    switch(letter)
	    {
		    case 's': inputs.set = atoi(optarg);
			      totalSets = pow(2, inputs.set);     //gets the 2^s for total number of sets
		      	      break;
		    case 'E': inputs.lines = atoi(optarg);       // gets the number of lines
			break;
		    case 'b': inputs.blocks = atoi(optarg);      //get the number of blocks.
			break;
		    case 't': inputs.trace = optarg;           //gets the name of the trace file as a string.
			break;
		    default:
      			      printf("please give the valid input");    //prints the statement if the input is given in the wrong format
			exit(1);
	    }
    }
    
    //printf("this is s = %d, E = %d, b = %d, file location =   %s",inputs.set,inputs.lines,inputs.blocks,inputs.trace);   //for debigging purpose
    pFile = fopen(inputs.trace, "r");               
    if(pFile== NULL){
	    printf("there is no trace file");
	    exit(1);
    }

    //allocating the space for the lines
    linePointer = malloc(totalSets*8);
    int i =0;
    int counter =0;
    //getting hte space for lines
    for(i =0; i<totalSets;i++){
	    linePointer[i] = malloc(inputs.lines* sizeof(eachLine));
    }

    //we keep reading files until we hit the end of the file 
    while(fscanf(pFile, " %c %lx", &operation, &address)== 2)
    {
	    tag = (address>>inputs.set)>>inputs.blocks;
	    int tagSize = 64 - inputs.set - inputs.blocks;
	    set = (address<< tagSize)>>(64-inputs.set);
	    printf("\nOperation is %c, with address %ld tag = %lx, set = %lx",operation,address, tag, set); //tested and found its working properly

	    i = 0;

	    //boolean to check if we had the hit.
	    int isHit = 0;

	    //boolean to check if there is any invalid line.
	    int isValidLine = 0;

	    //boolean to check if there is any evictions.
	    int isEviction =0;
	    
	    //this int is used to hold the integer for least recently used line.
	    int oldestLine = -1;
	    int m =0;

	    //this stores the first invalid line if any invalid line is found.
	    counter =0;
	    if(operation == 'M' || operation == 'S' || operation == 'L'){     // we do not perform the hits or miss evaluation if the operation is instruction load.
	    while(i<inputs.lines){

		    // we only enter this loop once for getting the first invalid bit
		    if((linePointer[set][i]).valid == 0 && isValidLine ==0 ){
			    isValidLine = 1;
			    counter = i;
		    } else if ((linePointer[set][i]).valid ==1 && (linePointer[set][i]).tag == tag){   //this gives us the hit
			    isHit = 1;
			    for(m = 0; m< inputs.lines; m++){
				    if(m == i){
					    (linePointer[set][m]).timeStamp = 0;                 //this line has the hit so, it is recently used.
				    } else {
					    (linePointer[set][m]).timeStamp = (linePointer[set][m]).timeStamp +1;      //we increase the time stamp by 1.
				    }
			    }
			    break;
		    }
		    i++;
	    }

	    //we meet tghis condition if there is no hit
	    if(isHit==0){
		if(isValidLine == 1 ){    //we meet this condition if there was any invalid lines
			(linePointer[set][counter]).valid = 1;      //we set the specific invalid lines of code to valid.
			(linePointer[set][counter]).tag = tag;      //tag for the corresponding line is set
				for(m = 0; m< inputs.lines; m++){    
                                    		if(m == counter){
                                            		(linePointer[set][m]).timeStamp = 0;       //since this is first invalid lime, we reset the time stamp to zero.
                                    		} else {
                                            		(linePointer[set][m]).timeStamp = (linePointer[set][m]).timeStamp +1;  //other set lines are updated.
                                    		}
				}
				isEviction = 0;     //since we had the invalid cache, we have no eviction

                } else if (isValidLine == 0){
			int k  =0;
			int lru =0;

			//following for loop gives oldest line number stored in lru with the highest time stamp.
			for( k=0; k<inputs.lines;k++){
				if(linePointer[set][k].timeStamp >oldestLine){
						    oldestLine = (linePointer[set][k]).timeStamp;
						    lru = k;
				}
			}

			
			for(m = 0; m< inputs.lines; m++){
                                if(m == lru){
                                        (linePointer[set][m]).timeStamp = 0;     //since this is recently used we reset the time stamp to zero.
                                } else {
                                     (linePointer[set][m]).timeStamp = (linePointer[set][m]).timeStamp +1;       //we increase the time stamp for every other lines.
				}
			}
				(linePointer[set][lru]).valid = 1;
				(linePointer[set][lru]).tag = tag;
				isEviction  =1;
		}
	    }


	    
		if (isHit){       //if we have any hit.
			hitCounter += 1;
			//printf("\nthis is hit");

		} else if(isEviction){    //if we have any eviction
			missCounter +=1;
			evictionCounter +=1;
			//printf("\nthis is eviction and miss");
		} else {
			    missCounter +=1;
			    printf("\nthis is no eviction but is miss");
		}

		if(operation == 'M'){              //if we have the Modify instruction.
			hitCounter +=1;
			printf("\nthis is M");
		}

	    }
    }



    fclose(pFile);
    int f = 0;


    //freeing up the allocated memory
    for(f = 0; f<totalSets;f++){
	    free(linePointer[f]);
    }
    free(linePointer);
    printSummary(hitCounter, missCounter, evictionCounter);

  
    return 0;
}
