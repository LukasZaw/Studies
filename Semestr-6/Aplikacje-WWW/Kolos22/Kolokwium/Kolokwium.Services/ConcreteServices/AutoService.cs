using AutoMapper;
using Kolokwium.DAL;
using Kolokwium.Model.DataModels;
using Kolokwium.Services.Interfaces;
using Kolokwium.ViewModel.VM;
using Microsoft.Extensions.Logging;
using System.Linq.Expressions;

namespace Kolokwium.Services.ConcreteServices
{
    public class AutoService : BaseService, IAutoService
    {
        public AutoService(ApplicationDbContext dbContext, IMapper mapper, ILogger<AutoService> logger)
            : base(dbContext, mapper, logger)
        {
        }

        public IEnumerable<AutoVm> GetAuta(Expression<Func<AutoVm, bool>>? filter = null)
        {
            var auta = DbContext.Auta.ToList();
            var autaVm = Mapper.Map<List<AutoVm>>(auta);

            if (filter != null)
            {
                return autaVm.AsQueryable().Where(filter).ToList();
            }
            return autaVm;
        }

        public AutoVm AddAuto(AddAutoVm addAutoVm)
        {
            var auto = Mapper.Map<Auto>(addAutoVm);
            DbContext.Auta.Add(auto);
            DbContext.SaveChanges();
            return Mapper.Map<AutoVm>(auto);
        }

        public AutoVm DeleteAuto(int id)
        {
            var auto = DbContext.Auta.FirstOrDefault(a => a.Id == id);
            if (auto == null)
                throw new Exception("Auto nie istnieje");

            DbContext.Auta.Remove(auto);
            DbContext.SaveChanges();
            return Mapper.Map<AutoVm>(auto);
        }
    }
}