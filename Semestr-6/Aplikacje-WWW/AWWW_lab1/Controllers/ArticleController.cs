using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Components.Web;
using Microsoft.AspNetCore.Razor;
//using AWWW_lab1.Models;

public class ArticleController : Controller {
    public IActionResult Index(int id = 1)
    {
        
        var articles = new List<Article>
        {
        new Article{
            Id = 1,
            Title = "Artykuł 1",
            Content = "Lorem ipsum",
            CreationDate = DateTime.Now
            
        },
         new Article{
            Id = 1,
            Title = "Artykuł 2",
            Content = "Lorem ipsum",
            CreationDate = DateTime.Now
        },
        new Article{
            Id = 1,
            Title = "Artykuł 3",
            Content = "Lorem ipsum",
            CreationDate = DateTime.Now
        }
        };
        
        return View(articles[id - 1]);
    }
}