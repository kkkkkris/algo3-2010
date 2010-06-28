 #!/bin/bash

MAX_ITER_LIST="100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700"
root="casos_test/"

echo "iniciando testing..."

for grafo in $(ls $root)
do
	echo $root$grafo
	echo $grafo >> test_resultado
	for k in $MAX_ITER_LIST
	do
		echo $k
		./ts $root$grafo resultado $k >> test_resultado
	done
done

echo "testing finalizando!"
