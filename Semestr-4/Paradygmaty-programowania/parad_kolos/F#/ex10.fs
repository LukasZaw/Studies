let rec TekstIle tekst liczba =
    match tekst with
    | "" -> 0
    | _ when tekst.[0] = '1' -> TekstIle (tekst.Substring(1)) liczba + 1
    | _ when tekst.[0] = '2' -> TekstIle (tekst.Substring(1)) liczba + 1
    | _ when tekst.[0] = '3' -> TekstIle (tekst.Substring(1)) liczba + 1
    | _ when tekst.[0] = '4' -> TekstIle (tekst.Substring(1)) liczba + 1
    | _ when tekst.[0] = '5' -> TekstIle (tekst.Substring(1)) liczba + 1
    | _ when tekst.[0] = '6' -> TekstIle (tekst.Substring(1)) liczba + 1
    | _ when tekst.[0] = '7' -> TekstIle (tekst.Substring(1)) liczba + 1
    | _ when tekst.[0] = '8' -> TekstIle (tekst.Substring(1)) liczba + 1
    | _ when tekst.[0] = '9' -> TekstIle (tekst.Substring(1)) liczba + 1
    | _ -> TekstIle (tekst.Substring(1)) liczba

let text = "Jakis 12 a8sd 123 tekst"

TekstIle text 0