#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>

class ManagerPrivate;

class Manager : public QObject
{
    Q_OBJECT

public:
    explicit Manager(QObject *parent = 0);
    virtual ~Manager();

signals:

private:
    Q_DECLARE_PRIVATE(Manager)
    ManagerPrivate* const d_ptr;
};

#endif // MANAGER_H
