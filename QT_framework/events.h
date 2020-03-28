#ifndef EVENTS_H
#define EVENTS_H

#include <QDialog>

namespace Ui {
class Events;
}

class Events : public QDialog
{
    Q_OBJECT

public:
    explicit Events(QWidget *parent = nullptr);
    ~Events();

private:
    Ui::Events *ui;
};

#endif // EVENTS_H
