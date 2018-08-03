#include <QDebug>
#include <QTextCodec>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "manager.h"
#include "settings.h"

#include <clocale>

/*
 * TODO:
 * ---> Excel: http://smhfa.blogspot.com/2014/07/qt-excel.html
 *      http://www.cyberforum.ru/qt/thread1065774.html
 *      https://evileg.com/ru/post/158/
 */

int main(int argc, char *argv[])
{

    setlocale(LC_ALL, "RUS");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));

    if (!nsSettings::Settings::instance()->isValid())
        nsSettings::Settings::instance()->createDefaultFile();

    __print;
    Manager* m = new Manager();

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

