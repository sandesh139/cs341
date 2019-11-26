/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";




void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{

    int i,j,x,a,b,c,d,e,f,g,h;
    if(M == 32){
    for (i = 0; i < N; i+=8) {
        for (j = 0; j < M; j+=8) {
		for(x =0; x<8;x++){
                               a = A[i][j+x];
			       b = A[i+1][j+x];
			       c = A[i+2][j+x];
			       d =  A[i+3][j+x];
			       e = A[i+4][j+x];
			       f = A[i+5][j+x];
			       g =  A[i+6][j+x];
			       h =  A[i+7][j+x];
			       B[j+x][i]=a;
			       B[j+x][i+1] = b;
			       B[j+x][i+2] = c;
			       B[j+x][i+3] = d;
			       B[j+x][i+4] = e;
			       B[j+x][i+5] = f;
			       B[j+x][i+6] = g;
			       B[j+x][i+7] = h;
		}
	}
    }

    }
    if(M ==61 && N == 67){
	    for(i = 0; i< N; i+=16){
		    for(j = 0; j<M; j+=16){
			    for(x=0; (x<16) &&(j+x)<61; x++){
				    for(a = 0; a<16&& (i+a)<67; a++){
					    
						    //printf("this is i+a = %d, and j+x = %d\n",(i+a),(j+x));
						    B[j+x][i+a]= A[i+a][j+x];
					    
				    }
			    }
		    }
	    }
    }

    if(M==64){
	for (i = 0; i < N; i+=4) {
        	for (j = 0; j < M; j+=4) {
                	for(x =0; x<4;x++){
                               a = A[i][j+x];
                               b = A[i+1][j+x];
                               c = A[i+2][j+x];
                               d =  A[i+3][j+x];
                               B[j+x][i]=a;
                               B[j+x][i+1] = b;
                               B[j+x][i+2] = c;
                               B[j+x][i+3] = d;
			}
		}
	}
    }


}


/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

