#!/bin/bash

folder="."

files=($(ls -p $folder | grep -v /))

options=("Koniec" "${files[@]}")

select opt in "${options[@]}"
do
  if [ "$opt" == "Koniec" ]; then
    echo "Zakończenie działania skryptu."
    break
  elif [[ -n "$opt" ]]; then
    # Tworzenie kopii wybranego pliku z rozszerzeniem .cpy
    cp "$folder/$opt" "$folder/$opt.cpy"
    echo "Utworzono kopię pliku: $opt.cpy"
  else
    echo "Nieprawidłowy wybór. Spróbuj ponownie."
  fi
done