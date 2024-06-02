type Lista<'a> = 
    |Pusta
    |Wezel of 'a*Lista<'a>

let lista1 = Wezel (1, Wezel (2, Wezel (3, Wezel (4, Pusta))))
let lista2 = Wezel (2, Wezel (3, Wezel (4, Wezel (5, Pusta))))

let rec SumujListy lista1 lista2 = 
    match lista1, lista2 with
    | Wezel(glowa1, ogon1), Wezel(glowa2, ogon2) -> Wezel(glowa1+glowa2, SumujListy ogon1 ogon2)
    | Pusta, Pusta -> Pusta
    | _ -> failwith "nie rowne listy"

SumujListy lista1 lista2