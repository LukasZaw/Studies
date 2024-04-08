namespace Generic.Extensions
{
    public static class DisplayActionExtensions
    {
        public static void Print<TObjectType>(this TObjectType obj)
        {
            Console.WriteLine(obj);
        }

        public static void Print<TObjectType>(this IList<TObjectType> list)
        {
            foreach (var item in list)
            {
                Console.WriteLine(item + "\n");
            }
        }
    }
}
