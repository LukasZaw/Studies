namespace Kolokwium.Models;

public class Comment
{
    public int Id { get; set; }
    public string Title { get; set; } = null!;
    public string Content { get; set; } = null!;

    // Relacja: wiele komentarzy do jednego artykułu
    public int ArticleId { get; set; }
    public Article Article { get; set; } = null!;
}