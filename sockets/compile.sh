#! /bin/bash

echo "Compiling Producer..."

g++ client.cpp -o producer -std=c++11

echo "Compiling Consumer..."

g++ server.cpp -o consumer -std=c++11