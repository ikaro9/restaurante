#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define tamanhoinicio 100

// cadastro de cardápio
typedef enum
{
    ENTRADA,
    PRINCIPAL,
    SOBREMESA,
    BEBIDA
} Categoria;
typedef struct
{
    char nome[20];
    float preco;
    char descricao[100];
    Categoria categ;
} cardapio;
cardapio *expandirmemoria(cardapio *cardapioantigo, int *capacidade)
{
    int novacapacidade = (*capacidade) * 2;
    cardapio *novo = (cardapio *)malloc(novacapacidade * sizeof(cardapio));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória\n");
        return cardapioantigo;
    }
    int i;
    for (i = 0; i < *capacidade; i++)
    {
        strcpy(novo[i].nome, cardapioantigo[i].nome);
        strcpy(novo[i].descricao, cardapioantigo[i].descricao);
        novo[i].categ = cardapioantigo[i].categ;
        novo[i].preco = cardapioantigo[i].preco;
    }
    free(cardapioantigo);
    *capacidade = novacapacidade;
    return novo;
}

void cadastrar(cardapio *p)
{
    getchar();
    printf("Digite o nome do prato\n");
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = '\0';
    printf("Qual a descrição do cardápio\n");
    fgets(p->descricao, sizeof(p->descricao), stdin);
    p->descricao[strcspn(p->descricao, "\n")] = '\0';
    char categoria[20];
    printf("Informe a categoria do prato\nEntrada\nPrincipal\nSobremesa\nBebida\n");

    while (1)
    {
        fgets(categoria, sizeof(categoria), stdin);
        categoria[strcspn(categoria, "\n")] = '\0';

        if (strcmp(categoria, "entrada") == 0)
        {
            p->categ = ENTRADA;
            break;
        }
        else if (strcmp(categoria, "principal") == 0)
        {
            p->categ = PRINCIPAL;
            break;
        }
        else if (strcmp(categoria, "sobremesa") == 0)
        {
            p->categ = SOBREMESA;
            break;
        }
        else if (strcmp(categoria, "bebida") == 0)
        {
            p->categ = BEBIDA;
            break;
        }
        else
        {
            printf("Opção inválida, digite uma das opções acima\n");
        }
    }
    printf("Digite o preço do pedido\n");
    scanf("%f", &p->preco);
}
void mostrar(cardapio *p1, int qitens)
{
    int i;
    for (i = 0; i < qitens; i++)
    {
        printf("Nome: %s\n", p1[i].nome);
        printf("Descrição %s\n", p1[i].descricao);
        printf("Categoria: ");
        switch (p1[i].categ)
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
        printf("Preço: R$ %.2f\n", p1[i].preco);
    }
}

void removeritem(cardapio *menuremover,int *quantiDADE){
    
    char nomeremover[20];
    getchar();
    printf("Digite o nome do item que quer remover \n");
    fgets(nomeremover,sizeof(nomeremover),stdin);
    nomeremover[strcspn(nomeremover,"\n")]='\0';
    int i;
    int encontrei=0;
    for(i=0;i<*quantiDADE;i++){
    if(strcmp(menuremover[i].nome,nomeremover) == 0){
        encontrei=1;
        break;
    }
  }  
  if(!encontrei){
    printf("Item não encontrado\n");
    return;
  }
int j;
  for(j=i;j<*quantiDADE-1;i++){
    menuremover[j]=menuremover[j+1];
  }
  (*quantiDADE)--;
  printf("Item removido\n");
}

int main()
{
    setlocale(LC_ALL, "portuguese");
    int opcao;
    int quantidade = 0;
    int capacidadeatual = tamanhoinicio;

    cardapio *menu = (cardapio *)malloc(capacidadeatual * sizeof(cardapio));
    if (menu == NULL)
    {
        printf("Erro ao alocar memória\n");
        return 1;
    }
    do
    {
        printf("INFORME O QUE QUER  FAZER ?\n");
        printf("Digite 1 - Adicionar item\nDigite 2 - Mostrar cardapio\nDigite 3 - Remover item\nDigite  4 - Atualizar item\nDigite 5 - Sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            if (quantidade == capacidadeatual)
            {
                menu = expandirmemoria(menu, &capacidadeatual);
            }
            cadastrar(&menu[quantidade]);
            quantidade++;
            break;
        case 2:
            mostrar(menu, quantidade);
            break;
        
        case 3:
        removeritem(menu,&quantidade);
        break;
        }
    } while (opcao != 5);
    free(menu);
    return 0;
}

