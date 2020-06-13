#include "funcoes.c"

int main() {
    
   //Criacao da variavel
    Lista *inicio, *fim;
    int *dia,*mes, *ano, i,ctd;
    float *indice;
    long int *data;
    

    //Criar uma lista vazia
    iniciarLista(&inicio);

	//Exibe itens na lista
    exibirLista(inicio);

    //Lê o arquivo o covid19.txt
    lerArquivo(&inicio,&fim);
    
	//Gera um espaco no vetor para cada linha do arquivo
	ctd = contarElementos(inicio);
	dia = (int*) malloc(ctd * sizeof(int));
	mes = (int*) malloc(ctd * sizeof(int));
	ano = (int*) malloc(ctd * sizeof(int));
	indice = (float*) malloc(ctd * sizeof(float));
	data = (long int*) malloc(ctd * sizeof(long int));
	
    //Copia o conteudo da lista para o vetor
    porNoVetor(&inicio,dia,mes,ano,indice,data,&ctd);

    //Apaga todos os elementos na lista
	limparLista(&inicio,&fim);
    
    //Ordena os dados por data
    ordenarLista(data, ano, mes, dia, indice, ctd);
	
    //Poe os dados na lista
    for ( i = 0; i < ctd; i++)
    	porNaLista(&inicio,&fim, dia[i], mes[i], ano[i], indice[i]);
    	
    //Exibe itens na lista
    exibirLista(inicio);
    
    //Descobre o tipo de grafico e exibe o resultado
    tipoGrafico(fim);
    
    //Gerar um Json na pasta htdocs do xampp para ser lido pelo canvas.html
    gerarArq(inicio);
    
    //Inicia o processo de busca
    buscarDados(data, indice, ctd);
    
	
    return 0;

}
