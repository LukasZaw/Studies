using Microsoft.EntityFrameworkCore;
using kolos_WebAPI.Models;

namespace kolos_WebAPI.Data;

public class AppDbContext : DbContext
{
    public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
    {
    }

    public DbSet<Product> Products => Set<Product>();
}
