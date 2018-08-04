TEMPLATE = app

QT += qml quick

CONFIG += c++11

DEFINES += __print="\"qDebug()<<__FILE__<<__LINE__<<Q_FUNC_INFO\""

SOURCES += main.cpp \
    settings.cpp \
    manager.cpp

RESOURCES += qml.qrc

HEADERS += \
    settings.h \
    manager.h \
    manager_p.h \
    application.h

DISTFILES += \
    main.qml \
    views/CurrentViewComponent.qml \
    views/GeneralViewComponent.qml \
    views/ResultsViewComponent.qml \
    views/SettingsViewComponent.qml \
    ArenaImage.qml \
    ArenaComponent.qml
