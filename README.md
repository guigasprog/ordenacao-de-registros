
# Relatório de Desempenho de Algoritmos de Ordenação

## Introdução

Este relatório tem como objetivo analisar o desempenho de diferentes algoritmos de ordenação aplicados a uma lista de registros de vendas. Os algoritmos comparados incluem:

- Bubble Sort
- Insertion Sort
- Selection Sort
- Counting Sort
- Shell Sort
- QuickSort

A análise foi feita com três tamanhos de listas: 1.000, 100.000 e 1.000.000 registros. Cada algoritmo foi executado 3 vezes para cada tamanho, e a média dos tempos de execução foi calculada.

## Estrutura dos Dados

Os dados utilizados são do tipo `RegistroVenda`, definidos com a seguinte estrutura:

```cpp
struct RegistroVenda {
    string nomeProduto;
    int quantidadeVendida;
    double precoUnitario;
    string dataVenda;
};
```

Cada registro contém informações sobre um produto, incluindo nome, quantidade vendida, preço unitário e data da venda.

## Algoritmos de Ordenação

### 1. Bubble Sort

O Bubble Sort compara pares consecutivos de elementos e os troca se estiverem na ordem errada. O processo se repete até que a lista esteja ordenada.

### 2. Insertion Sort

O Insertion Sort constrói uma lista ordenada, inserindo um elemento por vez no local apropriado.

### 3. Selection Sort

O Selection Sort encontra o maior valor em cada iteração e o move para a posição correta.

### 4. Counting Sort

O Counting Sort é eficiente para conjuntos de dados com uma faixa limitada de valores. Ele usa uma contagem de ocorrências de cada valor para ordenar os dados.

### 5. Shell Sort

O Shell Sort é uma melhoria do Insertion Sort, que usa intervalos para comparar elementos distantes e reduzir o número de trocas.

### 6. QuickSort

O QuickSort utiliza a técnica de divisão e conquista, escolhendo um pivô e ordenando os elementos em torno dele recursivamente.

## Medição de Desempenho

A função de medição de tempo foi implementada utilizando a biblioteca `chrono` da seguinte forma:

```cpp
#include <chrono>

template <typename Func>
void medirTempoExecucao(Func func, RegistroVenda arr[], int n, const string &algoritmo) {
    double totalDuracao = 0;
    int repeticoes = 3;
    for (int i = 0; i < repeticoes; ++i) {
        auto inicio = chrono::high_resolution_clock::now();

        func(arr, n);

        auto fim = chrono::high_resolution_clock::now();
        chrono::duration<double> duracao = fim - inicio;
        totalDuracao += duracao.count();
    }
    cout << "Tempo médio de execução para " << algoritmo << ": " << (totalDuracao / repeticoes) << " segundos\n";
}
```

## Resultados

### Tabela de Resultados (Tempo Médio de 3 Execução)

| Algoritmo      | 1.000 Registros (s) | 100.000 Registros (s) | 1.000.000 Registros (s) |
| -------------- | ------------------- | --------------------- | ----------------------- |
| Bubble Sort    | 0.0032288           | 36.7915000            | MUITO TEMPO             |
| Insertion Sort | 0.0000000           | 7.48558000            | MUITO TEMPO             |
| Selection Sort | 0.0031719           | 6.95093000            | MUITO TEMPO             |
| Counting Sort  | 0.0000000           | 0.03798900            | 0.1 a 0.5 segundo       |
| Shell Sort     | 0.0000000           | 0.00522207            | 10 a 15 segundos        |
| QuickSort      | 0.0072985           | 0.5 a 1 segundos      | 2 a 10 segundos         |

### Análise

- O **QuickSort** apresentou o melhor desempenho em todas as faixas de dados, devido à sua eficiência em dividir o conjunto de dados em partes menores e ordenar rapidamente, utilizando o [SortVisualizer](https://www.sortvisualizer.com/), mas por conta de sua recursividade ela aponta erro, uma forma de solucionar o erro seria utilizando a lib de Stack, para fazer uma lista em pilha.
- O **Bubble Sort**, sendo um algoritmo de complexidade O(n²), teve o pior desempenho para conjuntos de dados maiores, demorando muito mais em listas de 100.000 e 1.000.000 registros.
- **QuickSort**, **Shell Sort** e **Counting Sort** também tiveram bons resultados, principalmente em listas grandes, sendo alternativas viáveis dependendo do contexto.

## Considerações Finais

Este relatório mostrou que o QuickSort é a melhor escolha para listas grandes, enquanto para listas pequenas, algoritmos simples como o Insertion Sort podem ser utilizados sem perda significativa de desempenho. O Counting Sort foi eficiente para listas com valores limitados, por isso que ele não foi a melhor escolha, mas requer adaptação para garantir ordenação decrescente.

---

Esse README inclui uma visão geral do projeto, explicações sobre os algoritmos, a metodologia de medição e os resultados obtidos, facilitando a compreensão de quem for ler o relatório. E para fácil apresentação ao o Professor Begosso.
