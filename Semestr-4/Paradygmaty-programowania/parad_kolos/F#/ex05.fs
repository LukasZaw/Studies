open System

let ProOblicz a b =
    let Pole = a*b
    let Obw = 2*a + 2*b
    (Pole, Obw)

let wynik = ProOblicz 2 4

printfn $"Pole: {fst wynik}, Obw: {snd wynik}"