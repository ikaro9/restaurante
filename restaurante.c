#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define tamanhoinicio 100
#define maximo 1000

typedef enum
{
    ENTRADA,
    PRINCIPAL,
    SOBREMESA,
    BEBIDA
} Categoria;

typedef enum
{
    PENDENTE,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;

typedef struct
{
    char nome[20];
    float preco;
    char descricao[100];
    Categoria categ;
} Cardapio;

typedef struct
{
    int id;
    char cliente[50];
    Cardapio *itens;
    int quantidadeItens;
    StatusPedido status;
    float totalpagar;
    int *quantidades;
} Pedido;

Cardapio *expandirmemoriaitens(Cardapio *itens_Antigos, int *quantidade_Itens, int *capacidade_Itens)
{
    int novacapacidade = (*capacidade_Itens) * 2;
    Cardapio *novositens = (Cardapio *)malloc(novacapacidade * sizeof(Cardapio));
    if (novositens == NULL)
    {
        printf("Erro ao alocar memória\n");
        return itens_Antigos;
    }
    int i;
    for (i = 0; i < *quantidade_Itens; i++)
    {
        novositens[i] = itens_Antigos[i];
    }
    free(itens_Antigos);
    *capacidade_Itens = novacapacidade;
    return novositens;
}

void cadastrarpedidos(Pedido *pedir, int *quantipedidos, Cardapio *itenscardapio, int qitens)
{
    
    printf("Digite o seu nome:\n");
    getchar(); 
    fgets(pedir[*quantipedidos].cliente, sizeof(pedir[*quantipedidos].cliente), stdin);
    pedir[*quantipedidos].cliente[strcspn(pedir[*quantipedidos].cliente, "\n")] = '\0';

    pedir[*quantipedidos].id = *quantipedidos + 1;
    pedir[*quantipedidos].quantidadeItens = 0;
    pedir[*quantipedidos].totalpagar = 0.0;

    pedir[*quantipedidos].itens = (Cardapio *)malloc(maximo * sizeof(Cardapio));
    pedir[*quantipedidos].quantidades = (int *)malloc(maximo * sizeof(int));

  
    if (pedir[*quantipedidos].itens == NULL || pedir[*quantipedidos].quantidades == NULL) {
        printf("Erro ao alocar memória para os itens do pedido.\n");
        return;
    }

    char additem[50];
    int quantidade;
    
    while (1)
    {
        printf("Cardápio:\n");
        for (int i = 0; i < qitens; i++)
        printf("%d - %s (R$ %.2f)\n", i + 1, itenscardapio[i].nome, itenscardapio[i].preco);
        printf("Digite o nome do item (ou 'sair' para finalizar): ");
        fgets(additem, sizeof(additem), stdin);
        additem[strcspn(additem, "\n")] = '\0';

        if (strcmp(additem, "sair") == 0) 
        break;

        int encontrado = 0;
        for (int i = 0; i < qitens; i++)
        {
            if (strcmp(additem, itenscardapio[i].nome) == 0)
            {
                
                printf("Quantidade: ");
                if (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
                    printf("Quantidade inválida. Tente novamente.\n");
                    while (getchar() != '\n'); 
                }
                   getchar();

          
                int itemposi = pedir[*quantipedidos].quantidadeItens;
                pedir[*quantipedidos].itens[itemposi] = itenscardapio[i]; 
                pedir[*quantipedidos].quantidades[itemposi] = quantidade; 
                pedir[*quantipedidos].quantidadeItens++;

                pedir[*quantipedidos].totalpagar =   pedir[*quantipedidos].totalpagar +itenscardapio[i].preco * quantidade;

                printf("Item adicionado!\n");
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) printf("Item não encontrado. Tente novamente.\n");
    }
    printf("\nPedido cadastrado! Total: R$ %.2f\n", pedir[*quantipedidos].totalpagar);
    (*quantipedidos)++;
}



Pedido *expandirMemoriaPedido(Pedido *pedidoAntigo, int *capacidadePedidos)
{
    int novaCapacidade = (*capacidadePedidos) * 2;
    Pedido *novo = (Pedido *)malloc(novaCapacidade * sizeof(Pedido));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória para pedidos.\n");
        return pedidoAntigo;
    }
    for (int i = 0; i < *capacidadePedidos; i++)
    {
        novo[i] = pedidoAntigo[i];
    }
    free(pedidoAntigo);
    *capacidadePedidos = novaCapacidade;
    return novo;
}
Cardapio *expandirMemoriaCardapio(Cardapio *cardapioAntigo, int *capacidade)
{
    int novaCapacidade = (*capacidade) * 2;
    Cardapio *novo = (Cardapio *)malloc(novaCapacidade * sizeof(Cardapio));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return cardapioAntigo;
    }
    for (int i = 0; i < *capacidade; i++)
    {
        strcpy(novo[i].nome, cardapioAntigo[i].nome);
        strcpy(novo[i].descricao, cardapioAntigo[i].descricao);
        novo[i].categ = cardapioAntigo[i].categ;
        novo[i].preco = cardapioAntigo[i].preco;
    }
    free(cardapioAntigo);
    *capacidade = novaCapacidade;
    return novo;
}

void cadastrarItem(Cardapio *item)
{
    printf("Digite o nome do prato: ");
    fgets(item->nome, sizeof(item->nome), stdin);
    item->nome[strcspn(item->nome, "\n")] = '\0';
    printf("Informe a descrição do prato: ");
    fgets(item->descricao, sizeof(item->descricao), stdin);
    item->descricao[strcspn(item->descricao, "\n")] = '\0';
    printf("Informe a categoria do prato (entrada, principal, sobremesa, bebida): ");
    char categoria[20];
    while (1)
    {
        fgets(categoria, sizeof(categoria), stdin);
        categoria[strcspn(categoria, "\n")] = '\0';
        if (strcmp(categoria, "entrada") == 0)
        {
            item->categ = ENTRADA;
            break;
        }
        else if (strcmp(categoria, "principal") == 0)
        {
            item->categ = PRINCIPAL;
            break;
        }
        else if (strcmp(categoria, "sobremesa") == 0)
        {
            item->categ = SOBREMESA;
            break;
        }
        else if (strcmp(categoria, "bebida") == 0)
        {
            item->categ = BEBIDA;
            break;
        }
        else
        {
            printf("Opção inválida, digite uma das opções acima: ");
        }
    }
    printf("Digite o preço do pedido: ");
    scanf("%f", &item->preco);
}

void mostrarCardapio(Cardapio *cardapio, int quantidadeItens)
{
    if (quantidadeItens == 0)
    {
        printf("Ainda não há itens no cardápio.\n");
        return;
    }
    for (int i = 0; i < quantidadeItens; i++)
    {
        printf("Nome: %s\n", cardapio[i].nome);
        printf("Descrição: %s\n", cardapio[i].descricao);
        printf("Categoria: ");
        switch (cardapio[i].categ)
        {
        case PRINCIPAL:
            printf("Principal\n");
            break;
        case ENTRADA:
            printf("Entrada\n");
            break;
        case SOBREMESA:
            printf("Sobremesa\n");
            break;
        case BEBIDA:
            printf("Bebida\n");
            break;
        }
        printf("Preço: R$ %.2f\n", cardapio[i].preco);
    }
}

void removerItem(Cardapio *cardapio, int *quantidadeItens)
{
    char nomeRemover[20];
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';
    int encontrado = 0;
    for (int i = 0; i < *quantidadeItens; i++)
    {
        if (strcmp(cardapio[i].nome, nomeRemover) == 0)
        {
            encontrado = 1;
            for (int j = i; j < *quantidadeItens - 1; j++)
            {
                cardapio[j] = cardapio[j + 1];
            }
            (*quantidadeItens)--;
            printf("Item removido com sucesso.\n");
            break;
        }
    }
    if (!encontrado)
    {
        printf("Item não encontrado.\n");
    }
}

void atualizarItem(Cardapio *cardapio, int *quantidadeItens)
{
    char nomeAtualizar[20];
    printf("Digite o nome do item que deseja atualizar: ");
    fgets(nomeAtualizar, sizeof(nomeAtualizar), stdin);
    nomeAtualizar[strcspn(nomeAtualizar, "\n")] = '\0';
    int encontrado = 0;
    for (int i = 0; i < *quantidadeItens; i++)
    {
        if (strcmp(cardapio[i].nome, nomeAtualizar) == 0)
        {
            encontrado = 1;
            printf("Item encontrado! O que deseja alterar?\n");
            printf("1 - Nome\n2 - Descrição\n3 - Categoria\n4 - Preço\n");
            int opcao;
            scanf("%d", &opcao);
            getchar();
            switch (opcao)
            {
            case 1:
                printf("Informe o novo nome: ");
                fgets(cardapio[i].nome, sizeof(cardapio[i].nome), stdin);
                cardapio[i].nome[strcspn(cardapio[i].nome, "\n")] = '\0';
                break;
            case 2:
                printf("Informe a nova descrição: ");
                fgets(cardapio[i].descricao, sizeof(cardapio[i].descricao), stdin);
                cardapio[i].descricao[strcspn(cardapio[i].descricao, "\n")] = '\0';
                break;
            case 3:
                printf("Informe a nova categoria (entrada, principal, sobremesa, bebida): ");
                char categoria[20];
                while (1)
                {
                    fgets(categoria, sizeof(categoria), stdin);
                    categoria[strcspn(categoria, "\n")] = '\0';
                    if (strcmp(categoria, "entrada") == 0)
                    {
                        cardapio[i].categ = ENTRADA;
                        break;
                    }
                    else if (strcmp(categoria, "principal") == 0)
                    {
                        cardapio[i].categ = PRINCIPAL;
                        break;
                    }
                    else if (strcmp(categoria, "sobremesa") == 0)
                    {
                        cardapio[i].categ = SOBREMESA;
                        break;
                    }
                    else if (strcmp(categoria, "bebida") == 0)
                    {
                        cardapio[i].categ = BEBIDA;
                        break;
                    }
                    else
                    {
                        printf("Opção inválida, digite uma das opções acima: ");
                    }
                }
                break;
            case 4:
                printf("Informe o novo preço: ");
                scanf("%f", &cardapio[i].preco);
                break;
            default:
                printf("Opção inválida.\n");
            }
            break;
        }
    }
    if (!encontrado)
    {
        printf("Item não encontrado.\n");
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    int quantidadeItens = 0;
    int capacidadeCardapio = tamanhoinicio;
    int p;
    int quantidadePedidos = 0;
    int capacidadePedidos = tamanhoinicio;
    Cardapio *cardapio = (Cardapio *)malloc(capacidadeCardapio * sizeof(Cardapio));
    if (cardapio == NULL)
    {
        printf("Erro ao alocar memória\n");
        return 1;
    }
    Pedido *pedido = (Pedido *)malloc(capacidadePedidos * sizeof(Pedido));
    if (pedido == NULL)
    {
        printf("Erro ao alocar memória\n");
        return 1;
    }
    printf("Olá, esse é o sistema de gerenciamento do seu restaurante!\nDigite:\n");
    while (1)
    {
        printf("1 - Gerenciar cardápio\n");
        printf("2 - Gerenciar pedidos\n");
        printf("3 - Sair\n");
        scanf("%d", &p);
        getchar();
        if (p == 1)
        {
            do
            {
                printf("INFORME O QUE QUER FAZER?\n");
                printf("1 - Adicionar item\n");
                printf("2 - Mostrar cardápio\n");
                printf("3 - Remover item\n");
                printf("4 - Atualizar item\n");
                printf("5 - Sair\n");
                scanf("%d", &opcao);
                getchar();
                switch (opcao)
                {
                case 1:
                    if (quantidadeItens == capacidadeCardapio)
                    {
                        cardapio = expandirMemoriaCardapio(cardapio, &capacidadeCardapio);
                    }
                    cadastrarItem(&cardapio[quantidadeItens]);
                    quantidadeItens++;
                    break;
                case 2:
                    mostrarCardapio(cardapio, quantidadeItens);
                    break;
                case 3:
                    removerItem(cardapio, &quantidadeItens);
                    break;
                case 4:
                    atualizarItem(cardapio, &quantidadeItens);
                    break;
                }
            } while (opcao != 5);
        }
        else if (p == 2)
        {
            printf("INFORME O QUE QUER FAZER?\n");
            printf("1 - Criar pedidos\n");
            printf("2 - Mostrar meus pedidos\n");
            printf("3 - Remover pedidos\n");
            printf("4 - Atualizar pedidos\n");
            printf("5 - Sair\n");
            int seila;
            scanf("%d", &seila);
            getchar();
            switch (seila)
            {
            case 1:
                if (quantidadePedidos == capacidadePedidos)
                {
                    pedido = expandirMemoriaPedido(pedido, &capacidadePedidos);
                }
                cadastrarpedidos(pedido, &quantidadePedidos, cardapio, quantidadeItens);
                break;
            case 2:
                // função de mostrar os pedidos
                break;
            case 3:
                // função de remover os pedidos
                break;
            case 4:
                // função de alterar os pedidos
                break;
            }
        }
        else if (p == 3)
        {
            break;
        }
        else
        {
            printf("Opção inválida! Digite uma das opções acima\n");
        }
    }

    free(cardapio);
    return 0;
}