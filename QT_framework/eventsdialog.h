#ifndef EVENTSDIALOG_H
#define EVENTSDIALOG_H

#include <QDialog>
#include <QDate>
#include <QVector>
#include <QButtonGroup>
#include "event.h"

namespace Ui {
class EventsDialog;
}

class EventsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventsDialog(QVector<Event> *events, QDate currentDate, QWidget *parent = nullptr);
    ~EventsDialog();

private slots:
     void deleteButtonWasClicked(int);
     void editEvent(int);
     void closeWindow();
     void addEvent();

private:

    QDate currentDate;
    QVector<Event> *events;
    QButtonGroup editBtns;
    QButtonGroup deleteBtns;


    // Methods
    void renderEvents(bool firstTime = false);
    static bool sortRule(const Event &ev1, const Event &ev2);



};

#endif // EVENTSDIALOG_H
