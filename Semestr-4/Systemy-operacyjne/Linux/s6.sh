echo "Podaj 2 liczby"
read x1
read x2

echo "podaj działanie"
read dz

case $dz in 
    "1") echo "Dod: "$(($x1+$x2));;
    "2") echo "Ode: "$(($x1-$x2));;

    *) echo "domysle";;
esac

