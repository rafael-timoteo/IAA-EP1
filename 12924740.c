/*********************************************************************/
/**   ACH2002 - Introducao à Análise de Algoritmos                  **/
/**   EACH-USP - Segundo Semestre de 2022                           **/
/**   Turma extra - Prof. Marcos Lordello Chaim                     **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   <Rafael Francisco de Freitas Timoteo>     <12924740>          **/
/**                                                                 **/
/*********************************************************************/


#include <stdio.h>

/*
subMaxArray() é uma função iterativa que retorna o valor da soma dos
elementos da  subsequência máxima de um outro arranjo chamado x.
Além disso, retorna por referência os arranjos com a subsequência
máxima e o sufixo máximo.

Parâmetros:
x : o ponteiro para o arranjo para o qual será determinada a subsequência máxima;
n : tamanho de x;
sfmarray : ponteiro para o arranjo com os elementos que formam o sufixo máximo;
nsfm : ponteiro para a variável que contém o tamanho de sfmarray;
gbmarray : ponteiro para o arranjo com os elementos que formam a subsequência máxima;
ngbm : ponteiro para a variável que contém o tamanho de gbmarray.

Valor de retorno: soma da subsequência máxima.

*/
double subMaxArray(double *x, int n, double * sfmarray, int * nsfm, double * gbmarray, int * ngbm) {
  double globalmax = 0, sufixmax = 0;
  *nsfm = 0;
  *ngbm = 0;

  for(int i = 0; i < n; i++) {
    if(x[i] + sufixmax > globalmax)
    {
      sufixmax = x[i] + sufixmax;
      globalmax = sufixmax;
      sfmarray[*nsfm] = x[i];
      (*nsfm)++;
      for(int j = 0; j < *nsfm; j++){
        gbmarray[j] = sfmarray[j];
        *ngbm = *nsfm;
      }
    }
    else
    {
      if(x[i] + sufixmax > 0)
      {
        sufixmax = x[i] + sufixmax;
        sfmarray[*nsfm] = x[i];
        (*nsfm)++;
      }
      else
      {
        sufixmax = 0;
        *(nsfm) = 0;
      }
    }
  }

return globalmax;
}


/*
rsubMaxArray() é uma função recursiva que retorna o valor da soma dos
elementos da  subsequência máxima de um outro arranjo chamado x.
Além disso, retorna por referência os arranjos com a subsequência
máxima e o sufixo máximo.

Parâmetros:
x : o ponteiro para o arranjo para o qual será determinada a subsequência máxima;
n : tamanho de x;
sfm : ponteiro para a variável que contém o soma dos elementos do arranjo com  sufixo máximo;
sfmarray : ponteiro para o arranjo com os elementos que formam o sufixo máximo;
nsfm : ponteiro para a variável que contém o tamanho de sfmarray;
gbmarray : ponteiro para o arranjo com os elementos que formam a subsequência máxima;
ngbm : ponteiro para a variável que contém o tamanho de gbmarray.

Valor de retorno: soma da subsequência máxima.
*/


double rsubMaxArray(double *x, int n,  double * sfm, double * sfmarray, int * nsfm, double * gbmarray, int * ngbm) {
  double globalmax;

  if(n <= 0)
  {
    *sfm = 0;
    *ngbm = 0;
    *nsfm = 0;
    printf("n = 0 Globalmax: %f\n", 0.0);
    printf("n = 0 Sufixmax: %f\n", 0.0);
    return 0;
  }
  else {
    globalmax = rsubMaxArray(x, n-1, sfm, sfmarray, nsfm, gbmarray, ngbm);
    if(x[n-1] + (*sfm) > globalmax)
    {
      (*sfm) = x[n-1] + (*sfm);
      globalmax = (*sfm);
      sfmarray[*nsfm] = x[n-1];
      (*nsfm)++;
      for(int j = 0; j < *nsfm; j++){
        gbmarray[j] = sfmarray[j];
        *ngbm = *nsfm;
      }
    }
    else {
      if (x[n-1] + (*sfm) > 0){
        (*sfm) = x[n-1] + (*sfm);
        sfmarray[*nsfm] = x[n-1];
        (*nsfm)++;
      }
      else{
        (*sfm) = 0;
        *(nsfm) = 0;
      }
    }
  }
  printf("n = %d, Globalmax: %f\n", n, globalmax);
  printf("n = %d, Sufixmax: %f\n", n, (*sfm));
  return globalmax;
}

/*
Heap máximo (mínimo) é uma estrutura de dados que pode ser vista como uma árvore
binária com a seguinte propriedade: os nós filhos possuem valores menores (maiores)
ou iguais aos do nó pai.

Exemplo:
16 (raiz)
├─ 10 (direita)
|   ├─ 3 (direita)
|   ├─ 9 (esquerda)
├─ 14 (esquerda)
    ├─ 7 (direita)
    |  ├─ 1 (direita)
    ├─ 8 (esquerda)
       ├─ 2 (direita)
       ├─ 4 (esquerda)


O exemplo acima é de um heap máximo. Veja que o nó (raiz) 16 possui dois
filhos 10 e 14; 10 também possui dois filhos, 3 e 9, que não possuem filhos; e
14 possui dois filhos, 7 e 8. O nó 8  possui dois filhos: 2 e 4,
que não possuem filhos. Finalmente, o nó 7 possui apenas um filho, nó 1,
que não possui filhos. Observe que os filhos possuem valores menores ou
iguais ao do nó pai.

Do lado de cada filho está informado se ele está à direita ou à esquerda
do nó pai. O primeiro nó, 16, é a raiz.

Podemos representar o heap máximo acima como um arranjo, por exemplo,:
int array [] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};

array[0] = 16 é a raiz do heap; seus filhos são array[1] = 14, que é
a raiz da subárvore à esquerda de 16,  e array[2] = 10, que é a raiz da
subárvore à direita de 16. array[5] = 9 é o filho à esquerda de array[2] = 10
e array[6] = 3 é o filho à direita de array[2] = 10.
De modo inverso, array[2] = 10 é o pai de array[5] = 9 e array[6] = 3.
Utilizando as mesmas regras, é possível obter os filhos e o pai de cada nó do heap.

Nesse exemplo, o array possui tamanho 10 (tamArray = 10)e o heap máximo
que ele representa também possui tamanho 10 (compHeap = 10).

Mas não precisa ser sempre assim. A propriedade geral de um heap é que:
comprimento do heap (compHeap) <= tamanho do arranjo que armazena o heap (tamArray).

O mesmo exemplo poderia ser implementado pelo arranjo abaixo.

int array2 [] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1, 0, 3, 4, 5, 12};
onde o compHeap é 10 e tamArray é 15.

Portanto, os elementos válidos para a estrutura heap vão de 0 ... até compHeap - 1.
Os demais elementos do array (compHeap ... tamArray-1) não fazem parte do heap.

Use a descrição acima para criar as funções a seguir.
*/

/*
pai() é uma função que retorna o índice do pai de um nó do heap.

Parâmetro:

i: índice do nó do heap.

Valor de retorno: índice do nó do heap que é pai do índice i passado
como parâmetro.

*/

int pai(int i) {

return (i-1)/2;
}

/*
esquerda() é uma função que retorna o índice do filho de um nó do heap
que está à sua esquerda.

Parâmetro:

i: índice do nó do heap.

Valor de retorno: índice do nó do heap que é filho à esquerda do índice i passado
como parâmetro.

*/

int esquerda(int i) {

return 2*i+1;
}

/*
direita() é uma função que retorna o índice do filho de um nó do heap
que está à sua direita.

Parâmetro:

i: índice do nó do heap.

Valor de retorno: índice do nó do heap que é filho à direita do índice i passado
como parâmetro.

*/

int direita(int i) {

return 2*(i+1);
}

/*
 verificaHeapMax() é uma função que verifica se os elementos de um array constituem
 um heap máximo, ou seja, os filhos de cada nó são menores ou iguais ao nó pai.

 Parâmetros:

 array : arranjo que possivelmente contém um heap máximo.
 inicio: índice do elemento do array a partir de onde começará a verificação da
 propriedade de heap máximo
 compHeap: comprimento do heap máximo
 n: tamanho do array.

 Valor de retorno: 1, se for heap máximo; 0, caso contrário. Se o comprimento
 do  heap (compHeap) for maior ou igual ao tamanho do arranjo (n), então não é um
 heap e, portanto, deve-se retornar o valor 0.

 Dica: Lembre-se de que os filhos de um nó de um heap máximo são também a raiz
 de um heap máximo.

*/

int verificaHeapMax(int * array, int inicio, int compHeap, int n) {

  if(compHeap >= n || compHeap < 1){
    return 0;
  }
  for(int i = compHeap; i > 0; i--)
 {
    if (array[esquerda(inicio)] > array[inicio]){
      return 0;
    }
    if (array[direita(inicio)] > array[inicio]){
      return 0;
    }
    inicio = inicio + 1;
 }
 return 1;
}

/*
onde() uma função recursiva que recebe um inteiro x, um arranjo v de inteiros e
inteiros ini e fim e devolve j tal  que ini ≤ j ≤ fim-1 e v[j] é igual a x;
se tal j não existe então devolve ini-1.

Parâmetros:

x :  inteiro
v : arranjo de inteiros
ini :  início do espaço de busca em v
fim : fim do espaço de busca em v

valor de retorno: inteiro j tal  que ini ≤ j ≤ fim-1 e v[j] é igual a x;
se tal j não existe então devolve ini-1.
*/

int onde(int x, int * v, int ini, int fim) {
  int j;

  if (ini > fim)
  {
    return ini-1;
  }
  if(v[fim-1] == x){
    j = fim-1;
    if(ini <= j && j <= fim-1){
      return j;
    }
    else
      return ini-1;
  }

return onde(x, v, ini, fim-1);
}

/*
	função main criada apenas para seus testes.
  Os testes abaixo são apenas ilustrativos.
  A correção será realizada com testes diferentes.
	Voce deve adicionar novos testes que testem
  o mais completamente possível seu código.
	ESTA função SERA IGNORADA NA CORRECAO
*/

int main() {
    int i, noErros = 0, noTestes = 0;
    double a[] ={2,-3, 1.5, -1, 3, -2, -3, 3};
    double b[] ={2,-3, -1.5, -1, -3, -2, -3, 3};
    double c[] ={-2,-3, -1.5, -1, -3, -2, -3, -3};

    double globalmax = -1, sufixmax = -1;
    double globalmax_array[8], sufixmax_array[8];
    int n_globalmax_array = -1, n_sufixmax_array = -1;

    printf("Vetor: [");
    for(i = 0; i < 8; ++i)
      printf("%3.2f ", a[i]);
    printf("]\n");


    globalmax = subMaxArray(a,8,sufixmax_array,&n_sufixmax_array, globalmax_array,&n_globalmax_array);

    printf("subMaxArray:\n");
    printf("Globalmax: %3.2f\n", globalmax);
    printf("Subsequência máxima correta: [ ");
    for(i = 0; i < n_globalmax_array; ++i)
      printf("%3.2f ", globalmax_array[i]);
    printf("]\n");

    noTestes++;
    if(globalmax == 3.5)
       {
         printf("Teste %d: OK\n", noTestes);
       }
    else {
      printf("Teste %d: NOK: globalmax correta 3.5\n",noTestes);
      noErros++;
    }

    noTestes++;
    if(globalmax_array[0] == 1.5 && globalmax_array[1] == -1.0 &&
      globalmax_array[2] == 3.0)
       {
         printf("Teste %d: OK\n", noTestes);
       }
    else {
      printf("Teste %d: NOK: ",noTestes);
      printf("Subsequência máxima correta: [ 1.50 -1.00 3.00 ]\n");
      noErros++;
    }

    printf("Sufixo máximo: [ ");
    for(i = 0; i < n_sufixmax_array; ++i)
      printf("%3.2f ", sufixmax_array[i]);
    printf("]\n");

    noTestes++;
    if(sufixmax_array[0] ==  3.0)
       {
         printf("Teste %d: OK\n", noTestes);
       }
    else {
      printf("Teste %d: NOK: ",noTestes);
      printf("Sufixo máximo correto: [ 3.00 ]\n");
      noErros++;
    }


    printf("Vetor: [");
    for(i = 0; i < 8; ++i)
      printf("%3.2f ", b[i]);
    printf("]\n");
    globalmax = subMaxArray(b,8,sufixmax_array,&n_sufixmax_array, globalmax_array,&n_globalmax_array);

    printf("subMaxArray:\n");
    printf("Globalmax: %3.2f\n", globalmax);
    printf("Subsequência máxima: [ ");

    for(i = 0; i < n_globalmax_array; ++i)
      printf("%3.2f ", globalmax_array[i]);
    printf("]\n");

    printf("Sufixo máximo: [ ");
    for(i = 0; i < n_sufixmax_array; ++i)
      printf("%3.2f ", sufixmax_array[i]);
    printf("]\n");

    noTestes++;
    if(globalmax == 3.0)
       {
         printf("Teste %d: OK\n", noTestes);
       }
    else {
      printf("Teste %d: NOK: globamax correta 3.0\n",noTestes);
      noErros++;
    }

    noTestes++;
    if(globalmax_array[0] ==  3.0)
       {
         printf("Teste %d: OK\n", noTestes);
       }
    else {
      printf("Teste %d: NOK: ",noTestes);
      printf("Subsequência máxima correta: [ 3.00 ]\n");
      noErros++;
    }

    printf("Sufixo máximo: [ ");
    for(i = 0; i < n_sufixmax_array; ++i)
      printf("%3.2f ", sufixmax_array[i]);
    printf("]\n");

    noTestes++;
    if(sufixmax_array[0] ==  3.0)
       {
         printf("Teste %d: OK\n", noTestes);
       }
    else {
      printf("Teste %d: NOK: ",noTestes);
      printf("Sufixo máximo correto: [ 3.00 ]\n");
      noErros++;
    }


    printf("Vetor: [");
    for(i = 0; i < 8; ++i)
          printf("%3.2f ", c[i]);
    printf("]\n");
    globalmax = subMaxArray(c,8,sufixmax_array,&n_sufixmax_array, globalmax_array,&n_globalmax_array);

    printf("subMaxArray:\n");
    printf("Globalmax: %3.2f\n", globalmax);
    printf("Subsequência máxima: [ ");

    for(i = 0; i < n_globalmax_array; ++i)
          printf("%3.2f ", globalmax_array[i]);
    printf("]\n");

    printf("Sufixo máximo: [ ");
    for(i = 0; i < n_sufixmax_array; ++i)
          printf("%3.2f ", sufixmax_array[i]);
    printf("]\n");

    noTestes++;
    if(globalmax == 0.0)
       {
         printf("Teste %d: OK\n", noTestes);
       }
    else {
      printf("Teste %d: NOK: sufixmax correta 0.0\n",noTestes);
      noErros++;
    }

    noTestes++;
    if(n_globalmax_array ==  0)
     {
      printf("Teste %d: OK\n", noTestes);
     }
    else {
      printf("Teste %d: NOK: ",noTestes);
      printf("Subsequência máxima correta: [ ]\n");
      noErros++;
    }

    printf("Sufixo máximo: [ ");
    for(i = 0; i < n_sufixmax_array; ++i)
          printf("%3.2f ", sufixmax_array[i]);
    printf("]\n");

    noTestes++;
    if(n_sufixmax_array ==  0)
      {
      printf("Teste %d: OK\n", noTestes);
      }
    else {
      printf("Teste %d: NOK: ",noTestes);
      printf("Sufixo máximo correto: [ ]\n");
      noErros++;
      }

  printf("Vetor: [");
  for(i = 0; i < 8; ++i)
          printf("%3.2f ", a[i]);
  printf("]\n");

  globalmax = rsubMaxArray(a,8,&sufixmax,sufixmax_array,&n_sufixmax_array, globalmax_array,&n_globalmax_array);

  printf("rsubMaxArray:\n");
  printf("Globalmax: %3.2f\n", globalmax);
  printf("Sufixmax: %3.2f\n", sufixmax);
  printf("Subsequência máxima correta: [ ");
  for(i = 0; i < n_globalmax_array; ++i)
          printf("%3.2f ", globalmax_array[i]);
  printf("]\n");

  noTestes++;
  if(globalmax == 3.5)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: globalmax correta 3.5\n",noTestes);
    noErros++;
    }

  noTestes++;
  if(sufixmax == 3.0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: sufixmax correta 3.0\n",noTestes);
    noErros++;
    }

  noTestes++;
  if(globalmax_array[0] == 1.5 && globalmax_array[1] == -1.0 &&
      globalmax_array[2] == 3.0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: ",noTestes);
    printf("Subsequência máxima correta: [ 1.50 -1.00 3.00 ]\n");
    noErros++;
  }

  printf("Sufixo máximo: [ ");
  for(i = 0; i < n_sufixmax_array; ++i)
          printf("%3.2f ", sufixmax_array[i]);
  printf("]\n");

  noTestes++;
  if(sufixmax_array[0] ==  3.0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: ",noTestes);
    printf("Sufixo máximo correto: [ 3.00 ]\n");
    noErros++;
  }

  printf("Vetor: [");
  for(i = 0; i < 8; ++i)
          printf("%3.2f ", b[i]);
  printf("]\n");
  globalmax = rsubMaxArray(b,8,&sufixmax,sufixmax_array,&n_sufixmax_array, globalmax_array,&n_globalmax_array);

  printf("rsubMaxArray:\n");
  printf("Globalmax: %3.2f\n", globalmax);
  printf("Sufixmax: %3.2f\n", sufixmax);

  printf("Subsequência máxima: [ ");
  for(i = 0; i < n_globalmax_array; ++i)
          printf("%3.2f ", globalmax_array[i]);
  printf("]\n");

  printf("Sufixo máximo: [ ");
  for(i = 0; i < n_sufixmax_array; ++i)
          printf("%3.2f ", sufixmax_array[i]);
  printf("]\n");

  noTestes++;
  if(globalmax == 3.0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: globalmax correta 3.0\n",noTestes);
    noErros++;
    }

  noTestes++;
  if(sufixmax == 3.0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: sufixmax correta 3.0\n",noTestes);
    noErros++;
    }

  noTestes++;
  if(globalmax_array[0] ==  3.0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: ",noTestes);
    printf("Subsequência máxima correta: [ 3.00 ]\n");
    noErros++;
  }

  printf("Sufixo máximo: [ ");
  for(i = 0; i < n_sufixmax_array; ++i)
          printf("%3.2f ", sufixmax_array[i]);
  printf("]\n");

  noTestes++;
  if(sufixmax_array[0] ==  3.0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: ",noTestes);
    printf("Sufixo máximo correto: [ 3.00 ]\n");
    noErros++;
  }

  printf("Vetor: [");
  for(i = 0; i < 8; ++i)
      printf("%3.2f ", c[i]);
  printf("]\n");

  globalmax = rsubMaxArray(c,8,&sufixmax,sufixmax_array,&n_sufixmax_array, globalmax_array,&n_globalmax_array);

  printf("rsubMaxArray:\n");
  printf("Globalmax: %3.2f\n", globalmax);
  printf("Sufixmax: %3.2f\n", sufixmax);

  noTestes++;
  if(globalmax == 0.0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: globalmax correta 0\n",noTestes);
    noErros++;
    }

  noTestes++;
  if(sufixmax == 0.0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: sufixmax correta 0.0\n",noTestes);
    noErros++;
    }

  printf("Subsequência máxima: [ ");

  for(i = 0; i < n_globalmax_array; ++i)
      printf("%3.2f ", globalmax_array[i]);
  printf("]\n");

  printf("Sufixo máximo: [ ");
  for(i = 0; i < n_sufixmax_array; ++i)
      printf("%3.2f ", sufixmax_array[i]);
  printf("]\n");

  noTestes++;
  if(n_globalmax_array ==  0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: ",noTestes);
    printf("Subsequência máxima correta: [ ]\n");
    noErros++;
  }

  printf("Sufixo máximo: [ ");
  for(i = 0; i < n_sufixmax_array; ++i)
      printf("%3.2f ", sufixmax_array[i]);
  printf("]\n");

  noTestes++;
  if(n_sufixmax_array ==  0)
    {
    printf("Teste %d: OK\n", noTestes);
    }
  else {
    printf("Teste %d: NOK: ",noTestes);
    printf("Sufixo máximo correto: [ ]\n");
    noErros++;
  }

  int array2 [] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1, 0, 3, 4, 5, 12};
  int compHeap = 10;
  int tamArray2 = 15;

  printf("Arranjo: [ ");
  for(i = 0; i < tamArray2; ++i)
      printf("%d ", array2[i]);
  printf("]\n");

  printf("É heap max: %s\n", verificaHeapMax(array2,0,1,15)?"Sim!":"Não!");

  noTestes++;
  if(verificaHeapMax(array2,0,1,15))
       {
         printf("Teste %d: OK\n", noTestes);
       }
  else {
      printf("Teste %d: NOK: é um heap máximo\n",noTestes);
      noErros++;
  }
  noTestes++;
  if(array2[pai(4)] == 14)
       {
         printf("Teste %d: OK\n", noTestes);
       }
  else {
      printf("Teste %d: NOK: o pai é 14\n",noTestes);
      noErros++;
  }

  noTestes++;
  if(array2[pai(9)] == 7)
       {
         printf("Teste %d: OK\n", noTestes);
       }
  else {
      printf("Teste %d: NOK: o pai é 7\n",noTestes);
      noErros++;
  }

  noTestes++;
  if(array2[direita(2)] == 3)
       {
         printf("Teste %d: OK\n", noTestes);
       }
  else {
      printf("Teste %d: NOK: o filho à direita é 3\n",noTestes);
      noErros++;
  }

  noTestes++;
  if(array2[esquerda(2)] == 9)
       {
         printf("Teste %d: OK\n", noTestes);
       }
  else {
      printf("Teste %d: NOK: o filho à esquerda é 9\n",noTestes);
      noErros++;
  }

  noTestes++;
  if(onde(9,array2,0,15) == 5)
       {
         printf("Teste %d: OK\n", noTestes);
       }
  else {
      printf("Teste %d: NOK: a posição correta: 5\n",noTestes);
      noErros++;
  }

  noTestes++;
  if(onde(9,array2,5,10) == 5)
       {
         printf("Teste %d: OK\n", noTestes);
       }
  else {
      printf("Teste %d: NOK: a posição correta: 5\n",noTestes);
      noErros++;
  }

  noTestes++;
  if(onde(9,array2,0,5) == -1)
       {
         printf("Teste %d: OK\n", noTestes);
       }
  else {
      printf("Teste %d: NOK: a posição correta: -1\n",noTestes);
      noErros++;
  }

  noTestes++;
  if(onde(9,array2,7,5) == 6)
       {
         printf("Teste %d: OK\n", noTestes);
       }
  else {
      printf("Teste %d: NOK: a posição correta: 6\n",noTestes);
      noErros++;
  }

  return 0;
}
