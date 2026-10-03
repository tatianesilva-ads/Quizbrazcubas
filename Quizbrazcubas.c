#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "agenda.txt"
#define TAM 100

typedef struct{
	char nome[TAM];
	char telefone[20];
	char email[TAM];
} Contato;


void cadastrar() {
    Contato c;
    FILE *f = fopen(ARQUIVO, "a");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    
    printf("Digite o nome: ");
    scanf(" %99[^\n]", c.nome);		
    printf("Digite o telefone: ");
    scanf(" %19[^\n]", c.telefone);
    printf("Digite o email: ");
    scanf(" %99[^\n]", c.email);
    

    fprintf(f, "%s;%s;%s\n", c.nome, c.telefone, c.email);
    fclose(f);
    printf("Contato salvo com sucesso!\n");
}

void listar() {
    Contato c;
    int total = 0;
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("A agenda esta vazia.\n");
        return;
    }

    printf("\n--- CONTATOS ---\n");
    char linha[250];

    //fgets() lê uma linha do arquivo f e armazena em linha
    while (fgets(linha, 250, f) != NULL) {

	    strcpy(c.nome, strtok(linha, ";"));     //strtok() procura o primeiro ; e pega tudo que está antes dele. 
	    strcpy(c.telefone, strtok(NULL, ";"));  //aqui o strtok pega na mesma string no próximo trecho . O NULL permite isso
	    strcpy(c.email, strtok(NULL, ";\n"));

        printf("\nNome: %s\n", c.nome);
        printf("Telefone: %s\n", c.telefone);
        printf("Email: %s", c.email);
    }
    fclose(f);
}


void remover() {
    FILE *f = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.txt", "w");

    char linha[250];
    char nomeBusca[TAM];
    Contato c;
    int encontrou = 0;

    if (f == NULL) {
        printf("A agenda esta vazia.\n");
        return;
    }

    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(f);
        return;
    }

    printf("Digite o nome do contato que deseja remover: ");
    scanf(" %99[^\n]", nomeBusca);

    while (fgets(linha, 250, f) != NULL) {

        char copia[250];
        strcpy(copia, linha);

        strcpy(c.nome, strtok(copia, ";"));
        strcpy(c.telefone, strtok(NULL, ";"));
        strcpy(c.email, strtok(NULL, ";\n"));

        if (strcmp(c.nome, nomeBusca) == 0) {
            encontrou = 1;
        }
        else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.txt", ARQUIVO);

    if (encontrou == 1) {
        printf("Contato removido com sucesso!\n");
    }
    else {
        printf("Contato nao encontrado.\n");
    }
}

void atualizar() {
    FILE *f = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.txt", "w");

    char linha[250];
    char nomeBusca[TAM];
    Contato c;
    int encontrou = 0;

    if (f == NULL) {
        printf("A agenda esta vazia.\n");
        return;
    }

    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(f);
        return;
    }

    printf("Digite o nome do contato que deseja atualizar: ");
    scanf(" %99[^\n]", nomeBusca);

    while (fgets(linha, 250, f) != NULL) {

        char copia[250];
        strcpy(copia, linha);

        strcpy(c.nome, strtok(copia, ";"));
        strcpy(c.telefone, strtok(NULL, ";"));
        strcpy(c.email, strtok(NULL, ";\n"));

        if (strcmp(c.nome, nomeBusca) == 0) {

            encontrou = 1;

            printf("Digite o novo nome: ");
            scanf(" %99[^\n]", c.nome);

            printf("Digite o novo telefone: ");
            scanf(" %19[^\n]", c.telefone);

            printf("Digite o novo email: ");
            scanf(" %99[^\n]", c.email);

            fprintf(temp, "%s;%s;%s\n",
                    c.nome,
                    c.telefone,
                    c.email);
        }
        else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.txt", ARQUIVO);

    if (encontrou == 1) {
        printf("Contato atualizado com sucesso!\n");
    }
    else {
        printf("Contato nao encontrado.\n");
    }
}


int main(){
	
	int op;
	
	do{
	    system("cls");
		printf("\nAgenda");
		printf("\n1 - cadastrar contato");
		printf("\n2 - listar contato");
		printf("\n3 - deletar contato");
		printf("\n4 - atualizar contato");
		printf("\n0 - Sair");
		printf("\nEntre com a opcao desejada: ");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				printf("Cadastrar novo contato");
				cadastrar();
				break;
			case 2:
				printf("Listar um contato");
				listar();
				break;
			case 3:
				printf("Deletar um contato");
				remover();
				break;
			case 4: 
				printf("Atualizar um contato");
				atualizar();
				break;								
		}
		system("Pause");
	}
	while(op != 0);
	return 0;
}
