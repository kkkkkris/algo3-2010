#!/bin/bash

MAX_ITER_LIST="5 10 20 30 40 50"
MAX_TABU_LIST="20 50 100 200"

echo "iniciando testing..."

for lt in $MAX_TABU_LIST
do
    for k in $MAX_ITER_LIST
    do
        rm "tests_resultados"
        touch "tests_resultados"
        echo "modo p - maxIter: "$k" maxTabu: "$lt
        ./ts $k p $lt >> "tests_resultados"
    done

    for k in $MAX_ITER_LIST
    do
        rm "tests_resultados"
        touch "tests_resultados"
        echo "modo s - maxIter: "$k" maxTabu: "$lt
        ./ts $k s $lt >> "tests_resultados"
    done
done
echo "testing finalizando!"
