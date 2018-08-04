#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QStringList>

class ManagerPrivate;

class Manager : public QObject
{
    Q_OBJECT

public:
    explicit Manager(QObject *parent = 0);
    virtual ~Manager();

    Q_INVOKABLE void setFinished(const int& arena);
    Q_INVOKABLE QStringList getGroup(const int& arena);
    Q_INVOKABLE void setPlayer(const int& arena, const int& player,
                               const bool& check);

signals:
    void noGroupsAvailable();

private:
    Q_DECLARE_PRIVATE(Manager)
    ManagerPrivate* const d_ptr;
};

#endif // MANAGER_H
