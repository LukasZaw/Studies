open System
type Punkt = { X: float; Y: float }

let generujLosowo (random: Random) = 
    let x = random.NextDouble() * 40.0 - 20.0
    let y = random.NextDouble() * 40.0 - 20.0
    {X = x; Y = y}


let rnd = Random()

let randomPunkty = List.init 100 (fun _ -> generujLosowo rnd)

let punktyWSr = List.filter (fun pkt -> Math.Sqrt(pkt.X * pkt.X + pkt.Y * pkt.Y) < 5.0) randomPunkty

