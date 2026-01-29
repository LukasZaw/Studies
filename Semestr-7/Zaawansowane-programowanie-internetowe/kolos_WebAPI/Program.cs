using Microsoft.EntityFrameworkCore;
using kolos_WebAPI.Data;
using kolos_WebAPI.Services;
using kolos_WebAPI.Models;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

// EF Core DbContext
var connectionString = builder.Configuration.GetConnectionString("DefaultConnection");
builder.Services.AddDbContext<AppDbContext>(options =>
    options.UseSqlServer(connectionString));

// Application services
builder.Services.AddScoped<IProductService, ProductService>();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

// API endpoints
app.MapGet("/api/products", (IProductService service) =>
{
    var products = service.GetProducts();
    return Results.Ok(products);
})
.Produces<IEnumerable<Product>>(StatusCodes.Status200OK)
.Produces(StatusCodes.Status500InternalServerError)
.WithDescription("Tworzy nowy produkt")
.WithSummary("Tworzy nowy produkt")
.WithTags("Products")
.WithName("GetProducts");

app.MapGet("/api/products/{id:int}", (int id, IProductService service) =>
{
    try{
        var product = service.GetProduct(id);
        return product is null ? Results.NotFound() : Results.Ok(product);
    }
    catch
    {
        return Results.Problem(
            detail: "Wystąpił błąd podczas pobierania produktu.",
            title: "Błąd serwera"
        );
    }
   
});

app.MapPost("/api/products", (Product product, IProductService service) =>
{
    service.Add(product);
    return Results.Created($"/api/products/{product.Id}", product);
});

app.MapDelete("/api/products/{id:int}", (int id, IProductService service) =>
{
    var existing = service.GetProduct(id);
    if (existing is null)
    {
        
        return Results.NotFound();
    }

    service.RemoveProduct(existing);
    return Results.NoContent();
});

app.Run();
