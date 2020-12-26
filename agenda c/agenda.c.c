#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>

struct Scontato
{
    char nome[50];
    char numero[20];
    char email[50];
    bool indisponivel;
} typedef contato;

void novoContato(int numero, contato registros[], int tamanho);
int excluirContato(contato registros[], int tamanho);
void editarContato(contato registros[], int tamanho);
void listarContatos(contato registros[], int tamanho);
int sair(contato registros[], int tamanho);
void inicio(contato registros[], int tamanho);
int menu(contato registros[], int tamanho);
void mensagem(char mensagem[], int tamanho);
int tamanhoString(char mensagem[]);
void buscaString(contato registros[], char nomeBusca[], int tamanhoString, int tamanho);
void backup(contato registros[], int tamanho);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    contato *registros;
    int tamanho = 0;
	registros = (contato*)malloc((tamanho + 1) * sizeof(contato));
	
	FILE *arqagenda = fopen("agenda.dat", "rb");
	  if (arqagenda == NULL){
	     fclose(arqagenda);
	     arqagenda = fopen("agenda.dat", "wb+");
	     fclose(arqagenda);
	     arqagenda = fopen("agenda.dat", "rb");
	  }
	  int result = 0;
	  	while(!feof(arqagenda)){
			result += fread(&registros[result], sizeof(contato),1,arqagenda);
			registros = (contato*) realloc(registros, (result+1) * sizeof (contato));	
		  }
		  
  	fclose(arqagenda);
	tamanho = result;
    inicio(registros, tamanho);
    return 0;
}
void inicio(contato registros[], int tamanho)
{
	
    int opcao;
    printf(" *********  *********  *********  ***      **  ********   *********\n");
    printf(" *********  *********  *********  ****     **  *********  *********\n");
    printf(" **     **  **         **         ** **    **  **     **  **     **\n");
    printf(" *********  **   ****  *******    **  **   **  **     **  *********\n");
    printf(" *********  **   ****  *******    **   **  **  **     **  *********\n");
    printf(" **     **  **     **  **         **    ** **  **     **  **     **\n");
    printf(" **     **  *********  *********  **     ****  *********  **     **\n");
    printf(" **     **  *********  *********  **      ***  ********   **     **\n\n");


    printf("Olá, sou sua agenda. Escolha uma dessas opções para continuar(ou não haha): \n\n");
    printf("1 - Menu / 2 - Encerrar\n");
    printf("Digite a opção desejada: ");
    scanf("%d", &opcao);


    switch(opcao)
    {
    case 1:
        system("cls");
        menu(registros, tamanho);
        break;
    case 2:
        printf("\nAté mais!!\n");
        exit(0);
    default:
        system("cls");
        printf("-- A OPÇÃO INSERIDA É INVÁLIDA, TENTE NOVAMENTE --\n\n");
        inicio(registros, tamanho);
    }

}
int menu(contato registros[], int tamanho)
{

    int opcao;

    char mensagemMenu[] = "****    Menu    ****";
    int tamanhoMensagem = tamanhoString(mensagemMenu);
    printf("\n");
    mensagem(mensagemMenu, tamanhoMensagem);
    printf("\n");
    printf("1 - Novo Contato\n");
    printf("2 - Excluir Contato\n");
    printf("3 - Editar Contato\n");
    printf("4 - Listar Contatos\n");
    printf("5 - Sair\n");
    printf("\nDigite a opção desejada: ");
    scanf("%i", &opcao);

    system("cls");

    switch(opcao)
    {
    case 1:
        novoContato(opcao, registros, tamanho);
        break;
    case 2:
        excluirContato(registros, tamanho);
        break;
    case 3:
        editarContato(registros, tamanho);
        break;
    case 4:
        listarContatos(registros, tamanho);
        break;
    case 5:
        sair(registros, tamanho);
        break;
    default:
        printf("-- A OPÇÃO INSERIDA É INVÁLIDA, TENTE NOVAMENTE --\n");
        menu(registros, tamanho);
        break;
    }


}

void novoContato(int numero, contato registros[], int tamanho)
{
    char mensagemSucesso[] = " Contato Incluído com Sucesso! ";
    char mensagemInicio[] = "**********   Incluir Contato   **********";
    int tamanhoMensagem = tamanhoString(mensagemInicio);
    mensagem(mensagemInicio, tamanhoMensagem);

    printf("Digite o Nome do contato: ");
    scanf("%s", registros[tamanho].nome);

    printf("Digite o Número do contato: ");
    scanf("%s", registros[tamanho].numero);

    printf("Digite o email do contato: ");
    scanf("%s", registros[tamanho].email);
    
    registros[tamanho].indisponivel = false;
    system("cls");

    tamanhoMensagem = tamanhoString(mensagemSucesso);
    mensagem(mensagemSucesso, tamanhoMensagem);
    
    tamanho++;
    registros = (contato*) realloc(registros, (tamanho + 1) * sizeof (contato));
    backup(registros, tamanho);
    menu(registros, tamanho);

}

int excluirContato(contato registros[], int tamanho){
	
    char mensagemInicio[] = "**********   Excluir Contato   **********";
    char divisao[] = "\n---------------------------------------------------------------------\n";
    char final[50] = "---------------------------------------";
    int tamanhoMensagem = tamanhoString(mensagemInicio);
    char nomeBusca[50];
    int tamanhoBusca, codigoContato, verificar;
    char mensagemSucesso[] = " Exclusão Realizada Com Sucesso! ";
    mensagem(mensagemInicio, tamanhoMensagem);

    printf("Digite pelo menos parte do nome do contato que deseja excluir: ");
    scanf("%s", nomeBusca);
    tamanhoBusca = tamanhoString(nomeBusca);
    buscaString(registros, nomeBusca, tamanhoBusca, tamanho);
    printf("%s", divisao);
    printf("Digite o CÓDIGO referente a o contato que deseja excluir: ");
    scanf("%d", &codigoContato);
    system("cls");

    printf("%s", divisao);
    printf(" %d. ", codigoContato);
    printf("Nome: %s | ", registros[codigoContato].nome);
    printf("Numero: %s | ", registros[codigoContato].numero);
    printf("Email: %s ", registros[codigoContato].email);
    printf("%s", divisao);

    printf("Deseja realmente excluir o contato *%s*? \n(sim: 1 | não: 0): ", registros[codigoContato].nome);
    scanf("%d", &verificar);
    switch(verificar)
    {
        case 0:
            system("cls");
            printf("%s", final);
            printf("\n      Exclusão Cancelada!     \n");
            printf("%s", final);
            break;
        case 1:
            registros[codigoContato].indisponivel = true;
            backup(registros, tamanho);
            system("cls");
            tamanhoMensagem = tamanhoString(mensagemSucesso);
            mensagem(mensagemSucesso, tamanhoMensagem);
            break;
        default:
            system("cls");
            printf("%s", final);
            printf("\n Opção inválida, contato não excluído!\n");
            printf("%s", final);
    }

    menu(registros, tamanho);
}

void editarContato(contato registros[], int tamanho)
{
    char mensagemInicio[] = "**********   Editar Contato   **********";
    char divisao[] = "\n-------------------------------------------------\n";
    int tamanhoMensagem = tamanhoString(mensagemInicio);
    char nomeBusca[50];
    int tamanhoBusca, codigoContato, verificar;
    char mensagemSucesso[] = " Alteração Concluída Com Sucesso! ";
    mensagem(mensagemInicio, tamanhoMensagem);

    printf("Digite pelo menos parte do nome do contato que deseja alterar: ");
    scanf("%s", nomeBusca);
    tamanhoBusca = tamanhoString(nomeBusca);
    buscaString(registros, nomeBusca, tamanhoBusca, tamanho);
    printf("%s", divisao);
    printf("Digite o CÓDIGO referente a o contato que deseja alterar: ");
    scanf("%d", &codigoContato);
    system("cls");
    
    if(registros[codigoContato].indisponivel){
    	
    	printf("\n *** Contato inexistente ou excluído previamente. ***\n");
		printf(" *** TENTE NOVAMENTE ***\n");
		    	
    	listarContatos(registros,tamanho);
	}

    printf("%s", divisao);
    printf(" %d. ", codigoContato);
    printf("Nome: %s | ", registros[codigoContato].nome);
    printf("Numero: %s | ", registros[codigoContato].numero);
    printf("Email: %s ", registros[codigoContato].email);
    printf("%s", divisao);

    printf("Deseja alterar o nome? Nome atual *%s* (sim: 1 | não: 0): ", registros[codigoContato].nome);
    scanf("%d", &verificar);
    switch(verificar)
    {
    case 0:
        printf("Nome não alterado.\n");
        break;
    case 1:
        printf("Digite o novo nome: ");
        scanf("%s", registros[codigoContato].nome);
        break;
    default:
        printf("Opção inválida, nome não alterado.\n");
    }

    printf("Deseja alterar o número? Número atual *%s* (sim: 1 | não: 0): ", registros[codigoContato].numero);
    scanf("%d", &verificar);
    switch(verificar)
    {
    case 0:
        printf("Numero não alterado.\n");
        break;
    case 1:
        printf("Digite o novo número: ");
        scanf("%s", registros[codigoContato].numero);
        break;
    default:
        printf("Opção inválida, número não alterado.\n");
    }

    printf("Deseja alterar o email? Email atual *%s* (sim: 1 | não: 0): ", registros[codigoContato].email);
    scanf("%d", &verificar);
    switch(verificar)
    {
    case 0:
        printf("Email não alterado.\n");
        break;
    case 1:
        printf("Digite o novo email: ");
        scanf("%s", registros[codigoContato].email);
        break;
    default:
        printf("Opção inválida, email não alterado.\n");
    }

    system("cls");
    tamanhoMensagem = tamanhoString(mensagemSucesso);
    mensagem(mensagemSucesso, tamanhoMensagem);

    printf("%s", divisao);
    printf(" %d. ", codigoContato);
    printf("Nome: %s | ", registros[codigoContato].nome);
    printf("Numero: %s | ", registros[codigoContato].numero);
    printf("Email: %s ", registros[codigoContato].email);
    printf("\n*************************************************");
	
	backup(registros, tamanho);
    menu(registros, tamanho);

}

void listarContatos(contato registros[], int tamanho)
{
	
    char inicio[50] = " 		Lista De Contatos 	";
    char final[50] = "*************************************************";
    int tamanhoMensagem = tamanhoString(inicio);
    contato registroTemp;
    int i, j;


    for (i=1; i < tamanho; i++)
    {
        registroTemp = registros[i];
        j=i-1;

        while(toupper(registroTemp.nome[0]) < toupper(registros[j].nome[0]))
        {
            registros[j+1] = registros[j];
            j--;
        }
        registros[j+1] = registroTemp;
    }
    mensagem(inicio, 49);
    for(i=0; i < tamanho; i++)
    {
        if(!registros[i].indisponivel){
            printf(" %d. ", i);
            printf("Nome: %s | ", registros[i].nome);
            printf("Numero: %s | ", registros[i].numero);
            printf("Email: %s ", registros[i].email);
            printf("\n");
        }
    }
    printf("%s\n", final);

    menu(registros, tamanho);
}

int sair(contato registros[], int tamanho)
{
    int opcaoSair;

    printf("\nDeseja sair da Agenda?\n");
    printf("1 - Sim / 2 - Não\n");
    scanf("%d", &opcaoSair);

    if(opcaoSair == 1)
    {
        printf("\n -- ATÉ MAIS!!! --\n");
        exit(0);
    }
    else if(opcaoSair == 2)
    {
        system("cls");
        menu(registros, tamanho);
    }
    else
    {
        printf("\n-- OPÇÃO INVÁLIDA --\n");
        sair(registros, tamanho);
    }
}

void mensagem(char mensagem[], int tamanho)
{
    int i;
    for(i=0; i < tamanho; i++)
    {
        printf("-");
    }
    printf("\n%s\n", mensagem);

    for(i=0; i < tamanho; i++)
    {
        printf("-");
    }
    printf("\n");
}
int tamanhoString(char mensagem[])
{
    int tamanho = 0;

    while(mensagem[tamanho] != '\0')
    {
        tamanho++;
    }
    return tamanho;
}
void buscaString(contato registros[],char nomeBusca[], int tamanhoString, int tamanho)
{
    int i, j, cont;
    for(i = 0; i < tamanho; i++)
    {
        j = 0;
        if(!registros[i].indisponivel)
        {
            while(tolower(registros[i].nome[j]) == tolower(nomeBusca[j]) && j < tamanhoString )
            {
                j++;
                if(j == tamanhoString)
                {
                    printf("Código: %i | Nome: %s \n", i, registros[i].nome);
                }
            }
        }
    }
}

void backup(contato registros[], int tamanho){
	FILE *arqagenda = fopen("agenda.dat", "wb+");
	int result = fwrite (&registros[0], sizeof(contato), tamanho, arqagenda);
	
	fclose(arqagenda);
	
	menu(registros, tamanho);
	
}

   

