let para = (1, "text")
let krotka = (1, 3.14, "pi")
let x, y, z = krotka

let sumaR x y = ("policzone: ", x+y, x-y)
let kom, sum, roz = sumaR 5 4

let get2 (a, b, c) = b

get2 krotka

type Punkt = {
    x:int
    y:int
    kolor:string
}

let p1 = {
    x = 2
    y = 5
    kolor = "red"
}


let p2 = { p1 with x=1 }

let opiszPkt p1 = printf "x: %d, y: %d, kolor: %s\n" p1.x p1.y p1.kolor