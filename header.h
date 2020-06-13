#ifndef HEADER_H
#define HEADER_H

//Definicao de Tipo
typedef struct _lista {
    struct _lista *anterior;
    int dia;
    int mes;
    int ano;
    float indice;
    struct _lista *proximo;
}Lista;

typedef struct _args{
	long int pesquisa;
	long int *datas;
	float *indice;
	int ctd;
}Dados;

//Definicao das Funcoes
void lerArquivo(Lista **,Lista **);
void ordenarLista(long int *,int *,int *, int *, float *,int );
void exibirLista(Lista *);
void iniciarLista(Lista **);

void porNaLista(Lista **,Lista **,int,int,int,float);
void gerarArq(Lista *);
void tipoGrafico(Lista *);
void *prePesquisa(void *);

void buscarDados(long int *,float *, int);
int listaVazia(Lista *);
void *carregando(void*);
void pesquisar(long int *,int ,int ,long int ,float *);

int contarElementos(Lista *);
void mergesort(long int *, int);
void sort(long int *, long int *, int, int);
void merge(long int *, long int *, int , int, int);

void codificarData(int[],int[],int[],float[],int, long int *);
void descodificarData(long int[],int *,int *,int *,float *,int );
void printarDados(float *,int);
void gotoxy(int, int);

void porNoVetor(Lista **,int *,int *,int *,float *,long int *,int*);
void limparLista(Lista **, Lista **);



#endif
