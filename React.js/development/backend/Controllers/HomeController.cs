using Calendar.Models;
using Microsoft.AspNetCore.Mvc;
using System;

namespace Calendar.Controllers
{
    public class HomeController : Controller
    {

        public IActionResult Index()
        {
            var staticPageToRender = new FilePathResult("~/img/test.html", "text/html");
            return staticPageToRender;
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
