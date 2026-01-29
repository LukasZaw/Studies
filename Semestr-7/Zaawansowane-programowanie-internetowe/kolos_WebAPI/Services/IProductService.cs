using kolos_WebAPI.Models;

namespace kolos_WebAPI.Services;

public interface IProductService
{
    IEnumerable<Product> GetProducts();
    Product? GetProduct(int productId);
    Product? GetProductByName(string productName);
    void Add(Product product);
    void RemoveProduct(Product product);
}
