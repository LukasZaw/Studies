// Definicja typu danych reprezentującego drzewo binarne
type 'a BinaryTree =
    | Empty
    | Node of 'a * 'a BinaryTree * 'a BinaryTree

// Funkcja do wyświetlania elementów drzewa w kolejności postorder
let rec postorder tree =
    match tree with
    | Empty -> []
    | Node(value, left, right) ->
        postorder left @ postorder right @ [value]

// Funkcja pomocnicza do wyświetlania elementów listy
let printList lst =
    lst |> List.iter (printf "%A ")
    printfn ""

// Przykładowe użycie
let tree =
    Node(1,
        Node(2,
            Node(4, Empty, Empty),
            Node(5, Empty, Empty)
        ),
        Node(3,
            Node(6, Empty, Empty),
            Node(7, Empty, Empty)
        )
    )

// Wyświetlenie elementów drzewa w kolejności postorder
let postorderElements = postorder tree
printList postorderElements