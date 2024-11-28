#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct arvore{
	char string[100];
	int nivel;
	struct arvore* esquerda;
	struct arvore* direita;
} arvore;

typedef struct{
	char string[100];
	int nivel;
} linha;

arvore* alocar_dinamicamente_uma_arvore(char string[]);
linha* alocar_dinamicamente_vetor_de_linhas(int capacidade_do_vetor);
void imprimir_vetor_de_linhas(linha vetor_de_linhas[], int tamanho);
void diminuir_vetor_de_linhas(linha vetor_de_linhas[], int* tamanho);
int caucular_valor_da_arvore(arvore* a);
void caucular_arvore_recursivo(arvore* a);
void preencher_toda_a_arvore_recursivo(arvore* no_atual, int marcador_de_linhas, linha vetor_de_linhas[], int* tamanho);
arvore* criar_e_preencher_a_arvore(linha vetor_de_linhas[], int* tamanho);
void imprimir_arvore_pos_ordem(arvore* a);
void desalocar_dinamicamente_arvore(arvore* a);
void desalocar_dinamicamente_vetor_de_linha(linha vetor_de_linhas[]);

#endif