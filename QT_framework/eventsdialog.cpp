#include "eventsdialog.h"
#include <QLabel>
#include <QVector>
#include <QSplitter>
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QDebug>
#include <QLayoutItem>
#include <QGroupBox>
#include <QDesktopWidget>
#include "neweventdialog.h"

EventsDialog::EventsDialog(QVector<Event> *events, QDate currentDate, QWidget *parent) :
    QDialog(parent)
{
    this->events = events;
    this->setWindowTitle(currentDate.toString("dd-MM-yyyy"));
    this->currentDate = currentDate;

    resize(QDesktopWidget().availableGeometry(this).size() * 0.15);
    this->setModal(true);
    this->renderEvents(true);
}

EventsDialog::~EventsDialog()
{
}

void EventsDialog::deleteButtonWasClicked(int id)
{
    this->events->remove(id);
    this->renderEvents();
}

void EventsDialog::renderEvents(bool firstTime)
{

    if (!firstTime)
    {
        disconnect(&this->deleteBtns, SIGNAL(buttonClicked(int)), this, SLOT(deleteButtonWasClicked(int)));
        disconnect(&this->editBtns, SIGNAL(buttonClicked(int)), this, SLOT(editEvent(int)));
        qDeleteAll(this->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    }
    delete layout();

    QBoxLayout *windowLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    QBoxLayout *rowSplitterTitles = new QBoxLayout(QBoxLayout::LeftToRight);
    rowSplitterTitles->addWidget(new QLabel("Time: ", this));
    rowSplitterTitles->addWidget(new QLabel("Description:", this));
    rowSplitterTitles->addWidget(new QLabel("", this));
    rowSplitterTitles->addWidget(new QLabel("", this));
    windowLayout->addLayout(rowSplitterTitles);

    // Generating events
    bool flag = false;
    std::sort(this->events->begin(), this->events->end(), this->sortRule);
    for (int i = 0; i < this->events->length(); i++)
    {

        QBoxLayout *rowSplitter = new QBoxLayout(QBoxLayout::LeftToRight);
        if (this->events->value(i).date == currentDate)
        {
            flag = true;
            rowSplitter->addWidget(new QLabel(events->value(i).time.toString("hh:mm"), this));
            QLabel *desc = new QLabel(events->value(i).description, this);
            desc->setMaximumWidth(150);
            rowSplitter->addWidget(desc);
            this->editBtns.addButton(new QPushButton("Edit", this), i);
            rowSplitter->addWidget( this->editBtns.button(i));
            this->deleteBtns.addButton(new QPushButton("Delete", this), i);
            rowSplitter->addWidget( this->deleteBtns.button(i));
        }
        windowLayout->addLayout(rowSplitter);
    }
    if (!flag) {
        QBoxLayout *rowSplitter = new QBoxLayout(QBoxLayout::LeftToRight);
        rowSplitter->addWidget(new QLabel("There are no events on that day.", this));
        windowLayout->addLayout(rowSplitter);
    } else {
        // Connecting edit and delete buttons
        connect(&this->deleteBtns, SIGNAL(buttonClicked(int)), this, SLOT(deleteButtonWasClicked(int)));
        connect(&this->editBtns, SIGNAL(buttonClicked(int)), this, SLOT(editEvent(int)));
    }



    // Creating add and close buttons
    QBoxLayout *rowSplitter = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *add = new QPushButton("Add new", this);
    QPushButton *close = new QPushButton("Close", this);
    rowSplitter->addWidget(add);
    rowSplitter->addWidget(close);
    windowLayout->addLayout(rowSplitter);

    connect(close, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(add, SIGNAL(clicked()), this, SLOT(addEvent()));

    this->setLayout(windowLayout);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.15);
}


bool EventsDialog::sortRule(const Event &ev1, const Event &ev2)
{
    if (ev1.time == ev2.time)
    {
        return ev1.description < ev2.description;
    }
    return ev1.time < ev2.time;
}

void EventsDialog::addEvent()
{
    NewEventDialog *newEventDialog = new NewEventDialog(this->events, this->currentDate, this);

    newEventDialog->setModal(true);
    if(newEventDialog->exec())
        this->renderEvents();

}

void EventsDialog::editEvent(int id)
{
    Event *editedEvent = new Event(this->events->value(id));
    NewEventDialog *newEventDialog = new NewEventDialog(this->events, this->currentDate, this, editedEvent);

    if(newEventDialog->exec())
    {
        this->renderEvents();
        delete editedEvent;
    }

}

void EventsDialog::closeWindow()
{
    this->close();
}
