# Matrix.h

Biblioteca simples de manipulação de matrizes de valores `double` em C++.

## Quick Start

Obtenha os arquivos `matrix.cpp` e `matrix.h`, e use:

```c++
#include "matrix.h"

int main(int argc, char **argv) {
    Matrix m1(3, 3);
    m1.ones();
    std::cout << m1 << "\n";

    Matrix m2(3, 3);
    m2.unit();
    std::cout << m2 << "\n";

    Matrix m3 = m1 * m2;
    std::cout << (m1 == m3) << "\n"; // true

    return EXIT_SUCCESS;
}
```

## Documentação completa

### Construtor

O único construtor disponível recebe dois parâmetros inteiros, o número de linhas e o número de colunas (nessa ordem). Caso algum deles seja menor que 1, uma exceção do tipo `std::invalid_argument` será lançada. A matriz resultante automaticamente tem todas suas entradas inicializadas em zero.

Se não houver espaço suficiente em memória para inicialização, será lançada uma exceção do tipo `std::bad_alloc` (como de costume).

### Construtor cópia, atribuição cópia, destrutor e swap

Internamente, a matriz é armazenada usando um ponteiro para array de ponteiros para `double`. A implementação segue o padrão da [Rule of Three](https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)), portanto o usuário pode ficar tranquilo que não há nenhum *leaking* de memória ocorrendo.

Portanto, tanto o construtor cópia quanto o operador de atribuição por cópia (`operator=`) são disponibilizados normalmente. O destrutor também está implementado e garante que não haja *leaks* de memória.

Além disso, para a implementação adequada destes métodos, foi utilizado o [copy-and-swap idiom](https://stackoverflow.com/questions/3279543), e sendo assim fica automaticamente disponibilizado mais um método bastante útil para o usuário, o `void swap(Matrix& a, Matrix& b)`, para fazer o swap de duas matrizes.

### Getters e setters básicos

Os seguintes *getters* básicos são disponibilizados:

* `int Matrix::getRows() const;` que retorna o número de linhas da matriz.
* `int Matrix::getCols() const;` que retorna o número de colunas da matriz.
* `double get(int row, int col) const;` que retorna o conteúdo da célula na linha `row` e coluna `col`.

O operador `()` também é sobrecarregado para leitura de conteúdo, como no método `get()`, com a única diferença de que ele não é `const`, pois o mesmo operador pode ser usado como setter do conteúdo daquela célula, como no exemplo a seguir:

```c++
Matrix m(3, 4);
std::cout << m.getRows() << "\n"; // 3
std::cout << m.getCols() << "\n"; // 4
std::cout << m.get(1, 2) << "\n"; // 0
m(1, 2) = 5;
std::cout << m.get(1, 2) << "\n"; // 5
std::cout << m(1, 2) << "\n"; // 5
```

Além disso, os seguintes *setters* também estão disponíveis:

* `void zeros()`: altera todas as células da matriz para 0.
* `void ones()`: altera todas as células da matriz para 1.
* `void unit()`: se a matriz for quadrada, altera-a para a matriz unidade, isto é, altera todas as células da diagonal principal para 1 e o restante para 0. Caso a matriz não seja quadrada, uma exceção do tipo `std::logic_error` é lançada.

### Conversão para string e print

Para conversão para string, o método `std::string toJSON() const` é disponibilizada, em que a representação da matriz em formato [JSON](https://en.wikipedia.org/wiki/JSON) é retornada como string.

Além disso, a sobrecarga do operador `<<` está disponível como de costume, que automaticamente converte a matriz para string usando o método `toJSON()`:

```c++
Matrix m(2, 2);
m.unit();
std::cout << m; // "[[1,0],[0,1]]"
```

Também está disponível o método `void prettyPrint() const`, que printa o conteúdo da matriz de forma legível, linha por linha, com os valores arredondados para duas casas decimais.

### Operadores de comparação

Os operadores `==` e `!=` foram sobrecarregados. Duas matrizes são consideradas iguais se e somente se têm dimensões iguais e conteúdos iguais, célula por célula.

### Operadores aritméticos

Os operadores de soma (`+`, `+=`), subtração (`-` unário, `-` binário, `-=`) e multiplicação de matrizes (`*`, `*=`) estão disponíveis. A tentativa de operar com matrizes de forma inválida (por exemplo, somando matrizes de dimensões diferentes) causará o lançamento de uma exceção do tipo `std::invalid_argument`.

Além disso, o operador unário `~` foi sobrecarregado para retornar a matriz transposta da matriz dada.

### Licensa

MIT © Pedro Augusto de Paula Barbosa