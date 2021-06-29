#include <iostream>
#include <string.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <ctime>


using namespace std;

//prototypes
void cadastrar();
int iniLogin();
void preencherClientes();
void preencherMenu();
void mostrarMenu();
float precoItem(int escolha, int qtd);
float calculaTotal();
void pedido();
void alteraPedido();
void salvarPedido(float total);
int verHistorico();


struct cliente
{
	string nome;
	string endereco;
	int id;
} CLIENTE[50];

struct item
{
	int codigo;
	string nome;
	int qtd;
	float preco;
	string descricao;
	
}ITEM[5];


	string arquivo, clienteN, clienteEnd;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
	int menuPrincipal, escolha, adicionar, quantidade, alterar, login, intArquivo=-1, voltar=0;
	float totPreco=0.0, totPedido=0.0;

	do
	{
		preencherClientes();
		preencherMenu();
		
		system("cls");
		cout << "****Bem-vindo à Valbernielson's Hamburgueria****" << endl << endl;
		cout << setw(15) << left << "Fazer Login" << "(1)" << endl;
		cout << setw(15) << left << "Cadastrar" << "(2)" << endl;
		cout << setw(15) << left << "Sair" << "(0)" << endl << endl;
		cout << "Escolha: ";
		cin >> login;
		
		switch (login)
		{
			case 1:
				{
					intArquivo=iniLogin();
					if (intArquivo >= 0 && intArquivo < 50)
					{
						ostringstream converter;
						converter << intArquivo;
						arquivo = converter.str();
					}
					else if (intArquivo == -1)
					{
						arquivo = "Sem cadastro";
						clienteN = "Nao cadastrado.";
						clienteEnd = "Nao cadastrado.";
					}
				}
				
				break;	
			case 2:
				system("cls");
				cadastrar ();
				break;
			case 0:
				return 0;
			default:
				cout << "Escolha invalida.";
				system ("pause");
				return 0;
		}
	}while (intArquivo==-1);
	

	
	do
	{
		system("cls");
		cout << "**** [" << clienteN << "] bem-vindo(a) à Valbernielson's Hamburgueria****" << endl;
		cout << "Endereo da entrega: " << clienteEnd << endl << endl;
		cout << setw(25) << left << "Iniciar Pedido" << "(1)" << endl;
		cout << setw(25) << left << "Historico de Pedidos" << "(2)" << endl;
		cout << setw(25) << left << "Sair" << "(0)" << endl << endl;
		cout << "Escolha: ";
		cin >> menuPrincipal;
		switch(menuPrincipal)
		{
			case 1:
				do
				{
					do
					{
						system("cls");
						mostrarMenu();
						cout << "Escolha: ";
						cin >> escolha;
					}while (escolha < 1 || escolha > 5);
					
					do
					{
						cout << "Quantidade: ";
						cin >> quantidade;	
					} while (quantidade < 0);
					totPreco=precoItem(escolha, quantidade);
					totPedido=calculaTotal();
					printf("\nPreco total do item: R$%.2f \n\n", totPreco);
					printf("\nPreco total do pedido: R$%.2f \n\n", totPedido);
					cout << "Adicionar mais um lanches? Sim (1) Nao (0)" << endl;
					cin >> adicionar;
				} while (adicionar != 0);
				
				do
				{
					system("cls");
					pedido();
					printf("\nPreco total do pedido: R$%.2f \n\n", totPedido);
					cout << setw(20) << left << "Alterar Pedido" << "(1)" << endl;
					cout << setw(20) << left << "Finalizar Pedido" << "(2)" << endl;
					cout << "Escolha: ";
					cin >> alterar;
					if (alterar == 1)
					{
						system("cls");
						cout << "*** ALTERANDO PEDIDO ***" << endl << endl;
						alteraPedido();
						totPedido=calculaTotal();
					}
				} while(alterar != 2);
				
				system("cls");
				printf("\nPreco total do pedido: R$%.2f \n\n", totPedido);
				salvarPedido(totPedido);
				for (int count=0; count<5; count++)
				{
					ITEM[count].qtd=0;
				}
				system("pause");
				break;
				
			case 2:
				voltar=verHistorico();
				break;
			case 0:
				return 0;
			default:
				cout << "Escolha invalida, tente novamente: ";
				cin >> menuPrincipal;
		}
		
	} while (menuPrincipal < 0 || menuPrincipal > 2 || voltar == 0);
		
	return 0;
	
}


//Funcoes
void cadastrar ()
{
	string nomeCad, endCad, idCad;
	int idR, salvar=0;
	
	cout << "****** CADASTRO DE CLIENTE *******"<< endl << endl;
	cout << "Nome: ";
	cin.ignore();
	getline(cin, nomeCad);
	cout << "Endereco: ";
	getline(cin, endCad);
	cout << "CPF (sem pontos): ";
	getline(cin, idCad);
	
	idR = atoi(idCad.c_str() );
	
	for (int count=0; count<50; count++)
	{
		if (idR == CLIENTE[count].id)
		{
			cout << "\nCliente ja cadastrado!!!" << endl << endl;
			system("pause");
			break;
		}
		else
		{
			salvar=1;	
		}
	}
	
	if (salvar==1)
	{
		ofstream cadastrar;
	
		cadastrar.open("CadastroClientes.txt", ios::out | ios::app);
	
		cadastrar << nomeCad << endl;
		cadastrar << endCad << endl;
		cadastrar << idCad << endl;
		
		cadastrar.close();
	}

	return;	
}

int iniLogin()
{
	int id, arq;
	
	system("cls");
	cout << "CPF (sem pontos): ";
	cin >> id;
	
	for (int count=0; count<50; count++)
	{
		if (id == CLIENTE[count].id)
		{
			arq = count;
			clienteN = CLIENTE[count].nome;
			clienteEnd = CLIENTE[count].endereco;
			break;
		}
		else
		{
			arq=-1;
		}
	}
	
	return arq;
}


void preencherClientes()
{
	
	/*CLIENTE[0].id=1234;
	CLIENTE[0].nome="Rafaela";
	CLIENTE[0].endereco="Rua 123";*/
	
	ifstream preencherC;
	preencherC.open("CadastroClientes.txt", ios::in);
	int count;
	string idC;
	
	if (preencherC.is_open())
	{
		while (!preencherC.eof())
		{
			for (int count=0; count<50; count++)
			{
				getline(preencherC, CLIENTE[count].nome);
				getline(preencherC, CLIENTE[count].endereco);
				getline(preencherC, idC);
				CLIENTE[count].id = atoi(idC.c_str());
			}
			
		}
		preencherC.close();
	}
	
	
}



void preencherMenu()
{
	ITEM[0].codigo=1;
	ITEM[0].nome="X-Burger";
	ITEM[0].preco=10.00;
	ITEM[0].descricao="Pao, hamburger e queijo";
	
	ITEM[1].codigo=2;
	ITEM[1].nome="X-Salada";
	ITEM[1].preco=12.00;
	ITEM[1].descricao="Pao, hamburger, queijo e salada";
	
	ITEM[2].codigo=3;
	ITEM[2].nome="X-Bacon ";
	ITEM[2].preco=13.00;
	ITEM[0].descricao="Pao, hamburger, queijo e bacon";
	
	ITEM[3].codigo=4;
	ITEM[3].nome="X-Salada Bacon";
	ITEM[3].preco=15.00;
	ITEM[0].descricao="Pao, hamburger, queijo, salada e bacon";
	
	ITEM[4].codigo=5;
	ITEM[4].nome="X-Tudo  ";
	ITEM[4].preco=17.00;
	ITEM[0].descricao="Pao, hamburger, queijo, salada, bacon, presunto e milho";
	
}


void mostrarMenu()
{	
	cout <<"***********MENU**************" << endl << endl;
	cout << setw(10) << left << "Codigo" << setw(15) << left << "Lanche" << setw(10) << left << "Preco" << "Descricao" << endl;
	cout << setw(10) << left << "1" << setw(15) << left << "X-Burger" << setw(10) << left << "10.00" << "Pao, hamburger e queijo" << endl;
	cout << setw(10) << left << "2" << setw(15) << left << "X-Salada" << setw(10) << left << "12.00" << "Pao, hamburger, queijo e salada" << endl;
	cout << setw(10) << left << "3" << setw(15) << left << "X-Bacon" << setw(10) << left << "13.00" << "Pao, hamburger, queijo e bacon" << endl;
	cout << setw(10) << left << "4" << setw(15) << left << "X-Salada Bacon" << setw(10) << left << "15.00" << "Pao, hamburger, queijo, salada e bacon" << endl;
	cout << setw(10) << left << "5" << setw(15) << left << "X-Tudo" << setw(10) << left << "17.00" << "Pao, hamburger, queijo, salada, bacon, presunto e milho" << endl << endl;
					
	return;
}

float precoItem(int escolha, int qtd)
{
	int count;
	float totItem=0.0, precoItem=0.0;
	precoItem=ITEM[escolha-1].preco;
	
	for (count=0; count<5; count++)
	{
		if (escolha==count+1)
		{
			ITEM[count].qtd+=qtd;
		}
	}
	
	totItem=precoItem*qtd;

	return totItem;
}

float calculaTotal()
{
	float total=0.0;
	int count;
	
	for(count=0; count<5; count++)
	{
		total=total+ITEM[count].preco*ITEM[count].qtd;
	}
	
	return total;
}

void pedido()
{
	int alt;
	int count;
	system("cls");
	cout <<"*************Seu Pedido ******************" << endl << endl;
	cout << setw(10) << left << "Codigo" << setw(20) << left << "Item" << setw(15) << left << "Quantidade" << "Preco" << endl;
	
	for (count=0; count<5; count++)
	{
		if (ITEM[count].qtd > 0)
		{
			cout << setw(10) << left << ITEM[count].codigo << setw(20) << left << ITEM[count].nome << setw(15) << left << ITEM[count].qtd;
			printf("R$%5.2f\n", ITEM[count].qtd*ITEM[count].preco);
		}
	}
	
	printf("\n\n");
	
	return;
	
}


void alteraPedido()
{
	int item, quantidade, count, sim;
	
	cout << "Seu pedido" << endl << endl;
	pedido();
	cout << "\n\n";
	mostrarMenu();
	
	cout << "Digite o codigo do item que deseja alterar ou adicionar: ";
	cin >> item;
	cout << "Digite a quantidade esejada: ";
	cin >> quantidade;
	for(count=0; count<5; count++)
	{
		if (item==count+1)
		{
			ITEM[count].qtd=quantidade;
		}
	}
	
	//precoItem(item, quantidade);
	
	return;
	
}

void salvarPedido(float total)
{
	time_t timer;
  	struct tm *horarioLocal;

  	time(&timer);
  	horarioLocal = localtime(&timer);

  	int dia = horarioLocal->tm_mday;
 	int mes = horarioLocal->tm_mon + 1;
 	int ano = horarioLocal->tm_year + 1900;
  	int hora = horarioLocal->tm_hour;
  	int min  = horarioLocal->tm_min;
  	int sec  = horarioLocal->tm_sec;
  	
	ofstream salvar;
	
	salvar.open((arquivo).c_str(), ios::out | ios::app);
	
	salvar << "Pedido realizado em: " << dia << "/" << mes << "/" << ano << " as: " << hora << ":" << min << ":" << sec << endl;
	
		for (int count=0; count<5; count++)
		{
			if (ITEM[count].qtd > 0)
			{
				salvar << "Lanche: " << setw(20) << left << ITEM[count].nome << "Quantidade: " << setw(4) << left << ITEM[count].qtd << "Preco itens: R$" << setprecision(2) << fixed << ITEM[count].qtd*ITEM[count].preco << endl;
			}
		}
		salvar << "Total do pedido: R$" << setprecision(2) << fixed << total << endl << endl << endl;
	
	salvar.close();
		
		return;			
}

int verHistorico()
{
	int volt;
	string getcontent;
	ifstream mostrar;
	
	mostrar.open((arquivo).c_str(), ios::in);
	
	system("cls");
	cout << "**********Seu Historico de Pedidos *******" << endl << endl;
	
	if(mostrar.is_open())
	{
	    while(! mostrar.eof())
	    {
	        getline(mostrar, getcontent);
	        cout << getcontent << endl;
	    }
	}
	
	mostrar.close();
	
	cout << "\nVoltar(0)   Sair(1)" << endl;
	cin >> volt;
	
	return volt;
}
