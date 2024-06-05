echo "Siema $1"
let zm=$2+3
echo "Liczba $zm"

read liczba

echo "Witam "$((liczba+10))

echo "Y / N"
read yesno

if [[ $yesno == "Y" ]]; then 
    echo "TAAAAAK"
elif [[ $yesno == "N" ]]; then 
    echo "NOOOOOOOOOO"
else
    echo "?????????"
fi
