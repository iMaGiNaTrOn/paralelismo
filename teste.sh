#!/bin/bash
for ((i=0; i<10; i++)); do
	./trabalho.x 15000 1
done

for ((i=0; i<10; i++)); do
	for ((j=2; j<=32;j+=2)); do
		./trabalho.x 15000 $j
	done
done
