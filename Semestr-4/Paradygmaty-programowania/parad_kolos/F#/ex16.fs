type Lista<'a> = 
    |Pusta
    |Wezel of 'a*Lista<'a>

let rec spelniaWarunek warunek lista =
    match lista with
    | Pusta -> true
    | Wezel(head, tail) ->
        if warunek head then 
            spelniaWarunek warunek tail
        else 
            false

let warunek x = x % 2 = 0

let lista = Wezel(-4,Wezel(2,Wezel(4,Wezel(-8,Wezel(0,Pusta)))))
let wynik = spelniaWarunek warunek lista