#include "estrutura.h"
// Imprimindo o menu
int menu(void){
	int op;
	printf("\nEscolha a opcao:\n\n");
	printf("0 - Sair e salvar\n");
	printf("1 - Inserir contato\n");
	printf("2 - Deletar contato\n");
	printf("3 - listar contatos\n");
	printf("4 - Consultar um contato pelo name\n");
	printf("Sua opcao: "); scanf("%d", &op);
	//op lê a opção selecionada pelo usuário
	return op;
}
void opcao(Contact *lista, int op){
	char name[30];
	// op é o que foi lido do teclado - se 0 então salva a lista
	switch(op){
		case 0:
            printf("\nObrigado por usar nossa agenda!\n");
            salvarLista(lista);
            // Se a lista não for vazia em contact ele define os ponteiros
            if(!vazia(lista)){
                Contact *ProximoContato,*ContatoAtual;
                //Contato atual vai para o proximo da lista
                ContatoAtual = lista->next;
                //Se contato atual for diferente de nulo o proximo contato recebe o proximo do contato atual 
                while(ContatoAtual != NULL){
                    ProximoContato = ContatoAtual->next;
                    //libera o contato atual
                    free(ContatoAtual);
                    //contato atual recebe o proximo contato
                    ContatoAtual = ProximoContato;
                }
	        }
	        //proximo da lista recebe nulo
            lista->next = NULL;
			break;
			
		//Se o usuário digitar 1, então chama a função insContact
		case 1:
            printf("\n---------------------------------------\n");
            printf("INSERIR CONTATO\n");
            printf("---------------------------------------\n");
			insContact(lista);
			salvarLista(lista);
			break;
		
		//Se o usuário digitar 2, então chama a função delContact
		case 2:
            printf("\n---------------------------------------\n");
            printf("DELETAR CONTATO\n");
            printf("---------------------------------------\n");
			printf("Insira o name do contato a ser deletado: ");
            setbuf(stdin,NULL);
            scanf("%s",name);
            delContact(name,lista);
            salvarLista(lista);
			break;
		
		//Se o usuário digitar 3, então chama a função listContacts
        case 3: 
            printf("\n---------------------------------------\n");
            printf("LISTAR CONTATOS\n");
            printf("---------------------------------------\n");
            listContacts(lista);
            break;
            
        //Se o usuário digitar 4, então chama a função queryContact
        case 4:
        	printf("---------------------------------------\n");
            printf("CONSULTAR CONTATO PELO NOME\n");
        	printf("---------------------------------------\n");
            printf("Digite o nome do contato a ser buscado: ");
            scanf("%s",name);
        	queryContact(name,lista);
        	break;

		default:
			printf("\nComando invalido\n");
	}
}
void listContacts (Contact *lista){
	FILE* arq = fopen("agenda.txt", "r");
	    int i = 0;
    char Linha[100];
    char *result;
    //Se o arquivo agenda.txt for nulo
    if(arq == NULL){
        printf("Sem dados");
    }
    //Enquanto não tiver no fim do arquivo
    while (!feof(arq))
    {
	// Lê uma linha 
	// o 'fgets' lê até 99 caracteres ou até o '\n'
      result = fgets(Linha, 100, arq);  
      // Se foi possível ler
      if (result)  
	  printf("%s",Linha);
      i++;
    }
    if(i<1){
        printf("Não possui contatos na lista \n");
    }
    printf("---------------------------------------\n");
    //Fecha o arquivo
    fclose(arq);
    
}
void queryContact(char name[], Contact *lista){
    formataname(name);
    Contact *minhaLista = lista;
    char novo[30];
    char *save;
    int cont = 1;
//Enquanto na lista for diferennte de nulo, o save recebe o nome
    while(minhaLista != NULL){
        save = strstr(minhaLista->name,name);
        //Se o nome for nulo a minha lista recebe o proximo nome
        if(save == NULL){
            minhaLista = minhaLista->next;
        }else{
            printf("\n---------------------------------------\n");
            printf("Nome: %s - Email: %s - Telefone: %s\n", minhaLista->name, minhaLista->email, minhaLista->phone);
            printf("---------------------------------------\n");
            cont= 0;
            return;
        }
    }
    if (cont ==1)  {
        printf("%s Contato não encontrado!\n",name);
    }
}

int vazia(Contact *lista){
	if(lista->next == NULL)
		return 1;
	else
		return 0;
}

//Insere novo contato
void insContact(Contact *lista){
	//contact aponta para o ponteiro "novo" e aloca um espaço de memória 
    Contact *novo=(Contact *) malloc(sizeof(Contact));
    int i = 0;
    //se novo for false informa o usuário que não tem memória disponível para alocar 
	if(!novo){
		printf("Sem memoria disponivel!\n");
		//Sai
		exit(1);
	}
 
    printf("\nNome: "); 
    //pede e armazena o nome
    scanf(" %s",novo->name); 
    //Deixa todos os caracteres com a mesma formatação
    formataname(novo->name);
    printf("Email: ");
    //pede e armazena o email
    scanf("%s", novo->email);
    printf("Telefone: ");
    //pede e armazena o telefone
    scanf("%s",novo->phone);
// um novo contato é criado
    novo->next = NULL; 
    // se a lista esta vazia, ele adiciona direto o "novo";
	if(vazia(lista)){ 
		lista->next = novo;
    }else{
    	//Contact *auxiliar recebe o proximo da lista
		Contact *auxiliar = lista->next; 
		Contact *ant = lista; 

        int cont = 0;
        //Contact aponta para o ponteiro aux
        Contact *aux;
        // aux recebe o proximo da lista
        aux = lista->next;
        // enquanto o proximo da lista for diferente de nulo, o contador recebe +1 e o aux recebe o proxima da lista
        //Fica ordenando a lista
        while(aux != NULL){
            cont++;
            aux = aux->next;
        }
// no caso de ter um Contact,
        if(cont == 1){  
		  //verifica a ordem alfabetica
			if(strcmp(auxiliar->name,novo->name) > 0){ 
                novo->next = auxiliar;
				ant->next = novo;
				return;
			}
			auxiliar->next = novo;
			return;
		}
        // caso tenha mais de um Contact insere o novo ja ordenado
		do{ 
			if(strcmp(auxiliar->name,novo->name) > 0){
				novo->next = auxiliar;
				ant->next = novo;
				return;
			}
			ant = ant->next;
			auxiliar = auxiliar->next;
		}while( auxiliar->next != NULL  ||  novo->next != NULL);
		
        if(strcmp(auxiliar->name,novo->name) > 0){
            ant->next = novo;
            novo->next = auxiliar;
            return;
        }
        //insere novo Contact caso ele esteja na ultima posicao
		auxiliar->next = novo; 
	}
}


void salvarLista(Contact *lista){
	//se nao existir, vai ser criado, nunca sera nulo;
	//arq = fopen("agenda.txt", "r");
  //arq2 = fopen("agenda2.txt", "w+");
    FILE *arq = fopen("agenda.txt","w"); 
    Contact *auxiliar;
    auxiliar = lista->next;
    Contact c;

    if(arq == NULL){
        printf("Arquivo NULL!");
        exit(1);
    }
    
    while(auxiliar != NULL){
        strcpy(c.name,auxiliar->name);
        strcpy(c.email,auxiliar->email);
        strcpy(c.phone,auxiliar->phone);
        fprintf(arq,"Nome: %s -  Email: %s - Telefone: %s\n", c.name, c.email, c.phone);
        auxiliar = auxiliar-> next;
    }
    fclose(arq);
}

//Recebe o ponteiro nome e o ponteiro Lista
void delContact(char *name, Contact *lista){
    Contact *minhaLista = lista;
    //Ponteiro MinhaListaNext recebe o proximo contato da lista 
    Contact *minhaListaNext = lista->next;
    formataname(name);

    if (minhaLista->next == NULL){
        printf("Lista vazia!");
    }
    // Enquanto a lista for diferente de nulo e se o nome digitado é diferente ao nome que está na lista
    while(minhaListaNext != NULL && strcmp(minhaListaNext->name,name) != 0){
    	//Minha lista recebe o proximo da lista
        minhaLista = minhaListaNext;
        //O proximo da lista recebe o proximo da lista
        minhaListaNext = minhaListaNext->next;
    }
    // Se o nome for igual ao nome do proximo da lista 
    if(strcmp (name, minhaListaNext->name) == 0){
    	//O proximo da minha lista recebe o proximo do proximo da lista
        minhaLista->next = minhaListaNext->next;
        printf("%s foi excluido!",name);
    }else{
        printf("%s nao foi encontrado!",name);
    }
}


void formataname(char name[]){
    int i = 0;
    // Formatar o name
    while(i < strlen(name)){
		name[i] = tolower(name[i]);
		if(i == 0 || name[i-1] == ' '){
			name[i] = toupper(name[i]);
		}
		i++;
	}
}
