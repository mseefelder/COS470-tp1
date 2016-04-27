#! /bin/bash

echo "Compiling Signals Assignment..."

cd signals
./compile.sh
cd ..

echo "Compiling Pipes Assignment..."

cd pipes
./compile.sh
cd ..

echo "Compiling Sockets Assignment..."

cd sockets
./compile.sh
cd ..
