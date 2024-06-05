#!/bin/bash

# Wyświetlanie plików z prawem do odczytu
echo "Pliki z prawem do odczytu:"
for file in *; do
  [ -r "$file" ] && echo "$file"
done
echo

# Wyświetlanie plików z prawem do zapisu
echo "Pliki z prawem do zapisu:"
for file in *; do
  [ -w "$file" ] && echo "$file"
done
echo

# Wyświetlanie plików z prawem do wykonania
echo "Pliki z prawem do wykonania:"
for file in *; do
  [ -x "$file" ] && echo "$file"
done