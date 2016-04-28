# COS470-tp1

Na root do projeto é possível encontrar um *script bash* `compileAll.sh`. O mesmo foi desenvolvido para compilar todos os programas do trabalho de uma vez no Linux. Ele chama os *scripts bash* `compile.sh` das pastas inferiores que compilam os códigos presentes nas próprias pastas.

**O trabalho não foi testado em ambientes Windows ou OSX.**

Dentro de cada uma das pastas, há um README.md com explicações de como compilar os códigos presentes nas mesmas, além da explicação do funcionamento.

As aplicações executáveis após a compilação geral são:

	./signals/raiser/raiser <pid> <signal id>
	./signals/handler/handler <flag, 1 = bloqueante, 0 = não-bloqueante>
	./pipes/pipes <número de valores a serem gerados>
	./sockets/consumer <port>
	./sockets/consumer <server host> <server port> <número de valores a serem gerados>

