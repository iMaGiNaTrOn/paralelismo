/* Somatório da Diferença dos Quadrados das Matrizes
	exemplo 01.c

   compilação:
      gcc -fopenmp trabalho.c -o trabalho.x
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "omp.h"

long long int** alocando(long long int** ponteiro, int qtd){
    ponteiro = (long long int**)malloc(sizeof(long long int*) * qtd);
    for(int i = 0; i < qtd; i++){
        ponteiro[i] = (long long int*)malloc(sizeof(long long int) * qtd);
    }
    return ponteiro;
}

int main(const int argc, char *argv[]){
    int qtd = atoi(argv[1]);
    long long int **pont1;
    long long int **pont2;
    long long int **mResult;
    long long int somaDiferenca = 0;
    int threads = atoi(argv[2]);
    int i, j;
    double startTime, endTime;
    

    startTime = omp_get_wtime();

    pont1 = alocando(pont1, qtd);

    pont2 = alocando(pont2, qtd);

    mResult = alocando(mResult, qtd);

    unsigned int timer = time(NULL);

    

    omp_set_num_threads(threads);
    #pragma omp parallel shared(pont1, pont2, i) private(j) firstprivate(timer)
    {
        #pragma omp for
        for(i = 0; i < qtd; i++) {
            for (j = 0; j < qtd; j++) {
                pont1[i][j] = rand_r(&timer);
                pont1[i][j] = pont1[i][j]*pont1[i][j];
            }
        }

        #pragma omp for
        for(i = 0; i < qtd; i++) {
            for (j = 0; j < qtd; j++) {
                pont2[i][j] = rand_r(&timer);
                pont2[i][j] = pont2[i][j]*pont2[i][j];
            }
        }
    }
    
    
    #pragma omp parallel shared(mResult, pont1, pont2, i) private(j)
    {
        #pragma omp for
        for(i = 0; i < qtd; i++) {
            for (j = 0; j < qtd; j++) {
                mResult[i][j] = pont1[i][j] - pont2[i][j];
            }
        }

        #pragma omp for reduction(+:somaDiferenca)
        for (i = 0; i < qtd; i++) {
            for (j = 0; j < qtd; j++) {
                somaDiferenca += mResult[i][j];
            }
            
        }
        
    }

    endTime = omp_get_wtime() - startTime;

    FILE *arqPont;
    arqPont = fopen("saida.txt", "a");
    fprintf(arqPont, "%d threads\n", threads);
    fprintf(arqPont, "A matriz é %d x %d\n", qtd, qtd);
    fprintf(arqPont, "%lf s\n\n", endTime);
    fclose(arqPont);

    //printf("%lld\n", somaDiferenca);
    return 0;
}