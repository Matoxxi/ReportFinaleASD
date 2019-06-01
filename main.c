#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MANUALE 0
#define AUTOMATICA 1
#define NUM_DIMENSIONI 3
#define NUM_TIPOLOGIE 4
#define NUM_ALGORITMI 5
int cont_confr;
int cont_scamb;
typedef enum{ORDINATO, QUASI_ORDINATO, INV_ORDINATO, CASUALE} inputType;
typedef enum{SelectionSort,InsertionSort,HeapSort,QuickSort,MergeSort} algoritmi;

typedef  struct{
    double t;
    int scambi,confronti;
}Report;
typedef struct {
    Report r[NUM_TIPOLOGIE][NUM_DIMENSIONI];
}Risultati;
int generaCasuale(int min, int max);
int *genera_array(int dim,inputType tipo_schema,int flag);
void selectionSort(int *v,int n,Report *r);
void insertionSort(int v[],int dim,Report *r);
void adatta(int *a,int radice,int n,Report *r);
void heapsort(int *a,int n,Report *r);
void merge(int *a, int *o, int i, int m, int n,Report *r);
void swap(int *a, int*b);
void mergesort(int *a, int *o, int lower, int upper,Report *r);
int perno(int vet[],int primo,int ultimo,Report *r);
void quickSort(int vet[],int u,int v,Report *r);
void ordinaArray(int *v,int dim,int algoritmo,Report *r);
void inzializzaReport(Report v[][NUM_DIMENSIONI]);
int main() {
    srand(time(NULL));
    int scelta,dim;
    cont_confr=cont_scamb=0;
    int dimensioni[NUM_DIMENSIONI]={4,5,6};
    char nomiTipologie[NUM_TIPOLOGIE][30]={"Ordinato","Quasi ordinato","Inversamente ordinato","Casuale"};
    char nomiAlgoritmi[NUM_ALGORITMI][30]={"SelectionSort","InsertionSort","HeapSort","QuickSort","MergeSort"};
    algoritmi algoritmo;
    inputType tipologia;
    //Report r[NUM_TIPOLOGIE][NUM_DIMENSIONI];
    Risultati ris[NUM_ALGORITMI];
    Report rS;
    rS.scambi=rS.confronti=0;


    int i,j,k,numero=0;
    for(i=0;i<NUM_ALGORITMI;i++){
        inzializzaReport(ris[i].r);
    }
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
            if(algoritmo==HeapSort) {
                v = genera_array(dimensioni[dim], tipologia, 1);

            }
            else {
                v = genera_array(dimensioni[dim], tipologia, 0);

            }
            ordinaArray(v,dimensioni[dim],algoritmo,&rS);
            printf("Per ordinare un insieme di %d elementi con lo schema %s usando l'algoritmo %s ho impiegato %lf secondi \n"
                   "ho eseguito %d scambi e %d confronti",dimensioni[dim],nomiTipologie[tipologia],nomiAlgoritmi[algoritmo],rS.t,rS.scambi,rS.confronti);
             break;
        case AUTOMATICA:
            for(i=0;i<NUM_ALGORITMI;i++){
                for(j=0;j<NUM_DIMENSIONI;j++){
                    for(k=0;k<NUM_TIPOLOGIE;k++){
                        if(i==HeapSort) {
                            v = genera_array(dimensioni[j], k, 1);
                            ordinaArray(v,dimensioni[j]+1,i,&ris[i].r[j][k]);
                            numero++;
                            printf("[%d]Per ordinare un insieme di %d elementi con lo schema %s usando l'algoritmo %s ho impiegato %lf secondi \n"
                                   "ho eseguito %d scambi e %d confronti\n", numero, dimensioni[j], nomiTipologie[k],
                                   nomiAlgoritmi[i], ris[i].r[j][k].t, ris[i].r[j][k].scambi, ris[i].r[j][k].confronti);
                            free(v);

                        }
                        else {
                            v = genera_array(dimensioni[j], k, 0);
                            ordinaArray(v, dimensioni[j], i, &ris[i].r[j][k]);
                            numero++;
                            printf("[%d]Per ordinare un insieme di %d elementi con lo schema %s usando l'algoritmo %s ho impiegato %lf secondi \n"
                                   "ho eseguito %d scambi e %d confronti\n", numero, dimensioni[j], nomiTipologie[k],
                                   nomiAlgoritmi[i], ris[i].r[j][k].t, ris[i].r[j][k].scambi, ris[i].r[j][k].confronti);
                            free(v);
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
    return 0;
}


void ordinaArray(int *v,int dim,int algoritmo,Report *r){
    int *o;
    clock_t start,end;
    switch (algoritmo){
        case SelectionSort:

            start=clock();
            selectionSort(v,dim,r);
            end=clock();
            r->t=((double) (end-start))/CLOCKS_PER_SEC;
            break;
        case InsertionSort:

            start=clock();
            insertionSort(v,dim,r);
            end=clock();
            r->t=((double) (end-start))/CLOCKS_PER_SEC;
            break;
        case HeapSort:

            start=clock();
            heapsort(v,dim,r);
            end=clock();
            r->t=((double) (end-start))/CLOCKS_PER_SEC;
            break;
        case QuickSort:

            start=clock();
            quickSort(v,0,dim-1,r);
            end=clock();
            r->t=((double) (end-start))/CLOCKS_PER_SEC;
            break;
        case MergeSort:

            o=(int*)malloc(sizeof(int)*dim);
            start=clock();
            mergesort(v,o,0,dim-1,r);
            end=clock();
            free(o);
            r->t=((double) (end-start))/CLOCKS_PER_SEC;
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
void selectionSort(int *v,int n,Report *r){
    int i,j;
    int min=0;
    for(i=0;i<n-1;i++){
        min=i;
        for(j=i+1;j<n;j++){
            r->confronti++;
            if(v[j]<v[min])
                min = j;
        }
        r->scambi++;
        swap(&v[i],&v[min]);
    }
}

void insertionSort(int v[],int dim,Report *r){
    int i,prossimo,j;
    for(i=0;i<=dim-1;i++){
        prossimo=v[i];
        for(j=i-1;j>=0;j--){
            if(prossimo<v[j]) {
                r->confronti++;
                v[j + 1] = v[j];
            }
            else
                break;
        }
        v[j+1]=prossimo;
        r->scambi++;
    }
}

void heapsort(int *a,int n,Report *r){
    int i;
    for(i=n/2;i>=1;i--){
        adatta(a,i,n,r);
    }
    for(i=n-1;i>=1;i--){
        swap(&a[1],&a[i+1]);
        r->scambi++;
        adatta(a,1,i,r);
    }
}

void adatta(int *a,int radice,int n,Report *r){
    int temp=a[radice];
    int figlio=2*radice;
    while (figlio<=n){
        if(figlio<n && a[figlio]<a[figlio+1]) {
            figlio++;
            r->confronti++;
        }
        if(temp>a[figlio]) {
            r->confronti++;
            break;
        }
        else{
            a[figlio/2]=a[figlio];
            r->scambi++;
            figlio=figlio*2;
        }

    }
    a[figlio/2]=temp;
    r->scambi++;
}

void mergesort(int *a, int *o, int lower, int upper,Report *r) {
    int medium;
    if (lower >= upper) return;
    medium = (lower + upper) / 2;
    mergesort(a, o, lower, medium,r);
    mergesort(a, o, medium + 1, upper,r);
    merge(a, o, lower, medium, upper,r);
}

void merge(int *a, int *o, int i, int m, int n,Report *r) {
    int j, k, pos_iniziale, t;
    j = m + 1;
    k = i;
    pos_iniziale = i;
    while (i <= m && j <= n) {
        if (a[i] <= a[j]) {
            r->confronti++;
            r->scambi++;
            o[k] = a[i];
            i++;
            k++;
        } else {
            r->confronti++;
            r->scambi++;
            o[k] = a[j];
            j++;
            k++;
        }
    }

    if (i > m) {
        for (t = j; t <= n; t++) {
            o[k + t - j] = a[t];
            r->scambi++;
        }
    } else {
        for (t = i; t <= m; t++) {
            o[k + t - i] = a[t];
            r->scambi++;
        }
    }

    for (t = pos_iniziale; t <= n; t++) {
        a[t] = o[t];
    }
}

void quickSort(int vet[],int u,int v,Report *r){
    int q;
    if(u==v) return;
    q=perno(vet,u,v,r);
    if(u<q) quickSort(vet,u,q-1,r);
    if(q<v) quickSort(vet,q+1,v,r);
}

int perno(int vet[],int primo,int ultimo,Report *r){
    int i,j,pivot;
    i=primo;
    j=ultimo+1;
    pivot=vet[primo];
    while (i<j){
        do{
            i++;
            r->confronti++;
        }while (vet[i]<=pivot && i<=ultimo);
        do{
            j--;
            r->confronti++;
        }while (vet[j]>pivot && j>=primo);
        if(i<j){
            swap(&vet[i],&vet[j]);
            r->scambi++;
        }

    }
    swap(&vet[primo],&vet[j]);
    r->scambi++;
    return j;
}


void inzializzaReport(Report v[][NUM_DIMENSIONI]){
    int i,j;
    for(i=0;i<NUM_TIPOLOGIE;i++){
        for(j=0;j<NUM_DIMENSIONI;j++){
            v[i][j].confronti=0;
            v[i][j].scambi=0;
        }
    }
}