#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

void criarArquivo(void) {
    FILE *arquivo = fopen("dados.txt", "w");
    int valores[] = {45, 12, 89, 3, 27, 66, 8, 51};
    int i, quantidade = sizeof(valores) / sizeof(valores[0]);

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d\n", valores[i]);
    }

    fclose(arquivo);
    printf("Arquivo dados.txt criado com sucesso!\n");
}

int lerArquivo(int valores[]) {
    FILE *arquivo = fopen("dados.txt", "r");
    int quantidade = 0;

    if (arquivo == NULL) {
        printf("Nao foi possivel abrir dados.txt. Crie o arquivo primeiro.\n");
        return -1;
    }

    while (quantidade < MAX && fscanf(arquivo, "%d", &valores[quantidade]) == 1) {
        quantidade++;
    }

    fclose(arquivo);
    return quantidade;
}

void salvarOrdenado(int valores[], int quantidade) {
    FILE *arquivo = fopen("ordenado.txt", "w");
    int i;

    if (arquivo == NULL) {
        printf("Erro ao criar ordenado.txt.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d\n", valores[i]);
    }

    fclose(arquivo);
    printf("Resultado salvo em ordenado.txt!\n");
}

void mostrarValores(int valores[], int quantidade) {
    int i;

    if (quantidade == 0) {
        printf("Nenhum valor encontrado.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        printf("%d ", valores[i]);
    }
    printf("\n");
}

void bubbleSort(int v[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int v[], int n) {
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

void selectionSort(int v[], int n) {
    int i, j, menor, temp;
    for (i = 0; i < n - 1; i++) {
        menor = i;
        for (j = i + 1; j < n; j++) {
            if (v[j] < v[menor]) {
                menor = j;
            }
        }
        temp = v[i];
        v[i] = v[menor];
        v[menor] = temp;
    }
}

void merge(int v[], int inicio, int meio, int fim) {
    int temp[MAX];
    int i = inicio, j = meio + 1, k = 0;

    while (i <= meio && j <= fim) {
        if (v[i] <= v[j])
            temp[k++] = v[i++];
        else
            temp[k++] = v[j++];
    }

    while (i <= meio) temp[k++] = v[i++];
    while (j <= fim) temp[k++] = v[j++];

    for (i = 0; i < k; i++) {
        v[inicio + i] = temp[i];
    }
}

void mergeSort(int v[], int inicio, int fim) {
    int meio;
    if (inicio < fim) {
        meio = (inicio + fim) / 2;
        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}

void quickSort(int v[], int inicio, int fim) {
    int i = inicio, j = fim;
    int pivo = v[(inicio + fim) / 2];
    int temp;

    while (i <= j) {
        while (v[i] < pivo) i++;
        while (v[j] > pivo) j--;

        if (i <= j) {
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            i++;
            j--;
        }
    }

    if (inicio < j) quickSort(v, inicio, j);
    if (i < fim) quickSort(v, i, fim);
}

void alterarValor(void) {
    int valores[MAX];
    int quantidade = lerArquivo(valores);
    int posicao, novoValor, i;
    FILE *arquivo;

    if (quantidade <= 0) return;

    printf("\nValores atuais:\n");
    for (i = 0; i < quantidade; i++) {
        printf("%d - %d\n", i + 1, valores[i]);
    }

    printf("Digite a posicao que deseja alterar (1 a %d): ", quantidade);
    if (scanf("%d", &posicao) != 1 || posicao < 1 || posicao > quantidade) {
        printf("Posicao invalida.\n");
        return;
    }

    printf("Digite o novo valor: ");
    if (scanf("%d", &novoValor) != 1) {
        printf("Valor invalido.\n");
        return;
    }

    valores[posicao - 1] = novoValor;

    arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao atualizar dados.txt.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d\n", valores[i]);
    }

    fclose(arquivo);
    printf("Valor alterado e dados.txt atualizado!\n");
}

int main(void) {
    int valores[MAX];
    int quantidade, opcao, metodo;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Criar arquivo dados.txt\n");
        printf("2 - Ler e mostrar dados.txt\n");
        printf("3 - Ordenar os valores\n");
        printf("4 - Alterar um valor e reordenar\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            return 1;
        }

        switch (opcao) {
            case 1:
                criarArquivo();
                break;

            case 2:
                quantidade = lerArquivo(valores);
                if (quantidade >= 0) {
                    printf("Valores do arquivo:\n");
                    mostrarValores(valores, quantidade);
                }
                break;

            case 3:
            case 4:
                if (opcao == 4) {
                    alterarValor();
                }

                quantidade = lerArquivo(valores);
                if (quantidade <= 0) {
                    if (quantidade == 0)
                        printf("O arquivo nao possui valores.\n");
                    break;
                }

                printf("\nEscolha o metodo de ordenacao:\n");
                printf("1 - Bubble Sort\n");
                printf("2 - Insertion Sort\n");
                printf("3 - Selection Sort\n");
                printf("4 - Merge Sort\n");
                printf("5 - Quick Sort\n");
                printf("Opcao: ");

                if (scanf("%d", &metodo) != 1) {
                    printf("Opcao invalida.\n");
                    break;
                }

                switch (metodo) {
                    case 1: bubbleSort(valores, quantidade); break;
                    case 2: insertionSort(valores, quantidade); break;
                    case 3: selectionSort(valores, quantidade); break;
                    case 4: mergeSort(valores, 0, quantidade - 1); break;
                    case 5: quickSort(valores, 0, quantidade - 1); break;
                    default:
                        printf("Metodo invalido.\n");
                        quantidade = -1;
                        break;
                }

                if (quantidade > 0) {
                    printf("Valores ordenados:\n");
                    mostrarValores(valores, quantidade);
                    salvarOrdenado(valores, quantidade);
                }
                break;

            case 0:
                printf("Programa encerrado.\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
