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
            string id = (string) this.RouteData.Values["id"];
            int year = int.Parse(id.Substring(0, 4));
            int month = int.Parse(id.Substring(5, 2));
            int day = int.Parse(id.Substring(8, 2));
            DateTime date = new DateTime(year, month, day);
            EventsViewModel model = new EventsViewModel(date);

            ViewData["Date"] = date.ToString("yyyy-MM-dd");
            return View(model);
        }

    }
}