#!/bin/bash

# Pętla select
select opt in "Opcja 1" "Opcja 2" "Opcja 3" "Opcja 4" "Opcja 5" "Opcja 6" "Opcja 7 - Zakończ" "Opcja 8" "Opcja 9" "Opcja 10" "Opcja 11" "Opcja 12"
do
  if [ "$REPLY" -eq 7 ]; then
    echo "Wybrałeś opcję 7 - Zakończ. Koniec pętli."
    break
  else
    echo "Wybrałeś opcję: $opt"
  fi
done