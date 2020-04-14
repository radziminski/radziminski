#ifndef EVENTS_MODEL_H
#define EVENTS_MODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QVariant>
#include <QModelIndex>
#include <QList>
#include "event.h"

class EventsModel : public QAbstractTableModel
{
public:
    EventsModel(QObject *parent = nullptr);

    void add(const Event &event);
    void remove(const int &id);
    void remove(const Event &event);

    int rowCount(const QModelIndex &) const override;
    int rowCount() const;
    int columnCount(const QModelIndex &) const override { return 3; }

    Event* getEvent(const int &id) { return &events[id]; }
    Event* getEvent(const Event &event);

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QList<Event> events;
};

#endif // EVENTS_MODEL_H

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************
