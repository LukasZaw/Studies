using Kolokwium.ViewModel.VM;
using System.Linq.Expressions;

namespace Kolokwium.Services.Interfaces
{
    public interface IAutoService
    {
        IEnumerable<AutoVm> GetAuta(Expression<Func<AutoVm, bool>>? filter = null);
        AutoVm AddAuto(AddAutoVm addAutoVm);
        AutoVm DeleteAuto(int id);
    }
}