#!/bin/sh

#for i in $(seq 20)
#do
#	./adhocSim.exe 250 50 5
#done
echo "NODES: 250 | MATRIX: 50 | CHANNELS: 5"  
./adhocSim.exe 250 50 5
echo "NODES: 250 | MATRIX: 50 | CHANNELS: 10"  
./adhocSim.exe 250 50 10
echo "NODES: 250 | MATRIX: 50 | CHANNELS: 20"  
./adhocSim.exe 250 50 20

echo "DONE"
