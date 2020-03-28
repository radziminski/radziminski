#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QButtonGroup>
#include <QVector>
#include "event.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_nextMonth_clicked();
    void on_prevMonth_clicked();
    void buttonWasClicked(int);

private:

    QVector<Event> events;
    Ui::MainWindow *ui;
    QDate currentDate;
    QButtonGroup days;


    // Methods
    void readEventsFile();
    void saveEventsFile();
    void addEvent(Event);
    bool removeEvent(int position);
    void renderDays();
    void nextMonth();
    void prevMonth();
    void updateMonthLabel();
    void buttonsInit();
};

#endif // MAINWINDOW_H
