import java.util.Scanner;

class Contador {
    long comparar;
    long armazenar;
}

public class BubbleInsertionSelection {
    public static void InsertionSort(int tam, int[] vetor, Contador cont ){
        int copia, indice;
        for(int i = 1; i < tam; i++) {
            copia = vetor[i];
            indice = i;

            while(indice > 0) {
                cont.comparar++;
                
                if(vetor[indice - 1] > copia) {
                    vetor[indice] = vetor[indice - 1];
                    cont.armazenar++;
                    indice--;
                } else {
                    break;
                }
            }

            vetor[indice] = copia;
            cont.armazenar++;
        }
    }

    public static void SelectionSort(int tam, int[] vetor, Contador cont) {
        int copia, indice;
        for(int i = 0; i < tam - 1; i++) {
            indice = i;
            for(int j = i + 1; j < tam; j++) {
                cont.comparar++;
                if(vetor[j] < vetor[indice]) {
                    indice = j;
                }
            }
            if(indice != i) {
                copia = vetor[i];
                vetor[i] = vetor[indice];
                vetor[indice] = copia;
                cont.armazenar += 3;
            } else {
                cont.armazenar += 1;
            }
        }
    }

    public static void BubbleSort(int tam, int[] vetor, Contador cont) {
        int troca;
        for(int i = 0; i < tam - 1; i++) {
            for(int j = 0; j < tam - 1 - i; j++) {
                cont.comparar++;

                if(vetor[j] > vetor[j + 1]) {
                    troca = vetor[j];
                    vetor[j] = vetor[j + 1];
                    vetor[j + 1] = troca;
                    cont.armazenar += 3;
                } else {
                    cont.armazenar++;
                }
            }
        }
    }

    public static void GerarAleatorio(int tam, int[] vetor) {
        for(int i = 0; i < tam; i++) {
            vetor[i] = i;
        }
    }

    public static void GerarOrdenado(int tam, int[] vetor) {
        for(int i = 0; i < tam; i ++) {
            vetor[i] = i;
        }
    }

    public static void InversamenteOrdenado(int tam, int[] vetor) {
        for(int i = 0; i < tam; i++) {
            vetor[i] = tam - i - 1;
        }
    }

    public static double Timer() {
        return System.nanoTime() / 1_000_000_000.0;
    }

    public static void MENU() {
        System.out.println("Escolha uma das opcoes de algoritmo a seguir:");
        System.out.println("1. Insertion Sort.");
        System.out.println("2. Selection Sort.");
        System.out.println("3. Bublle sort.");
        System.out.println("4. Sair.");
        System.out.println("escolha uma das opcoes apresentadas(1-4), pfv rs:");
    }

    public static void TIPO() {
        System.out.println("Escolha o tipo de vetor que deseja realizar a operação:");
        System.out.println("1. Aleatório.");
        System.out.println("2. Ordenado.");
        System.out.println("3. Inversamente Ordenado.");
        System.out.println("Escolha que tipo de interação que será feita:");
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        int escolher, tam;
        int tipo;
        int[] vetor;
        Contador cont = new Contador();
        double TempoI, TempoF;

        while(true) {
            MENU();
            escolher = scan.nextInt();

            if(escolher == 4) {
                System.out.println("ACABOU-SE");
                break;
            }

            System.out.println("Tamanho desejado para a realização das operações: 100, 1000, 10000, 100000");
            tam = scan.nextInt();

            TIPO();
            tipo = scan.nextInt();

            vetor = new int[tam];

            switch(tipo) {
                case 1:
                    GerarAleatorio(tam, vetor);
                    break;
                case 2:
                    GerarOrdenado(tam, vetor);
                    break;
                case 3:
                    InversamenteOrdenado(tam, vetor);
                    break;
                default :
                    System.out.println("Opção inválida chefia");
                    break;
            }

            cont.comparar = 0;
            cont.armazenar = 0;
            TempoI = Timer();

            switch(escolher) {
                case 1:
                    InsertionSort(tam, vetor, cont);
                    break;
                case 2:
                    SelectionSort(tam, vetor, cont);
                    break;
                case 3:
                    BubbleSort(tam, vetor, cont);
                    break;
                default:
                    System.out.println("INVALIDO");
                    continue;
            }

            TempoF = Timer();

            System.out.println("\nEm " + tam + " elementos, foram comparados: " + cont.comparar + " vezes");
            System.out.println("Armazenados: " + cont.armazenar);
            System.out.printf("Tempo total para execucao: %.5f segundos%n", (TempoF - TempoI));
        }

        scan.close();
    }
}