#!/bin/bash

# Ścieżka do pliku .bash_history
history_file="$HOME/.bash_history"

# Sprawdzenie, czy plik .bash_history istnieje
if [ ! -f "$history_file" ]; then
  echo "Plik .bash_history nie istnieje."
  exit 1
fi

# Wyszukiwanie polecenia cat w pliku .bash_history i wyświetlanie wyników
echo "Wystąpienia polecenia 'cat' w pliku .bash_history:"
grep "cat" "$history_file"