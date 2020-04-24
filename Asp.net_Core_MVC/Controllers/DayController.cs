using System;
using Microsoft.AspNetCore.Mvc;
using Calendar.Models;

namespace Calendar.Controllers
{
    public class DayController : Controller
    {
        [HttpGet]
        public IActionResult Index()
        {
            string dateString = (string) this.RouteData.Values["id"];
            DateTime? date = MyUtils.PareStringToDate(dateString);
            if (date == null) 
            {
                return View("~/Views/Home/Error.cshtml");
            }

            EventsViewModel model = new EventsViewModel(date.Value);

            ViewData["Date"] = date.Value.ToString("yyyy-MM-dd");
            return View(model);
        }

    }
}