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
    if(qitens == 0){
        printf("Ainda não há itens no cardápio\n");
        return;
    }
    for (i = 0; i < qitens; i++)
    {
        printf("Nome: %s\n", p1[i].nome);
        printf("Descrição: %s\n", p1[i].descricao);
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


void removeritem(cardapio *menuremover, int *quantiDADE)
{

    char nomeremover[20];
    printf("Digite o nome do item que quer remover \n");
    getchar();
    fgets(nomeremover, sizeof(nomeremover), stdin);
    nomeremover[strcspn(nomeremover, "\n")] = '\0';
    int i;
    int encontrei = 0;
    for (i = 0; i < *quantiDADE; i++)
    {
        if (strcmp(menuremover[i].nome, nomeremover) == 0)
        {
            encontrei = 1;
            break;
        }
    }
    if (!encontrei)
    {
        printf("Item não encontrado\n");
        return;
    }
    int j;
    for (j = i; j < *quantiDADE - 1; j++)
    {
        menuremover[j] = menuremover[j + 1];
    }
    (*quantiDADE)--;
    printf("Item removido\n");
}

void atualizar_item(cardapio *atualizacao, int *quantidadE)
{
    getchar();
    printf("Digite o nome do item que irá atualizar\n");
    char nome_atualizar[20];
    fgets(nome_atualizar, sizeof(nome_atualizar), stdin);
    nome_atualizar[strcspn(nome_atualizar, "\n")] = '\0';
    int i;
    int encontrado = 0;
    for (i = 0; i < *quantidadE; i++)
    {
        if (strcmp(atualizacao[i].nome, nome_atualizar) == 0)
        {
            encontrado = 1;
            break;
        }
    }
    if (encontrado)
    {
        printf("Item encontrado! O que quer alterar?\n");
        {
            printf("1 - Nome\n2 - Descrição\n3 - Categoria\n4 - Preço\n");
            int a;
            scanf("%d", &a);
            getchar();
            switch (a)
            {
            case 1:
            printf("Informe o novo nome\n");   
            fgets(atualizacao[i].nome, sizeof(atualizacao[i].nome), stdin);
                atualizacao[i].nome[strcspn(atualizacao[i].nome, "\n")] = '\0';
                break;
            case 2:
            printf("Informe a nova descrição\n");   
            fgets(atualizacao[i].descricao, sizeof(atualizacao[i].descricao), stdin);
                atualizacao[i].descricao[strcspn(atualizacao[i].descricao, "\n")] = '\0';
                break;
            case 3:
                
                printf("Informe a nova categoria do prato\nEntrada\nPrincipal\nSobremesa\nBebida\n");
                char categoria[20];
                while (1)
                {
                    fgets(categoria, sizeof(categoria), stdin);
                    categoria[strcspn(categoria, "\n")] = '\0';

                    if (strcmp(categoria, "entrada") == 0)
                    {
                        atualizacao[i].categ = ENTRADA;
                        break;
                    }
                    else if (strcmp(categoria, "principal") == 0)
                    {
                        atualizacao[i].categ = PRINCIPAL;
                        break;
                    }
                    else if (strcmp(categoria, "sobremesa") == 0)
                    {
                        atualizacao[i].categ = SOBREMESA;
                        break;
                    }
                    else if (strcmp(categoria, "bebida") == 0)
                    {
                        atualizacao[i].categ = BEBIDA;
                        break;
                    }
                    else
                    {
                        printf("Opção inválida, digite uma das opções acima\n");
                    }
                }
                break;
            case 4:
                printf("Informe o novo preço do pedido\n");
                scanf("%f", &atualizacao[i].preco);
            }
        }  
}
else
{
    printf("Item não encontrado");
    return;
}
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
        printf("Digite 1 - Adicionar item\nDigite 2 - Mostrar cardapio\nDigite 3 - Remover item\nDigite 4 - Atualizar item\nDigite 5 - Sair\n");
        scanf("%d", &opcao);
        getchar();
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
            removeritem(menu, &quantidade);
            break;
        case 4:
        atualizar_item(menu,&quantidade);
        break;
        }
    } while (opcao != 5);
free(menu);
    return 0;
}