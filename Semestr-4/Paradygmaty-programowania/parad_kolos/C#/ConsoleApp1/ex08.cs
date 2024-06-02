namespace ConsoleApp1
{
    public static class ExtensionMethods
    {
        public static int Silnia(this int n)
        {
            if (n == 0)
                return 1;
            else
                return n * Silnia(n - 1);
        }
    }
}
