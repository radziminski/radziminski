#include "eventsmodelfilter.h"

EventsModelFilter::EventsModelFilter(QObject* parent) : QSortFilterProxyModel(parent)
{
}

bool EventsModelFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = this->sourceModel()->index(sourceRow, 2, sourceParent);
    QDate date = this->sourceModel()->data(index).toDate();
    if (date == this->dateFilter) return true;
    return false;
}

bool EventsModelFilter::filterAcceptsColumn(int sourceColumn, const QModelIndex &sourceParent) const
{
    if (sourceColumn == 2) return false;
    return true;
}

void EventsModelFilter::setDateFilter(const QDate &date)
{
    this->dateFilter = date;
}

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************
