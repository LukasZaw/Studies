namespace ConsoleApp1
{
    public class Ksiazka
    {
        public string Tytul { get; set; }
        public int RokWydania { get; set; }
        public int Autor { get; set; }
        public double Cena { get; set; }
    }

    public class Autor
    {
        public int id { get; set; }
        public string Imie { get; set; }
        public string Nazwisko { get; set; }
    }
}
