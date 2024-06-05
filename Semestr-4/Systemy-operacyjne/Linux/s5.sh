#!/bin/bash
suma=0

if [ $# -eq 3 ]; then 
    suma=$(($1+$2+$3))
    echo "Suma: " $suma
else
    echo "Liczba param rozna od 3"
    exit 1
fi

