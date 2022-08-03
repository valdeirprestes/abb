#ifndef ABBR
#define ABBR
#define TEXTO 100
#define FAILURE 0
#define SUCESS 1
typedef struct Dados{
	int Idade;
	char Nome[TEXTO];
}Dados;

typedef struct Nodo{
	Dados dado;
	struct Nodo *filho_direita;
	struct Nodo *filho_esquerda;
}Nodo;


typedef struct Arvore{
	Nodo *raiz;
	int qtd;
}Arvore;

void CriaAbb(Arvore **arvoreAbb);
int AbbVazio(Arvore ** arvoreAbb);
int QuantidadeAbb(Arvore **arvoreAbb);
int insereAbb(Arvore **arvoreAbb, Dados dado);
int removeAbb(Arvore **arvoreAbb, Dados *dado);
Dados MaiorMenoresAbb(Nodo *nohatual );
int ConsultaAbb(Arvore **arvoreAbb, Dados *dado);
void ImprimaOrdemAbb(Arvore **arvoreAbb);
void ImprimaOrdemNoh(Nodo *noh);
void ImprimaPreOrdemAbb(Arvore **arvoreAbb);
void ImprimaPosOrdemAbb(Arvore **arvoreAbb);
void MostraAbb(Arvore **arvoreAbb);
int Mostre(Nodo *noh, int nivel, int elemento);

#endif
