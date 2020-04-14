#ifndef NEWEVENTDIALOG_H
#define NEWEVENTDIALOG_H

#include <QDialog>
#include <QDate>
#include <QTime>
#include <QString>
#include "event.h"
#include "eventsmodel.h"

namespace Ui {
class NewEventDialog;
}

class NewEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewEventDialog(EventsModel *model, QDate currentDate,  QWidget *parent = nullptr, Event *editedEvent = nullptr);
    ~NewEventDialog();

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    Ui::NewEventDialog *ui;
    QDate currentDate;
    Event *currentEvent;
    EventsModel *model;

    void inputsInit(const QTime &time, const QString &desc);
};

#endif // NEWEVENTDIALOG_H

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************
