using Kolokwium.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
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

        public IActionResult Add()
        {
            ViewBag.Authors = new SelectList(
            _context.Authors.Select(a => new { a.Id, FullName = a.FirstName + " " + a.LastName }).ToList(), "Id", "FullName");
            ViewBag.Categories = new SelectList(_context.Categories.ToList(), "Id", "Name");
            return View();
        }

        // POST: Article/Add
        [HttpPost]
        [ValidateAntiForgeryToken]
        public IActionResult Add(Article article)
        {
            article.CreationDate = DateTime.Now;
            _context.Articles.Add(article);
            _context.SaveChanges();
            return RedirectToAction("Index");
        }
    }

}