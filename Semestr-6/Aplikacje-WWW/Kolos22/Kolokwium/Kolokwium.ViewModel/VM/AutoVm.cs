namespace Kolokwium.ViewModel.VM
{
    public class AutoVm
    {
        public int Id { get; set; }
        public string Marka { get; set; } = string.Empty;
        public string Model { get; set; } = string.Empty;
        public int RokProdukcji { get; set; }
        public string ParkingNazwa { get; set; } = string.Empty;
        public string WlascicielImieNazwisko { get; set; } = string.Empty;
    }
}