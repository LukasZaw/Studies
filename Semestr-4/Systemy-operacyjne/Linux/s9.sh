for i in * ; do
    if [ -f $i ] ; then
        echo $i jest plikiem    
    elif [ -d $i ] ; then
        echo $i jest katalogiem
    else
        echo $i jest czyms innym
    fi
done
