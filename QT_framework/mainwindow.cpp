#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QRegularExpression>
#include <QDate>
#include <QDebug>
#include <QObject>
#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QSplitter>
#include "event.h"
#include "eventsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setting up UI
    ui->setupUi(this);
    this->setWindowTitle("Calendar");
    this->buttonsInit();

    // Reading events from file
    this->readEventsFile();

    // Setting current day
    QDate *today = new QDate(QDate::currentDate());
    today->setDate(today->year(), today->month(), 1);
    this->currentDate = *today;
    delete today;

    this->updateMonthLabel();
    this->renderDays();

    // Connecting days to a event dialog controller
    connect(&this->days, SIGNAL(buttonClicked(int)), this, SLOT(buttonWasClicked(int)));
}

MainWindow::~MainWindow()
{
    // Saving events to the file data.txt (in build directory !!!)
    this->saveEventsFile();
    delete ui;
}

void MainWindow::readEventsFile()
{
    QFile input("data.txt");
    if (!input.open(QFile::ReadOnly | QFile::Text))
    {
        QFile output("data.txt");
        if (!output.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this, "title", "Could not read nor create data file. Make sure that program can operate on files if You want to save your events.");
            return;
        }
        output.close();
        return;
    }
    while(!input.atEnd())
    {
        QString eventString = input.readLine();
        const int year = eventString.left(4).toInt();
        const int month = eventString.mid(5,2).toInt();
        const int day = eventString.mid(8,2).toInt();
        const int hours = eventString.mid(11,2).toInt();
        const int minutes = eventString.mid(14,2).toInt();
        QString description = eventString.mid(17,(eventString.length() - 18));
        Event newEvent = {QDate(year, month, day), QTime(hours, minutes), description};
        this->events.push_back(newEvent);
    }
    input.close();
}

void MainWindow::saveEventsFile()
{
    QFile output("data.txt");
    if (!output.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "title", "Could not write data file. No events were saved.");
        return;
    }
    for (int i = 0; i < this->events.length(); i++)
    {
        Event currEvent = this->events.value(i);
        QString eventString = currEvent.date.toString("yyyy-MM-dd") + ",";
        eventString += currEvent.time.toString("HH:mm") + "," + currEvent.description + "\n";
        output.write(eventString.toUtf8());
    }
    output.close();
}


void MainWindow::buttonsInit()
{
    for (int i = 1; i <= 42; i++)
    {
        QString s = QString::number(i);
        s = "day" + s;
        QAbstractButton* button = this->findChild<QPushButton*>(s);
        this->days.addButton(button, i);
    }
}

void MainWindow::updateMonthLabel()
{
    QString monthName = this->currentDate.toString("MMMM yyyy");
    monthName = monthName.toUpper();
    this->findChild<QLabel*>("monthLabel")->setText(monthName);
}

void MainWindow::nextMonth() {
    this->currentDate = this->currentDate.addMonths(1);
    this->currentDate.setDate(this->currentDate.year(), this->currentDate.month(), 1);
    this->updateMonthLabel();
}

void MainWindow::prevMonth() {
    this->currentDate = this->currentDate.addMonths(-1);
    this->currentDate.setDate(this->currentDate.year(), this->currentDate.month(), 1);
    this->updateMonthLabel();
}

void MainWindow::renderDays()
{
    QDate *today = new QDate(this->currentDate);
    const int currentWeekDay = today->dayOfWeek() - 1;
    const int currentMonth = today->month();
    *today = today->addDays(-currentWeekDay);

    // Iterating through all buttons representing days and assigning proper number and styling to them
    for (int i = 1; i <= 42; i++)
    {
        QAbstractButton* button = this->days.button(i);
        QString s = QString::number(today->day());
        button->setText(s);

        if (today->month() != currentMonth)
        {
            button->setStyleSheet("* {background-color: white; color: gray; border-width: 0px;} *:hover{border-width: 1px;}");
            // I used checkable proprty to mark days that belong to other month
            button->setCheckable(false);
            if (today->dayOfWeek() == 7)
            {
                button->setStyleSheet(button->styleSheet().append("* {color: #e29191}"));
            }  else if (today->dayOfWeek() == 6)
            {
                button->setStyleSheet(button->styleSheet().append("* {color: #92c8e8}"));
            }

        } else
        {
            button->setStyleSheet("* {background-color: #F7F7F7; border-width: 1px; border-style: solid; border-color: #E6E6E6; color: black;} *:hover{ border-color: #B6B6B6;}");
            button->setCheckable(true);

            for (int j = 0; j < this->events.length(); j++)
            {
                if (this->events.value(j).date == *today)
                {
                    button->setStyleSheet(button->styleSheet().append("* {background-color: #C8CEF4;}"));
                }
            }

            if (*today == QDate::currentDate())
            {
                button->setStyleSheet(button->styleSheet().append("* {border-color: red}"));
            }
            if (today->dayOfWeek() == 7)
            {
                button->setStyleSheet(button->styleSheet().append("* {color: red}"));
            } else if (today->dayOfWeek() == 6)
            {
                button->setStyleSheet(button->styleSheet().append("* {color: #515de8}"));
            }
        }


        *today = today->addDays(1);
    }

    delete today;
}

void MainWindow::on_nextMonth_clicked()
{
    this->nextMonth();
    this->renderDays();
}

void MainWindow::on_prevMonth_clicked()
{
    this->prevMonth();
    this->renderDays();
}

void MainWindow::buttonWasClicked(int buttonID)
{
    QAbstractButton *button = this->days.button(buttonID);
    QString day = button->text();

    // Changing the month if clicked button was not from current month
    if (!button->isCheckable())
    {
        if (day.toInt() < 15) {
            this->nextMonth();
            button = this->days.button(buttonID - 7);
            if (button->isCheckable()) {
                if (buttonID > 35) button = this->days.button(buttonID - 35);
                else button = this->days.button(buttonID - 28);

            } else {
                button = this->days.button(buttonID - 28);

            }
            this->renderDays();
            if (!button->isCheckable()) button = this->days.button(buttonID - 28);
        }
        else {
            this->prevMonth();
            this->renderDays();
            button = this->days.button(35 + buttonID);
            if (!button->isCheckable()) button = this->days.button(28 + buttonID);
        }


    };

    // Marking clicked day with light blue color to visualize which day events user is editing
    button->setStyleSheet(button->styleSheet().append("* {background-color: #6ad8e2;}"));

    QDate currentDate(this->currentDate.year(), this->currentDate.month(), day.toInt());

    // Displaying dialog
    EventsDialog eventDialog(&this->events, currentDate, this);
    eventDialog.exec();

    this->renderDays();
}
