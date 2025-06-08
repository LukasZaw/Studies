using System.ComponentModel.DataAnnotations.Schema;
namespace Kolokwium.Model.DataModels;
public class Auto
{
    public int Id { get; set; }
    public string Marka { get; set; }

    public string Model { get; set; }

    public int RokProdukcji { get; set; }

    [ForeignKey("ParkingId")]
    public int ParkingId { get; set; } //relacje aut do jednego parkingu
    public virtual Parking Parking { get; set; }

    public int WlascicielId { get; set; }
    public virtual Wlasciciel Wlasciciel { get; set; } // relacja jedno auto jeden wlasciciel

}
