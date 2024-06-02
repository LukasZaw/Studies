type Lista<'T> =
    | Pusta
    | Wezel of 'T * Lista<'T>


let rec NaLitereA (lista:Lista<string>) =
    match lista with
    | Pusta -> 0
    | Wezel(glowa, ogon) when (glowa.ToLower())[0] = 'a' -> 1 + NaLitereA ogon
    | Wezel(glowa, ogon) -> NaLitereA ogon

let lista = Wezel("Ala",Wezel("ma",Wezel("psa",Wezel("asd",Wezel("aaaaaa",Pusta)))))

NaLitereA lista