#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct contador {
	long comparar; //contar o n�mero de compara��es realizadas durante a ordena��o.
	long armazenar; //contar o n�mero de movimenta��es de dados (armazenamentos ou trocas).
}Contador;

void InsertionSort(int tam, int vetor[], Contador* cont) { //armazena(copia) o numero do indice caso seja menor q o atual e troca de lugar
    int copia, indice;
    for (int i = 1; i < tam; i++) {  // Come�a a partir do segundo elemento
        copia = vetor[i]; //Armazena o valor do elemento atual do vetor que ser� ordenado.
        indice = i; //Inicializa a posi��o atual do elemento.

        // Conta a compara��o antes de verificar a condi��o
        while (indice > 0) { //Entra no loop para verificar se o elemento anterior � maior.
            cont->comparar++;  // Contabiliza a compara��o para cada realiza��o do while
            
            // Se o valor � esquerda for maior, fazemos o movimento
            if (vetor[indice - 1] > copia) {
                vetor[indice] = vetor[indice - 1];  // Move o valor para a direita
                cont->armazenar++;  // Contabiliza o movimento de dados
                indice--;  // Vai para o pr�ximo �ndice
            } else {
                break;  // Se o valor � esquerda n�o for maior, sai do loop
            }
        }
        
        vetor[indice] = copia;  //Insere o valor de copia na posi��o correta
        cont->armazenar++;  //Contabiliza o armazenamento
    }
}

void SelectionSort(int vetor[], int tam, Contador* cont) { //come�a com o 1 e procura o menor, ent�o troca
	int copia, indice;
	for(int i = 0; i < tam - 1; i++) { //Loop para percorrer o vetor at� o pen�ltimo elemento
		indice = i; //Assume inicialmente que o menor elemento est� na posi��o atual i.
		for(int j = i + 1; j < tam; j++) { //Loop interno para encontrar o menor elemento no restante do vetor.
			cont->comparar++; //Incrementa o contador de compara��es para cada itera��o do j.
			if(vetor[j] < vetor[indice]) {//se encontrar um valor menos q o atual entra no if
				indice = j; //substitui o lugar do indice i atual pelo menor, que seria indice j
			}
		}
		if(indice != i) { //Verifica se o menor valor encontrado n�o est� na posi��o correta
			copia = vetor[i];//faz troca
			vetor[i] = vetor[indice];//faz troca
			vetor[indice] = copia; //apenas faz a copia ser igual o indice i
			cont->armazenar += 3;//conta as 3 trocas 
		} else {
			cont->armazenar += 1; //Se n�o houve troca, conta um acesso ao vetor.
		}
	}
}

void BubbleSort(int tam, int vetor[], Contador* cont) {
    int troca;
    for (int i = 0; i < tam - 1; i++) { //Controla o n�mero de passadas pelo vetor
        for (int j = 0; j < tam - 1 - i; j++) {  //Compara elementos at� a posi��o correta, q diminui a cada itera��o externa
            cont->comparar++;  // Contabiliza a compara��o

            if (vetor[j] > vetor[j + 1]) { //se apos a compara��o o indice i for menor que o seguinte, ir� trocar
                // Realiza a troca
                troca = vetor[j];//faz troca
                vetor[j] = vetor[j + 1];//faz troca
                vetor[j + 1] = troca; //trocou
                cont->armazenar += 3;  // Conta o movimento dos dados(3 trocas)
            } else {
                // Mesmo que n�o haja troca, ainda incrementa o contador de armazenamentos
                cont->armazenar++;  // Contabiliza a leitura do valor
            }
        }
    }
}

void gerarAleatorio(int tam, int vetor[]) { //cada posi��o do vetor, ser� atribu�do um n�mero aleat�rio entre 0 e 9999 (inclusive)
	for(int i = 0; i < tam; i++) {
		vetor[i] = rand() % 10000;
	}
}

void gerarOrdenado(int tam, int vetor[]) { //ada �ndice i, a fun��o atribui a ele o valor de i. Ou seja, o valor de cada elemento do vetor ser� igual ao seu �ndice
	for(int i = 0; i < tam; i++) {
		vetor[i] = i;
	}
}

void gerarInversamenteOrdenado(int tam, int vetor[]) { //vetor[i] diminui conforme o tamanho aumenta, deixando ele decrescente
	for(int i = 0; i < tam; i++) {
		vetor[i] = tam - i - 1; //come�a com o maior ate chegar em 0
	}
}

double Tempo() {
	struct timespec inicio, fim;
	clock_gettime(CLOCK_MONOTONIC, &inicio); //tempo atual
	return inicio.tv_sec + inicio.tv_nsec / 1000000000.0; //convers�o do tempo para segundos, 1 seg para n nanossegundos
}

void MENU() {
	printf("Escolha o algoritmo que planeja efetuar a operacao:\n");
    printf("1-Insertion Sort\n");
    printf("2-Selection Sort\n");
    printf("3-Bubble Sort\n");
    printf("4-Sair\n");
    printf("Escolha uma das opcoes (1-4):");
}

void escolherVetor() {
	printf("Escolha o tipo de vetor:\n");
    printf("1. Aleatorio\n");
    printf("2. Ordenado\n");
    printf("3. Inversamente Ordenado\n");
    printf("Escolha uma opcao (1-3): ");
}

int main() {
	int escolher;
	int tam;
	int tipo;
	int *vetor;
	Contador cont;
	double tempoInicio, tempoFim;
	
	while(1) { //loop infinito ate dada ordem
		MENU();
		scanf("%d", &escolher);
		
		if(escolher == 4) {
			printf("Encerrou.\n");
			break;
		}
		
		printf("Tamanho desejado do vetorentre as seguintes opcoes - 100, 1000, 10000, 100000: ");
		scanf("%d", &tam);
		
		escolherVetor();
		scanf("%d", &tipo);
		
		vetor = (int*)malloc(tam * sizeof(int)); //aloca memoria para vetor de inteiros
		
		switch(tipo) {
			case 1:
				gerarAleatorio(tam, vetor);
				break;
			case 2:
				gerarOrdenado(tam, vetor);
				break;
			case 3:
				gerarInversamenteOrdenado(tam, vetor);
				break;
			default:
				printf("Invalido\n");
				free(vetor);
				continue;
		}
		cont.comparar = 0;
		cont.armazenar = 0;
		tempoInicio = Tempo(); //come�a e puxa a fun��o para transformar em segundos
		
		switch(escolher) {
			case 1:
				InsertionSort(tam, vetor, &cont);
				break;
			case 2:
				SelectionSort(vetor, tam, &cont);
				break;
			case 3:
				BubbleSort(tam, vetor, &cont);
				break;
			default:
				printf("Invalido\n");
				continue;
		}
		tempoFim = Tempo(); //termina contagem de tempo
		printf("\nEm %d elementos foram comparados: %ld vezes\n", tam, cont.comparar);
		printf("\nArmazenados: %ld\n", cont.armazenar);
		printf("Tempo total para execucao: %.5f segundos\n", tempoFim - tempoInicio);
		free(vetor); //libera memoria usada anteriormente para utilizar numa proxima vez
	}
	return 0;
}
