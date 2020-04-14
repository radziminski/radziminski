#ifndef EVENTSDIALOG_H
#define EVENTSDIALOG_H

#include <QDialog>
#include <QDate>
#include <QTableView>
#include <QModelIndex>
#include "event.h"
#include "eventsmodel.h"
#include "eventsmodelfilter.h"

namespace Ui {
class EventsDialog;
}

class EventsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventsDialog(EventsModel *model, QDate currentDate, QWidget *parent = nullptr);
    ~EventsDialog();

private slots:
     void onDelete();
     void onEdit();
     void closeWindow();
     void onAdd();

private:
    QDate currentDate;
    EventsModel *model;
    EventsModelFilter modelFiltered;
    QTableView eventsView;

    // Methods
    void windowUiInit();
    void tableUiInit();
    void resized();
    int getSelectedRow();
    QModelIndex getSelectedIndex();

};

#endif // EVENTSDIALOG_H

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************
