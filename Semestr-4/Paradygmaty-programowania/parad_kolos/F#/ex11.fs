open System

let generuj n =
    let rnd = Random()
    [for i in 0 .. n -> (rnd.Next(-20, 21), rnd.Next(-20,21))]


let odleglosc (x, y) = 
    sqrt (float(x*x + y*y))

let punkty = generuj 10

let odlegloscDlaPkt = List.map odleglosc punkty

odleglosc punkty

