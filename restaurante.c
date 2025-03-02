#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>

//cadastro de cardápio
typedef enum{ENTRADA,PRINCIPAL,SOBREMESA,BEBIDA}Categoria;
typedef struct{
char nome[20];
float preco;
char descricao[100];
Categoria categ;
}cardapio;

void cadastrar(cardapio *p){
    printf("Digite o nome do prato\n");
    fgets(p->nome,sizeof(p->nome),stdin);
    p->nome[strcspn(p->nome,"\n")] = '\0';
    printf("Qual a descrição do cardápio\n");
    fgets(p->descricao,sizeof(p->descricao),stdin);
    p->descricao[strcspn(p->descricao,"\n")] = '\0';
    char categoria[20];
    printf("Informe a categoria do prato\nEntrada\nPrincipal\nSobremesa\nBebida\n");
    while(strcmp(categoria,"Entrada")!=0 && strcmp(categoria,"Principal")!=0 &&
    strcmp(categoria,"Sobremesa")!=0 && strcmp(categoria,"Bebida")!=0){
   printf("Opção inválida, digite uma das opções acima\n");
        fgets(categoria,sizeof(categoria),stdin);
    categoria[strcspn(categoria,"\n")]='\0';
    }
    if(strcmp(categoria,"Entrada")==0){
        p->categ = ENTRADA;
    }
    else if(strcmp(categoria,"Principal")==0){
        p->categ = PRINCIPAL;
    }
    else if(strcmp(categoria,"Sobremesa")==0){
        p->categ = SOBREMESA;
    }
    else if(strcmp(categoria,"Bebida")==0){
        p->categ = BEBIDA;
    }
    printf("Digite o preço do pedido\n");
    scanf("%f",&p->preco);
}
void mostrar(cardapio *p1){
    printf("%s\n",p1->nome);
    printf("%s\n",p1->descricao);
    switch(p1->categ){
        case PRINCIPAL: 
        printf("Principal\n"); break;
        case ENTRADA:
        printf("Entrada\n");break;
        case SOBREMESA:
        printf("Sobremesa\n");break;
        case BEBIDA:
        printf("Bebida\n");break;
    }
    printf("%.2f\n",p1->preco);
}

int main(){
    setlocale(LC_ALL,"portuguese");
    cardapio *ptr = (cardapio *)malloc(sizeof(cardapio));
    if(ptr == NULL){
        printf("Erro ao alocar memória\n");
        exit(1);
    }
cadastrar(ptr);
mostrar(ptr);
free(ptr); 
   
   
    return 0;
}