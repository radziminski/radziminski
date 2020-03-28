#include "neweventdialog.h"
#include "ui_neweventdialog.h"

NewEventDialog::NewEventDialog(QVector<Event> *events, QDate currentDate, QWidget *parent, Event *editedEvent) :
    QDialog(parent),
    ui(new Ui::NewEventDialog)
{
    // Setting up UI
    ui->setupUi(this);

    this->events = events;
    this->currentDate = currentDate;

    // Window title
    this->setWindowTitle("New event on " + currentDate.toString("dd-MM-yyyy"));
    if (editedEvent) this->setWindowTitle("Editing event on " + currentDate.toString("dd-MM-yyyy"));

    // editedEvent pointer is supplied only when user is editing existing event
    if (editedEvent)
    {
        this->currentEvent = editedEvent;
        this->inputsInit(editedEvent->time, editedEvent->description);
    } else {
        this->currentEvent = nullptr;
    }
}

NewEventDialog::~NewEventDialog()
{
    delete ui;
}

void NewEventDialog::inputsInit(QTime time, QString desc)
{
    this->findChild<QTimeEdit*>("eventTime")->setTime(time);
    this->findChild<QTextEdit*>("eventDesc")->setText(desc);
}

void NewEventDialog::on_cancelBtn_clicked()
{
    this->reject();
    this->close();
}

void NewEventDialog::on_saveBtn_clicked()
{
    QTime time = this->findChild<QTimeEdit*>("eventTime")->time();
    QTextEdit *desc = this->findChild<QTextEdit*>("eventDesc");

    // Overwriting event in case of edit
    if (this->currentEvent)
    {
        for (int i = 0; i < this->events->length(); i++)
        {
               if (this->currentEvent->date == this->events->value(i).date && this->currentEvent->time == this->events->value(i).time && (this->currentEvent->description == this->events->value(i).description || (this->currentEvent->description.isEmpty() && this->events->value(i).description.isEmpty())))
               {
                   this->events->remove(i);
                   break;
               }

        }
    }
    // Adding new event to Events vector
    Event newEvent = {this->currentDate, time, desc->toPlainText()};
    this->events->push_back(newEvent);

    this->accept();
    this->close();

}
