/*
 *  Class for working with config files
 */

#include "settings.h"
#include <QList>
#include <QDebug>

using namespace nsSettings;

namespace
{
    const QString gColumnMap("MAP/");
    const QString gAppSettings("APP/");
    const QString gMainSettings("MAIN/");
    const QString kClasses("CLASSES/list");
    const QString kArenasNumber(gMainSettings + "arenas_number");
    const QString kDatabaseFile(gMainSettings + "database_file");
    const QString kClassesNumber(gMainSettings + "classes_number");
}

static Settings* settings = nullptr;

Settings* Settings::instance()
{
    if (!settings) settings = new Settings();

    return settings;
}

void Settings::destroy()
{
    delete settings;
    settings = nullptr;
}

Settings::Settings()
{
    pSettings = new QSettings("settings.ini", QSettings::IniFormat);
}

Settings::~Settings()
{

}

void Settings::createDefaultFile()
{
    QSettings lsettings("settings.ini", QSettings::IniFormat);

    int classesN = 4;
    QStringList classes = {"Tribot", "Quadrobot", "Megabot", "Arduino"};

    lsettings.setValue(::kArenasNumber, 4);
    lsettings.setValue(::kClasses, classes);
    lsettings.setValue(::kClassesNumber, classesN);
    lsettings.setValue(::kDatabaseFile, "database.csv");
    lsettings.setValue(this->getColumnName(Column::Player), 0);
    lsettings.setValue(this->getColumnName(Column::Robot), 1);
    lsettings.setValue(this->getColumnName(Column::Class), 2);

    lsettings.sync();
}

bool Settings::isValid()
{
   // validates only config file, not its contents
   if (pSettings->status() != QSettings::NoError) return false;

   int nArenas = this->getNumberOfArenas();
   if (nArenas < 1) return false;

   int nClasses = this->getNumberOfClasses();
   if (nClasses < 1) return false;

   QString fDatabase = this->getDatabaseFileName();
   if (fDatabase.isEmpty()) return false;

   QStringList lClasses = this->getClasses();
   if (lClasses.isEmpty()) return false;

   if (lClasses.size() != nClasses)
   {
       __print << "WARNING: Number of classes is invalid!";
       return false;
   }

   int p = this->getColumnNumber(Column::Player);
   int r = this->getColumnNumber(Column::Robot);
   int c = this->getColumnNumber(Column::Class);
   if (p < 0 || r < 0 || c < 0)
   {
       __print;
       return false;
   }

   return true;
}

int Settings::getNumberOfArenas()
{
    return pSettings->value(::kArenasNumber, -1).toInt();
}

void Settings::setNumberOfArenas(const int &n)
{
    pSettings->setValue(::kArenasNumber, n);
    pSettings->sync();
}

int Settings::getNumberOfClasses()
{
    return pSettings->value(::kClassesNumber, -1).toInt();
}

void Settings::setNumberOfClasses(const int &n)
{
    pSettings->setValue(::kClassesNumber, n);
    pSettings->sync();
}

QString Settings::getDatabaseFileName()
{
    return pSettings->value(::kDatabaseFile, "").toString();
}

void Settings::setDatabaseFileName(const QString &fileName)
{
    pSettings->setValue(::kDatabaseFile, fileName);
    pSettings->sync();
}

QStringList Settings::getClasses()
{
    return pSettings->value(::kClasses, QStringList()).toStringList();
}

void Settings::setClasses(const QStringList &classes)
{
    pSettings->setValue(::kClasses, classes);
    pSettings->sync();
}

QString Settings::getColumnName(const Column& col)
{
    switch(col)
    {
    case Column::Player:
        return QString(::gColumnMap + "player");
    case Column::Robot:
        return QString(::gColumnMap + "robot");
    case Column::Class:
        return QString(::gColumnMap + "class");
    }
    return QString();
}

int Settings::getColumnNumber(const Column& col)
{
    return pSettings->value(this->getColumnName(col), -1).toInt();
}

void Settings::setColumnNumber(const Column &col, const int &num)
{
    pSettings->setValue(this->getColumnName(col), num);
    pSettings->sync();
}
