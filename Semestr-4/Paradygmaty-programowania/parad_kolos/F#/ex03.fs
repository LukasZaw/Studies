open System

let rec Wariacja (n : float) (k : float) = 
    if k = 0.0 then
        1.0
    elif k > n then
        0.0
    else
        n * Wariacja (n-1.0) (k-1.0)

Wariacja 5 3