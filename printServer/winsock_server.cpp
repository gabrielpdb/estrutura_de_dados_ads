#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#pragma pack(push, 1)
struct Pacote {
	int method;
	char nome[50];
	char info[100];
	char timestamp[20];
};
#pragma pack(pop)

typedef struct Impressao {
	char nome[50];
	char info[100];
	char timestamp[20];
	struct Impressao *prox;
};

typedef struct {
	Impressao *inicio;
	Impressao *fim;
	int tamanho;
} Fila;

Fila *cria(void);
bool vazia(Fila *f);
int tamanho(Fila *f);
void inserir(Fila *f, Impressao impressao);
void mostrarLista(Fila *f);
void mostraImpressao(Impressao *i);
void salvarArquivo(Fila *f);
void liberaFila(Fila *f);

int __cdecl main(void) {
	system("cls");

	Fila *Fila = cria();

	int limiteFila = 0;
	printf("Servidor online...\n")	;
	printf("Informe o limite maximo da fila de impressao: ");
	scanf("%d", &limiteFila);
	system("cls");
	printf("Esperando por impressoes...\n\n");

	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;



	// Receive until the peer shuts down the connection
	bool abresocket=true;
	do {

		if (abresocket) {
			// Initialize Winsock
			iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
			if (iResult != 0) {
				printf("WSAStartup failed with error: %d\n", iResult);
				return 1;
			}

			ZeroMemory(&hints, sizeof(hints));
			hints.ai_family = AF_INET;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;
			hints.ai_flags = AI_PASSIVE;

			// Resolve the server address and port
			iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
			if ( iResult != 0 ) {
				printf("getaddrinfo failed with error: %d\n", iResult);
				WSACleanup();
				return 1;
			}

			// Create a SOCKET for the server to listen for client connections.
			ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
			if (ListenSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				freeaddrinfo(result);
				WSACleanup();
				return 1;
			}

			// Setup the TCP listening socket
			iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				printf("bind failed with error: %d\n", WSAGetLastError());
				freeaddrinfo(result);
				closesocket(ListenSocket);
				WSACleanup();
				return 1;
			}

			freeaddrinfo(result);

			iResult = listen(ListenSocket, SOMAXCONN);
			if (iResult == SOCKET_ERROR) {
				printf("listen failed with error: %d\n", WSAGetLastError());
				closesocket(ListenSocket);
				WSACleanup();
				return 1;
			}

			// Accept a client socket
			ClientSocket = accept(ListenSocket, NULL, NULL);
			if (ClientSocket == INVALID_SOCKET) {
				printf("accept failed with error: %d\n", WSAGetLastError());
				closesocket(ListenSocket);
				WSACleanup();
				return 1;
			}

			// No longer need server socket
			closesocket(ListenSocket);
		}
		abresocket = false;
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);




		if (iResult > 0) {
			//AQUI EU VOU DESMEMBRAR A STRUCT RECEBIDA COMO STRING
			Pacote pacote;
			memcpy(&pacote, recvbuf, sizeof(Pacote));

			if(pacote.method == 1) { //METODO IMPRIMIR

				Impressao novaImpressao;
				
				strcpy(novaImpressao.nome, pacote.nome);
				strcpy(novaImpressao.info, pacote.info);
				strcpy(novaImpressao.timestamp, pacote.timestamp);
				
				inserir(Fila, novaImpressao);
				
				if(tamanho(Fila) == limiteFila) {
					salvarArquivo(Fila);
				}
				
				system("cls");
				printf("Fila de impressao: %d/%d\n", Fila->tamanho, limiteFila);
			} else if (pacote.method == 2) { // METODO LISTAR
				system("cls");
				mostrarLista(Fila);
				
				Impressao *atual = Fila->inicio;
				
				while(atual != NULL){
					struct Pacote envio;
					envio.method = 2;
					strcpy(envio.nome, atual->nome);
					strcpy(envio.info, atual->info);
					strcpy(envio.timestamp, atual->timestamp);
					
					iSendResult = send(ClientSocket, (const char*)&envio, sizeof(envio), 0);
					if(iSendResult == SOCKET_ERROR) {
						printf("ENVIO FALHOU COM ERRO: %d\n", WSAGetLastError());
						break;
					}
					
					atual = atual->prox;
					
				}
				
				struct Pacote fim;
				memset(&fim, 0, sizeof(fim));
				fim.method = -1;
				send(ClientSocket, (const char*)&fim, sizeof(fim), 0);
			}

			/*
			// shutdown the connection since we're done
			iResult = shutdown(ClientSocket, SD_SEND);
			if (iResult == SOCKET_ERROR) {
			    printf("shutdown failed with error: %d\n", WSAGetLastError());
			    closesocket(ClientSocket);
			    WSACleanup();
			    return 1;
			}

			// cleanup
			closesocket(ClientSocket);
			WSACleanup();
			abresocket=true;
			 */
		} else if (iResult == 0) {
			printf("Connection closing...\n");
			closesocket(ClientSocket);
			WSACleanup();
			abresocket = true;
		} else  {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			abresocket = true;
		}

		//iResult > 0
	} while (true);

	return 0;
}

Fila *cria(void) {
	Fila *f = (Fila *)malloc(sizeof(Fila));
	f->inicio = NULL;
	f->fim = NULL;
	f->tamanho = 0;

	return f;
}

bool vazia(Fila *f) {
	return (f->tamanho == 0);
}

int tamanho(Fila *f) {
	return f->tamanho;
}

void inserir(Fila *f, Impressao impressao) {
	Impressao *i = (Impressao *)malloc(sizeof(Impressao));
	strcpy(i->info, impressao.info);
	strcpy(i->nome, impressao.nome);
	strcpy(i->timestamp, impressao.timestamp);
	i->prox = NULL;
	
	if(vazia(f)) {
		f->inicio = i;
	} else {
		f->fim->prox = i;
	}
	
	f->fim = i;
	f->tamanho++;
}

void mostraImpressao(Impressao *i) {
	printf("Nome: %s\n", i->nome);
	printf("Mensagem: %s\n", i->info);
	printf("Data: %s\n", i->timestamp);
}

void mostrarLista(Fila *f) {
	if(vazia(f)) {
		printf("Fila vazia!\n");
	} else {
		Impressao *i = f->inicio;
		
		while(i != NULL) {
			mostraImpressao(i);
			printf("\n");
			i = i->prox;
		}
	}
}

void salvarArquivo(Fila *f){
	FILE *fp = fopen("impressora.txt", "a");
	if(fp == NULL) {
		perror("Erro ao abrir arquivo de impressao");
		return;
	}
	
	Impressao *atual = f->inicio;
	
	while(atual != NULL) {
		fprintf(fp, "%s;%s;%s\n", atual->nome, atual->info, atual->timestamp);
		
		atual = atual->prox;
	}
	
	fclose(fp);
	liberaFila(f);
}

void liberaFila(Fila *f) {
	Impressao *atual = f->inicio;
	
	while(atual != NULL){
		Impressao *temp = atual->prox;
		free(atual);
		atual = temp;
	}
	
	f->inicio = NULL;
	f->fim = NULL;
	f->tamanho = 0;
}