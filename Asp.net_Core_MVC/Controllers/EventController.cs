using System;
using Microsoft.AspNetCore.Mvc;
using Calendar.Models;

namespace Calendar.Controllers
{
    public class EventController : Controller
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

            EventEditorViewModel model = new EventEditorViewModel(date.Value);
            return View(model);
        }

        [HttpGet]
        public IActionResult Edit()
        {
            string id = (string) this.RouteData.Values["id"];
            if (id == null) return View("~/Views/Home/Error.cshtml");;
            EventsViewModel allEventsModel = new EventsViewModel();
            Event edited = allEventsModel.GetEventById(id);

            if (edited == null) return View("~/Views/Home/Error.cshtml");

            EventEditorViewModel model = new EventEditorViewModel(edited.Id, edited.Date, edited.Description);
      
            return View("Index", model);
        }

        [HttpPut]
        public JsonResult Update(int Year, int Month, int Day, int Hours, int Minutes, string Description)
        {
            string id = (string)this.RouteData.Values["id"];
            Console.WriteLine("Updating: " + id);
            EventsViewModel model = new EventsViewModel();
            if (model.UpdateEvent(id, new DateTime(Year, Month, Day, Hours, Minutes, 0), Description))
                return new JsonResult(new { StatusCode = 201 });
            return new JsonResult(new { StatusCode = 400 });
        }

        [HttpPost]
        public JsonResult Add(int Year, int Month, int Day, int Hours, int Minutes, string Description)
        {
            EventsViewModel model = new EventsViewModel();
            model.AddEvent(new DateTime(Year, Month, Day, Hours, Minutes, 0), Description);
            return new JsonResult(new { StatusCode = 201 });
        }

        [HttpDelete]
        public JsonResult Delete()
        {
            string id = (string) this.RouteData.Values["id"];
            EventsViewModel model = new EventsViewModel();
            bool status = model.RemoveEventById(id);
            if (status)
                return new JsonResult(new { StatusCode = 204 });
            return new JsonResult(new { StatusCode = 400 });
        }
    }
}