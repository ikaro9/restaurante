#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define tamanhoinicio 100

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
} Pedido;

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
  getchar();
  print("Digite o nome do pedido: ");
  fgets(item->nome, sizeof(item->nome), stdin);
  item->nome[strcspn(item->nome, "\n")] = '\0';
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
  printf("Digite o preço do pedido");
  scanf("%f", &item->preco);
}

void mostrarCardapio(Cardapio *cardapio, int quantidadeItens)
{
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
  getchar();
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

Pedido *criarPedido(int id, char *cliente, Cardapio *cardapio, int *quantidadeItens, int *quantidadePedidos, Pedido **pedidos)
{
  Pedido *novoPedido = (Pedido *)malloc(sizeof(Pedido));
  novoPedido->id = id;
  strcpy(novoPedido->cliente, cliente);
  novoPedido->itens = (Cardapio *)malloc(*quantidadeItens * sizeof(Cardapio));
  novoPedido->quantidadeItens = 0;
  novoPedido->status = PENDENTE;

  printf("Digite os itens do pedido (digite 'fim' para encerrar):\n");
  char nomeItem[20];
  while (1)
  {
    getchar();
    printf("Nome do item: ");
    fgets(nomeItem, sizeof(nomeItem), stdin);
    nomeItem[strcspn(nomeItem, "\n")] = '\0';
    if (strcmp(nomeItem, "fim") == 0)
    {
      break;
    }
    int encontrado = 0;
    for (int i = 0; i < *quantidadeItens; i++)
    {
      if (strcmp(cardapio[i].nome, nomeItem) == 0)
      {
        novoPedido->itens[novoPedido->quantidadeItens] = cardapio[i];
        novoPedido->quantidadeItens++;
        encontrado = 1;
        break;
      }
    }
    if (!encontrado)
    {
      printf("Item não encontrado no cardápio.\n");
    }
  }

  *pedidos = (Pedido *)realloc(*pedidos, (*quantidadePedidos + 1) * sizeof(Pedido));
  (*pedidos)[*quantidadePedidos] = *novoPedido;
  (*quantidadePedidos)++;

  return novoPedido;
}

void mostrarPedidos(Pedido *pedidos, int quantidadePedidos)
{
  for (int i = 0; i < quantidadePedidos; i++)
  {
    printf("Pedido ID: %d\n", pedidos[i].id);
    printf("Cliente: %s\n", pedidos[i].cliente);
    printf("Itens:\n");
    for (int j = 0; j < pedidos[i].quantidadeItens; j++)
    {
      printf("  - %s\n", pedidos[i].itens[j].nome);
    }
    printf("Status: ");
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
}

void atualizarStatusPedido(Pedido *pedidos, int quantidadePedidos)
{
  int id;
  printf("Digite o ID do pedido que deseja atualizar: ");
  scanf("%d", &id);
  for (int i = 0; i < quantidadePedidos; i++)
  {
    if (pedidos[i].id == id)
    {
      printf("Status atual: ");
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
      printf("Novo status (0-Pendente, 1-Em preparo, 2-Pronto, 3-Entregue): ");
      int novoStatus;
      scanf("%d", &novoStatus);
      pedidos[i].status = (StatusPedido)novoStatus;
      printf("Status atualizado com sucesso.\n");
      return;
    }
  }
  printf("Pedido não encontrado.\n");
}

int main()
{
  setlocale(LC_ALL, "Portuguese");
  int opcao;
  int quantidadeItens = 0;
  int capacidadeCardapio = tamanhoinicio;
  int quantidadePedidos = 0;
  Pedido *pedidos = NULL;

  Cardapio *cardapio = (Cardapio *)malloc(capacidadeCardapio * sizeof(Cardapio));
  if (cardapio == NULL)
  {
    printf("Erro ao alocar memória\n");
    return 1;
  }

  do
  {
    printf("\nMENU PRINCIPAL\n");
    printf("1 - Adicionar item ao cardápio\n");
    printf("2 - Mostrar cardápio\n");
    printf("3 - Remover item do cardápio\n");
    printf("4 - Criar pedido\n");
    printf("5 - Mostrar pedidos\n");
    printf("6 - Atualizar status do pedido\n");
    printf("7 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

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
    {
      char cliente[50];
      int id = quantidadePedidos + 1;
      getchar();
      printf("Digite o nome do cliente: ");
      fgets(cliente, sizeof(cliente), stdin);
      cliente[strcspn(cliente, "\n")] = '\0';
      criarPedido(id, cliente, cardapio, &quantidadeItens, &quantidadePedidos, &pedidos);
      break;
    }
    case 5:
      mostrarPedidos(pedidos, quantidadePedidos);
      break;
    case 6:
      atualizarStatusPedido(pedidos, quantidadePedidos);
      break;
    case 7:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida.\n");
    }
  } while (opcao != 7);

  free(cardapio);
  for (int i = 0; i < quantidadePedidos; i++)
  {
    free(pedidos[i].itens);
  }
  free(pedidos);

  return 0;
}