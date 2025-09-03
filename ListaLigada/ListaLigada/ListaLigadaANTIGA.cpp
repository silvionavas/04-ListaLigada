#include <iostream>
using namespace std;

// Definição de tipo
struct NO {
	int valor;
	NO* prox;
};

NO* primeiro = NULL;

// Headers
void menu();
void inicializar();
void exibirQuantidadeElementos();
void exibirElementos();
void inserirElemento();
void excluirElemento();
void buscarElemento();
NO* posicaoElemento(int numero);
//--------------------------

int main() {
	menu();
}

void menu() {
	int op = 0;
	while (op != 7) {
		system("cls"); // somente no Windows
		cout << "Menu Lista Ligada";
		cout << endl << endl;
		cout << "1 - Inicializar Lista \n";
		cout << "2 - Exibir quantidade de elementos \n";
		cout << "3 - Exibir elementos \n";
		cout << "4 - Buscar elemento \n";
		cout << "5 - Inserir elemento \n";
		cout << "6 - Excluir elemento \n";
		cout << "7 - Sair \n\n";

		cout << "Opcao: ";
		cin >> op;

		switch (op) {
		case 1: inicializar(); break;
		case 2: exibirQuantidadeElementos(); break;
		case 3: exibirElementos(); break;
		case 4: buscarElemento(); break;
		case 5: inserirElemento(); break;
		case 6: excluirElemento(); break;
		case 7: return;
		default: break;
		}

		system("pause"); // somente no Windows
	}
}

void inicializar() {
	// Se a lista já possuir elementos, libera a memória ocupada
	NO* aux = primeiro;
	while (aux != NULL) {
		NO* paraExcluir = aux;
		aux = aux->prox;
		free(paraExcluir);
	}

	primeiro = NULL;
	cout << "Lista inicializada \n";
}

void exibirQuantidadeElementos() {
	int nElementos = 0;
	NO* aux = primeiro;
	while (aux != NULL) {
		nElementos++;
		aux = aux->prox;
	}
	cout << "Quantidade de elementos: " << nElementos << endl;
}

void exibirElementos() {
	if (primeiro == NULL) {
		cout << "Lista vazia \n";
		return;
	}
	else {
		cout << "Elementos: \n";
		NO* aux = primeiro;
		while (aux != NULL) {
			cout << aux->valor << endl;
			aux = aux->prox;
		}
	}
}

void inserirElemento() {
	int valor;
	cout << "Digite o elemento: ";
	cin >> valor;

	// Verifica se o elemento já existe
	if (posicaoElemento(valor) != NULL) {
		cout << "Elemento já existe na lista. Não será inserido.\n";
		return;
	}

	// Aloca memória dinamicamente para o novo elemento
	NO* novo = (NO*)malloc(sizeof(NO));
	if (novo == NULL) {
		return;
	}
	novo->valor = valor;
	novo->prox = NULL;

	if (primeiro == NULL) {
		primeiro = novo;
	}
	else {
		NO* aux = primeiro;
		NO* anterior = NULL;

		// Insere de forma ordenada
		while (aux != NULL && aux->valor < valor) {
			anterior = aux;
			aux = aux->prox;
		}

		if (anterior == NULL) {
			// Inserção no início da lista
			novo->prox = primeiro;
			primeiro = novo;
		}
		else {
			// Inserção no meio ou no fim
			anterior->prox = novo;
			novo->prox = aux;
		}
	}
}

void excluirElemento() {
	int valor;
	cout << "Digite o elemento a ser excluído: ";
	cin >> valor;

	NO* atual = primeiro;
	NO* anterior = NULL;

	// Busca o elemento
	while (atual != NULL && atual->valor != valor) {
		anterior = atual;
		atual = atual->prox;
	}

	if (atual == NULL) {
		cout << "ELEMENTO NÃO ENCONTRADO\n";
		return;
	}

	// Remove o elemento
	if (anterior == NULL) {
		// Se o elemento a ser excluído for o primeiro
		primeiro = atual->prox;
	}
	else {
		anterior->prox = atual->prox;
	}

	free(atual);
	cout << "Elemento excluído com sucesso\n";
}

void buscarElemento() {
	int valor;
	cout << "Digite o elemento a ser buscado: ";
	cin >> valor;

	if (posicaoElemento(valor) != NULL) {
		cout << "ENCONTRADO\n";
	}
	else {
		cout << "ELEMENTO NÃO ENCONTRADO\n";
	}
}

// Retorna um ponteiro para o elemento buscado ou NULL se não estiver na lista
NO* posicaoElemento(int numero) {
	NO* aux = primeiro;
	while (aux != NULL) {
		if (aux->valor == numero) {
			return aux;
		}
		aux = aux->prox;
	}
	return NULL;
}
