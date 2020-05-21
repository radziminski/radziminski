using System;

namespace Calendar.Controllers
{
    public static class MyUtils
    {
        // Format yyyy-MM-dd
        public static DateTime? PareStringToDate(string Date)
        {
            if (Date == null || Date.Length < 9) 
            {
                return null;
            }
            int year;
            int month;
            int day;
            if (!int.TryParse(Date.Substring(0, 4), out year) || 
                !int.TryParse(Date.Substring(5, 2), out month) || 
                !int.TryParse(Date.Substring(8, 2), out day))
                return null;
            if (year > 2050 || year < 1900 || month < 1 || month > 11 || day < 1 || day > 31)
                return null;
           return new DateTime(year, month, day, 0, 0, 0);
        }
    }
}