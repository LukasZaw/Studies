using Microsoft.AspNetCore.Mvc;
using Kolokwium.Models;
using Microsoft.EntityFrameworkCore;

namespace Kolokwium.Controllers
{
    public class AuthorController : Controller
    {
        private readonly AppDbContext _context;

        public AuthorController(AppDbContext context)
        {
            _context = context;
        }

        public IActionResult Index()
        {
            var authors = _context.Authors.ToList();
            return View(authors);
        }
    }
}