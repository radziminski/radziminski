#ifndef EVENT_H
#define EVENT_H

#include <QDate>
#include <QTime>
#include <QString>

struct Event {
    QDate date;
    QTime time;
    QString description;
};

#endif // EVENT_H
