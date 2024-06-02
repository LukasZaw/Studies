type Lista<'a> = 
    | Pusta
    | Wezel of 'a * Lista<'a>

let lista1 = Wezel(-2,Wezel(2,Wezel(3,Wezel(-8,Wezel(1,Pusta)))))

let rec Filtr predykat lista =
    match lista with
    | Pusta -> Pusta
    | Wezel(glowa, ogon) -> if not(predykat glowa) then
                                Wezel(glowa, Filtr predykat ogon)
                            else
                                Filtr predykat ogon
                                

let wieksze x = x > 0

Filtr wieksze lista1