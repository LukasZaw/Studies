echo "wybierz od 1 do 3"
x=1

read liczba

case $liczba in 
    1) echo "jeden"
    let x=10;;
    2) echo "dwa"
    x=20;;
    3) echo "trzy";;
esac

wypisz()
{
    echo "Wypisuje:"
    echo $1
}

wypisz $x

for (( i=1; $i <= $x; i++ )); do
    wypisz $i
done

