#ifndef EVENTSMODELFILTER_H
#define EVENTSMODELFILTER_H

#include <QSortFilterProxyModel>
#include <QDate>
#include <QObject>
#include <QModelIndex>

class EventsModelFilter : public QSortFilterProxyModel
{
public:
    explicit EventsModelFilter(QObject* parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const  override;
    bool filterAcceptsColumn(int sourcColumn, const QModelIndex &source_parent) const override;

public slots:
    void setDateFilter(const QDate &date);

private:
    QDate dateFilter;
};

#endif // EVENTSMODELFILTER_H

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************
