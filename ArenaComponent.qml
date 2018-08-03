import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    id: component

    // must be bind!
    property var players;
    property int number: 0

    ColumnLayout{
        anchors.fill: parent

        ArenaImage{
            id: img
            size: parent.width;
            number: component.number
            Layout.alignment: Qt.AlignTop
        }
        ColumnLayout{
            anchors.top: img.bottom

            anchors.topMargin: 20

            Repeater{
                model: players.length
                anchors.fill: parent

                delegate: Text{
                    text: players[index]
                    width: component.width
                    height: 20
                    font.pixelSize: 20
                    Layout.leftMargin: 20

                    MouseArea{
                        id: area
                        anchors.fill: parent
                        Rectangle{
                            anchors.fill: parent
                        }
                    }
                }
            }

        }
    }
}

