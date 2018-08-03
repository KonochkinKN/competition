#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMap>
#include <QString>
#include <QSettings>

namespace nsSettings
{
    struct Player
    {
        QString playerName;
        QString robotName;
        QString model;
    };

    enum class Column : int
    {
        Player,
        Robot,
        Class
    };

    /*
     * default order of columns:
     * 1) P - player name
     * 2) R - robot name
     * 3) C - class
     */
    // ???
    // 1) headers for table: P R C
    // 2) order of headers in settings
    const QList<QPair<Column, QString>> columnNames = {{Column::Player, "P"},
                                                       {Column::Robot, "R"},
                                                       {Column::Class, "C"}};

    class Settings
    {
    public:
        static Settings* instance();
        static void destroy();

        void createDefaultFile();
        bool isValid();

        int getNumberOfArenas();
        void setNumberOfArenas(const int& n);

        int getNumberOfClasses();
        void setNumberOfClasses(const int& n);

        QString getDatabaseFileName();
        void setDatabaseFileName(const QString& fileName);

        QStringList getClasses();
        void setClasses(const QStringList& classes);

        QString getColumnName(const Column& col);
        int getColumnNumber(const Column& col);
        void setColumnNumber(const Column& col, const int& num);

    private:
        Settings();
        ~Settings();
        QSettings *pSettings;
    };

} // namespace nsSettings

#endif // SETTINGS_H
