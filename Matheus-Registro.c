#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nome;
    int codigo;
    double preco;
    int quantidade;
} produto;

int verificarProdutoExistente(const char *nome, int codigo) {
    // Abre o arquivo para leitura
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        return 0; // Assume que o produto não existe se o arquivo não puder ser aberto
    }

    char linha[600]; // Ajuste o tamanho conforme necessário

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomeArquivo[501];
        int codigoArquivo;

        // Lê os dados da linha do arquivo
        if (sscanf(linha, "%[^\n] %d", nomeArquivo, &codigoArquivo) == 2) {
            // Verifica se o nome ou o código já existem
            if (strcmp(nomeArquivo, nome) == 0 || codigoArquivo == codigo) {
                fclose(arquivo);
                return 1; // Produto já existe
            }
        }
    }

    fclose(arquivo);
    return 0; // Produto não existe
}

void registrarProduto() {
    printf("Opcao 1 selecionada: Registrar Produto\n");

    produto *novoProduto = (produto *)malloc(sizeof(produto));

    if (novoProduto == NULL) {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }

    // Alocar dinamicamente o tamanho da string do nome
    novoProduto->nome = (char *)malloc(500 * sizeof(char));
    if (novoProduto->nome == NULL) {
        printf("Erro na alocacao de memoria para o nome.\n");
        exit(1);
    }

    // Solicita ao usuário os dados do produto
    printf("Informe o nome do produto: ");
	scanf("%[^\n]%*c", novoProduto->nome);

    printf("Informe o codigo do produto: ");
    scanf("%d", &novoProduto->codigo);

    // Verifica se o produto já existe
    if (verificarProdutoExistente(novoProduto->nome, novoProduto->codigo)) {
        printf("Produto com o mesmo nome ou codigo ja existe. Registro cancelado.\n");
        free(novoProduto->nome);
        free(novoProduto);
        return;
    }

    printf("Informe o preco do produto: ");
    scanf("%lf", &novoProduto->preco);

    printf("Informe a quantidade em estoque: ");
    scanf("%d", &novoProduto->quantidade);

    // Abre o arquivo para adicionar um novo produto
    FILE *arquivo = fopen("produtos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Salva os dados do novo produto no arquivo
    fprintf(arquivo, "%s %d %.2lf %d\n", novoProduto->nome, novoProduto->codigo, novoProduto->preco, novoProduto->quantidade);

    // Fecha o arquivo
    fclose(arquivo);

    // Libera a memória alocada dinamicamente
    free(novoProduto->nome);
    free(novoProduto);

    printf("Produto registrado com sucesso!\n");
}

/*#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *nome;
    int codigo;
    double preco;
    int quantidade;
} produto;

int verificarProdutoExistente(const char *nome, int codigo) {
    // Abre o arquivo para leitura
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        return 0; // Assume que o produto não existe se o arquivo não puder ser aberto
    }

    char linha[600]; // Ajuste o tamanho conforme necessário

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nomeArquivo[501];
        int codigoArquivo;

        // Lê os dados da linha do arquivo
        if (sscanf(linha, "%499s %d", nomeArquivo, &codigoArquivo) == 2) {
            // Verifica se o nome ou o código já existem
            if (strcmp(nomeArquivo, nome) == 0 || codigoArquivo == codigo) {
                fclose(arquivo);
                return 1; // Produto já existe
            }
        }
    }

    fclose(arquivo);
    return 0; // Produto não existe
}

void registrarProduto() {
    printf("Opcao 1 selecionada: Registrar Produto\n");

    produto *novoProduto = (produto *)malloc(sizeof(produto));

    if (novoProduto == NULL) {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }

    // Solicita ao usuário os dados do produto
    printf("Informe o nome do produto: ");

    // Alocar dinamicamente o tamanho da string do nome
    novoProduto->nome = (char *)malloc(501 * sizeof(char));
    if (novoProduto->nome == NULL) {
        printf("Erro na alocacao de memoria para o nome.\n");
        exit(1);
    }

    scanf("%[^\n]%*c", novoProduto->nome);

    printf("Informe o codigo do produto: ");
    scanf("%d", &novoProduto->codigo);
    
    // Verifica se o produto já existe
    if (verificarProdutoExistente(novoProduto->nome, novoProduto->codigo)) {
        printf("Produto com o mesmo nome ou codigo ja existe. Registro cancelado.\n");
        free(novoProduto->nome);
        free(novoProduto);
    }

    printf("Informe o preco do produto: ");
    scanf("%lf", &novoProduto->preco);

    printf("Informe a quantidade em estoque: ");
    scanf("%d", &novoProduto->quantidade);

    // Abre o arquivo para adicionar um novo produto
    FILE *arquivo = fopen("produtos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Salva os dados do novo produto no arquivo
    fprintf(arquivo, "%s %d %.2lf %d\n", novoProduto->nome, novoProduto->codigo, novoProduto->preco, novoProduto->quantidade);

    // Fecha o arquivo
    fclose(arquivo);

    printf("Produto registrado com sucesso!\n");
        
}*/

void alterarEstoque() {
    // Implemente a lógica para alterar o estoque aqui
    printf("Opcao 2 selecionada: Alterar Estoque\n");
    printf("AINDA NAO FUNCIONA");
}

void excluirRegistro() {
    // Implemente a lógica para excluir um registro aqui
    printf("Opcao 3 selecionada: Excluir Registro\n");
	printf("AINDA NAO FUNCIONA");
}

void processarVenda() {
    // Implemente a lógica para processar uma venda aqui
    printf("Opcao 4 selecionada: Processar Venda\n");
	printf("AINDA NAO FUNCIONA");
}

int main() {

    int menu;

    do {
        printf("SELECIONE O QUE GOSTARIA DE FAZER:\n");
        printf("(1) - REGISTRAR PRODUTO\n");
        printf("(2) - ALTERAR ESTOQUE\n");
        printf("(3) - EXCLUIR REGISTRO\n");
        printf("(4) - PROCESSAR VENDA\n");
        printf("(0) - SAIR\n");
        scanf("%d%*c", &menu);

        switch (menu) {
            case 1:
            	
                registrarProduto();
                break;
            case 2:
                alterarEstoque();
                break;
            case 3:
                excluirRegistro();
                break;
            case 4:
                processarVenda();
                break;
            case 0:
                printf("Saindo do programa... Volte sempre!\n");
                break;
            default:
                printf("Erro! Tente novamente.\n");
        }
    } while (menu != 0);

    return 0;
}
