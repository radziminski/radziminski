using Calendar.Controllers;
using System;
using System.Collections.Generic;

namespace Calendar.Models
{
    public class EventsViewModel
    {
        DateTime? _currDate;

        public EventsViewModel()
        {
            _currDate = null;
        }

        public EventsViewModel(DateTime currDate)
        {
            _currDate = currDate;
        }
        
        public List<Event> GetAllEvents()
        {
            List<Event> events = EventsDataManager.ReadEventsFile();
            if (_currDate != null) events.RemoveAll(ev => ev.Date.ToString("yyyy-MM-dd") != _currDate.Value.ToString("yyyy-MM-dd"));
            SortEvents(events);
            return events;
        }

        public void AddEvent(Event Ev)
        {
            EventsDataManager.AddEvent(Ev);
        }

        public Event GetEventById(string Id)
        {
            return EventsDataManager.GetEvent(Id);
        }
        
        public void AddEvent(DateTime Date, string Description)
        {
            EventsDataManager.AddEvent(Date, Description);
        }

        public bool UpdateEvent(string Id, DateTime Date, string Description)
        {
            return EventsDataManager.UpdateEvent(Id, Date, Description);
        }

        public bool RemoveEventById(string Id)
        {
            return EventsDataManager.RemoveEvent(Id);
        }

        private void SortEvents(List<Event> Events)
        {
            Events.Sort((ev1, ev2) => ev1.Date.CompareTo(ev2.Date));
        }
    }
}
