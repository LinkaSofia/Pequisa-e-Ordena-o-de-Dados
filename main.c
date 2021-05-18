#include "funcoes.h"
int main(){
    printf("\nAgenda telefonica - Linka Sofia Lunkes e Vitor Hugo dos Santos\n");
    Contact *lista = (Contact *) malloc(sizeof(Contact));
	if(!lista){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	lista->next = NULL;
    Contact *tempor,*novo;
    tempor = lista;
    Contact c;
    FILE *arq;
    arq = fopen("agenda.txt","w");

    if(arq == NULL){
        printf("ERRO!\n");
        exit(1);
    }

    while( fscanf(arq,"Nome: %s - Email: %s - Telefone: %s\n", &c.name,&c.email, &c.phone) != EOF){
        if(c.name != NULL){
            novo = (Contact*)malloc(sizeof(Contact));
            strcpy(novo->name, c.name);
            strcpy(novo->phone,c.phone);
            strcpy(novo->email,c.email);
            novo->next = NULL;
            if(vazia(lista)){ 
            // se a lista esta vazia adciona contact direto
            lista->next = novo;
            }
            else{
                while(tempor->next != NULL){
                    tempor = tempor->next;
                }
            tempor->next = novo;
            }
        }
    }
    fclose(arq);
	int op;
	do{
		op = menu();
		opcao(lista,op);
	}while(op);

    free(lista);
	return 0;
}
