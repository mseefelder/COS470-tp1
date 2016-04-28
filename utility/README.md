# Utility

## isPrime.h

A função de verificação do número Primo foi implementada de forma que pudesse ser reaproveitada pela aplicação do Sockets. De maneira simples,o funcionamento da verificação pode ser descrita :

*  Verifica se o número $N$ é divisível por 2 ou por 3, eliminando assim uma grande quantidade de números possíveis,
*  Caso passem por esse teste, começamos a verificar a divisibilidade por outros números a partir do 5.
* Levando em conta que números primos são da forma $K = (6 \times K \pm 1)$ (mas nem todos os números dessa forma são primos), tentamos a divisão por todos os inteiros $I$ dessa forma que encontramos até que $I^2 > K$;
    * Caso seja encontrado um $I$ pelo qual $N$ é divisível, $N$ não é primo;
    * Caso contrário, o é.
