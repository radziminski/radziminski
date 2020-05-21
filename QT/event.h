#ifndef EVENT_H
#define EVENT_H

#include <QDate>
#include <QTime>
#include <QString>

class Event {

public:
     Event();
     Event(QDate date, QTime time, QString description)
     {
         this->date = date;
         this->time = time;
         this->description = description;
     }


     friend bool operator== (const Event &e1, const Event &e2)
     {
         return (e1.date.day() == e2.date.day() &&
                 e1.date.month() == e2.date.month() &&
                 e1.date.year() == e2.date.year() &&
                 e1.time == e2.time &&
                 e1.description == e2.description);
     }

     QDate getDate() const {return this->date;}
     QTime getTime() const {return this->time;}
     QString getDescription() const {return this->description;}

     void setDate(const QDate &date) {this->date = date;}
     void setTime(const QTime &time) {this->time = time;}
     void setDescription(const QString &description) {this->description = description;}

private:
    QDate date;
    QTime time;
    QString description;
};

#endif // EVENT_H

//****  Author: Jan Radzimiński   **********************************
//****  Index Number: 293052      **********************************
