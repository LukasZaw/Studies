for i in `seq 1 1 15` ; do
    zm=$(( $i % 2))
    if [ $zm -eq 1 ]; then
        echo $i
        mkdir kat$i
    fi
done