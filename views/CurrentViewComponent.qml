import QtQuick 2.0
import QtQuick.Layouts 1.1
import awesome.dkrc.app 1.0

import "../"

Item {
    id: component

    readonly property int numberOfArenas: app.numberOfArenas
    readonly property int arenaWidth: Math.floor(parseFloat(width)/(numberOfArenas+2))
    property bool groupsAvailable: true

    onNumberOfArenasChanged: console.log(numberOfArenas)

    App{ id: app;}

    Manager{
        id: manager;
        onNoGroupsAvailable: groupsAvailable = false
    }

    ColumnLayout{
        anchors.fill: parent
        Text{
            text: groupsAvailable ? "" : qsTr("No more groups in queue")
            Layout.preferredWidth: parent.width
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }

        RowLayout{
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height
            spacing: arenaWidth/10

            Repeater{
                model: numberOfArenas

                delegate:
                    ArenaComponent{
                        number: index+1
                        Layout.leftMargin: arenaWidth/5
                        Layout.preferredHeight: parent.height
                        Layout.preferredWidth: arenaWidth

                        onStarted: players = manager.getGroup(number);
                        onPlayerChecked: manager.setPlayer(number, player, checked);
                        onFinished: manager.setFinished(number);
                        startMatchAvailable: groupsAvailable
                    }
            }

//            ArenaComponent{
//                number: 1
//                Layout.leftMargin: arenaWidth/5
//                Layout.preferredHeight: parent.height
//                Layout.preferredWidth: arenaWidth

//                onStarted: players = manager.getGroup(1);
//                onPlayerChecked: manager.setPlayer(1, player, checked);
//                onFinished: manager.setFinished(1);
//                startMatchAvailable: groupsAvailable
//            }

//            ArenaComponent{
//                number: 2
//                Layout.preferredHeight: parent.height
//                Layout.preferredWidth: arenaWidth

//                onStarted: players = manager.getGroup(2);
//                onPlayerChecked: manager.setPlayer(2, player, checked);
//                onFinished: manager.setFinished(2);
//                startMatchAvailable: groupsAvailable
//            }

//            ArenaComponent{
//                number: 3
//                Layout.preferredHeight: parent.height
//                Layout.preferredWidth: arenaWidth

//                onStarted: players = manager.getGroup(3);
//                onPlayerChecked: manager.setPlayer(3, player, checked);
//                onFinished: manager.setFinished(3);
//                startMatchAvailable: groupsAvailable
//            }

//            ArenaComponent{
//                number: 4
//                Layout.preferredHeight: parent.height
//                Layout.preferredWidth: arenaWidth

//                onStarted: players = manager.getGroup(4);
//                onPlayerChecked: manager.setPlayer(4, player, checked);
//                onFinished: manager.setFinished(4);
//                startMatchAvailable: groupsAvailable
//            }
        }
    }
}

