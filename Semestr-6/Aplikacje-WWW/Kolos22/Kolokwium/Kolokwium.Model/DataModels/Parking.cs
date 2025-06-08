using System.ComponentModel.DataAnnotations.Schema;
namespace Kolokwium.Model.DataModels;
public class Parking
{
    public int Id { get; set; }
    public string Nazwa { get; set; }

    public virtual IList<Auto> Auta { get; set; } // relacje wiele auta do jednego parkingu

}