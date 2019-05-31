#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MANUALE 0
#define AUTOMATICA 1
#define NUM_DIMENSIONI 7
#define NUM_TIPOLOGIE 4
#define NUM_ALGORITMI 5
typedef enum{ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;
typedef enum{SelectionSort,InsertionSort,HeapSort,QuickSort,MergeSort} algoritmi;
int generaCasuale(int min, int max);
int *genera_array(int dim,inputType tipo_schema,int flag);
int main() {
    srand(time(NULL));
    int scelta,dim;
    int dimensioni[NUM_DIMENSIONI]={500,1000,2000,5000,10000,20000,50000};
    char nomiTipologie[NUM_TIPOLOGIE][30]={"Ordinato","Quasi ordinato","Inversamente ordinato","Casuale"};
    char nomiAlgoritmi[NUM_ALGORITMI][30]={"SelectionSort","InsertionSort","HeapSort","QuickSort","MergeSort"};
    algoritmi algoritmo;
    inputType tipologia;
    int i;
    int *v;
    do {
        printf("0-Modalita' manuale\n1-Modalita' automatica\n");
        scanf("%d", &scelta);
    }while(scelta<MANUALE || scelta>AUTOMATICA);
    switch (scelta){
        case MANUALE:
            do {
                printf("Scegli la dimensione dell'array\n");
                for (i = 0; i < NUM_DIMENSIONI; i++) {
                    printf("%d - %d\n", i, dimensioni[i]);
                }
                scanf("%d", &dim);
            }while (dim <0 || dim >=NUM_DIMENSIONI);
            printf("dimensione scelta %d \n",dimensioni[dim]);
            do{
                printf("Scegli la tipologia di array\n");
                for(i=0;i<NUM_TIPOLOGIE;i++){
                    printf("%d - %s\n",i,nomiTipologie[i]);
                }
                scanf("%d",&tipologia);
            }while(tipologia<ORDINATO || tipologia>CASUALE);
            do{
                printf("Scegli l'algoritmo con cui vuoi ordinare l'array\n");
                for(i=0;i<NUM_ALGORITMI;i++){
                    printf("%d - %s\n",i,nomiAlgoritmi[i]);
                }
                scanf("%d",&algoritmo);
            }while(algoritmo<SelectionSort || algoritmo>MergeSort);
            printf("Hai scelto di creare un array di %d elementi con lo schema %s, che verra' ordinato"
                   " con l'algoritmo %s \n",dimensioni[dim],nomiTipologie[tipologia],nomiAlgoritmi[algoritmo]);
            if(algoritmo==2) {
                v = genera_array(dimensioni[dim], tipologia, 1);

            }
            else {
                v = genera_array(dimensioni[dim], tipologia, 0);
                for(i=0;i<dimensioni[dim];i++){
                    printf("%d ",v[i]);
                }
                printf("\n");
            }
             break;
        case AUTOMATICA:
            break;
        default:
            break;
    }
    return 0;
}


int *genera_array(int dim,inputType tipo_schema,int flag){
    int *v,i,j;
    switch (flag){
        case 0:
            v = (int *) malloc(sizeof(int) * dim);
            if(v==NULL)
                exit(-1);
            switch(tipo_schema){
                case ORDINATO:

                    for(i=0;i<dim;i++){
                        v[i]=i+1;
                    }
                    break;
                case INV_ORDINATO:
                    for(i=0;i<dim;i++){
                        v[i]=dim-i;
                    }
                    break;
                case CASUALE:
                    for(i=0;i<dim;i++){
                        v[i]=generaCasuale(1,dim);
                    }
                    break;
                case QUASI_ORDINATO:
                    for(i=0;i<dim/2;i++){
                        v[i]=i+1;
                    }
                    for(j=i;j<dim;j++){
                        v[j]=generaCasuale(10,20);
                    }
                    break;
                default:
                    break;
            }
            break;
        case 1:
            v = (int *) malloc(sizeof(int) * dim+1);
            if(v==NULL)
                exit(-1);
            switch(tipo_schema){
                case ORDINATO:
                    v[0]=0;
                    for(i=1;i<dim+1;i++){
                        v[i]=i-1;
                    }
                    break;
                case INV_ORDINATO:
                    v[0]=0;
                    for(i=1;i<dim+1;i++){
                        v[i]=dim-i;
                    }
                    break;
                case CASUALE:
                    v[0]=0;
                    for(i=1;i<dim+1;i++){
                        v[i]=generaCasuale(1,dim);
                    }
                    break;
                case QUASI_ORDINATO:
                    v[0]=0;
                    for(i=1;i<dim+1/2;i++){
                        v[i]=i+1;
                    }
                    for(j=i;j<dim+1;j++){
                        v[j]=generaCasuale(10,20);
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return v;
}


int generaCasuale(int min, int max) {
    int r;
    r = min + rand() % (max - min + 1);
    return r;
}