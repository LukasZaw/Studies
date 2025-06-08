using System.ComponentModel.DataAnnotations.Schema;
namespace Kolokwium.Model.DataModels;
public class Wlasciciel
{
    public int Id { get; set; }
    public string Imie { get; set; }

    public string Nazwisko { get; set; }

    public virtual Auto Auto { get; set; }
}