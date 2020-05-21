using System;

namespace Calendar.Models
{
    public class EventEditorViewModel
    {
        public string Id { get; set; }
        public DateTime Date { get; set; }
        public string Description { get; set; }
        public bool Edited { get; set; }

        public EventEditorViewModel(DateTime EvDate)
        {
            Id = "0";
            Date = EvDate;
            Description = "";
            Edited = false;
        }
        
        public EventEditorViewModel(string EvId, DateTime EvDate, string EvDescription)
        {
            Id = EvId;
            Date = EvDate;
            Description = EvDescription;
            Edited = true;
        }

        
    }
}
