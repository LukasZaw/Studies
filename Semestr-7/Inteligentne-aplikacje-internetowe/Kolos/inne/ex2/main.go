package main

import (
	"fmt"
	"kolos/kod"
	"kolos/web"
)

func main() {


	for i := 0; i < 2; i++ {
		println(
			kod.ListaApartow()[i].Nazwa,
			kod.ListaApartow()[i].Liczba_megapikseli,
			kod.ListaApartow()[i].Rozmiar_matrycy,
			kod.ListaApartow()[i].Zoom_optyczny,
		)
	}
	wynik := kod.Roznica(&kod.ListaApartow()[0] , &kod.ListaApartow()[1])
	fmt.Printf("%s %2f","Różnia między aparatami:", wynik)
	println()
	web.StartServer()


}
