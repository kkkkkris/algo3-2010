#!/bin/bash

MAX_ITER_LIST="5 10 20 30 40 50"
MAX_TABU_LIST="20 50 100 200"
ROOT="../cliques/entradas/"

echo "iniciando testing..."

for archivo in $(ls $ROOT)
do
	rm $ROOT$archivo".test"
	touch $ROOT$archivo".test"
	
	for lt in $MAX_TABU_LIST
	do
		#for k in $MAX_ITER_LIST
		#do		
		#	echo "archivo: "$ROOT$archivo" modo p maxIter: "$k" maxTabu: "$lt
		#	./ts $ROOT$archivo out $k p $lt >> $ROOT$archivo".test"
		#done

		for k in $MAX_ITER_LIST
		do
			echo "archivo: "$ROOT$archivo" modo s maxIter: "$k" maxTabu: "$lt
			./ts $ROOT$archivo out $k s $lt >> $ROOT$archivo".test"
		done
	done
done
echo "testing finalizando!"
