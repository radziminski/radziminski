using Calendar.Models;
using Microsoft.AspNetCore.Mvc;
using System;

namespace Calendar.Controllers
{
    public class HomeController : Controller
    {

        public IActionResult Index()
        {
            EventsViewModel events = new EventsViewModel();
            ViewData["CurrDate"] = DateTime.Now.ToString("yyyy-MM-dd");
            if (this.RouteData.Values["id"] != null)
            {
                string dateString = (string) this.RouteData.Values["id"];
                DateTime? date = MyUtils.PareStringToDate(dateString);
                if (date == null) 
                {
                    return View("~/Views/Home/Error.cshtml");
                }
                ViewData["CurrDate"] = date.Value.ToString("yyyy-MM-dd");
            }

            return View(events);
        }

        public IActionResult Error()
        {
            return View();
        }

        //[ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        //public IActionResult Error()
        //{
        //    return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        //}
    }
}
