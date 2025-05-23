using System.ComponentModel.DataAnnotations;

namespace Kolokwium.Models;

public class Article
{
    public int Id { get; set; }

    [Required]
    public string Title { get; set; } = null!;

    [Required]
    public string Lead { get; set; } = null!;

    [Required]
    public string Content { get; set; } = null!;

    public DateTime CreationDate { get; set; }

    public int? AuthorId { get; set; }
    public Author Author { get; set; } = null!;

    public int? CategoryId { get; set; }
    public Category Category { get; set; } = null!;

    public ICollection<Comment> Comments { get; set; } = new List<Comment>();
    public ICollection<Tag> Tags { get; set; } = new List<Tag>();
}