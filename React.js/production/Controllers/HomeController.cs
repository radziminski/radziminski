using Calendar.Models;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Web;

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
