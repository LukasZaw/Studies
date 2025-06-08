using Microsoft.AspNetCore.Mvc;
using Kolokwium.Services.Interfaces;
using Kolokwium.ViewModel.VM;

namespace Kolokwium.Web.Controllers;

public class DeleteAutoController : Controller
{
    private readonly IAutoService _autoService;

    public DeleteAutoController(IAutoService autoService)
    {
        _autoService = autoService;
    }

    [HttpPost]
    public IActionResult Delete(int id)
    {
        var auto = _autoService.DeleteAuto(id);
        if (auto == null)
        {
            return NotFound();
        }
        return RedirectToAction("Index", "Auto");
    }
}