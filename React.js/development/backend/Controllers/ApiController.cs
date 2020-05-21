using Calendar.Models;
using System;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace Calendar.Controllers
{
    public class ApiController : Controller
    {

        [HttpGet]
        public JsonResult Events()
        {
            // getting events from specific date
            if (this.RouteData.Values["id"] != null)
            {
                string dateString = (string)this.RouteData.Values["id"];
                DateTime? date = MyUtils.PareStringToDate(dateString);

                // wrong param supplied
                if (date == null)
                {
                    return new JsonResult(new
                    {
                        status = "error",
                        message = "Wrong route param provided. Please use format \"yyyy-mm-dd\""
                    });
                }

                // returning events from specific date
                EventsViewModel model = new EventsViewModel(date.Value);
                List<Event> eventsList = model.GetAllEvents();
                String data = JsonSerializer.Serialize(eventsList);
                return new JsonResult(new
                {
                    status = "success",
                    data = data
                });
            }

            // getting all events
            EventsViewModel eventsModel = new EventsViewModel();
            List<Event> events = eventsModel.GetAllEvents();
            String x = JsonSerializer.Serialize(events);
            return new JsonResult(new
            {
                status = "success",
                data = x
            });
        }

        [HttpPut]
        public JsonResult UpdateEvent(int Year, int Month, int Day, int Hours, int Minutes, string Description)
        {
            string id = (string)this.RouteData.Values["id"];
            Console.WriteLine("Updating: " + id);
            EventsViewModel model = new EventsViewModel();
            if (model.UpdateEvent(id, new DateTime(Year, Month, Day, Hours, Minutes, 0), Description))
                return new JsonResult(new { StatusCode = 201 });
            return new JsonResult(new { StatusCode = 400 });
        }

        [HttpPost]
        public JsonResult AddEvent(int Year, int Month, int Day, int Hours, int Minutes, string Description)
        {
            EventsViewModel model = new EventsViewModel();
            model.AddEvent(new DateTime(Year, Month, Day, Hours, Minutes, 0), Description);
            return new JsonResult(new { StatusCode = 201 });
        }

        [HttpDelete]
        public JsonResult DeleteEvent()
        {
            string id = (string)this.RouteData.Values["id"];
            EventsViewModel model = new EventsViewModel();
            bool status = model.RemoveEventById(id);
            if (status)
                return new JsonResult(new { StatusCode = 204 });
            return new JsonResult(new { StatusCode = 400 });
        }

        public IActionResult Error()
        {
            return new JsonResult(new { status = "error" });
        }
    }
}
