#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "header.h"
#include <pthread.h>
#include <windows.h>

#define NUM_THREADS 2
#define MAX_PONTOS 5

pthread_t thread_pesquisa, thread_carregamento;

int listaVazia(Lista *lista) {
    if (lista == NULL) {
        return 1;   
    }
    return 0;
}

int contarElementos(Lista *lista) {
    int quantidade = 0;
    Lista *aux = lista;

    while (aux != NULL){
        quantidade++;
        aux = aux->proximo;
    }
    return quantidade;
}

void iniciarLista(Lista **lista) {
    *lista = NULL;
} 

void porNaLista(Lista **inicio,Lista **fim,int dia,int mes,int ano,float indice) {
    Lista *aux = *inicio;
    Lista *novoPonto;

    novoPonto = (Lista *) malloc(sizeof(Lista));
        
    novoPonto->dia = dia;
    novoPonto->mes = mes;
    novoPonto->ano = ano;
    novoPonto->indice = indice;

    if (listaVazia(*inicio)){
        novoPonto->proximo = NULL;
        novoPonto->anterior = NULL;
        *fim = novoPonto; 
    } else {
       novoPonto->proximo = aux;
       aux->anterior = novoPonto;
       novoPonto->anterior = NULL;
    }
    
    *inicio = novoPonto;
}

void * prePesquisa(void * arg) {
	
	Dados *aux = (Dados *) arg;
	
	int ctd = aux->ctd;
	float *indice = aux->indice;
	long int *datas = aux->datas;
	long int pesquisa = aux->pesquisa;
	
	pesquisar(datas, 0,ctd ,pesquisa, indice);
}

void * carregando(void*arg) {
	int i,v,tempo, voltas;
	int mili_segundos = 100 * 3;
	
	voltas = 3;
	tempo = 3;
	
	for(v = 0; v < voltas; v++) {
		gotoxy(11,10);
		printf("    ");
		fflush(stdout);
		gotoxy(0,9);
		printf("\nProcurando");
		for(i=0;i < tempo; i++){
	   		clock_t inicio = clock(); 
			while (clock() < inicio + mili_segundos);
		  	printf("."); 
		  	fflush(stdout);
		}
	}
   	
	printf("\n");
}

void limparLista(Lista **inicio, Lista **fim) {
	Lista *aux = *inicio;
	
	while(aux != NULL) {
		free(aux);
		aux = aux->proximo;	
	}
	*inicio = aux;
	*fim = aux;
}

void buscarDados(long int *data,float *indice, int ctd) {
	
	Dados *arg;
	int dia, mes, ano;
	char resposta;
	
	printf("\nDeseja procurar algo [s/n]: ");
	scanf(" %c",&resposta);
	
	if(resposta == 's') {
		printf("\nDigite uma data [DD MM AAAA]: ");
		scanf("%d %d %d",&dia, &mes, &ano);
		
		gotoxy(5,11);
		
		printf("\nDia: %d",dia);
		printf("\nMes: %d",mes);
		printf("\nAno: %d",ano);
		
		pthread_create(&thread_carregamento,NULL,carregando,(void*)NULL);
		
		arg->pesquisa = (ano * 365) + (mes * 30) + dia;
		
		arg->indice = indice;
		arg->datas = data;
		arg->ctd = ctd;
		
    
    	pthread_create(&thread_pesquisa,NULL,prePesquisa,(void*)arg);
    	
    	pthread_join(thread_pesquisa, NULL);
		
		
	} else {
		printf("\nPesquisa abortada!\n");
	}
	
}

void gotoxy(int x, int y) {
    COORD c = {x, y};
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE), c);
}

void pesquisar(long int *item,int inicio,int fim,long int dado,float *indice) {
	int ind, ctd;
	int dia, mes, ano;
	
	ind = round((inicio + fim)/ 2);
	
	if(item[ind] == dado) {
        pthread_join(thread_carregamento, NULL);
        
        gotoxy(10,14);
		printf("\nIndice: %.2f", indice[ind]);
		return;
	}
	
	if(fim <= inicio) {
		pthread_join(thread_carregamento, NULL);
		
		gotoxy(10,14);
		
		printf("\nValor nao encontrado!");
		return;
	}
	
	if(item[ind] < dado) {
		pesquisar(item, ind+1, fim, dado, indice);
	} else {
		pesquisar(item, inicio, ind-1, dado, indice);
	}
		
}
void porNoVetor(Lista **inicio,int *dia,int *mes,int *ano,float *indice,long int *data,int *ctd) {
	
	int i;
	Lista *aux = *inicio; 
	
	//Salva os dados da lista no vetor
	for(i = 0; aux != NULL; i++) {
		dia[i] = aux->dia;
		mes[i] = aux->mes;
		ano[i] = aux->ano;
		indice[i] = aux->indice;
		
		aux = aux->proximo;
	}
	
}

void tipoGrafico(Lista *lista) {
    Lista *aux = lista; 
    int quantidade, voltas, ctd;
    float valores[MAX_PONTOS];

    voltas = ctd = 0;

    if(listaVazia(lista)) {
        printf("\nLista vazia!\n");
        return;
    }

    quantidade = contarElementos(lista);
    quantidade = (int) quantidade / MAX_PONTOS;
    
    if (quantidade < 1)
        quantidade++;
    

    valores[ctd] = aux->indice;
    ctd++;

    while(aux != NULL && MAX_PONTOS != ctd){
        if (voltas == quantidade) {
            valores[ctd] = aux->indice;
            ctd++;
            voltas = 0;
        }
        aux = aux->anterior;
        voltas++;
    }
	
    if (valores[0] > valores[1]) {
            if ((valores[1] == valores[2]) || (valores[2] == valores[3])) {
                printf("\nGrafico em U!\n");
            } else if (valores[1] < valores[2] && valores[3] < valores[4]){
                printf("\nGrafico em W!\n");
            } else if (valores[3] < valores[4]) {
                printf("\nGrafico em V!\n");
            } else {
                printf("\nFormato de grafico indefinido!\n");
            }
            
    } else if (valores[3] > valores[4]) {
        printf("\nGrafico em L!\n");
    } else {
        printf("\nFormato de grafico indefinido!\n");
    }
    
}

void exibirLista(Lista *lista) {
	
    Lista *aux = lista;

    if (listaVazia(aux)) {
        printf("Lista Vazia!\n");
        return;
    }

    printf("\nDados Lidos: [");
    while (aux != NULL) {
       printf(" %.2f",aux->indice);
       aux = aux->proximo;
    }
    printf("]\n");
    
    
}

void codificarData(int *ano,int *mes,int *dia,float *indice,int ctd, long int *dataFormatada) {
    int auxd, auxm, auxa, auxf, i;
    
    
    for (i = 0; i < ctd; i++) {
        auxf = (int) (indice[i] * 10);
        dataFormatada[i] = ((ano[i] * 365) + (mes[i] * 30) + dia[i])*1000 + auxf;
    }
}
void descodificarData(long int *datas,int *ano,int *mes,int *dia,float *indice,int ctd) {
	int i;
	long int auxd, auxi;
	
    for (i = 0; i < ctd; i++) {
    	
    	indice[i] = datas[i] % 1000;
    	
    	datas[i] = (datas[i] - indice[i]) / 1000;
    	
    	indice[i] /= 10; 
    	
    	auxd = datas[i];
    	
        ano[i] = (int) datas[i] / 365;
        
       	datas[i] -= ano[i] * 365;
        
        mes[i] = (int) datas[i] / 30;
        
        dia[i] = datas[i] - mes[i] * 30;
        
        if(dia[i] == 0 )
        	dia[i]++;
        if(mes[i] == 0 )
        	mes[i]++;
           
        datas[i] = auxd;
    }
    
}

void printarDados(float *datas, int ctd) {
	int i;
    printf("Itens em datas[X]: [");
    for( i = 0; i < ctd; i++)
        printf("%f, ",datas[i]);
    printf("]\n");
}

void ordenarLista(long int *datas,int *ano,int *mes, int *dia, float *indice,int ctd) {
    
    codificarData(ano, mes, dia, indice,ctd, datas);
    
    mergesort(datas,ctd);
    
    descodificarData(datas, ano, mes, dia, indice,ctd);
    
}

void mergesort(long int *v, int n) {
  long int *c = malloc(sizeof(long int) * n);
  sort(v, c, 0, n - 1);
  free(c);
}

void sort(long int *v, long int *c, int i, int f) {
  if (i >= f) return;

  int m = (i + f) / 2;

  sort(v, c, i, m);
  sort(v, c, m + 1, f);

  if (v[m] <= v[m + 1]) return;

  merge(v, c, i, m, f);
}


void merge(long int *v, long int *c, int i, int m, int f) {
  int z,
      iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = v[z];

  z = i;

  while (iv <= m && ic <= f) {

    if (c[iv] < c[ic])
		 v[z++] = c[iv++];
    else 
		 v[z++] = c[ic++];
  }

  while (iv <= m) v[z++] = c[iv++];

  while (ic <= f) v[z++] = c[ic++];
}

void lerArquivo(Lista **inicio, Lista **fim) {

    FILE *arq;
    int i, auxd, auxm, auxa;
    float  auxi;

    arq = fopen("covid20.txt","r");
    if(arq == NULL)
        exit(1);

    for ( i = 0; !feof(arq) ; i++) {
    	fscanf(arq,"%d %d %d %f\n",&auxd, &auxm ,&auxa,&auxi);
    	porNaLista(inicio, fim, auxd, auxm, auxa, auxi);
	}

    fclose(arq);

}

void gerarArq(Lista *lista) {
    Lista *aux = lista;
    FILE *arq;
    char dados[100];

    arq = fopen("C:/xampp/htdocs/dadosDoGrafico.json", "w");

    fputs("[\n", arq);

    while (aux->proximo != NULL) {

        sprintf(dados,"{\n\"data\":\"%d-%d-%d\",\n \"indice\":%.2f\n},",
                aux->ano,
                aux->mes,
                aux->dia,
                aux->indice);
                
        fputs(dados, arq);

        aux = aux->proximo;
    }

    sprintf(dados,"{\n\"data\":\"%d-%d-%d\",\n \"indice\":%.2f\n}",
                aux->ano,
                aux->mes,
                aux->dia,
                aux->indice);

    fputs(dados, arq);

    fputs("\n]", arq);
    
  	fclose(arq);

}
