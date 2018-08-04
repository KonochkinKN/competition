#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include "settings.h"

#define inst nsSettings::Settings::instance()

class Application : public QObject
{
    Q_OBJECT
public:
    Application(QObject* parent = 0) : QObject (parent) {}
    virtual ~Application() {}

    Q_PROPERTY(int numberOfArenas READ numberOfArenas
               NOTIFY numberOfArenasChanged)
    Q_INVOKABLE int numberOfArenas() {return inst->getNumberOfArenas();}

signals:
    void numberOfArenasChanged(int n);
};

#endif // APPLICATION_H

