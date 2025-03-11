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
    printf("Digite seu nome: ");
    fflush(stdin);
    fgets(pedir[*quantipedidos].cliente, sizeof(pedir[*quantipedidos].cliente), stdin);
    pedir[*quantipedidos].cliente[strcspn(pedir[*quantipedidos].cliente, "\n")] = '\0';

    pedir[*quantipedidos].id = *quantipedidos + 1;
    pedir[*quantipedidos].quantidadeItens = 0;
    pedir[*quantipedidos].totalpagar = 0.0;

    pedir[*quantipedidos].itens = (Cardapio *)malloc(maximo * sizeof(Cardapio));
    pedir[*quantipedidos].quantidades = (int *)malloc(maximo * sizeof(int));

    if (pedir[*quantipedidos].itens == NULL || pedir[*quantipedidos].quantidades == NULL)
    {
        printf("Erro ao alocar memória para os itens do pedido.\n");
        return;
    }

    char additem[50];
    int quantidade;

    while (1)
    {
        printf("Cardápio:\n");
        for (int i = 0; i < qitens; i++)
            printf("- %s (R$ %.2f)\n", itenscardapio[i].nome, itenscardapio[i].preco);
        printf("Digite o NOME do item (ou 'sair' para finalizar): ");
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
                if (scanf("%d", &quantidade) != 1 || quantidade <= 0)
                {
                    printf("Quantidade inválida. Tente novamente.\n");
                    while (getchar() != '\n')
                        ;
                }
                getchar();

                int itemposi = pedir[*quantipedidos].quantidadeItens;
                pedir[*quantipedidos].itens[itemposi] = itenscardapio[i];
                pedir[*quantipedidos].quantidades[itemposi] = quantidade;
                pedir[*quantipedidos].quantidadeItens++;

                pedir[*quantipedidos].totalpagar = pedir[*quantipedidos].totalpagar + itenscardapio[i].preco * quantidade;

                printf("Item adicionado!\n");
                encontrado = 1;
                break;
            }
        }
        if (!encontrado)
            printf("Item não encontrado. Tente novamente.\n");
    }
    printf("Selecione o status do pedido, digitando o NÚMERO correspondente:\n");
    printf("1 - Pendente\n2 - Em preparo\n3 - Pronto\n4 - Entregue\n");
    int escolha;
    scanf("%d", &escolha);
    getchar();
    Pedido *novoPedido = &pedir[*quantipedidos];
    switch (escolha)
    {
    case 1:
        novoPedido->status = PENDENTE;
        break;
    case 2:
        novoPedido->status = EM_PREPARO;
        break;
    case 3:
        novoPedido->status = PRONTO;
        break;
    case 4:
        novoPedido->status = ENTREGUE;
        break;
    default:
        printf("Opção inválida! Definindo como Pendente.\n");
        novoPedido->status = PENDENTE;
    }

    printf("Pedido cadastrado! Total: R$ %.2f\n", pedir[*quantipedidos].totalpagar);

    (*quantipedidos)++;
}

void removerPedido(Pedido *pedidos, int *quantidadePedidos)
{
    if (*quantidadePedidos == 0)
    {
        printf("Não há pedidos para remover.\n");
        return;
    }

    int idRemover;
    int encontrado = 0;

    do
    {
        printf("Digite o ID do pedido que deseja remover: ");
        scanf("%d", &idRemover);
        getchar();
        int encontrado = 0;

        for (int i = 0; i < *quantidadePedidos; i++)
        {
            if (pedidos[i].id == idRemover)
            {
                encontrado = 1;

                free(pedidos[i].itens);
                free(pedidos[i].quantidades);

                for (int j = i; j < *quantidadePedidos - 1; j++)
                {
                    pedidos[j] = pedidos[j + 1];
                    pedidos[j].id = j + 1;
                }

                (*quantidadePedidos)--;
                printf("Pedido removido com sucesso!\n");
                return;
            }
        }

        if (!encontrado)
        {
            printf("Pedido com ID %d não encontrado! Digite um Id válido\n", idRemover);
        }
    } while (!encontrado);
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
    printf("Você adicionou %s ao cardápio!\n", item->nome);
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
    printf("Digite o NOME do item que deseja remover: ");
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
    printf("Digite o NOME do item que deseja atualizar: ");
    fgets(nomeAtualizar, sizeof(nomeAtualizar), stdin);
    nomeAtualizar[strcspn(nomeAtualizar, "\n")] = '\0';
    int encontrado = 0;
    for (int i = 0; i < *quantidadeItens; i++)
    {
        if (strcmp(cardapio[i].nome, nomeAtualizar) == 0)
        {
            encontrado = 1;
            printf("Item encontrado! Digite o NÚMERO correspondente a categoria que deseja alterar?\n");
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
    printf("Item atualizado!\n");
}

void mostrarPedidos(Pedido *pedido, int quantidadePedidos)
{
    if (quantidadePedidos == 0)
    {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }

    for (int i = 0; i < quantidadePedidos; i++)
    {
        printf("Pedido ID: %d\n", pedido[i].id);
        printf("Cliente: %s\n", pedido[i].cliente);
        printf("Status: ");
        switch (pedido[i].status)
        {
        case PENDENTE:
            printf("Pendente\n");
            break;
        case EM_PREPARO:
            printf("Em Preparo\n");
            break;
        case PRONTO:
            printf("Pronto\n");
            break;
        case ENTREGUE:
            printf("Entregue\n");
            break;
        }
        printf("Itens do Pedido:\n");
        for (int j = 0; j < pedido[i].quantidadeItens; j++)
        {
            printf("%d x %s (R$ %.2f)\n", pedido[i].quantidades[j], pedido[i].itens[j].nome, pedido[i].itens[j].preco);
        }
        printf("Total a pagar: R$ %.2f\n", pedido[i].totalpagar);
    }
}

void atualizarPedido(Pedido *pedidos, int quantidadePedidos, Cardapio *cardapio, int quantidadeItens)
{
    if (quantidadePedidos == 0)
    {
        printf("Nenhum pedido registrado para atualizar.\n");
        return;
    }

    printf("Selecione o pedido que deseja atualizar:\n");
    for (int i = 0; i < quantidadePedidos; i++)
    {
        printf("%d - Pedido ID: %d, Cliente: %s, Status: ", i + 1, pedidos[i].id, pedidos[i].cliente);
        switch (pedidos[i].status)
        {
        case PENDENTE:
            printf("Pendente\n");
            break;
        case EM_PREPARO:
            printf("Em preparo\n");
            break;
        case PRONTO:
            printf("Pronto\n");
            break;
        case ENTREGUE:
            printf("Entregue\n");
            break;
        }
    }

    int idPedido;
    printf("Digite o ID do pedido que deseja atualizar: ");
    scanf("%d", &idPedido);
    getchar();

    if (idPedido < 1 || idPedido > quantidadePedidos)
    {
        printf("Pedido não encontrado.\n");
        return;
    }

    Pedido *pedidoSelecionado = &pedidos[idPedido - 1];

    int opcao;
    printf("O que deseja alterar?\n");
    printf("1 - Status\n");
    printf("2 - Alterar itens no pedido\n");
    printf("3 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao)
    {
    case 1:
        printf("Selecione o novo status para o pedido:\n");
        printf("1 - Pendente\n");
        printf("2 - Em preparo\n");
        printf("3 - Pronto\n");
        printf("4 - Entregue\n");
        int novoStatus;
        scanf("%d", &novoStatus);
        getchar();

        switch (novoStatus)
        {
        case 1:
            pedidoSelecionado->status = PENDENTE;
            break;
        case 2:
            pedidoSelecionado->status = EM_PREPARO;
            break;
        case 3:
            pedidoSelecionado->status = PRONTO;
            break;
        case 4:
            pedidoSelecionado->status = ENTREGUE;
            break;
        default:
            printf("Opção inválida, status não alterado.\n");
            break;
        }
        break;

    case 2:
        printf("1 - Adicionar item ao pedido\n");
        printf("2 - Remover item do pedido\n");
        printf("3 - Alterar quantidade de item\n");
        int alteracaoItens;
        scanf("%d", &alteracaoItens);
        getchar();

        switch (alteracaoItens)
        {
        case 1:
        {
            char nomeItem[50];
            printf("Digite o nome do item que deseja adicionar: ");
            fgets(nomeItem, sizeof(nomeItem), stdin);
            nomeItem[strcspn(nomeItem, "\n")] = '\0';

            int encontrado = 0;
            for (int i = 0; i < quantidadeItens; i++)
            {
                if (strcmp(nomeItem, cardapio[i].nome) == 0)
                {
                    printf("Quantos deste item você deseja adicionar? ");
                    int qtd;
                    scanf("%d", &qtd);
                    getchar();
                    int posicao = pedidoSelecionado->quantidadeItens;
                    pedidoSelecionado->itens[posicao] = cardapio[i];
                    pedidoSelecionado->quantidades[posicao] = qtd;
                    pedidoSelecionado->quantidadeItens++;
                    pedidoSelecionado->totalpagar += cardapio[i].preco * qtd;
                    printf("Item adicionado ao pedido!\n");
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado)
            {
                printf("Item não encontrado no cardápio.\n");
            }
            break;
        }

        case 2:
        {
            char nomeRemover[50];
            printf("Digite o nome do item que deseja remover: ");
            fgets(nomeRemover, sizeof(nomeRemover), stdin);
            nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

            int encontrado = 0;
            for (int i = 0; i < pedidoSelecionado->quantidadeItens; i++)
            {
                if (strcmp(pedidoSelecionado->itens[i].nome, nomeRemover) == 0)
                {
                    pedidoSelecionado->totalpagar -= pedidoSelecionado->itens[i].preco * pedidoSelecionado->quantidades[i];
                    for (int j = i; j < pedidoSelecionado->quantidadeItens - 1; j++)
                    {
                        pedidoSelecionado->itens[j] = pedidoSelecionado->itens[j + 1];
                        pedidoSelecionado->quantidades[j] = pedidoSelecionado->quantidades[j + 1];
                    }
                    pedidoSelecionado->quantidadeItens--;
                    printf("Item removido do pedido!\n");
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado)
            {
                printf("Item não encontrado no pedido.\n");
            }
            break;
        }

        case 3:
        {
            char nomeAlterar[50];
            printf("Digite o NOME do item que deseja alterar a quantidade: ");
            fgets(nomeAlterar, sizeof(nomeAlterar), stdin);
            nomeAlterar[strcspn(nomeAlterar, "\n")] = '\0';

            int encontrado = 0;
            for (int i = 0; i < pedidoSelecionado->quantidadeItens; i++)
            {
                if (strcmp(pedidoSelecionado->itens[i].nome, nomeAlterar) == 0)
                {
                    printf("Digite a nova quantidade: ");
                    int novaQuantidade;
                    scanf("%d", &novaQuantidade);
                    getchar();

                    if (novaQuantidade > 0)
                    {
                        pedidoSelecionado->totalpagar -= pedidoSelecionado->itens[i].preco * pedidoSelecionado->quantidades[i];
                        pedidoSelecionado->quantidades[i] = novaQuantidade;
                        pedidoSelecionado->totalpagar += pedidoSelecionado->itens[i].preco * novaQuantidade;
                        printf("Quantidade alterada!\n");
                    }
                    else
                    {
                        printf("Quantidade inválida.\n");
                    }
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado)
            {
                printf("Item não encontrado no pedido.\n");
            }
            break;
        }

        default:
            printf("Opção inválida.\n");
            break;
        }
        break;

    case 3:
        printf("Saindo da atualização de pedido.\n");
        break;

    default:
        printf("Opção inválida.\n");
        break;
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
                mostrarPedidos(pedido, quantidadePedidos);
                break;
            case 3:
                removerPedido(pedido, &quantidadePedidos);
                break;
            case 4:
                atualizarPedido(pedido, quantidadePedidos, cardapio, quantidadeItens);
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
    free(pedido);
    return 0;
}
