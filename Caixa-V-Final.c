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
        char nomeArquivo[500];
        int codigoArquivo;

        // Lê os dados da linha do arquivo
        sscanf(linha, "%s %d", nomeArquivo, &codigoArquivo);
        // Verifica se o nome ou o código já existem
        if (!strcmp(nomeArquivo, nome)) {
            fclose(arquivo);
            return 1;
        }
        if (codigoArquivo == codigo) {
            fclose(arquivo);
            return 2; // O codigo do produto já existe
        }
        
    }

    fclose(arquivo);
    return 0; // Produto não existe
}

void registrarProduto() {
    printf("Opcao 1 selecionada: Registrar Produto\n");
    produto *novoProduto = (produto *)malloc(sizeof(produto));
    FILE *arquivo = fopen("produtos.txt", "a+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    char linha[600];
    printf("======================\n");
    printf("#PRODUTO: #CODIGO: #VALOR: #ESTOQUE:\n");
    while(fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }
    printf("======================\n");
    if (novoProduto == NULL) {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }

    // Solicita ao usuário os dados do produto
    printf("Informe o nome do produto (digite 0 para cancelar): ");
    // Alocar dinamicamente o tamanho da string do nome
    novoProduto->nome = (char *)malloc(501 * sizeof(char));
    if (novoProduto->nome == NULL) {
        printf("Erro na alocacao de memoria para o nome.\n");
        exit(1);
    }

    scanf("\n%s", novoProduto->nome);
    if (!strcmp(novoProduto->nome, "0")) return;

    printf("Informe o codigo do produto: ");
    scanf("%d", &novoProduto->codigo);
    if (novoProduto->codigo == 0) return;
    
    if (verificarProdutoExistente(novoProduto->nome, novoProduto->codigo) == 1) {
        printf("Produto com o mesmo nome ja existe. Registro cancelado.\n");
        free(novoProduto->nome);
        free(novoProduto);
        fclose(arquivo);
        registrarProduto();
    // Verifica se o produto já existe
    } else if (verificarProdutoExistente(novoProduto->nome, novoProduto->codigo) == 2) {
        printf("Produto com o mesmo codigo ja existe. Registro cancelado.\n");
        free(novoProduto->nome);
        free(novoProduto);
        fclose(arquivo);
        registrarProduto();
    } else {

        printf("Informe o preco do produto: ");
        scanf("%lf", &novoProduto->preco);

        printf("Informe a quantidade em estoque: ");
        scanf("%d", &novoProduto->quantidade);

        // Salva os dados do novo produto no arquivo
        fprintf(arquivo, "%s %d %.2lf %d\n", novoProduto->nome, novoProduto->codigo, novoProduto->preco, novoProduto->quantidade);

        // Fecha o arquivo
        fclose(arquivo);

        printf("Produto registrado com sucesso!\n");
        return;
    }
        
}

void alterarEstoque() {
    printf("Opcao 2 selecionada: Alterar Estoque\n");
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char linha[600];

    printf("======================\n");
    printf("#PRODUTO: #CODIGO: #VALOR: #ESTOQUE:\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }
    printf("======================\n");

    fclose(arquivo);

    int codigo;
    int novaQuantidade;

    printf("Informe o codigo do produto (digite 0 para cancelar): ");
    scanf("%d", &codigo);
    if (codigo == 0) {
        return;
    }

    // Abre o arquivo para leitura e cria um arquivo temporário
    FILE *tempArquivo = fopen("temp_produtos.txt", "w");
    arquivo = fopen("produtos.txt", "r");
    if (tempArquivo == NULL || arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int produtoEncontrado = 0;

    // Leitura em cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nome[501];
        int codigoArquivo;
        double preco;
        int quantidade;

        sscanf(linha, "%s %d %lf %d", nome, &codigoArquivo, &preco, &quantidade);
        if (codigoArquivo == codigo) {
            printf("Informe a nova quantidade em estoque: ");
            scanf("%d", &novaQuantidade);
            quantidade = novaQuantidade;
            produtoEncontrado = 1;
        }

        // Escreve a linha no arquivo temporário
        fprintf(tempArquivo, "%s %d %.2lf %d\n", nome, codigoArquivo, preco, quantidade);
    }

    fclose(arquivo);
    fclose(tempArquivo);

    if (produtoEncontrado) {
        printf("Estoque alterado com sucesso!\n");
        // Remove o arquivo antigo e renomeia o temporário
        remove("produtos.txt");
        rename("temp_produtos.txt", "produtos.txt");
    } else {
        printf("Produto nao encontrado.\n");
        remove("temp_produtos.txt");
        return;
    }
}

void excluirRegistro() {
    int codigo, linha = 0, aux, linha_temp = 0, tem = 0;
    printf("Opcao 3 selecionada: Excluir Registro\n");

    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char buffer[100];

    // listagem dos produtos
    printf("======================\n");
    printf("#PRODUTO: #CODIGO: #VALOR: #ESTOQUE:\n");
    while(fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        printf("%s", buffer);
    }
    printf("======================\n");

    fclose(arquivo);

    printf("Digite o codigo do produto para excluir o registro (digite 0 para cancelar):\n");
    scanf("%i", &codigo);
    if (!codigo) return;
    
    // procurar produto
    fopen("produtos.txt", "r");
    while(!feof(arquivo)){
        linha++;
        fscanf(arquivo, "%s", buffer);
        aux = atoi(buffer);
        if((aux == codigo)){
            tem = 1;
            linha--;
            linha /= 4;
            break;
        }
    }

    if(!tem){
        printf("Produto nao encontrado!\n");
        return;
    }

    fclose(arquivo);
    fopen("produtos.txt", "r");

    char remover[100];
    while(!feof(arquivo)){
        fgets(buffer, 100, arquivo);
        if(linha_temp == linha){
            strcpy(remover, buffer);
        }
        linha_temp++;
    }
    fclose(arquivo);

    fopen("produtos.txt", "r");
    FILE *tmp = fopen("temp.txt", "a+");
    while(!feof(arquivo)){
        fgets(buffer, 100, arquivo);
        // printf("%s", buffer);
        if(feof(arquivo)) break;
        if(strcmp(buffer, remover)){
            fprintf(tmp, "%s", buffer);
        }

    }
    fclose(arquivo);
    fclose(tmp);

    // Remove o arquivo antigo e renomeia o temporário
    remove("produtos.txt");
    rename("temp.txt", "produtos.txt");

    printf("Produto Removido!\n");
}

void processarVenda() {
    printf("Opcao 4 selecionada: Processar Venda\n");
    double saldo = 0;
    while (1) {
        FILE *arquivo = fopen("produtos.txt", "r");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            exit(1);
        }
        char linha[600];

        printf("======================\n");
        printf("#PRODUTO: #CODIGO: #VALOR: #ESTOQUE:\n");
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            printf("%s", linha);
        }
        printf("======================\n");

        fclose(arquivo);

        int codigo;
        int novaQuantidade;

        printf("Informe o codigo do produto (digite 0 para finalizar): ");
        scanf("%d", &codigo);
        if (codigo == 0) {
            break;
        }

        // Abre o arquivo para leitura e cria um arquivo temporário
        FILE *tempArquivo = fopen("temp_produtos.txt", "w");
        arquivo = fopen("produtos.txt", "r");
        if (tempArquivo == NULL || arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            exit(1);
        }

        int produtoEncontrado = 0;

        // Leitura em cada linha do arquivo
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            char nome[501];
            int codigoArquivo;
            double preco;
            int quantidade;

            sscanf(linha, "%s %d %lf %d", nome, &codigoArquivo, &preco, &quantidade);
            if (codigoArquivo == codigo) {
                printf("Informe quantas unidades seram compradas: ");
                scanf("%d", &novaQuantidade);
                quantidade -= novaQuantidade;
                saldo += novaQuantidade * preco;
                produtoEncontrado = 1;
            }

            // Escreve a linha no arquivo temporário
            fprintf(tempArquivo, "%s %d %.2lf %d\n", nome, codigoArquivo, preco, quantidade);
        }

        fclose(arquivo);
        fclose(tempArquivo);

        if (produtoEncontrado) {
            printf("Estoque alterado com sucesso!\n");
            // Remove o arquivo antigo e renomeia o temporário
            remove("produtos.txt");
            rename("temp_produtos.txt", "produtos.txt");
        } else {
            printf("Produto nao encontrado.\n");
            remove("temp_produtos.txt");
            break;
        }
    }
    char extra[1];
    printf("Valor total (enter para continuar): %.2lf\n", saldo);
    scanf("\n %[^\n]*s", extra);
    return;
}

produto* buscarProdutoPorCodigo(int codigo) {
    FILE *arquivo = fopen("produtos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    char linha[600];

    // Leitura em cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char nome[501];
        int codigoArquivo;
        double preco;
        int quantidade;

        sscanf(linha, "%s %d %lf %d", nome, &codigoArquivo, &preco, &quantidade);

        if (codigoArquivo == codigo) {
            // Produto encontrado, aloca memória e preenche os dados
            produto* encontrado = (produto*)malloc(sizeof(produto));
            encontrado->nome = strdup(nome);
            encontrado->codigo = codigoArquivo;
            encontrado->preco = preco;
            encontrado->quantidade = quantidade;

            fclose(arquivo);
            return encontrado;
        }
    }

    fclose(arquivo);
    return NULL; // Produto não encontrado
}

void instrucoes() {
	printf("Com esse programa voce pode registrar seus produtos, controlar seu estoque e realizar vendas\n");
	printf("O nome do produto nao permite espaco, use '-';\n");
	printf("O tamanho maximo do nome e de 99 caracteres;\n");
	printf("O arquivo maximo permitido e de 599 linhas;\n");
	printf("Para o codigo utilize apenas numeros;\n");
	printf("Para acresentar casas decimais ao preco utiliza '.';\n");
	}

int main() {

    int menu;

    do {
        printf("SELECIONE O QUE GOSTARIA DE FAZER:\n");
        printf("(1) - REGISTRAR PRODUTO\n");
        printf("(2) - ALTERAR ESTOQUE\n");
        printf("(3) - EXCLUIR REGISTRO\n");
        printf("(4) - PROCESSAR VENDA\n");
        printf("(5) - BUSCAR PRODUTO\n");
        printf("(6) - INSTRUCOES\n");
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
            case 5:
    			{
        		int codigoBusca;
     		   printf("Informe o codigo do produto a ser buscado: ");
     		   scanf("%d", &codigoBusca);

     		   produto* produtoEncontrado = buscarProdutoPorCodigo(codigoBusca);

      			if (produtoEncontrado != NULL) {
            		printf("Produto encontrado:\n");
            		printf("Nome: %s\n", produtoEncontrado->nome);
            		printf("Codigo: %d\n", produtoEncontrado->codigo);
            		printf("Preco: %.2lf\n", produtoEncontrado->preco);
            		printf("Quantidade em estoque: %d\n", produtoEncontrado->quantidade);
            		free(produtoEncontrado->nome);
            		free(produtoEncontrado);
        		} else {
            		printf("Produto nao encontrado.\n");
        		}
    			}
				break;
			case 6:
				instrucoes();
				printf("\n");
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
