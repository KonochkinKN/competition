#include "manager.h"
#include "manager_p.h"
#include "settings.h"

#include <cmath>
#include <QList>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QtAlgorithms>

using namespace nsSettings;

Manager::Manager(QObject *parent)
    : QObject(parent)
    , d_ptr(new ManagerPrivate)
{
    Q_D(Manager);
    d->q_ptr = this;
}

Manager::~Manager()
{
    d_ptr->deleteLater();
}

QStringList Manager::getGroup(const int& arena)
{
    Q_D(Manager);
    __print << d->mGroupsPlayed;
    if (d->mGroupsPlayed < 0) return QStringList();
    if (d->mGroupsPlayed >= d->mGroups.size()) return QStringList();

    QStringList names;
    d->mArenasForGroups[d->mGroupsPlayed] = arena; // save arena number
    foreach (int index, d->mGroups.at(d->mGroupsPlayed))
        names.append(d->mNames.at(index));

    d->mGroupsPlayed++;
    return names;
}

void Manager::setFinished(const int &arena)
{
    __print << arena;
    Q_D(Manager);
    if (!d->mArenasForGroups.contains(arena))
    {
        __print << "Invalid arena number";
        return;
    }
    d->mArenasForGroups[d->mArenasForGroups.indexOf(arena)] = 0;
}

void Manager::setPlayer(const int &arena, const int &player, const bool &check)
{
    __print << arena << player << check;
    Q_D(Manager);
    if (!d->mArenasForGroups.contains(arena))
    {
        __print << "Invalid arena number";
        return;
    }
    int arenaInd = d->mArenasForGroups.indexOf(arena);

    if (arenaInd >= d->mGroups.size())
    {
        __print << "Invalid arena index";
        return;
    }

    QList<int> players = d->mGroups.at(d->mArenasForGroups.indexOf(arena));

    if (player >= players.size())
    {
        __print << "Invalid player number";
        return;
    }

    int playerNum = players.at(player);

    if (check && !d->mChampions.contains(playerNum))
    {
        d->mChampions.append(playerNum);
    }
    else if (!check && d->mChampions.contains(playerNum))
    {
        d->mChampions.removeAll(playerNum);
    }
    else __print << "Something goes wrong";

    foreach (int ind, d->mChampions)
    {
        qDebug() << d->mNames.at(ind);
    }
}

ManagerPrivate::ManagerPrivate(QObject *parent)
    : QObject(parent)
    , mGroupsPlayed(-1)
    , pThread(new QThread())
{
    this->moveToThread(pThread);

    // test
    this->read();
    this->makeGroups();
}

ManagerPrivate::~ManagerPrivate()
{
    if (pThread->isRunning())
        pThread->quit();

    pThread->deleteLater();
}

bool ManagerPrivate::read()
{
    mNames.clear();
    mRobots.clear();
    mClasses.clear();
    QString dbName = Settings::instance()->getDatabaseFileName();

    QFile dbFile(dbName);
    if (!dbFile.open(QFile::ReadOnly | QFile::Text))
    {
        __print << "Invalid database file:" << dbName;
        return false;
    }

    QTextStream db(&dbFile);

    while(!db.atEnd())
    {
        QString line = db.readLine();
        QStringList elements =  line.split(";");

        int n = Settings::instance()->getColumnNumber(Column::Player);
        if (n > elements.size() || n < 0)
        {
            __print << "Something wrong with \"Player\" column"
                    << n << elements.size();
            return false;
        }
        mNames.append(elements.at(n));

        n = Settings::instance()->getColumnNumber(Column::Robot);
        if (n > elements.size() || n < 0)
        {
            __print << "Something wrong with \"Robot\" column"
                    << n << elements.size();
            return false;
        }
        mRobots.append(elements.at(n));

        n = Settings::instance()->getColumnNumber(Column::Class);
        if (n > elements.size() || n < 0)
        {
            __print << "Something wrong with \"Class\" column"
                    << n << elements.size();
            return false;
        }
        mClasses.append(elements.at(n));
    }
    dbFile.close();

    if (mNames.size() != mRobots.size() || mNames.size() != mClasses.size())
    {
        __print << "Invalid sizes of lists";
        return false;
    }

    qDebug() << "\nNames:\t" << mNames
             << "\nRobots:\t" << mRobots
             << "\nClasses:\t" << mClasses;

    return true;
}

bool ManagerPrivate::makeGroups()
{
    int nPlayers = mNames.size();
    int nArenas = Settings::instance()->getNumberOfArenas();

    if (nPlayers < nArenas)
    {
        __print << "Too small number of players";
        return false;
    }

    mGroupsPlayed = -1;
    mGroups.clear();
    mUniqClasses.clear();
    mArenasForGroups.clear();
    QMap <QString, QList<int>> counts;
    for (int i = 0; i < nPlayers; i++)
    {
        QString c = mClasses.at(i);
        counts[c].append(i);
        if (!mUniqClasses.contains(c))
            mUniqClasses.append(c);
    }

    qDebug() << "Uniq classes:" << mUniqClasses;
    qDebug() << counts;

    int nGroup = 0;
    int ppa = nPlayers/nArenas; // players per arena
    foreach (QString c, mUniqClasses)
    {
        double n = static_cast<double>(counts[c].size());
        int q = std::round(n/ppa);
        q += (q < 1);
        for (int i = 0; i < q; i++)
        {
            mGroups.append(QList<int>());
            for (int j = i; j < n; j+=q)
            {
                mGroups[nGroup].append(counts[c].at(j));
            }
            nGroup++;
        }
    }

    // sort groups by size
    qSort(mGroups.begin(), mGroups.end(), [](const QList<int>& l1,
          const QList<int>& l2)
    {
        return l1.size() > l2.size();
    });

    for(int i = 0; i < nGroup; i++)
    {        
        mArenasForGroups.append(0);
        qDebug() << QString("Arena #%1:").arg(i+1) << mGroups[i];
    }

    mGroupsPlayed = 0;
    return true;
}


