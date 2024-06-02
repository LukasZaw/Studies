let wieksz (x, y) = 
    match (x, y) with
        | (x, y) when (x*x) > (y*y) -> x
        | (x, y) when (x*x) < (y*y) -> y
        | (x, y) when (x*x) = (y*y) -> x

let para = (-5, 2)

wieksz para