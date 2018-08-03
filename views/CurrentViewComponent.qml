import QtQuick 2.0
import QtQuick.Layouts 1.1

import "../"

Item {
    id: component

    readonly property int arenaWidth: Math.floor(parseFloat(width)/5)

    RowLayout{
        anchors.fill: parent
        spacing: arenaWidth/10

        ArenaComponent{
            number: 1
            players: ["Petrov", "Ivanov"]
            Layout.topMargin: 20
            Layout.leftMargin: arenaWidth/5
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: arenaWidth
            onWidthChanged: console.log(width, parent.width)
        }

        ArenaComponent{
            number: 2
            players: ["Petrov", "Ivanov", "Sidorov"]
            Layout.topMargin: 20
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: arenaWidth
        }

        ArenaComponent{
            number: 3
            players: ["Petrov", "Ivanov"]
            Layout.topMargin: 20
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: arenaWidth
        }

        ArenaComponent{
            number: 4
            players: ["Petrov", "Ivanov"]
            Layout.topMargin: 20
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: arenaWidth
        }
    }
}

