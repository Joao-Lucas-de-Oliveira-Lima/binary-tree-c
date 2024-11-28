#include <stdlib.h>
#include "binary_tree.h"
#include <stdio.h>
#include <string.h>

arvore* alocar_dinamicamete_uma_arvore(char string[], int nivel){
	arvore* nova_arvore = (arvore*)malloc(sizeof(arvore));
	strcpy(nova_arvore->string, string);//pega a string e colocar no vetor
	nova_arvore->nivel = nivel;
	nova_arvore->esquerda = NULL;
	nova_arvore->direita = NULL;
}


linha* alocar_dinamicamente_vetor_de_linhas(int capacidade_do_vetor){
	linha* a  = (linha*)malloc(sizeof(linha)*capacidade_do_vetor);
	return a;
}

void imprimir_vetor_de_linhas(linha vetor_de_linhas[], int tamanho){
	int k;
	for(k=0; k<tamanho; k++) printf("%d. String: %s\n", k, vetor_de_linhas[k].string);
}

void diminuir_vetor_de_linhas(linha vetor_de_linhas[], int* tamanho){
	int k;
	if(*tamanho != 0){
		for(k=0; k<*tamanho-1; k++){
			 vetor_de_linhas[k] = vetor_de_linhas[k+1];
		}
		*tamanho = *tamanho-1;
	}
}

int converter_string_para_int(char string[]){
	int resultado = 0;
	int condicao_para_numero_negativo = 0;
	int k;
	for(k=0; k<string[k]; k++){
		if(string[0] == '-'){
			 condicao_para_numero_negativo = 1;
			 continue;
		}
		resultado = resultado*10 + string[k] - '0';
	}
	if(condicao_para_numero_negativo == 1) return resultado*-1;
	else return resultado;
}

void preencher_toda_a_arvore_recursivo(arvore* no_atual, int marcador_de_linhas, linha vetor_de_linhas[], int* tamanho){
	if(*tamanho <= 0 || marcador_de_linhas != vetor_de_linhas[0].nivel) return;
	arvore* novo_no_irmao = alocar_dinamicamete_uma_arvore(vetor_de_linhas[0].string, marcador_de_linhas);
	diminuir_vetor_de_linhas(vetor_de_linhas, tamanho);
	no_atual->esquerda = novo_no_irmao;
	preencher_toda_a_arvore_recursivo(no_atual->esquerda, marcador_de_linhas+1, vetor_de_linhas, tamanho);
	if(*tamanho <= 0 || marcador_de_linhas != vetor_de_linhas[0].nivel) return;
	arvore* novo_no_irma = alocar_dinamicamete_uma_arvore(vetor_de_linhas[0].string, marcador_de_linhas);
	diminuir_vetor_de_linhas(vetor_de_linhas, tamanho);
	no_atual->direita = novo_no_irma;
	preencher_toda_a_arvore_recursivo(no_atual->direita, marcador_de_linhas+1, vetor_de_linhas, tamanho);
}

int caucular_valor_da_arvore(arvore* a){
	int resultado;
	if(a->direita != NULL && a->esquerda != NULL && a->string[0] == '-'){
		resultado = converter_string_para_int(a->direita->string) - converter_string_para_int(a->esquerda->string);
	}else if(a->direita == NULL || a->esquerda == NULL && a->string[0] == '-'){
		if(a->direita == NULL) resultado = converter_string_para_int(a->esquerda->string);
		else resultado = converter_string_para_int(a->direita->string);
		resultado = resultado*-1;
	}else if(a->direita != NULL && a->esquerda != NULL && a->string[0] == '+'){
		resultado = converter_string_para_int(a->direita->string) + converter_string_para_int(a->esquerda->string);	
	}else if(a->direita == NULL || a->esquerda == NULL && a->string[0] == '+'){
		if(a->direita == NULL) resultado = converter_string_para_int(a->esquerda->string);
		else resultado =converter_string_para_int(a->direita->string);
	}else if(a->direita != NULL && a->esquerda != NULL && a->string[0] == '*'){
		resultado = converter_string_para_int(a->direita->string) * converter_string_para_int(a->esquerda->string);
	}else if(a->direita != NULL && a->esquerda != NULL && a->string[0] == '/'){
		resultado = converter_string_para_int(a->direita->string) / converter_string_para_int(a->esquerda->string);
	}else if(a->direita != NULL && a->esquerda != NULL && a->string[0] == 'm' && a->string[1] == 'i'){
		int c = converter_string_para_int(a->direita->string);
		int b = converter_string_para_int(a->esquerda->string);
		if(c<=b) resultado = c;
		else resultado = b;
	}else if(a->direita == NULL || a->esquerda == NULL && a->string[0] == 'm' && a->string[1] == 'i'){
		if(a->direita == NULL) resultado = converter_string_para_int(a->esquerda->string);
		else resultado = converter_string_para_int(a->direita->string);
	}else if(a->direita != NULL && a->esquerda != NULL && a->string[0] == 'm' && a->string[1] == 'a'){
		int c = converter_string_para_int(a->direita->string);
		int b = converter_string_para_int(a->esquerda->string);
		if(c>=b) resultado = c;
		else resultado = b;
	}else if(a->direita == NULL || a->esquerda == NULL && a->string[0] == 'm' && a->string[1] == 'a'){
		if(a->direita == NULL) resultado = converter_string_para_int(a->esquerda->string);
		else resultado = converter_string_para_int(a->direita->string);
	}
	int copia = resultado;
	int contador = 0;
	if(copia == 0){
		contador = 1;
	}else{
		while(copia != 0){
			copia = copia/10;
			contador++;
		}
	}
	copia = resultado;
	char vetor_auxiliar[contador];
	int k;
	for(k=contador-1; k>=0; k--){
		vetor_auxiliar[k] = (copia%10) + '0';
		copia = copia/10;
	}
	vetor_auxiliar[contador] ='\0';
	strcpy(a->string, vetor_auxiliar);
	return resultado;
}

void imprimir_arvore_pos_ordem(arvore* a){
	if(a == NULL) return;
	imprimir_arvore_pos_ordem(a->direita);
	imprimir_arvore_pos_ordem(a->esquerda);
	printf("String: %s\n", a->string);
}

void caucular_arvore_recursivo(arvore* a){
	if(a == NULL) return;
	caucular_arvore_recursivo(a->direita);
	caucular_arvore_recursivo(a->esquerda);
	if((a->esquerda == NULL && a->direita != NULL) || (a->direita == NULL && a->esquerda != NULL) || 
	(a->esquerda != NULL && a->direita != NULL)){
		caucular_valor_da_arvore(a);
	}
}

arvore* criar_e_preencher_a_arvore(linha vetor_de_linhas[], int* tamanho){
	int marcador_de_linhas = 1;
	int resultado;
	arvore* raiz = alocar_dinamicamete_uma_arvore(vetor_de_linhas[0].string, 0);
	diminuir_vetor_de_linhas(vetor_de_linhas, tamanho);
	preencher_toda_a_arvore_recursivo(raiz, marcador_de_linhas, vetor_de_linhas, tamanho);
	return raiz;
}

void desalocar_dinamicamente_vetor_de_linha(linha vetor_de_linhas[]){
	free(vetor_de_linhas);
}

void desalocar_dinamicamente_arvore(arvore* a){
	if(a == NULL) return;
	caucular_arvore_recursivo(a->direita);
	caucular_arvore_recursivo(a->esquerda);
	free(a);
}