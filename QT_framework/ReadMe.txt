******************************************************************
******************************************************************
****         CALENDAR           **********************************
******************************************************************
****  Author: Jan Radzimiński   **********************************
****  Index Number: 293052      **********************************
****  LAB 1 - EGUI course       **********************************
******************************************************************
******************************************************************

0. Table of contents:
	1. General remarks
	2. How it works
	3. Reading and saving events
	4. Restictions and assumptions
	5. Classes description

1. General remarks

This project was made for LAB 1 of EGUI course. 
It was made using QT framework, version 5.14.0.


2. How it works

After opening application user should see calendar with week days and week numbers
shown at borders. User may navigate through calendar by scrolling up and down or using 
navbar at the top of the screen. The UI of this calendar was made using QTCalendarWidget.

The current date is highlighted using bolded day and dark green (or dark blue if there are
events that day) background color. 

User may click on any date in the calendar. After that new window should appear where user can 
add, edit, and delete events on that day.
Usar can navigate through the list by clicking given event. When event is clicked, it is 
selected and blue highlight is visible. After that user may choose delete or edit button.
Delete button will simply delete event while edit button will open new window where user can
correct the data of event.
User may also add new event (also new window will me opened) or close the window to get back to calendar.


3. Reading and saving events

The application supports storing program data in txt file called data.txt.
The file consist of list of events in the format:
DATE,TIME,DESCRIPTION - each in new line
for exaple:

01-01-2020,10:00,Description1
01-02-2020,10:00,Description1
...

The application is loading (or creating new one if it doesn't exist) the file on the start (it should
be placed in the program directory). If It would not be able to create new file the message will appear,
but the program will function normally.

When the program is closed, application saves current event state into the file (data.txt) replacing previous one, so 
that when application is run again events will be up to date.

User may also use premade file ''data.txt'' with some events already saved. File is located in this directory, though it
should be moved to the directory of program. 

4. Restictions and assumptions

	- There is no limit for events for a day or characters for description of event, although for best performance
	there should not be more than 20 events per day or more than 500 characters in description
	- The identical events MAY exist - If the user wants to, he can create multiple identical events. 
	- Different events may be placed at the same time.

5. Short class descriptions:
----> event.h
Class that stores information about single event - its date, time and description. 

----> eventsmodel.h
Model Class that stores the list of all events and provide proper manipultation on them.

----> eventsmodelfilter.h
Sort and Filter proxy class which is used to filter the events from EventModel class to display only events from a given day
in a TableView in EventDialog window. It also helps sorting events that they are always sorted by time ascending. 

----> mainwindow.h
The heart of application, the first window user sees after opening the program. It shows calendar to the user and provide 
ability to select the days. 
It also colors the days to lightblue if there are any events on given day.

----> eventdialog.h
The window that opens after clicking of a given day. User may see what days was clicked by looking on title of that window. 
The window uses QTableView to display contents of eventsmodel(filter) to the user. Only events from a given day are shown.
The window has 4 buttons
	add new - for adding new event
	edit - for editing selected event
	delete - for deleteing selected event
	close - for closing the window

----> neweventdialog.h
Window that show after clicking add new or edit button. It provides two inputs to user, one for inputing / editing time of
the event and other - description. The window is made that way that when resized only the area for description increases, so
the user is able to write or read realy long descriptions. 
After making some changes user may accept them by clicking save button or discard them by clicking cancel button.  


Jan Radzimiński 293052
