type Punkt = {X: float; Y: float}

type Prostokat = {P1: Point; P2: Point; P3: Point; P4: Point}

let CzyWSrodku (pkt: Punkt) (pro: Prostokat) =
    if  pro.P1.X > pkt.X && pro.P1.Y > pkt.Y &&
        pro.P2.X > pkt.X && pro.P2.Y < pkt.Y &&
        pro.P3.X < pkt.X && pro.P3.Y < pkt.Y &&
        pro.P4.X < pkt.X && pro.P4.Y > pkt.Y then
        true
    else
        false


let punkt1 = { X = 1.0; Y = 2.0 }
let punkt2 = { X = 9.0; Y = 2.0 }
let punkt3 = { X = -1.0; Y = 2.0 }


let prosto = {  P1 = { X = 3.0; Y = 4.0 };
                P2 = { X = 3.0; Y = 1.0 };
                P3 = { X = -2.0; Y = 1.0 };
                P4 = { X = -2.0; Y = 4.0 };
            }

if CzyWSrodku punkt1 prosto then
    printfn "W srodku"
else
    printfn "Poza"
