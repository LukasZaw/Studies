namespace kolos_WebAPI2.Models
{
    public class Student
    {
        public int IdStudent { get; set; }
        public string FirstName { get; set; } = string.Empty;
        public string LastName { get; set; } = string.Empty;
        public  int Age { get; set;   }
    }
}