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

void atualizarItem(Cardapio *cardapio, int *quantidadeItens)
{
  char nomeAtualizar[20];
  getchar();
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

  Cardapio *cardapio = (Cardapio *)malloc(capacidadeCardapio * sizeof(Cardapio));
  if (cardapio == NULL)
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