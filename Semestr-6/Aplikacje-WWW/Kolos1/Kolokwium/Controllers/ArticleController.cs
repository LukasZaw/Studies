using Kolokwium.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;


namespace Kolokwium.Controllers
{
    public class ArticleController : Controller{
        private readonly AppDbContext _context;

        public ArticleController(AppDbContext context)
        {
            _context = context;
        }

        public IActionResult Index()
        {
            var articles = _context.Articles
                .Include(a => a.Author)
                .Include(a => a.Category)
                .ToList();
            return View(articles);
        }
    }

}