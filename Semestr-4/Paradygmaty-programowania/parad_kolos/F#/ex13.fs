let CzyParzyste x = 
    if x % 2 = 0 then
        true
    else
        false

let rec WczytajListe liczba lista = 
    let input = Int32.Parse(Console.ReadLine())
    if input = 0 then
        printfn $"Liczby Parzysta:{lista}"
        liczba
    else
        if CzyParzyste input then 
            WczytajListe (liczba + 1) (lista + " " + input.ToString())
        else 
            WczytajListe liczba lista 

WczytajListe 0 ""