import QtQuick 2.0
import QtQuick.Layouts 1.1
import awesome.dkrc.app 1.0

import "../"

Item {
    id: component

    readonly property int arenaWidth: Math.floor(parseFloat(width)/5)

    Manager{ id: manager;}

    RowLayout{
        anchors.fill: parent
        spacing: arenaWidth/10

        ArenaComponent{
            number: 1
//            players: ["Petrov", "Ivanov"]
            Layout.topMargin: 20
            Layout.leftMargin: arenaWidth/5
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: arenaWidth
            onWidthChanged: console.log(width, parent.width)

            onStarted: players = manager.getGroup(1);
            onPlayerChecked: manager.setPlayer(1, player, checked);
            onFinished: manager.setFinished(1);
        }

        ArenaComponent{
            number: 2
//            players: ["Petrov", "Ivanov", "Sidorov"]
            Layout.topMargin: 20
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: arenaWidth

            onStarted: players = manager.getGroup(2);
            onPlayerChecked: manager.setPlayer(2, player, checked);
            onFinished: manager.setFinished(2);
        }

        ArenaComponent{
            number: 3
//            players: ["Petrov", "Ivanov"]
            Layout.topMargin: 20
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: arenaWidth

            onStarted: players = manager.getGroup(3);
            onPlayerChecked: manager.setPlayer(3, player, checked);
            onFinished: manager.setFinished(3);
        }

        ArenaComponent{
            number: 4
//            players: ["Petrov", "Ivanov"]
            Layout.topMargin: 20
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: arenaWidth

            onStarted: players = manager.getGroup(4);
            onPlayerChecked: manager.setPlayer(4, player, checked);
            onFinished: manager.setFinished(4);
        }
    }
}

