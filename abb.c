#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "abb.h"


void CriaAbb(Arvore **arvoreAbb){
	(**arvoreAbb).raiz = NULL;
	(**arvoreAbb).qtd = 0;
}
int AbbVazio(Arvore ** arvoreAbb){
	return ( (**arvoreAbb).raiz ==NULL);
}
int QuantidadeAbb(Arvore **arvoreAbb){
	return (**arvoreAbb).qtd;
}
int insereAbb(Arvore **arvoreAbb, Dados dado){
	Nodo **noh;
	int teste;
	if(ConsultaAbb(arvoreAbb, &dado)){
		return FAILURE;
	}
	noh = &(**arvoreAbb).raiz;
	while(*noh){
		teste = strcmp((**noh).dado.Nome, dado.Nome);
			if(teste > 0)
				noh = &(**noh).filho_esquerda;
			else
				noh = &(**noh).filho_direita;
	}
	*noh = (Nodo *) malloc(sizeof(Nodo));
	if(!*noh)	return FAILURE;
	(**noh).dado = dado;
	(**noh).filho_direita= NULL;
	(**noh).filho_esquerda = NULL;
	(**arvoreAbb).qtd += 1;
	return SUCESS;
}
int removeAbb(Arvore **arvoreAbb, Dados *dado){
	Nodo *nohpai, *noh;
	int teste;
	nohpai = NULL;
	noh = (**arvoreAbb).raiz;
	while(noh){
		teste = strcmp(noh->dado.Nome, dado->Nome);
		if(teste>0){
			nohpai = noh;
			noh = noh->filho_esquerda;
			}
		else if(teste<0){
			nohpai = noh;
			noh = noh->filho_direita;
			}
		else{
			(*dado) = noh->dado;
			if(!noh->filho_direita){
				if(!nohpai)
					(**arvoreAbb).raiz=noh->filho_esquerda;
				else if(strcmp(nohpai->dado.Nome,dado->Nome) > 0)
					nohpai->filho_esquerda = noh->filho_esquerda;
				else
					nohpai->filho_direita = noh->filho_esquerda;
				free(noh);
			}
			else if(!noh->filho_esquerda){
				if(!nohpai)
					(**arvoreAbb).raiz=noh->filho_direita;
				else if(strcmp(nohpai->dado.Nome,dado->Nome) > 0)
					nohpai->filho_esquerda = noh->filho_direita;
				else
					nohpai->filho_direita = noh->filho_direita;
				free(noh);
			}
			else{
				noh->dado = MaiorMenoresAbb(noh);
			}
			(**arvoreAbb).qtd -= 1;
			return SUCESS;
		}
	}
	return FAILURE;
}
Dados MaiorMenoresAbb(Nodo *nohatual){
		Nodo *noh, *nohaux;
		Dados auxdado;
		nohaux = NULL;
		noh = nohatual->filho_esquerda;
		while(noh->filho_direita){
			nohaux = noh;
			noh=noh->filho_direita;
		}
		auxdado = noh->dado;
		if(nohaux)
			nohaux->filho_direita= noh->filho_esquerda;
		else
			nohatual->filho_esquerda = noh->filho_esquerda;
		free(noh);
		return auxdado;
}
int ConsultaAbb(Arvore **arvoreAbb, Dados *dado){
	Nodo *noh;
	int teste;
	if(AbbVazio(arvoreAbb)){ return FAILURE;}
	noh = (**arvoreAbb).raiz;
	while(noh){
		teste=strcmp(noh->dado.Nome,dado->Nome);
		if(teste>0){
			noh = noh->filho_esquerda;
		}else if(teste<0){
			noh= noh->filho_direita;
		}
		else
			{
				(*dado) = noh->dado;
				return SUCESS;
			}
	}
	return FAILURE;
}
void ImprimaOrdemAbb(Arvore **arvoreAbb){
	Nodo *noh = (**arvoreAbb).raiz;
	if(noh){
		ImprimaOrdemNoh(noh);
	}
}
void ImprimaOrdemNoh(Nodo *noh){
	if(noh){
		if(noh->filho_esquerda)
			ImprimaOrdemNoh(noh->filho_esquerda);
		printf("%s\n", noh->dado.Nome);
		if(noh->filho_direita)
			ImprimaOrdemNoh(noh->filho_direita);
	}
}
void ImprimaPreOrdemAbb(Arvore **arvoreAbb);
void ImprimaPosOrdemAbb(Arvore **arvoreAbb);
void MostraAbb(Arvore **arvoreAbb){
	Nodo *noh;
	 double pow(double x, double y);
	int maiornivel,nivel, item,teste;
	maiornivel =1;
	nivel =1;
	noh= (**arvoreAbb).raiz;
	while(nivel<=maiornivel){
		for(item = 1; item <= (int)pow(2,nivel-1); item++){
			teste=Mostre(noh, nivel+1, item);
			if(teste>maiornivel)
				maiornivel = teste;
		}
		nivel++;
		printf("\n");
	}
}
int Mostre(Nodo *nodo, int nivel, int elemento){
	Nodo *noh;
	double pow(double x, double y);
	int n, e, teste,contanivel;
	n = nivel - 1;
	e = elemento;
	noh=nodo;
	contanivel=1;
	while(n >1 && noh){
		teste = (  ((int) pow(2, n-1))  / 2);
		if(e <= teste){
			noh = noh->filho_esquerda;
			//e = teste;
		}else{
			noh= noh->filho_direita;
			if(e - teste)
				e= e - teste;
			else
				e=((e - teste)==0)? 2:1;
		}
		n--;
		contanivel++;
	}
	if(noh){
		printf("[%s]", noh->dado.Nome);
		if(noh->filho_esquerda || noh->filho_direita)
			return contanivel+1;
	}
	else
		printf("[----]");
	return contanivel;
}
