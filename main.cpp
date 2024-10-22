#include <iostream>
#include <cstdlib> // Para usar rand()
#include <ctime>   // Para usar time()
#include <string>
#include <chrono>  // Para medir o tempo de execução
#include <algorithm> // Para copy

using namespace std;

struct RegistroVenda {
    string nomeProduto;
    int quantidadeVendida;
    double precoUnitario;
    string dataVenda;
};

void gerarRegistros(RegistroVenda registros[], int tamanho) {
    srand((unsigned)time(0));
    for (int i = 0; i < tamanho; ++i) {
        registros[i].nomeProduto = "Produto_" + to_string(i + 1);
        registros[i].quantidadeVendida = rand() % 100 + 1;
        registros[i].precoUnitario = (rand() % 10000) / 100.0;
        registros[i].dataVenda = "15/10/2024";
    }
}

// Bubble Sort
void bubbleSort(RegistroVenda arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j].precoUnitario < arr[j + 1].precoUnitario) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(RegistroVenda arr[], int n) {
    for (int i = 1; i < n; ++i) {
        RegistroVenda key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].precoUnitario < key.precoUnitario) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(RegistroVenda arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int max_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j].precoUnitario > arr[max_idx].precoUnitario) {
                max_idx = j;
            }
        }
        swap(arr[max_idx], arr[i]);
    }
}

// Counting Sort
void countingSort(RegistroVenda arr[], int n, int range) {
    int* count = new int[range + 1]();
    RegistroVenda* output = new RegistroVenda[n];

    for (int i = 0; i < n; ++i) {
        int precoInteiro = static_cast<int>(arr[i].precoUnitario * 100);
        ++count[precoInteiro];
    }

    for (int i = 1; i <= range; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        int precoInteiro = static_cast<int>(arr[i].precoUnitario * 100);
        output[count[precoInteiro] - 1] = arr[i];
        --count[precoInteiro];
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;
}

// Shell Sort
void shellSort(RegistroVenda arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            RegistroVenda temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].precoUnitario < temp.precoUnitario; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// QuickSort
int partition(RegistroVenda arr[], int low, int high) {
    double pivot = arr[high].precoUnitario;
    int i = (low - 1);
    for (int j = low; j < high; ++j) {
        if (arr[j].precoUnitario >= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(RegistroVenda arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Função para medir o tempo de execução
template <typename Func>
void medirTempoExecucao(Func func, RegistroVenda arr[], int n, const string &algoritmo) {
    double totalDuracao = 0;

    // ALTERAR REPETICOES PARA QUE VOCE POSSA TESTAR COM MAIORES REPETICOES PARA OBTER MEDIA
    int repeticoes = 1;

    for (int i = 0; i < repeticoes; ++i) {
        auto inicio = chrono::high_resolution_clock::now();

        func(arr, n);

        auto fim = chrono::high_resolution_clock::now();
        chrono::duration<double> duracao = fim - inicio;
        totalDuracao += duracao.count();
    }
    cout << "Tempo medio de execucao para " << algoritmo << ": " << (totalDuracao / repeticoes) << " segundos\n";
}

int main() {
    // ALTERAR TAMANHO PARA QUE VOCE POSSA TESTAR COM n NUMEROS DE PRODUTOS
    int tamanho = 100000;

    RegistroVenda* registros = new RegistroVenda[tamanho];

    // Bolha
    gerarRegistros(registros, tamanho);
    medirTempoExecucao(bubbleSort, registros, tamanho, "Bolha");

    // Inserção
    gerarRegistros(registros, tamanho);
    medirTempoExecucao(insertionSort, registros, tamanho, "Insercao");

    // Seleção
    gerarRegistros(registros, tamanho);
    medirTempoExecucao(selectionSort, registros, tamanho, "Selecao");

    // Shell
    gerarRegistros(registros, tamanho);
    medirTempoExecucao(shellSort, registros, tamanho, "Shell");

    // Contagem
    gerarRegistros(registros, tamanho);
    medirTempoExecucao([&](RegistroVenda arr[], int n) { countingSort(arr, n, 10000); }, registros, tamanho, "Contagem");

    // QuickSort
    gerarRegistros(registros, tamanho);
    medirTempoExecucao([&](RegistroVenda arr[], int n) { quickSort(arr, 0, n - 1); }, registros, tamanho, "QuickSort");

    delete[] registros;

    return 0;
}

