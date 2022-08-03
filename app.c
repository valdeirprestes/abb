#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"
#define MAX 100
Arvore *arvore;
char menuStr[][MAX]={
		"Inicializar",
		"Insere",
		"Consulta Nome",
		"Remove",
		"Imprimi em ordem",
		"Mostre a arvore",
		"Sair"
	};

void cmd(int op){
	Dados dado;
	switch(op){
		case 1:
			CriaAbb(&arvore);
			puts("Estrutura inicializada\n");
			break;
		case 2:
			printf("\n\nEntre com o nome:");
			scanf("%s",dado.Nome);
			printf("Entre com a idade:");
			scanf("%d", &dado.Idade);
			if(insereAbb(&arvore, dado))
				printf("[%s] registrado!\n\n", dado.Nome);
			else
				printf("Erro, registro não realizado\n\n");
			break;
		case 3:/*Consulta*/
			printf("\n\nEntre com o nome:");
			scanf("%s",dado.Nome);
			if(ConsultaAbb(&arvore, &dado)){
				printf("\n\nNome:%s\n",dado.Nome);
				printf("Idade:%d\n\n\n",dado.Idade);
			}
			else
				printf("O registro \'%s\' nao foi encontrado\n", dado.Nome);
			break;
		case 4:/* Remover*/
			printf("\n\nEntre com o nome:");
			scanf("%s",dado.Nome);
			if(ConsultaAbb(&arvore, &dado)){
				removeAbb(&arvore, &dado);
				printf("\'%s\' removido!", dado.Nome);
			}
			else
				printf("O registro \'%s\' nao foi encontrado\n", dado.Nome);
			break;
		case 5:/*imprimir em ordem*/
			printf("\n\n");
			ImprimaOrdemAbb(&arvore);
			printf("\n%d registro(s)\n", QuantidadeAbb(&arvore));
			printf("\n\n");
			break;
		case 6:/* Mostre a arvore*/
			printf("\n\n\n");
			MostraAbb(&arvore);
			break;
	}

}
int menu(){
	int i;
	puts("\n\nMenu:\n");
	for(i=0 ; i < sizeof(menuStr)/ MAX; i++)
		printf("%2.2d - %s\n",i+1,menuStr[i]);
	printf("\nOpcao:");
	scanf("%d", &i);
	return i;
}

int main(int argc, char *arqv[]){
	int i;
	FILE *fp;
	char buffer[MAX];
	char op;
	char strNome[MAX];
	int idade;
	Dados auxDado;
	int iLinha;
	
	arvore = (Arvore*) malloc(sizeof(Arvore));
	if(argc > 1){
		if((strcmp(arqv[1],"-f") == 0 ) && argc == 3 ){ 
		/* Opção para entrar com um arquivo que adiciona e remove registro 
		 * i - inserção
		 * r - remoção
		 * exemplo para adicionar e remover o nome maria (para inserir tem colocar a idade)
		 * i 25 maria
		 * r maria
		 * */
		 fp = fopen(arqv[2], "r");
		 if(!fp)
			 printf("Não carregou o arquivo %s\n",arqv[2]);
		 else{
			 CriaAbb(&arvore);
			 iLinha=0;
			 fgets(buffer, MAX, fp);
			 while(!feof(fp)){
				 if(buffer[0] == 'i')
					sscanf(buffer,"%c %d %s", &op, &idade, strNome);
				 else
					sscanf(buffer,"%c %s", &op, strNome);
				 auxDado.Idade = idade;
				 strncpy(auxDado.Nome,strNome, MAX);
				 iLinha = iLinha +1;
				 switch(op){
					 case 'i':		
						if(insereAbb(&arvore, auxDado))
							printf("Registrado [%s] com sucesso(Linha %d)\n",auxDado.Nome, iLinha);
						else
							printf("Não foi possivel inser [%s] (Linha %d)\n",auxDado.Nome, iLinha);
						break;
					case 'r':
						if(removeAbb(&arvore, &auxDado)){
							printf("Removido [%s] com sucesso (Linha %d)\n", auxDado.Nome, iLinha);
						}
						else
							printf("Não foi possivel remover [%s](Linha %d)\n", strNome, iLinha);
						break;
					default:
						printf("Erro de opção na linha %d\n", iLinha);
						break;
							
				 }
				 fgets(buffer, MAX, fp);
			 }
			 fclose(fp);
		 }
		}else{
			puts("Paramentros incorreto para carregar o arquivo");
			puts("Entre com:");
			printf("%s -f nomearquivo\n", arqv[0]); 
		}
	}
	do{
		i = menu();
		cmd(i);
	}while(i != (sizeof(menuStr) / MAX) );
	return SUCESS;
}
