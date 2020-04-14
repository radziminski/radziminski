#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDate>
#include <QObject>
#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QSplitter>
#include <QTextCharFormat>
#include <QTableView>

#include "event.h"
#include "eventsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setting up UI
    ui->setupUi(this);
    this->setWindowTitle("Calendar");

    // Reading events from file
    this->readEventsFile();

    // Styling calendar
    this->calendarInit();

    // Connecting calendar click on day to function invoking another dialog
    connect(this->ui->calendar, SIGNAL(clicked(const QDate&)), this, SLOT(onDayClicked(const QDate&)));


}

MainWindow::~MainWindow()
{
    // Saving events to the file data.txt (in build directory !!!)
    this->saveEventsFile();

    delete ui;
}

void MainWindow::calendarInit()
{
    // Coloring days with events and current day
    this->updateDaysStyling();

    // Aditional color styling for calendar widget made after checking implementation of this widget
    // It may not work properly if implemtation is different - although it would result only in different colors so its
    // just additional feature
    QTableView *view = this->ui->calendar->findChild<QTableView*>("qt_calendar_calendarview");
    if (view) {
        QPalette pal = view->palette();
        pal.setColor(QPalette::Base, Qt::white);
        pal.setColor(QPalette::AlternateBase, "#e1f9e0");
        view->setPalette(pal);
    }

    QWidget *calendarNavBar = this->ui->calendar->findChild<QWidget *>("qt_calendar_navigationbar");
    if (calendarNavBar) {
        QPalette pal = calendarNavBar->palette();
        pal.setColor(calendarNavBar->backgroundRole(), "#27ae60");
        pal.setColor(calendarNavBar->foregroundRole(), "#27ae60");
        calendarNavBar->setPalette(pal);
    }

}

void MainWindow::updateDaysStyling()
{
    // Reseting all days
    this->ui->calendar->setDateTextFormat(QDate(), QTextCharFormat());

    // Coloring current date
    QTextCharFormat today;
    today.setBackground(QBrush(QColor("#35b524")));

    QTextCharFormat eventStyle;
    eventStyle.setBackground(QBrush(QColor("#d5d9f2")));
    // Coliorng days with events
    for(int i = 0; i < this->model.rowCount(); i++)
    {
        if (this->model.getEvent(i)->getDate() == QDate::currentDate())
        {
            today.setBackground(QBrush(QColor("#b2bae8")));
        }

        this->ui->calendar->setDateTextFormat(this->model.getEvent(i)->getDate(), eventStyle);
    }


    today.setFontWeight(500);
    this->ui->calendar->setDateTextFormat(QDate::currentDate(), today);
}

void MainWindow::readEventsFile()
{
    // Opening file for read
    QFile input("data.txt");

    // If file does not exist
    if (!input.open(QFile::ReadOnly | QFile::Text))
    {
        // Create this file
        QFile output("data.txt");
        if (!output.open(QFile::WriteOnly | QFile::Text))
        {
            // If cannot create either throw warning - after that app will work notmally
            QMessageBox::warning(this, "title", "Could not read nor create data file. Make sure that program can operate on files if You want to save your events.");
            return;
        }
        output.close();
        return;
    }

    // Reading events line by line
    // Events are stored in format
    // 00-00-0000,00:00,description\n
    while(!input.atEnd())
    {
        QString eventString = input.readLine();
        const int year = eventString.left(4).toInt();
        const int month = eventString.mid(5,2).toInt();
        const int day = eventString.mid(8,2).toInt();
        const int hours = eventString.mid(11,2).toInt();
        const int minutes = eventString.mid(14,2).toInt();
        QString description = eventString.mid(17,(eventString.length() - 18));
        Event newEvent(QDate(year, month, day), QTime(hours, minutes), description);

        // Saving event in events vector
        this->model.add(newEvent);
    }
    input.close();
}

void MainWindow::saveEventsFile()
{
    // At the close of application, it is saving events in a format described above to the data.txt file in program directory

    QFile output("data.txt");
    if (!output.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "title", "Could not write data file. No events were saved.");
        return;
    }
    for (int i = 0; i < this->model.rowCount(); i++)
    {
        Event currEvent = *this->model.getEvent(i);
        QString eventString = currEvent.getDate().toString("yyyy-MM-dd") + ",";
        eventString += currEvent.getTime().toString("HH:mm") + "," + currEvent.getDescription() + "\n";
        output.write(eventString.toUtf8());
    }
    output.close();
}

void MainWindow::onDayClicked(const QDate &date)
{
    EventsDialog eventDialog(&this->model, date, this);
    eventDialog.exec();
    this->updateDaysStyling();
}

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************
