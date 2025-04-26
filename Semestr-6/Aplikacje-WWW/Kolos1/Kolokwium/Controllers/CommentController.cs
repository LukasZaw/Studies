using Kolokwium.Models;
using Microsoft.AspNetCore.Mvc;

namespace Kolokwium.Controllers
{
    public class CommentController : Controller
    {
        private readonly AppDbContext _context;

        public CommentController(AppDbContext context)
        {
            _context = context;
        }

        public IActionResult Index()
        {
            var comments = _context.Comments.ToList();
            return View(comments);
        }
    }
}