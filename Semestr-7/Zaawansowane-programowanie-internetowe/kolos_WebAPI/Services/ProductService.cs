using Microsoft.EntityFrameworkCore;
using kolos_WebAPI.Data;
using kolos_WebAPI.Models;

namespace kolos_WebAPI.Services;

public class ProductService : IProductService
{
    private readonly AppDbContext _context;

    public ProductService(AppDbContext context)
    {
        _context = context;
    }

    public IEnumerable<Product> GetProducts()
    {
        return _context.Products.AsNoTracking().ToList();
    }

    public Product? GetProduct(int productId)
    {
        return _context.Products.AsNoTracking().FirstOrDefault(p => p.Id == productId);
    }

    public Product? GetProductByName(string productName)
    {
        return _context.Products.AsNoTracking().FirstOrDefault(p => p.Name == productName);
    }

    public void Add(Product product)
    {
        _context.Products.Add(product);
        _context.SaveChanges();
    }

    public void RemoveProduct(Product product)
    {
        _context.Products.Remove(product);
        _context.SaveChanges();
    }
}
