using AutoMapper;
using Kolokwium.Model.DataModels;
using Kolokwium.ViewModel.VM;
namespace Kolokwium.Services.Configuration.AutoMapperProfiles;
public class MainProfile : Profile
{
    public MainProfile()
    {
        CreateMap<Auto, AutoVm>()
            .ForMember(dest => dest.ParkingNazwa, opt => opt.MapFrom(src => src.Parking.Nazwa))
            .ForMember(dest => dest.WlascicielImieNazwisko, opt => opt.MapFrom(src => src.Wlasciciel.Imie + " " + src.Wlasciciel.Nazwisko));
        CreateMap<AddAutoVm, Auto>();
    }
}