# Pipes

Realizamos a compilação com `g++ main.cpp -o pipes -std=c++11`.

A aplicação `pipes` abre um processo que sofre um `fork()`, dando origem a dois processos conectados por um pipe, funcionando num esquema *Produtor-Consumidor*. A ponta de escrita (produtor) gera uma sequência aleatória crescente de **N** valores inteiros e os escreve no pipe, escrevendo o valor `0` ao final. A ponta de leitura (consumidor) lê os valores escritos no pipe, verifica se os mesmos são primos e imprime o resultado da verificação.

O número **N** de valores inteiros gerados é passado como argumento para a aplicação. Exemplo: `./pipes 10` vai gerar 10 valores.