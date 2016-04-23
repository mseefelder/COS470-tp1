#! /bin/bash

echo "Compiling signal codes"
echo "Raiser: "

cd raiser
./compile.sh
cd ..

echo "Handler: "

cd handler
./compile.sh
cd ..
