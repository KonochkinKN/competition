#ifndef MANAGER_P
#define MANAGER_P

#include <QList>
#include <QObject>
#include <QThread>
#include <QStringList>

class Manager;

class ManagerPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(Manager)

public:
    explicit ManagerPrivate(QObject *parent = 0);
    ~ManagerPrivate() override;

    bool read();
    bool makeGroups();

private:
    int mGroupsPlayed;
    QStringList mNames;
    QStringList mRobots;
    QStringList mClasses;
    QList<int> mChampions;
    QStringList mUniqClasses;
    QList<QList<int>> mGroups;
    QList<int> mArenasForGroups;

    Manager* q_ptr;
    QThread* pThread;
};

#endif // MANAGER_P

