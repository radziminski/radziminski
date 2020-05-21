#include "eventsdialog.h"
#include <QLabel>
#include <QSplitter>
#include <QBoxLayout>
#include <QPushButton>
#include <QLayoutItem>
#include <QDesktopWidget>
#include <QTableView>
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>
#include "neweventdialog.h"


EventsDialog::EventsDialog(EventsModel *model, QDate currentDate, QWidget *parent) :
    QDialog(parent)
{
    // Setting up model (and filtering only events form  given day)
    this->model = model;
    this->modelFiltered.setDateFilter(currentDate);
    this->modelFiltered.setSourceModel(model);
    this->modelFiltered.sort(0);
    this->currentDate = currentDate;

    // Setting window styling
    this->setWindowTitle(currentDate.toString("dd-MM-yyyy"));
    this->setMinimumWidth(380);
    this->setStyleSheet("* {background-color: #efffea;} QPushButton {background-color: #27ae60; border: none; color: white; font-weight: 400} QPushButton:hover {background-color: #2bc46b;} QPushButton:pressed {background-color: #1d9950;}");

    // Makes the window resize more nicely
    this->resize(QDesktopWidget().availableGeometry(this).size() * 0.15);
    this->setModal(true);

    // Setting window UI
    this->resized();
    this->windowUiInit();
}

EventsDialog::~EventsDialog()
{
    // Destructor
}

void EventsDialog::resized()
{
    // Increasing window size if event was added (up to certain point - then scroll bar appears)
    int minimumHeight = this->modelFiltered.rowCount() * 30 + 101;
    if (minimumHeight > 500) minimumHeight = 500;
    this->setMinimumHeight(minimumHeight);
}

void EventsDialog::tableUiInit()
{
    this->eventsView.setModel(&this->modelFiltered);
    this->eventsView.showMaximized();
    this->eventsView.horizontalHeader()->setStretchLastSection(true);
    this->eventsView.verticalHeader()->hide();
    this->eventsView.setSelectionBehavior(QAbstractItemView::SelectRows);
    this->eventsView.setSelectionMode( QAbstractItemView::SingleSelection );
    this->eventsView.setStyleSheet("background-color: white");
}

void EventsDialog::windowUiInit()
{
    this->tableUiInit();

    // And re-render Layout
    QBoxLayout *windowLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    windowLayout->setMargin(15);
    // Creating table view based on model

    QBoxLayout *tableLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    tableLayout->addWidget(&this->eventsView);
    windowLayout->addLayout(tableLayout);

    // Creating add and close buttons
    QBoxLayout *rowSplitter = new QBoxLayout(QBoxLayout::LeftToRight);
    QPushButton *add = new QPushButton("Add new", this);
    add->setMinimumHeight(40);
    QPushButton *close = new QPushButton("Close", this);
    close->setMinimumHeight(40);
    QPushButton *edit = new QPushButton("Edit", this);
    edit->setMinimumHeight(40);
    QPushButton *deleteBtn = new QPushButton("Delete", this);
    deleteBtn->setMinimumHeight(40);
    rowSplitter->addWidget(add);
    rowSplitter->addWidget(edit);
    rowSplitter->addWidget(deleteBtn);
    rowSplitter->addWidget(close);
    windowLayout->addLayout(rowSplitter);

    connect(close, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(add, SIGNAL(clicked()), this, SLOT(onAdd()));
    connect(edit, SIGNAL(clicked()), this, SLOT(onEdit()));
    connect(deleteBtn, SIGNAL(clicked()), this, SLOT(onDelete()));


    this->setLayout(windowLayout);
    // Making window resize more nicely
    this->resize(QDesktopWidget().availableGeometry(this).size() * 0.15);

}

int EventsDialog::getSelectedRow()
{
    QModelIndexList selectedRows = this->eventsView.selectionModel()->selectedRows();

    int row = -1;
    for(QModelIndex modelIdx : selectedRows) {
        row = modelIdx.row();
    }

    return row;
}

QModelIndex EventsDialog::getSelectedIndex()
{
    QModelIndexList selectedRows = this->eventsView.selectionModel()->selectedRows();
    return selectedRows.value(0);
}

void EventsDialog::onAdd()
{
    NewEventDialog *newEventDialog = new NewEventDialog(this->model, this->currentDate, this);

    newEventDialog->setModal(true);

    // Displaying dialog and if it accepts (the user didnt cancel) then we should rerender events since they was changed
    if(newEventDialog->exec())
    {
        this->resized();
        this->modelFiltered.sort(0);
    }
}

void EventsDialog::onEdit()
{
    int selectedRow = this->getSelectedRow();
    if (selectedRow < 0)
    {
        QMessageBox::warning(this, "Choose event!", "Please, select event from the list to edit it.");
        return;
    }
    QTime time = QModelIndex(this->modelFiltered.index(selectedRow, 0)).data().toTime();
    QString desc = QModelIndex(this->modelFiltered.index(selectedRow, 1)).data().toString();
    Event *edited = this->model->getEvent(Event(this->currentDate, time, desc));
    NewEventDialog *newEventDialog = new NewEventDialog(this->model, this->currentDate, this, edited);
    newEventDialog->setModal(true);
    if (newEventDialog->exec())
    {
        this->modelFiltered.sort(0);
    }
}

void EventsDialog::onDelete()
{
    int selectedRow = this->getSelectedRow();
    if (selectedRow < 0)
    {
        QMessageBox::warning(this, "Choose event!", "Please, select event from the list to delete it.");
        return;
    }
    QTime time = QModelIndex(this->modelFiltered.index(selectedRow, 0)).data().toTime();
    QString desc = QModelIndex(this->modelFiltered.index(selectedRow, 1)).data().toString();
    this->model->remove(Event(this->currentDate, time, desc));
    this->resized();
}

void EventsDialog::closeWindow()
{
    this->close();
}

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************
