import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

import "views"

Window {
    id: mainWindow
    title: qsTr("Competition app")

    visible: true
    minimumWidth: Screen.width/2
    maximumWidth: Screen.width/2
    minimumHeight: Screen.height/1.5
    maximumHeight: Screen.height/1.5
    modality: Qt.ApplicationModal

    ColumnLayout{
        anchors.fill: parent

        TabView{
            anchors.fill: parent
            Tab{
                anchors.fill: parent
                title: qsTr("Current")
                CurrentViewComponent{
                    anchors.fill: parent
                }
            }

            Tab{
                anchors.fill: parent
                title: qsTr("General")
                GeneralViewComponent{
                  anchors.fill: parent
                }
            }

            Tab{
                width: mainWindow.width
                height: mainWindow.height
                title: qsTr("Results")
                ResultsViewComponent{
                  anchors.fill: parent
                }
            }

            Tab{
                width: mainWindow.width
                height: mainWindow.height
                title: qsTr("Settings")
                SettingsViewComponent{
                  anchors.fill: parent
                }
            }
        }
    }
}
