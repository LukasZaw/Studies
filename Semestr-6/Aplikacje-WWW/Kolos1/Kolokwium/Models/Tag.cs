namespace Kolokwium.Models;

public class Tag
{
    public int Id { get; set; }
    public string Name { get; set; } = null!;

    // Relacja wiele-do-wielu z Article
    public ICollection<Article> Articles { get; set; } = new List<Article>();
}