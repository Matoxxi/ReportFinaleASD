#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MANUALE 0
#define AUTOMATICA 1
#define NUM_DIMENSIONI 7
#define NUM_TIPOLOGIE 4
#define NUM_ALGORITMI 5
int cont_confr;
int cont_scamb;
typedef enum{ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;
typedef enum{SelectionSort,InsertionSort,HeapSort,QuickSort,MergeSort} algoritmi;
int generaCasuale(int min, int max);
int *genera_array(int dim,inputType tipo_schema,int flag);
void selectionSort(int *v,int n);
void insertionSort(int v[],int dim);
void adatta(int *a,int radice,int n);
void heapsort(int *a,int n);
void merge(int *a, int *o, int i, int m, int n);
void swap(int *a, int*b);
void mergesort(int *a, int *o, int lower, int upper);
int perno(int vet[],int primo,int ultimo);
void quickSort(int vet[],int u,int v);
void ordinaArray(int *v,int dim,int algoritmo);
int main() {
    srand(time(NULL));
    int scelta,dim;
    cont_confr=cont_scamb=0;
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

            }
            ordinaArray(v,dimensioni[dim],algoritmo);

             break;
        case AUTOMATICA:
            break;
        default:
            break;
    }
    return 0;
}


void ordinaArray(int *v,int dim,int algoritmo){
    int *o;
    switch (algoritmo){
        case SelectionSort:
            selectionSort(v,dim);
            break;
        case InsertionSort:
            insertionSort(v,dim);
            break;
        case HeapSort:
            heapsort(v,dim);
            break;
        case QuickSort:
            quickSort(v,0,dim-1);
            break;
        case MergeSort:
            o=(int*)malloc(sizeof(int)*dim);
            mergesort(v,o,0,dim-1);
            break;
        default:
            break;

    }
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
                        v[j]=generaCasuale(dim/2+1,dim);
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
                        v[j]=generaCasuale((dim+1/2)+1,dim);
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

void swap(int *a, int*b){

    int appoggio;

    appoggio = *a;
    *a = *b;
    *b = appoggio;
}

/**
 * Algoritmo di ordinamento selection sort
 * @param v vettore
 * @param n numero elementi
 */
void selectionSort(int *v,int n){
    int i,j;
    int min=0;
    for(i=0;i<n-1;i++){
        min=i;
        for(j=i+1;j<n;j++){
            cont_confr++;
            if(v[j]<v[min])
                min = j;
        }
        cont_scamb++;
        swap(&v[i],&v[min]);
    }
}

void insertionSort(int v[],int dim){
    int i,prossimo,j;
    for(i=0;i<=dim-1;i++){
        prossimo=v[i];
        for(j=i-1;j>=0;j--){
            if(prossimo<v[j])
                v[j+1]=v[j];
            else
                break;
        }
        v[j+1]=prossimo;
    }
}

void heapsort(int *a,int n){
    int i;
    for(i=n/2;i>=1;i--){
        adatta(a,i,n);
    }
    for(i=n-1;i>=1;i--){
        swap(&a[1],&a[i+1]);
        adatta(a,1,i);
    }
}

void adatta(int *a,int radice,int n){
    int temp=a[radice];
    int figlio=2*radice;
    while (figlio<=n){
        if(figlio<n && a[figlio]<a[figlio+1])
            figlio++;
        if(temp>a[figlio]) break;
        else{
            a[figlio/2]=a[figlio];
            figlio=figlio*2;
        }

    }
    a[figlio/2]=temp;
}

void mergesort(int *a, int *o, int lower, int upper) {
    int medium;
    if (lower >= upper) return;
    medium = (lower + upper) / 2;
    mergesort(a, o, lower, medium);
    mergesort(a, o, medium + 1, upper);
    merge(a, o, lower, medium, upper);
}

void merge(int *a, int *o, int i, int m, int n) {
    int j, k, pos_iniziale, t;
    j = m + 1;
    k = i;
    pos_iniziale = i;
    while (i <= m && j <= n) {
        if (a[i] <= a[j]) {
            o[k] = a[i];
            i++;
            k++;
        } else {
            o[k] = a[j];
            j++;
            k++;
        }
    }

    if (i > m) {
        for (t = j; t <= n; t++) {
            o[k + t - j] = a[t];
        }
    } else {
        for (t = i; t <= m; t++) {
            o[k + t - i] = a[t];
        }
    }

    for (t = pos_iniziale; t <= n; t++) {
        a[t] = o[t];
    }
}

void quickSort(int vet[],int u,int v){
    int q;
    if(u==v) return;
    q=perno(vet,u,v);
    if(u<q) quickSort(vet,u,q-1);
    if(q<v) quickSort(vet,q+1,v);
}

int perno(int vet[],int primo,int ultimo){
    int i,j,pivot;
    i=primo;
    j=ultimo+1;
    pivot=vet[primo];
    while (i<j){
        do{
            i++;
        }while (vet[i]<=pivot && i<=ultimo);
        do{
            j--;
        }while (vet[j]>pivot && j>=primo);
        if(i<j){
            swap(&vet[i],&vet[j]);
        }

    }
    swap(&vet[primo],&vet[j]);
    return j;
}
