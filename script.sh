#!/bin/bash
for i in {1..10}
do
	./a.out
	python3 viz.py "$i"
done
