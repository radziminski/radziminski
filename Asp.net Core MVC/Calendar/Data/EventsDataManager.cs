using System;
using System.Collections.Generic;
using Calendar.Models;
using System.IO;

namespace Calendar.Controllers
{
    public static class EventsDataManager
    {
        public static List<Event> ReadEventsFile()
        {
            List<Event> events = new List<Event>();
            try
            {   // Open the text file using a stream reader.
                using (StreamReader sr = new StreamReader("./Data/data.txt"))
                {
                    // Read the stream to a string, and write the string to the console.
                    while (!sr.EndOfStream)
                    {
                        string line = sr.ReadLine();
                        try
                        {
                            int GUIDLength = 32;
                            string id = line.Substring(0, GUIDLength);
                            string date = line.Substring(GUIDLength + 1, 10);
                            string time = line.Substring(GUIDLength + 12, 5);
                            string description = line.Substring(GUIDLength + 18, line.Length - (GUIDLength + 18));
                            DateTime eventDate = DateStringToDateTime(date, time);

                            Event newEvent = new Event() { Id = id, Date = eventDate, Description = description };
                            events.Add(newEvent);
                        } catch (IOException e)
                        {
                            Console.WriteLine("There was an error while processing database. Events might have not been loaded properly");
                            Console.WriteLine(e.Message);
                            continue;
                        }                       
                    }
                    Console.WriteLine();
                }
            }
            catch (IOException e)
            {
                Console.WriteLine("The file could not be read:");
                Console.WriteLine(e.Message);
            }

            return events;
        }

        public static bool WriteEventsFile(List<Event> Events)
        {
            try
            {   // Open the text file using a stream reader.
                using (StreamWriter sw = new StreamWriter("./Data/data.txt"))
                {
                    foreach(Event ev in Events)
                    {
                        sw.WriteLine(ev.Id + ',' + ev.Date.ToString("yyyy-MM-dd") + ',' + ev.Date.ToString("HH:mm") + ',' + ev.Description);
                    }
                }
                return true;
            }
            catch (IOException e)
            {
                Console.WriteLine("The file could not be written:");
                Console.WriteLine(e.Message);
                return false;
            }
        }

        public static void AddEvent(Event NewEvent)
        {
            List<Event> events = ReadEventsFile();
            NewEvent.Id = GenerateID();
            events.Add(NewEvent);
            WriteEventsFile(events);
        }

        public static Event GetEvent(string Id)
        {
            List<Event> events = ReadEventsFile();
            return events.Find(ev => (ev.Id == Id));
        }

        public static void AddEvent(DateTime EvDate, string EvDescription)
        {
            List<Event> events = ReadEventsFile();
            string guid = GenerateID();

            Event newEvent = new Event() { Id = guid, Date = EvDate, Description = EvDescription };
            events.Add(newEvent);
            WriteEventsFile(events);
        }

        public static bool UpdateEvent(string Id, DateTime EvDate, string EvDescription)
        {
            if (RemoveEvent(Id))
            {
                AddEvent(EvDate, EvDescription);
                return true;
            }

            return false;
        }

        public static bool RemoveEvent(DateTime EvDate, string EvDescription)
        {
            List<Event> events = ReadEventsFile();
            int index = events.FindIndex(ev => (ev.Date == EvDate && ev.Description == EvDescription));
            if (index == -1) return false;
            events.RemoveAt(index);
            WriteEventsFile(events);
            return true;
        }

        public static bool RemoveEvent(string Id)
        {
            List<Event> events = ReadEventsFile();
            int index = events.FindIndex(ev => (ev.Id == Id));
            if (index == -1) return false;
            events.RemoveAt(index);
            WriteEventsFile(events);
            return true;
        }

        public static DateTime DateStringToDateTime(string date, string time = "")
        {
            int year = int.Parse(date.Substring(0, 4));
            int month = int.Parse(date.Substring(5, 2));
            int day = int.Parse(date.Substring(8, 2));
            if (time.Length == 0)
            {
                return new DateTime(year, month, day);
            } 
            int hours = int.Parse(time.Substring(0, 2));
            int minutes = int.Parse(time.Substring(3, 2));
            return new DateTime(year, month, day, hours, minutes, 0);
        }

        private static string GenerateID()
        {
            string guid = Guid.NewGuid().ToString("N");
            return guid;
        }
    }
}