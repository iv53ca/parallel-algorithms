#!/bin/bash

# Компилируем программу
mpicc -o Integral parallel_integration.c -lm

# Очищаем файл результатов, если он существует
echo "" > results.txt

# Запускаем программу с количеством процессов от 1 до 28
for i in {1..28}
do
    echo "Running with $i processes..." >> results.txt
    (time mpirun -np $i --map-by :OVERSUBSCRIBE ./Integral 10000) 2>&1 | awk '/real/ {gsub("0m", "", $2); gsub("s", "", $2); print "Time: " $2}' >> results.txt
done
