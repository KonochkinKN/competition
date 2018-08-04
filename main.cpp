#include <QtQml>
#include <QDebug>
#include <QTextCodec>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "manager.h"
#include "settings.h"
#include "application.h"

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

//    __print;
//    Manager* m = new Manager();

    QGuiApplication app(argc, argv);
    QCoreApplication::setOrganizationName("awesome");
    // DK robotics competition
    QCoreApplication::setApplicationName("dkrc");

    qmlRegisterType<Manager>("awesome.dkrc.app", 1, 0, "Manager");
    qmlRegisterType<Application>("awesome.dkrc.app", 1, 0, "App");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

