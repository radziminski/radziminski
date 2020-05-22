using Calendar.Models;
using System;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Text.Json;

namespace Calendar.Controllers
{
    public class ApiController : Controller
    {

        // Getting all events or events filtered by day
        [HttpGet]
        public JsonResult Events()
        {
            // Getting events from specific date if id is supplied
            if (this.RouteData.Values["id"] != null)
            {
                // Getting id and date
                string dateString = (string)this.RouteData.Values["id"];
                DateTime? date = MyUtils.PareStringToDate(dateString);

                // Wrong param supplied
                if (date == null)
                {
                    return new JsonResult(new
                    {
                        status = "error",
                        message = "Wrong route param provided. Please use format \"yyyy-mm-dd\""
                    });
                }

                // Returning events from specific date
                EventsViewModel model = new EventsViewModel(date.Value);
                List<Event> eventsList = model.GetAllEvents();
                String data = JsonSerializer.Serialize(eventsList);

                // Sending response
                return new JsonResult(new
                {
                    status = "success",
                    data = data
                });
            }

            // Detting all events
            EventsViewModel eventsModel = new EventsViewModel();
            List<Event> events = eventsModel.GetAllEvents();
            String result = JsonSerializer.Serialize(events);

            // Sending Response
            return new JsonResult(new
            {
                status = "success",
                data = result
            });
        }

        // Getting single event by id
        [HttpGet]
        public JsonResult Event()
        {
            // Id must be supplied
            if (this.RouteData.Values["id"] == null)
            {
                return new JsonResult(new
                {
                    status = "error",
                    message = "Please provide Id of event."
                });
            }

            // FInding the event
            EventsViewModel model = new EventsViewModel();
            Event ev = model.GetEventById(this.RouteData.Values["id"].ToString());
            String result = JsonSerializer.Serialize(ev);

            return new JsonResult(new
            {
                status = "success",
                data = result
            });
        }

        // Updating Event By Id
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
            return new JsonResult(new { status = "error", message = "Please provide proper event ID." });
        }

        // Creating New Event
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

        // Deleting Event By Id
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
