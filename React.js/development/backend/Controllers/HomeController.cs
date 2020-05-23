using Calendar.Models;
using Microsoft.AspNetCore.Mvc;
using System;

namespace Calendar.Controllers
{
    public class HomeController : Controller
    {

        public IActionResult Index()
        {
            return View();
        }
    }
}
