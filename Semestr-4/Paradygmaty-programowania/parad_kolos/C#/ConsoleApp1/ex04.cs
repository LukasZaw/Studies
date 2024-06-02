namespace ConsoleApp1
{
    class Ksiazka1
    {
        public string Tytul { get; set; }
        public int RokWydania { get; set; }
        public int Gatunek { get; set; }
        public double Cena { get; set; }
    }

    public class Gatunek
    {
        public int id { get; set; }
        public string Nazwa { get; set; }
    }
}
