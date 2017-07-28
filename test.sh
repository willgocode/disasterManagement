#!/bin/sh
echo Hello World
counter=1
echo $counter

#while [ $counter != 20 ] 
#do
#	echo "Looping."
#	$counter=$counter + 1
#done

for i in $(seq 20)
do
	./adhocSim.exe 250 50 5
done
