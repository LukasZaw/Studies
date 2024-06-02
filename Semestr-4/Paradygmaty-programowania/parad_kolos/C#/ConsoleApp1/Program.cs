using ConsoleApp1;

Console.WriteLine("==== Drzewo binarne ====");

// Tworzenie drzewa binarnego
Drzewo korzen = new Drzewo(10);
korzen.Lewo = new Drzewo(5);
korzen.Prawo = new Drzewo(15);
korzen.Lewo.Lewo = new Drzewo(3);
korzen.Lewo.Prawo = new Drzewo(7);
korzen.Prawo.Lewo = new Drzewo(12);
korzen.Prawo.Prawo = new Drzewo(18);
Console.WriteLine("Suma: " + korzen.Suma());
Func<int, bool> warunek = value => value % 2 == 0;

Console.WriteLine("Suma Jezeli: " + korzen.SumaJezeli(warunek));



Console.WriteLine("==== LINQ ====");
var ksiazki = new[] {
    new Ksiazka {Tytul = "Pan Tadeusz", RokWydania = 1998, Autor = 1, Cena = 30},
    new Ksiazka {Tytul = "Potop", RokWydania = 1991, Autor = 2, Cena = 40},
    new Ksiazka {Tytul = "W pustyni i w puszczy", RokWydania = 1990, Autor = 2, Cena = 30},
    new Ksiazka {Tytul = "Lalka", RokWydania = 1990, Autor = 3, Cena = 50},
    new Ksiazka {Tytul = "Programowanie funkcyjne w języku C#", RokWydania = 2019, Autor = 4, Cena = 71.20},
    new Ksiazka {Tytul = "Programowanie funkcyjne z JavaScriptem", RokWydania = 2017, Autor = 5, Cena = 29.40},
};

var autorzy = new[] {
    new Autor { id = 1, Imie = "Adam", Nazwisko = "Mickiewicz" },
    new Autor { id = 2, Imie = "Henryk", Nazwisko = "Sienkiewicz" },
    new Autor { id = 3, Imie = "Bolesław", Nazwisko = "Prus" },
    new Autor { id = 4, Imie = "Enrico", Nazwisko = "Buonanno" },
    new Autor { id = 5, Imie = "Luis", Nazwisko = "Atencio" },
    new Autor { id = 6, Imie = "Robert C.", Nazwisko = "Martin" },
};

//Napisz zapytanie Linq, które dla każdego autora określi łączną cenę książek, które napisał
Console.WriteLine("Ex 15 Najtansza dla autora");
var wynik = autorzy.Select(a => new
{
    Autor = a,
    NajtanszaKsiazka = ksiazki.Where(k => k.Autor == a.id).Select(k => k.Cena).DefaultIfEmpty(0).Min(),
});

foreach (var item in wynik)
{
    Console.WriteLine("Autor: " + item.Autor.Nazwisko + ", Ksiazka: " + item.NajtanszaKsiazka);
}


Console.WriteLine("Ex 10 Łączna cena ksiazek dla autora");
//Napisz zapytanie Linq, które dla każdego autora określi łączną cenę książek, które napisał.

var wynik1 = autorzy.Select(a => new
{
    Autor = a,
    LacznaCena = ksiazki.Where(k => a.id == k.Autor).Select(c => c.Cena).Sum()
});

foreach (var item in wynik1)
{
    Console.WriteLine("Autor: " + item.Autor.Nazwisko + ", Łączna cena: " + item.LacznaCena);
}


Console.WriteLine("Ex 3 Liczba ksiazek autora");
//Napisz zapytanie Linq, okresli dla kazdego autora liczbe ksiazek ktore napisal
var wynik2 = autorzy.Select(a => new
{
    Autor = a,
    Liczba = ksiazki.Where(k => k.Autor == a.id).Count()
});

foreach (var item in wynik2)
{
    Console.WriteLine("Autor: " + item.Autor.Nazwisko + ", Liczba ksiazek: " + item.Liczba);
}
Console.WriteLine("===");

var ksiazki1 = new[]
{
    new Ksiazka1 { Tytul = "Pan Tadeusz", RokWydania = 1998, Gatunek = 1, Cena = 30 },
    new Ksiazka1 { Tytul = "Potop", RokWydania = 1991, Gatunek = 1, Cena = 40 },
    new Ksiazka1 { Tytul = "W pustyni i w puszczy", RokWydania = 1990, Gatunek = 2, Cena = 30 },
    new Ksiazka1 { Tytul = "Lalka", RokWydania = 1990, Gatunek = 1, Cena = 50 },
    new Ksiazka1 { Tytul = "Programowanie funkcyjne w języku C#", RokWydania = 2019, Gatunek = 3, Cena = 71.20 },
    new Ksiazka1 { Tytul = "Programowanie funkcyjne z JavaScriptem", RokWydania = 2017, Gatunek = 3, Cena = 29.40 },
};

var gatunki1 = new[]
{
    new Gatunek { id = 1, Nazwa = "Literatura piękna" },
    new Gatunek { id = 2, Nazwa = "Przygodowa" },
    new Gatunek { id = 3, Nazwa = "Programowanie" },
    new Gatunek { id = 4, Nazwa = "Projektowanie stron WWW" },
};

// Ex 03 Liczba ksiazek do gatunku
var liczbaKsiazek1 = gatunki1.Select(x => new
{
    Gatunek = x,
    Liczba = ksiazki1.Where(k => k.Gatunek == x.id).Count()
});

foreach (var item in liczbaKsiazek1)
{
    Console.WriteLine("Gatunek: " + item.Gatunek.Nazwa + ", Liczba ksiazek: " + item.Liczba);
}

// Ex 03 Laczna cena ksiazek dla gatunku
var lacznaCena = gatunki1.Select(g => new
{
    Gatunek = g,
    Cena = ksiazki1.Where(k => k.Gatunek == g.id).Select(k => k.Cena).Sum()
});


Console.WriteLine("=====================");
Console.WriteLine("==== Listy Linq =====");

Console.WriteLine("Ex 3 Liczba punktow ponad sin");
Random rnd = new Random();
int liczbaPunktow = 100;

List<Point> points = new List<Point>();
for (int i = 0; i < liczbaPunktow; i++)
{
    double x = rnd.NextDouble() * 20.0 - 10.0;
    double y = rnd.NextDouble() * 20.0 - 10.0;
    points.Add(new Point { X = x, Y = y });
}

var pointsSin = points.Where(p => p.Y > Math.Sin(p.X)).Count();

Console.WriteLine($"Punkty nad sin(x): {pointsSin}");

Console.WriteLine("Ex 13 Wyrazy zaczynajace sie na litere");
string[] wyrazy = { "Ala", "ma", "kota", "kot", "ma", "asd", "psa" };

var wyrazyNaLitere = wyrazy.GroupBy(w => w.First()).ToDictionary(g => g.Key, g => g.Count());


Console.WriteLine("   ============   ");
Console.WriteLine("==== Liniwe generowanie =====");
Console.WriteLine("Ex 6 Generowanie dopoki z > 0");

static IEnumerable<int[]> GenerujPunkty()
{
    Random random = new Random();
    while (true)
    {
        int x = random.Next(-20, 5);
        int y = random.Next(-20, 21);
        int z = random.Next(-5, 21);
        yield return new int[] { x, y, z };
    }
}

static IEnumerable<int[]> GenedrujGdyNieUjemne()
{
    foreach (var point in GenerujPunkty())
    {
        if (point[2] < 0)
            yield break;
        yield return point;
    }
}

static int[] SumaPunktow(IEnumerable<int[]> punkty)
{
    int[] suma = new int[3];
    foreach (var punkt in punkty)
    {
        suma[0] += punkt[0];
        suma[1] += punkt[1];
        suma[2] += punkt[2];
    }
    return suma;
}

var punkty = GenedrujGdyNieUjemne();

foreach (var point in punkty)
{
    Console.WriteLine($"[{point[0]}, {point[1]}, {point[2]}]");
}

var sumaPunktow = SumaPunktow(punkty);
Console.WriteLine($"Suma: {sumaPunktow[0]} {sumaPunktow[1]} {sumaPunktow[2]}");

Console.WriteLine("Ex 7 Generowanie dopoki x < 0");

static IEnumerable<int[]> GenerujGdyDodatnia()
{
    foreach (var punkt in GenerujPunkty())
    {
        if (punkt[0] > 0)
        {
            yield break;
        }
        yield return punkt;
    }

}

static int Policz(IEnumerable<int[]> punkty)
{
    int licznik = 0;
    foreach (var punkt in punkty)
    {
        licznik++;
    }

    return licznik;
}


var punktyDodatnie = GenerujGdyDodatnia();
foreach (var punkt in punktyDodatnie)
{
    Console.WriteLine($"[{punkt[0]}, {punkt[1]}, {punkt[2]}]");
}
int liczbaPkt = Policz(punktyDodatnie);
Console.WriteLine("Licznik punktów: " + liczbaPkt);
Console.WriteLine("====");

Console.WriteLine("Ex 8 Silnia 10.Silnia");

Console.WriteLine("Silnia: " + 100.Silnia());