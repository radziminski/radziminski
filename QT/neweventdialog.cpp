#include "neweventdialog.h"
#include "ui_neweventdialog.h"
#include <QWidget>

NewEventDialog::NewEventDialog(EventsModel *model, QDate currentDate, QWidget *parent, Event *editedEvent) :
    QDialog(parent),
    ui(new Ui::NewEventDialog)
{
    // Setting up UI
    ui->setupUi(this);
    this->model = model;
    this->currentDate = currentDate;

    // Window title
    this->setWindowTitle("New event on " + currentDate.toString("dd-MM-yyyy"));
    if (editedEvent) this->setWindowTitle("Editing event on " + currentDate.toString("dd-MM-yyyy"));

    // editedEvent pointer is supplied only when user is editing existing event
    if (editedEvent)
    {
        this->currentEvent = editedEvent;
        this->inputsInit(editedEvent->getTime(), editedEvent->getDescription());
    } else {
        this->currentEvent = nullptr;
    }

    // Connecting buttons
    connect(this->ui->saveBtn, SIGNAL(clicked()), this, SLOT(onSaveClicked()));
    connect(this->ui->cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
}

NewEventDialog::~NewEventDialog()
{
    delete ui;
}

void NewEventDialog::inputsInit(const QTime &time, const QString &desc)
{
    // Passing time and desc from edited event to inputs
    ui->eventTime->setTime(time);
    ui->eventDesc->setText(desc);
}

void NewEventDialog::onCancelClicked()
{
    // Cancel
    this->reject();
    this->close();
}

void NewEventDialog::onSaveClicked()
{
    QTime time = ui->eventTime->time();

    // Overwriting event in case of edit - deletieng the previous version and adding with corrected time and description
    if (this->currentEvent)
        this->model->remove(*this->currentEvent);

    Event newEvent = {this->currentDate, time, ui->eventDesc->toPlainText()};

    // Adding new event to Events vector
    this->model->add(newEvent);
    this->accept();
    this->close();

}

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************
