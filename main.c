#include <stdio.h>
#define MANUALE 0
#define AUTOMATICA 1
#define NUM_DIMENSIONI 7
#define NUM_TIPOLOGIE 4
#define NUM_ALGORITMI 5
typedef enum{ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;
typedef enum{SelectionSort,InsertionSort,HeapSort,QuickSort,MergeSort} algoritmi;
int main() {
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
            printf("Hai scelto di creare un array di %d elementi con lo schema %s\n",dim,nomiTipologie[tipologia]);
            do{
                printf("Scegli l'algoritmo con cui vuoi ordinare l'array\n");
                for(i=0;i<NUM_ALGORITMI;i++){
                    printf("%d - %s\n",i,nomiAlgoritmi[i]);
                }
                scanf("%d",&algoritmo);
            }while(algoritmo<SelectionSort || algoritmo>MergeSort);
             break;
        case AUTOMATICA:
            break;
        default:
            break;
    }
    return 0;
}