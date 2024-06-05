#!/bin/bash
data=$(date +%Y-%m-%d)
miesiac=${data:6:1}
if [ $miesiac -ge 3 && $miesiac -le 5 ]; then
  poraRoku="Wiosna"
else
  poraRoku="Zima"
fi

# Wyświetlenie wyniku
echo "Data: $data"
echo "Pora roku: $poraRoku"
