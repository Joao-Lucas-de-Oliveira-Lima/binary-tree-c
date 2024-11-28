#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "binary_tree/binary_tree.h"

int analisar_total_de_tabulacoes(char string[]){
	int contador = 0;
	int k;
	for(k=0; string[k]; k++) if(string[k] == '\t') contador++;
	return contador;
}	
// tira as tabulaçoes da string \n e\t
void simplificar_strings(linha vetor_de_linhas[], int tamanho){
	char vetor_auxiliar[100];
	int j=0, k, i;
	for(k=0; k<tamanho; k++){
		for(i=0; vetor_de_linhas[k].string[i]; i++){
			if(vetor_de_linhas[k].string[i] != '\t'){
				 vetor_auxiliar[j] = vetor_de_linhas[k].string[i];
				 j++;
			}
		}
		vetor_auxiliar[j] = '\0';
		j=0;
		strcpy(vetor_de_linhas[k].string, vetor_auxiliar);
	}
}

int main(){
	int opcao_escolhida;
	int opcao_2_ativada = 0;
	int k;
	while(opcao_escolhida != '3'){
		system("cls");
		printf("Enter the value corresponding to each option to access it:\n\n");
		printf("1. Read \"equation.txt\", required to have the file in the same folder as \"arvore.txt\"\n");
		printf("2. Write to \"equation.txt\"\n");
		printf("3. Exit\n");
		opcao_escolhida = getch();
		if(opcao_escolhida == '1'){
			system("cls");
			char linha_do_arqivo[100];//guarda as iformacoes do aqrv
			int total_de_linhas = 0;
			FILE* pont_1_arquivo = fopen("equation.txt", "r");//r = le o arquivo
			if(pont_1_arquivo != NULL){
				//Descobrindo total de linhas do arquivo
				while(1){
					fscanf(pont_1_arquivo, "%[^\n]%*c", linha_do_arqivo);
					total_de_linhas++;
					if(feof(pont_1_arquivo)) break;//feof = não posso ler mais o arquivo
				}
				if(opcao_2_ativada == 1){
					total_de_linhas--;
					opcao_escolhida = 0;
				}
				fclose(pont_1_arquivo);//fecha o arquivo
				printf("Total lines: %d\n", total_de_linhas);
				//Armazenando as informações do arquivo de texto
				FILE* pont_2_arquivo = fopen("equation.txt", "r");
				if(pont_2_arquivo != NULL){
					linha* vetor_de_linhas = alocar_dinamicamente_vetor_de_linhas(total_de_linhas);
					//Indexando linhas e níveis. pega as linha e joga no vetor
					for(k=0; k<total_de_linhas; k++){
						fscanf(pont_2_arquivo, "%[^\n]%*c", linha_do_arqivo);
						strcpy(vetor_de_linhas[k].string, linha_do_arqivo);
						vetor_de_linhas[k].nivel = analisar_total_de_tabulacoes(linha_do_arqivo);
					}
					fclose(pont_2_arquivo);
					printf("Tree: \n");
					imprimir_vetor_de_linhas(vetor_de_linhas, total_de_linhas);
					simplificar_strings(vetor_de_linhas, total_de_linhas);// tirar os \n do string
					arvore* a = criar_e_preencher_a_arvore(vetor_de_linhas, &total_de_linhas);
					caucular_arvore_recursivo(a);
					printf("\nResults: %s\n", a->string);
					desalocar_dinamicamente_arvore(a);
					desalocar_dinamicamente_vetor_de_linha(vetor_de_linhas);
				}else{
					printf("The file cannot be read or does not exist.\n");
				}
			}else{
				printf("The file cannot be read or does not exist.\n");
			}
			getch();
		}
		else if(opcao_escolhida == '2'){
			system("cls");
			char texto[100];
			FILE* pont_3_arquivo = fopen("equation.txt", "w");//apaga no fim e escreve na ultima linha
			FILE* pont_4_arquivo = fopen("equation.txt", "a");//escreve no fim
			int inicio = 0;
			while(texto[0] != 's'){
				char copia = texto[0];
				if(inicio == 0){ //inicio = 0 então usa o w
					system("cls");
					printf("Type \"s\" to finish writing\n");
				}
				if(inicio == 1){
					printf("Enter the text: ");
					scanf("%[^\n]%*c", texto);
					if(texto[0] != 's') fprintf(pont_4_arquivo, "%s\n", texto);	
				}
				if(inicio == 0){
					printf("\nEnter the text: ");
					if(texto[0] == '\n') texto[0] = 'x';
					scanf("%[^\n]%*c", texto);
					if(texto[0] != 's'){
						fprintf(pont_3_arquivo, "%s\n", texto);
						fclose(pont_3_arquivo);
						inicio = 1; //usa o a
					}
				}
			}
			texto[0] = 'a';
			opcao_2_ativada = 1;
			fclose(pont_4_arquivo);
		}
	}
	return 0;
}