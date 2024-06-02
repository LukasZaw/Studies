namespace ConsoleApp1
{
    public class Drzewo
    {
        public int Value { get; set; }
        public Drzewo Lewo { get; set; }
        public Drzewo Prawo { get; set; }

        public Drzewo(int value)
        {
            Value = value;
            Lewo = null;
            Prawo = null;
        }

        public void Add(int value)
        {
            if (value < Value)
            {
                if (Lewo == null)
                    Lewo = new Drzewo(value);
                else
                    Lewo.Add(value);
            }
            else
            {
                if (Prawo == null)
                    Prawo = new Drzewo(value);
                else
                    Prawo.Add(value);
            }
        }


        public int Suma()
        {
            int suma = 0;
            suma += Value;
            if (Lewo != null)
            {
                suma += Lewo.Suma();
            }
            if (Prawo != null)
            {
                suma += Prawo.Suma();
            }

            return suma;
        }

        public int SumaJezeli(Func<int, bool> warunek)
        {
            int suma = 0;
            if (warunek(Value))
            {
                suma += Value;
            }

            if (Lewo != null)
            {
                suma += Lewo.SumaJezeli(warunek);
            }

            if (Prawo != null)
            {
                suma += Prawo.SumaJezeli(warunek);
            }

            return suma;
        }
    }
}
