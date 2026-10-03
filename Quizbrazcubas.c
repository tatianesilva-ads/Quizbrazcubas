#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 

#define ARQUIVO "quizbrazcubas.csv"
#define TAM_TEXTO 250
#define TAM_CAT 50
#define TAM_CURSO 10
#define TAM_RESP 10

// Estrutura que representa a pergunta
typedef struct {
    int id;
    char texto[TAM_TEXTO];
    char categoria[TAM_CAT];
    char curso[TAM_CURSO];
    char resposta[TAM_RESP];
} Pergunta;

// ========================================================
// FUN합ES AUXILIARES DE VALIDA플O
// ========================================================

void validarCurso(char *curso) {
    do {
        printf("Curso (CC, ES ou ADS): ");
        scanf(" %9[^\n]", curso);
        if (strcmp(curso, "CC") != 0 && strcmp(curso, "ES") != 0 && strcmp(curso, "ADS") != 0) {
            printf("[ERRO] Curso invalido! Digite apenas CC, ES ou ADS.\n");
        }
    } while (strcmp(curso, "CC") != 0 && strcmp(curso, "ES") != 0 && strcmp(curso, "ADS") != 0);
}

void validarResposta(char *resposta) {
    do {
        printf("Resposta (SIM ou NAO): ");
        scanf(" %9[^\n]", resposta);
        if (strcmp(resposta, "SIM") != 0 && strcmp(resposta, "NAO") != 0) {
            printf("[ERRO] Resposta invalida! Digite apenas SIM ou NAO.\n");
        }
    } while (strcmp(resposta, "SIM") != 0 && strcmp(resposta, "NAO") != 0);
}

// ========================================================
// SUB-ROTINAS DO SISTEMA (CRUD)
// ========================================================

// 1. Cadastrar Pergunta
void cadastrarPergunta() {
    Pergunta p;
    FILE *f = fopen(ARQUIVO, "a");

    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    printf("Codigo (ID int): ");
    scanf("%d", &p.id);
    
    // Consome o \n (Enter) que sobrou no teclado apos ler o inteiro
    // Usa apenas stdio.h (padrao do material)
    getchar();

    printf("Pergunta: ");
    scanf(" %249[^\n]", p.texto);

    printf("Categoria: ");
    scanf(" %49[^\n]", p.categoria);

    validarCurso(p.curso);
    validarResposta(p.resposta);

    // Grava no arquivo CSV separado por ';'
    fprintf(f, "%d;%s;%s;%s;%s\n", p.id, p.texto, p.categoria, p.curso, p.resposta);
    fclose(f);

    printf("\nPergunta cadastrada com sucesso!\n");
}

// 2. Listar todas as Perguntas
void listarPerguntas() {
    Pergunta p;
    char linha[500];
    int total = 0;

    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Nenhuma pergunta cadastrada ou arquivo nao encontrado.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), f) != NULL) {
        char *id_str = strtok(linha, ";");
        char *texto = strtok(NULL, ";");
        char *categoria = strtok(NULL, ";");
        char *curso = strtok(NULL, ";");
        char *resposta = strtok(NULL, ";\n\r");

        if (id_str && texto && categoria && curso && resposta) {
            p.id = atoi(id_str);
            strcpy(p.texto, texto);
            strcpy(p.categoria, categoria);
            strcpy(p.curso, curso);
            strcpy(p.resposta, resposta);

            printf("\n[%d] %s\n", p.id, p.texto);
            printf("    Categoria: %s | Curso: %s | Resposta: %s\n", p.categoria, p.curso, p.resposta);
            total++;
        }
    }

    fclose(f);

    if (total == 0) {
        printf("Nenhuma pergunta encontrada.\n");
    } else {
        printf("\nTotal de perguntas: %d\n", total);
    }
}

// 3. Consultar por Categoria
void consultarPorCategoria() {
    char categoriaBusca[TAM_CAT];
    char linha[500];
    int encontradas = 0;

    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Arquivo nao encontrado ou sem perguntas cadastradas.\n");
        return;
    }

    printf("Digite a categoria desejada: ");
    scanf(" %49[^\n]", categoriaBusca);

    printf("\nPerguntas encontradas na categoria '%s':\n", categoriaBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        char *id_str = strtok(linha, ";");
        char *texto = strtok(NULL, ";");
        char *categoria = strtok(NULL, ";");
        char *curso = strtok(NULL, ";");
        char *resposta = strtok(NULL, ";\n\r");

        if (id_str && texto && categoria && curso && resposta) {
            if (strcmp(categoria, categoriaBusca) == 0) {
                printf("[%s] %s\n", id_str, texto);
                printf("    Curso: %s | Resposta: %s\n\n", curso, resposta);
                encontradas++;
            }
        }
    }

    fclose(f);

    if (encontradas == 0) {
        printf("Nenhuma pergunta encontrada para a categoria informada.\n");
    }
}

// 4. Consultar por Curso
void consultarPorCurso() {
    char cursoBusca[TAM_CURSO];
    char linha[500];
    int encontradas = 0;

    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("Arquivo nao encontrado ou sem perguntas cadastradas.\n");
        return;
    }

    validarCurso(cursoBusca);

    printf("\nPerguntas relacionadas ao curso %s:\n", cursoBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        char *id_str = strtok(linha, ";");
        char *texto = strtok(NULL, ";");
        char *categoria = strtok(NULL, ";");
        char *curso = strtok(NULL, ";");
        char *resposta = strtok(NULL, ";\n\r");

        if (id_str && texto && categoria && curso && resposta) {
            if (strcmp(curso, cursoBusca) == 0) {
                printf("[%s] %s (Categoria: %s) -> Resposta: %s\n", id_str, texto, categoria, resposta);
                encontradas++;
            }
        }
    }

    fclose(f);

    if (encontradas == 0) {
        printf("Nenhuma pergunta encontrada para o curso informado.\n");
    }
}

// 5. Atualizar Pergunta
void atualizarPergunta() {
    FILE *f = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.csv", "w");
    char linha[500];
    int idBusca, encontrou = 0;

    if (f == NULL) {
        printf("Arquivo nao encontrado.\n");
        if (temp) fclose(temp);
        return;
    }
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(f);
        return;
    }

    printf("Digite o codigo (ID) da pergunta que deseja atualizar: ");
    scanf("%d", &idBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        char copia[500];
        strcpy(copia, linha);

        char *id_str = strtok(copia, ";");
        
        if (id_str && atoi(id_str) == idBusca) {
            encontrou = 1;
            Pergunta p;
            p.id = idBusca;

            printf("\n--- Novas Informacoes ---\n");
            printf("Novo texto: ");
            scanf(" %249[^\n]", p.texto);

            printf("Nova categoria: ");
            scanf(" %49[^\n]", p.categoria);

            validarCurso(p.curso);
            validarResposta(p.resposta);

            fprintf(temp, "%d;%s;%s;%s;%s\n", p.id, p.texto, p.categoria, p.curso, p.resposta);
        } else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.csv", ARQUIVO);

    if (encontrou) {
        printf("\nPergunta atualizada com sucesso!\n");
    } else {
        printf("\nPergunta com codigo %d nao encontrada.\n", idBusca);
    }
}

// 6. Excluir Pergunta
void excluirPergunta() {
    FILE *f = fopen(ARQUIVO, "r");
    FILE *temp = fopen("temp.csv", "w");
    char linha[500];
    int idBusca, encontrou = 0;

    if (f == NULL) {
        printf("Arquivo nao encontrado.\n");
        if (temp) fclose(temp);
        return;
    }
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(f);
        return;
    }

    printf("Digite o codigo (ID) da pergunta que deseja excluir: ");
    scanf("%d", &idBusca);

    while (fgets(linha, sizeof(linha), f) != NULL) {
        char copia[500];
        strcpy(copia, linha);

        char *id_str = strtok(copia, ";");

        if (id_str && atoi(id_str) == idBusca) {
            encontrou = 1;
        } else {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(f);
    fclose(temp);

    remove(ARQUIVO);
    rename("temp.csv", ARQUIVO);

    if (encontrou) {
        printf("\nPergunta excluida com sucesso!\n");
    } else {
        printf("\nPergunta com codigo %d nao encontrada.\n", idBusca);
    }
}

// ========================================================
// FUN플O PRINCIPAL (MENU DE OP합ES)
// ========================================================

int main() {
    int op;
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    do {
        system("cls");
        printf("=========================================\n");
        printf("   GERENCIADOR DE PERGUNTAS QUIZ DE TI   \n");
        printf("=========================================\n");
        printf("1 - Cadastrar pergunta\n");
        printf("2 - Listar todas as perguntas\n");
        printf("3 - Consultar perguntas por categoria\n");
        printf("4 - Consultar perguntas por curso\n");
        printf("5 - Atualizar pergunta\n");
        printf("6 - Excluir pergunta\n");
        printf("0 - Sair\n");
        printf("=========================================\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &op) != 1) {
            while (getchar() != '\n');
            op = -1;
        }

        switch (op) {
            case 1:
                printf("\n--- CADASTRAR PERGUNTA ---\n");
                cadastrarPergunta();
                break;
            case 2:
                printf("\n--- LISTA DE PERGUNTAS ---\n");
                listarPerguntas();
                break;
            case 3:
                printf("\n--- CONSULTAR POR CATEGORIA ---\n");
                consultarPorCategoria();
                break;
            case 4:
                printf("\n--- CONSULTAR POR CURSO ---\n");
                consultarPorCurso();
                break;
            case 5:
                printf("\n--- ATUALIZAR PERGUNTA ---\n");
                atualizarPergunta();
                break;
            case 6:
                printf("\n--- EXCLUIR PERGUNTA ---\n");
                excluirPergunta();
                break;
            case 0:
                printf("\nSaindo do programa... Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        if (op != 0) {
            system("pause");
        }

    } while (op != 0);

    return 0;
}
