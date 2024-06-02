let CzyParzyste x = 
    if x % 2 = 0 then
        true
    else
        false

let rec WczytajListe liczba = 
    let input = Int32.Parse(Console.ReadLine())
    if input = 0 then
        liczba
    else
        if CzyParzyste input then 
            WczytajListe (liczba + 1)
        else 
            WczytajListe liczba

WczytajListe 0