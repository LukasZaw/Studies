printf "siema\n"

let x = 2
let y: int = 4545 + 2
let z: float = 45

printf "x: %d\n" x
printf "x: %d\n" (x + 10)

let text = "witam"
text.Length
text.Substring(2,2)
text.[0..2]

System.Console.WriteLine($"cześć {x}, {y}")

let k = (float 14) + 4.0
let k2 = (float "12.12")

if k2 > 10 then
    let a = 1
    printf "wiecej niz 10\n"
else
    printf "mniej niz 10\n"

let x1 = 52.5
let x2 = 20
let max = 
    if x1 > x2 then
        x1
    else
        x2


let sum = fun j k -> j + k
sum 5 8

let suma j k = j + k
suma 2 23


let show () =
    printf "funkcja bez arg\n"

show ()

let mnozenie (x: int) (y: int) : int = x*y

mnozenie 2 6


let m_max x y =
    if x > y then
        x
    else
        y
m_max 4 8


let rec silnia n = 
    if n < 0 then
        failwith "nie mozna policzyc dla 0"
    elif n = 0 then
        printf "n równe 0\n"
        1
    else
        printf "wykonanie dla n = %d\n" n
        let wynik = n * silnia (n - 1)
        printf "%d * " n
        wynik
silnia 10


let rec silnia2 n w =
    if x < 0 then
        failwith "nie mozna policzyc dla 0"
    elif n = 0 then
        w
    else
        printf "%d * %d\n" n w
        silnia2 (n - 1) (n * w)

silnia2 10 1







