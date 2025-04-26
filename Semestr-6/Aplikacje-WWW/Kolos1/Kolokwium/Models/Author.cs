namespace Kolokwium.Models;

public class Author
{
    public int Id { get; set; }
    public string FirstName { get; set; } = null!;
    public string LastName { get; set; } = null!;

    // Relacja: jeden autor - wiele artykułów
    public ICollection<Article> Articles { get; set; } = new List<Article>();
}