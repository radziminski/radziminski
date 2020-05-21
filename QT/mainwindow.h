#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include "event.h"
#include "eventsmodel.h"

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
    void onDayClicked(const QDate &date);

private:
    Ui::MainWindow *ui;
    EventsModel model;

    // Methods
    void readEventsFile();
    void saveEventsFile();
    void calendarInit();
    void updateDaysStyling();
};

#endif // MAINWINDOW_H

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************
