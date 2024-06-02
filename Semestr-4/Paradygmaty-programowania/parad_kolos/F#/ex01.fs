open System

let rec RzutNRazy n =
    if n > 1 then
        RzutNRazy (n-1) + (1.0/216.0) 
    elif n=1 then
        (1.0/216.0)//prawdopodobieństwo przy jednym rzucie
    else    
        0.0

let r = 100
let prawdo = RzutNRazy r * 100.0
Console.WriteLine($"Prawdopodobienstwo dla {r} rzutów wynosi: {prawdo} ")