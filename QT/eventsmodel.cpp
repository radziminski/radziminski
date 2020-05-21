#include "eventsmodel.h"

EventsModel::EventsModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int EventsModel::rowCount(const QModelIndex &) const
{
 return events.count();
}

int EventsModel::rowCount() const
{
 return events.count();
}

QVariant EventsModel::data(const QModelIndex &index, int role) const {
   if (role != Qt::DisplayRole && role != Qt::EditRole)
   {
       return QVariant();
   }

   const Event event = events[index.row()];

   switch(index.column())
   {
        case 0:
            return event.getTime();
        case 1:
            return event.getDescription();
        case 2:
            return event.getDate();
        default:
            return QVariant();
   }
}

QVariant EventsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
   {
       return QVariant();
   }

   if (section == 0)
   {
       return "Time";
   } else if (section == 1)
   {
       return "Description";
   } else return QVariant();
}

void EventsModel::add(const Event &event)
{
   beginInsertRows(QModelIndex(), events.count(), events.count());
   events.append(event);
   endInsertRows();
}

void EventsModel::remove(const int &id)
{
    beginRemoveRows(QModelIndex(), id, id);
    events.removeAt(id);
    endRemoveRows();
}

void EventsModel::remove(const Event &event)
{
    int indexToRemove = events.indexOf(event);
    beginRemoveRows(QModelIndex(), indexToRemove, indexToRemove);
    events.removeAt(indexToRemove);
    endRemoveRows();
}


Event* EventsModel::getEvent(const Event &event)
{
    int index = events.indexOf(event);
    return &events[index];
}

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************

