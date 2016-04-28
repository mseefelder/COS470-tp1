# Signals

Entrando nas respectivas pastas, foram compilados da seginte maneira:

* Handler: `g++ signalHandler.cpp -o handler`
* Raiser: `g++ main.cpp -o raiser`

`./handler/handler <flag>` recebe como argumento uma *flag* que pode ser apenas 0 ou 1. A aplicação define um conjunto de sinais a ser trataco por um signal handler que imprime o número do sinal que recebeu e então passa a aguardar pelo sinal. A *flag* define se a espera é *ocupada* (flag = `0`) ou *bloqueante* (flag = `1`)

`./raiser/raiser <pid> <signal>` permite enviar um sinal `signal` a um processo referenciado pelo pid `pid`.