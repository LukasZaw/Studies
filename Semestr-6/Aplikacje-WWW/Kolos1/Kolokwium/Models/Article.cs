namespace Kolokwium.Models;

public class Article
{
    public int Id { get; set; }
    public string Title { get; set; } = null!;
    public string Lead { get; set; } = null!;
    public string Content { get; set; } = null!;
    public DateTime CreationDate { get; set; }

    // Relacja: wiele artykułów do jednego autora
    public int AuthorId { get; set; }
    public Author Author { get; set; } = null!;

    // Relacja: wiele artykułów do jednej kategorii
    public int CategoryId { get; set; }
    public Category Category { get; set; } = null!;

    // Relacja: jeden artykuł - wiele komentarzy
    public ICollection<Comment> Comments { get; set; } = new List<Comment>();

    // Relacja wiele-do-wielu z Tag
    public ICollection<Tag> Tags { get; set; } = new List<Tag>();
}