#!/bin/bash

# Sprawdzenie, czy podano dwa argumenty
if [ $# -ne 2 ]; then
  echo "Użycie: $0 źródło cel"
  echo "Podaj dokładnie dwa argumenty: plik źródłowy i lokalizację docelową."
  exit 1
fi

# Zmienna dla pliku źródłowego
src=$1
# Zmienna dla pliku docelowego
dst=$2

cp "$src" "$dst"

rm "$src"

echo "Plik został przeniesiony z '$src' do '$dst'."