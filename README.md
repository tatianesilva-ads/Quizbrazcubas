# 🎓 Sistema de Gerenciamento de Perguntas para Quiz de TI

> Projeto prático desenvolvido em Linguagem C para gerenciamento e organização do banco de perguntas de orientação acadêmica para cursos da área de Tecnologia da Informação (Ciência da Computação, Engenharia de Software e ADS).

---

## 👥 Integrantes do Grupo
* **Turma:** [ADS 1º Semestre; CC 2º Semestre]
* **Curso:** [Algoritmos & Pensamento Computacional]
* **Integrantes:**
  1. [Heloiza Kaneda de Souza Santos] 
  2. [Leonardo Wilson de Oliveira]
  3. [Maria Alice Ferreira Gonzaga]
  4. [Tatiane Gonçalves da Silva] 
 

---

## 📌 Sobre o Projeto
O sistema tem como objetivo principal permitir o cadastro, a listagem, a consulta, a atualização e a exclusão (CRUD) de perguntas que compõem o banco de dados do Quiz.

Todas as informações são armazenadas de forma persistente em um arquivo no formato **CSV** (`quizbrazcubas.csv`), garantindo que os dados permaneçam salvos mesmo após o encerramento da aplicação.

### 🚀 Funcionalidades
- **1. Cadastrar Pergunta:** Permite inserir uma nova pergunta validando o código, texto, categoria, curso (`CC`, `ES` ou `ADS`) e a resposta (`SIM` ou `NAO`).
- **2. Listar todas as Perguntas:** Exibe todos os registros salvos no arquivo CSV.
- **3. Consultar por Categoria:** Filtra e exibe somente as perguntas pertencentes a uma categoria específica.
- **4. Consultar por Curso:** Lista as perguntas filtradas pelo curso informado (`CC`, `ES` ou `ADS`).
- **5. Atualizar Pergunta:** Permite editar os dados de uma pergunta existente buscando pelo seu código ID.
- **6. Excluir Pergunta:** Remove um registro do arquivo mantendo os demais salvos através de um arquivo temporário.

---

## 🛠️ Tecnologias e Conceitos Utilizados
- **Linguagem:** C
- **Ambiente de Desenvolvimento:** Dev-C++ 
- **Estruturas de Dados:** `struct`, arrays de caracteres (strings).
- **Manipulação de Arquivos:** `fopen`, `fclose`, `fprintf`, `fgets`.
- **Parsing e Manipulação de Strings:** `strtok`, `strcpy`, `strcmp`, `atoi`.
- **Validação e Controle:** Loops de repetição (`do-while`), estruturas condicionais (`switch-case`, `if-else`).
- **Codificação de Arquivo:** UTF-8 (`SetConsoleOutputCP(65001)`).

---

## 📂 Estrutura do Repositório
```text
.
├── main.c              # Código-fonte principal do sistema em C
├── quizbrazcubas.csv   # Base de dados com as perguntas cadastradas
└── README.md           # Documentação do projeto
```

## 🛠️ Instruções para Compilação e Execução

### Pré-requisitos
- Ter o **Dev-C++** instalado (ou qualquer compilador C como o **GCC/MinGW**).
- O arquivo de banco de dados `quizbrazcubas.csv` deve estar **obrigatoriamente na mesma pasta** onde o código `main.c` for executado.

---

### Opção 1: Executando via Dev-C++ (Recomendado)

1. Abra o **Dev-C++**.
2. Vá em **Arquivo > Abrir Arquivo/Projeto...** (ou pressione `Ctrl + O`) e selecione o arquivo `main.c`.
3. Garanta que o arquivo `quizbrazcubas.csv` está na mesma pasta do `main.c`.
4. Pressione a tecla **F11** no teclado (ou vá no menu superior em **Executar > Compilar e Executar**).
5. O terminal do programa abrirá automaticamente com o menu interativo do Quiz de TI.

---

## Link do YouTube ▶️: https://youtu.be/GvepLCO5WXE
