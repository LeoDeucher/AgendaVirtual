#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <stdbool.h>
#include <windows.h>


//Funcoes
void inserir(void);
void lista(void);
void apagar(void);
void apagarPorLinha(void);
void consulta(void);

struct ficha_telefonica
{
    char nome[50];
    char telefone[10];
};

struct ficha_telefonica listaContatos[100]; 
int totalContatos = 0; 


int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    //variavel que vai ser usada pra selecionar a opcao no menu
    char opcao;

    //Switch do menu de opcoes usando do-while
    do
    {
        system("cls");
        printf(" _______Menu__de__Opcoes_______\n");
        printf("[1] - Inserir contato          \n");
        printf("[2] - Lista de contatos        \n");
        printf("[3] - Apagar contatos          \n");
        printf("[4] - Apagar contato por linha \n");
        printf("[5] - Consultar contato        \n");
        printf("[6] - Sair                     \n");
        printf(" Selecione a opcao:");
        scanf("%c", &opcao);
        fflush(stdin);

        switch (opcao)
        {
        case '1':
            inserir();
        break;
        
        case '2':
            lista();
        break;
        
        case '3':
            apagar();
        break;
        
        case '4':
            apagarPorLinha();
        break;
        
        case '5':
            consulta();
        break;
        
        case '6':
            printf("Saindo...");
        break;
        
        default:
            system("cls");      
            printf("Opcao invalida \n(pressione Enter para continuar)");
            getch();
        break;
        }
    } while (opcao != '6');

    return 0;
}

//Funcao salvar contato
void inserir(void)
{
    FILE *arquivo;
    arquivo = fopen("nomes.txt", "a");
    struct ficha_telefonica novoContato;
    system("cls");
    
    printf("Digite um nome: ");
    fflush(stdin);
    gets(novoContato.nome);
    
    printf("Digite seu telefone: ");
    fflush(stdin);
    gets(novoContato.telefone);
    
    fprintf(arquivo, "Nome: %s | Numero de Telefone: %s\n", novoContato.nome, novoContato.telefone);
    fclose(arquivo);
    
    printf("Contato adicionado \n(pressione Enter para continuar)");
    getch();
}

//Funcao exibir lista de contato
void lista(void)
{
    FILE *arquivo;
    arquivo = fopen("nomes.txt", "r");
    char texto[100];

    system("cls");
    while (fgets(texto, sizeof(texto), arquivo))
    {
        printf("%s", texto);
    }

    fclose(arquivo);
    printf("\n Pressione Enter para continuar");
    getch();
}


//Funcao deletar contato
void apagar(void)
{
    FILE *arquivo;
    arquivo = fopen("nomes.txt", "w");
    fclose(arquivo);
    
    system("cls");
    printf("Contato deletado \n(pressione Enter para continuar)");
    getch();
}

//Funcao deletar contato 2
void apagarPorLinha(void)
{
    FILE *arquivo;
    FILE *temp;
    arquivo = fopen("nomes.txt", "r");
    temp = fopen("temp.txt", "w");
    char texto[100];
    int linha, cont = 1;
    bool encontrado = false;

    system("cls");
    printf("Digite o numero da linha do contato que deseja deletar: ");
    scanf("%d", &linha);

    while (fgets(texto, sizeof(texto), arquivo))
    {
        if (cont != linha)
        {
            fprintf(temp, "%s", texto);
        }
        else
        {
            encontrado = true;
        }
        cont++;
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado)
    {
        remove("nomes.txt");
        rename("temp.txt", "nomes.txt");
        printf("Contato apagado com sucesso \n(pressione Enter para continuar)");
    }
    else
    {
        remove("temp.txt");
        printf("Linha invalida selecionada \n (pressione Enter para continuar)");
    }
    getch();
}

void consulta(void)
{
    FILE *arquivo;
    arquivo = fopen("nomes.txt", "r");
    char nomeProcurado[50], texto[100];
    int cont = 1;
    bool encontrado = false;

    system("cls");
    printf("Digite o nome do contato que deseja consultar: ");
    fflush(stdin);
    gets(nomeProcurado);

    while (fgets(texto, sizeof(texto), arquivo))
    {
        if (strstr(texto, nomeProcurado) != NULL)
        {
            encontrado = true;
            printf("%i - %s", cont, texto);
        }
        cont++;
    }

    fclose(arquivo);

    if (!encontrado)
    {
        printf("Contato '%s' nao foi encontrado.\n(pressione Enter para continuar)", nomeProcurado);
    }
    getch();
}