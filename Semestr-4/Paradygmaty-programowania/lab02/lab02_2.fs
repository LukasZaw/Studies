open System

//zad 2.1
let fun1 = 
    System.Console.WriteLine("Podaj wartosc");
    let x = Int32.Parse(System.Console.ReadLine())
    match x with
    | 1 -> "Wprowadziles 1"
    | 2 -> "Wprowadziles 2"
    | 3 -> "Wprowadziles 3"
    | 4 -> "Wprowadziles 4"
    | _ -> "Wprowadziles inna wartosc 1, 2, 3 lub 4"

//zad 2.2
let fun22 =
    Console.Write("Podaj wartosc x: ");
    let x = Int32.Parse(Console.ReadLine());
    Console.Write("Podaj wartosc y: ");
    let y = Int32.Parse(Console.ReadLine());
    let para = (x, y)
    match para with
        | (x, y) when x > y -> "x wiekszy"
        | (x, y) when x < y -> "y wiekszy"
        | (x, y) when x = y -> "są rowne"
        | (_, _) -> "blad"

//zad2.3
let fun3 a b c = 
    let obwod = a + b + c
    let p = obwod / 2.0

    let pole = sqrt(p * (p-a) * (p-b) * (p-c))
    let para = (obwod, pole)
    para


let res = fun3 5 2 5
printf $"Obwód trójkąta: {fst res}, a obówd to: {snd res}.\n"

//zad2.4
let rozdziel (email : string) = 
    let text = email.Split[|'@'|]
    (text[0], text[1])

let fun4 (email : string) = 
    match rozdziel email with
        |(nazwa, domena) -> $"Nazwa: {nazwa}, domena: {domena}."

fun4 "asxc@asdfs.sd"


//zad2.5
let fun5 email = 
    let text = rozdziel email
    match text with
        | (_, domena) when domena.Equals("pcz.pl") -> "Należy do PCZ.PL"
        | _ -> "Nie należy do pcz.pl"

fun5 "asxc@asdfs.sd"
fun5 "asxc@pcz.pl"

//zad2.6
let fun6 (x1:float, y1:float, z1:float) (x2:float, y2:float, z2:float) =
    let odl = sqrt((x1-x2)**2 + (y1-y2)**2 + (z1-z2)**2)
    odl

fun6 (1,2,3) (4,5,6)

//zad2.7
let fun7 (x_sr: float, y_sr:float) (r: float) (x:float, y:float) = 
    let okr = (x+x_sr)**2 + (y+y_sr)**2
    if okr < r**2 then
        printfn "Lezy w okręgu"
    elif okr > r**2 then
        printfn "Leży poza okręgiem"
    else 
        printfn "Leży na okręgu"

fun7 (-1,4) 5 (1, 1)






