namespace Kolokwium.ViewModel.VM
{
    public class AddAutoVm
    {
        public string Marka { get; set; } = string.Empty;
        public string Model { get; set; } = string.Empty;
        public int RokProdukcji { get; set; }
        public int ParkingId { get; set; }
        public int WlascicielId { get; set; }
    }
}