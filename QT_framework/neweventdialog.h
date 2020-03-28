#ifndef NEWEVENTDIALOG_H
#define NEWEVENTDIALOG_H

#include <QDialog>
#include <QVector>
#include <QDate>
#include <QTime>
#include <QString>
#include "event.h"

namespace Ui {
class NewEventDialog;
}

class NewEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewEventDialog( QVector<Event> *events, QDate currentDate,  QWidget *parent = nullptr, Event *editedEvent = nullptr);
    ~NewEventDialog();

private slots:

    void on_cancelBtn_clicked();
    void on_saveBtn_clicked();

private:
    Ui::NewEventDialog *ui;
    QVector<Event> *events;
    QDate currentDate;
    Event *currentEvent;

    void inputsInit(QTime time, QString desc);
};

#endif // NEWEVENTDIALOG_H
