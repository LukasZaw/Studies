using Microsoft.AspNetCore.Mvc;
using Kolokwium.Services.Interfaces;
using Kolokwium.Model.DataModels;
namespace Kolokwium.Web.Controllers;

public class AutoController : Controller
{
    private readonly IAutoService _autoService;

    public AutoController(IAutoService autoService)
    {
        _autoService = autoService;
    }

    public IActionResult Index()
    {
        var auta = _autoService.GetAuta();
        return View(auta);
    }
}