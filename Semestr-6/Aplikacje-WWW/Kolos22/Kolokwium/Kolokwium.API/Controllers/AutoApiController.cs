using Kolokwium.Services.Interfaces;
using Kolokwium.ViewModel.VM;
using Microsoft.AspNetCore.Mvc;

namespace Kolokwium.API.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class AutoApiController : ControllerBase
    {
        private readonly IAutoService _autoService;

        public AutoApiController(IAutoService autoService)
        {
            _autoService = autoService;
        }

        [HttpGet]
        public IActionResult GetAll()
        {
            var auta = _autoService.GetAuta();
            return Ok(auta);
        }

        [HttpPost]
        public IActionResult Add([FromBody] AddAutoVm addAutoVm)
        {
            if (!ModelState.IsValid)
                return BadRequest(ModelState);

            var auto = _autoService.AddAuto(addAutoVm);
            return CreatedAtAction(nameof(Get), new { id = auto.Id }, auto);
        }

        [HttpDelete("{id}")]
        public IActionResult Delete(int id)
        {
            try
            {
                var deleted = _autoService.DeleteAuto(id);
                return Ok(deleted);
            }
            catch (Exception ex)
            {
                return NotFound(ex.Message);
            }
        }
    }
}