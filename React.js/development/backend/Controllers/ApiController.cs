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
            String result = JsonSerializer.Serialize(events);
            return new JsonResult(new
            {
                status = "success",
                data = result
            });
        }

        [HttpGet]
        public JsonResult Event()
        {
            if (this.RouteData.Values["id"] == null)
            {
                return new JsonResult(new
                {
                    status = "error"
                });
            }
            EventsViewModel model = new EventsViewModel();
            Event ev = model.GetEventById(this.RouteData.Values["id"].ToString());
            String result = JsonSerializer.Serialize(ev);
            return new JsonResult(new
            {
                status = "success",
                data = result
            });
        }

        [HttpPut]
        public JsonResult UpdateEvent(int Year, int Month, int Day, int Hours, int Minutes, string Description)
        {
            string id = (string)this.RouteData.Values["id"];
            EventsViewModel model = new EventsViewModel();
            if (model.UpdateEvent(id, new DateTime(Year, Month, Day, Hours, Minutes, 0), Description))
                return new JsonResult(new
                {
                    status = "success",
                    data = new
                    {
                        Id = id,
                        Date = new DateTime(Year, Month, Day, Hours, Minutes, 0),
                        Description = Description
                    }
                });
            return new JsonResult(new { status = "error" });
        }

        [HttpPost]
        public JsonResult AddEvent(int Year, int Month, int Day, int Hours, int Minutes, string Description)
        {
            EventsViewModel model = new EventsViewModel();
            model.AddEvent(new DateTime(Year, Month, Day, Hours, Minutes, 0), Description);

            return new JsonResult(new
            {
                status = "success",
                data = new
                {
                    Date = new DateTime(Year, Month, Day, Hours, Minutes, 0),
                    Description = Description
                }
            });
        }

        [HttpDelete]
        public JsonResult DeleteEvent()
        {
            string id = (string)this.RouteData.Values["id"];
            EventsViewModel model = new EventsViewModel();
            bool status = model.RemoveEventById(id);
            if (status)
                return new JsonResult(new { });
            return new JsonResult(new { status = "error" });
        }

        public IActionResult Error()
        {
            return new JsonResult(new { status = "error" });
        }
    }
}
