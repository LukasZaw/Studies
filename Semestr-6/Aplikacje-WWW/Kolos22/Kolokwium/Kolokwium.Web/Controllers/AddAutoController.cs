using Microsoft.AspNetCore.Mvc;
using Kolokwium.Services.Interfaces;
using Kolokwium.ViewModel.VM;

namespace Kolokwium.Web.Controllers;

public class AddAutoController : Controller
{
    private readonly IAutoService _autoService;

    public AddAutoController(IAutoService autoService)
    {
        _autoService = autoService;
    }

    public IActionResult Add()
    {
        return View("~/Views/Auto/Add.cshtml");
    }

    [HttpPost]
    public IActionResult Add(AddAutoVm addAutoVm)
    {
        if (ModelState.IsValid)
        {
            _autoService.AddAuto(addAutoVm);
            return RedirectToAction("Index", "Auto");
        }
        return View("~/Views/Auto/Add.cshtml", addAutoVm);
    }
}