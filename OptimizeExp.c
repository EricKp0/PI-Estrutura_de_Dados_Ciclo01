#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    int id;
    char nome[50];
    float preco;
    int estoque;
    int vendas;
    struct Produto* proximo;  
} Produto;

Produto* criarProduto(int id, char nome[], float preco, int estoque) {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    novoProduto->id = id;
    strcpy(novoProduto->nome, nome);
    novoProduto->preco = preco;
    novoProduto->estoque = estoque;
    novoProduto->vendas = 0;
    novoProduto->proximo = NULL;
    return novoProduto;
}

void adicionarProduto(Produto** lista, Produto* novoProduto) {
    if (*lista == NULL) {
        *lista = novoProduto;
    } else {
        Produto* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoProduto;
    }
}

void registrarVenda(Produto* lista, int id, int quantidade) {
    Produto* atual = lista;
    while (atual != NULL) {
        if (atual->id == id) {
            if (atual->estoque >= quantidade) {
                atual->estoque -= quantidade;
                atual->vendas += quantidade;
                printf("Venda registrada: %d unidades de %s\n", quantidade, atual->nome);
            } else {
                printf("Estoque insuficiente para %s\n", atual->nome);
            }
            return;
        }
        atual = atual->proximo;
    }
    printf("Produto nao encontrado.\n");
}

void exibirRelatorio(Produto* lista) {
    Produto* atual = lista;
    float totalLucro = 0;
    printf("Relatorio de produtos:\n");
    printf("ID | Nome         | Preco | Estoque | Vendas | Lucro\n");
    printf("------------------------------------------------------\n");
    while (atual != NULL) {
        float lucro = atual->vendas * atual->preco;
        totalLucro += lucro;
        printf("%d  | %-12s | %.2f | %7d | %6d | %.2f\n", atual->id, atual->nome, atual->preco, atual->estoque, atual->vendas, lucro);
        atual = atual->proximo;
    }
    printf("------------------------------------------------------\n");
    printf("Lucro total: %.2f\n", totalLucro);
}

void liberarMemoria(Produto* lista) {
    Produto* atual = lista;
    while (atual != NULL) {
        Produto* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

int main() {
    Produto* listaProdutos = NULL;
    
    adicionarProduto(&listaProdutos, criarProduto(1, "Produto A", 10.5, 100));
    adicionarProduto(&listaProdutos, criarProduto(2, "Produto B", 15.0, 50));
    adicionarProduto(&listaProdutos, criarProduto(3, "Produto C", 20.0, 30));
    
    registrarVenda(listaProdutos, 1, 10);
    registrarVenda(listaProdutos, 2, 5);
    registrarVenda(listaProdutos, 3, 3);
    
    exibirRelatorio(listaProdutos);
    
    liberarMemoria(listaProdutos);
    
    return 0;
}

