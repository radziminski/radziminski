# Graphical User Interfaces Project
Simple calendar application made for graphical user interfaces (EGUI) course laboratories in 3 different technologies (QT Framework, ASP.NET Core and React).

## Project Description
The task was to:
  - Write simple Calendar application using given technology (under linux) having three simple screens
  - Data should be stored in text file (format to be designed by the student)
#### Main window
  - In that phase application simply present data
  - Single month is visible
  - For days where events exist background colour is light blue
  - User may select a day to edit that day events
#### Single day window
  - An ordered (by time) events for a day is displayed
  - User may delete an event
  - User may press Add new to go to Event screen (with empty event)
  - User may press edit to go to Event screen (with selected event)
#### Single event window
  - User may enter time and description and Save changes (which creates an event or updates existing one)
  - User may press Cancel (which closes a window without doing any changes)
  
## Usage
#### Lab 1: QT Framework
In QT_Framework folder:
```
qmake
make
cd bin
./MyCalendar
```
#### Lab 2: ASP.NET Core MVC
In ASP.NET_Core_MVC folder:
```
dotnet build
dotnet run
```
