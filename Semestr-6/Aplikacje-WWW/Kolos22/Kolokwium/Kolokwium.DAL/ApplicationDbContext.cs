using Kolokwium.Model.DataModels;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;

namespace Kolokwium.DAL
{
    public class ApplicationDbContext : IdentityDbContext<User, Role, int>
    {
        // table properties
        // public virtual DbSet<Entity> TableName { get; set; } = null!;
        public virtual DbSet<Auto> Auta { get; set; } = null!;
        public virtual DbSet<Parking> Parkingi { get; set; } = null!;
        public virtual DbSet<Wlasciciel> Wlasciciele { get; set; } = null!;
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            base.OnConfiguring(optionsBuilder);
            //configuration commands            
            optionsBuilder.UseLazyLoadingProxies(); //enable lazy loading proxies
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
            // Fluent API commands
            modelBuilder.Entity<Auto>()
                .HasOne(a => a.Parking)
                .WithMany(p => p.Auta)
                .HasForeignKey(a => a.ParkingId);

            modelBuilder.Entity<Auto>()
                .HasOne(a => a.Wlasciciel)
                .WithOne(w => w.Auto)
                .HasForeignKey<Auto>(a => a.WlascicielId);
           
        }
    }
}
