import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

Item {
    id: component

    // must be bind!
    property var players;
    property int number: 0

    property bool isOccupied: false

    signal started();
    signal finished();
    signal playerChecked(int player, bool checked);

    // TODO: make normal view

    ColumnLayout{
        anchors.fill: parent

        ArenaImage{
            id: img
            size: parent.width;
            number: component.number
            Layout.alignment: Qt.AlignTop
            onSizeChanged: btn.width = size;
        }
        ColumnLayout{
            anchors.top: img.bottom
            anchors.topMargin: 20
            width: parent.width
            height: parent.height - img.size

            Repeater{
                id: rep
                visible: isOccupied
                model: (players == undefined) ? 0 : players.length
                anchors.fill: parent

                delegate: Text{
                    property bool checked: false
                    visible: isOccupied
                    text: players[index]
                    width: component.width
                    height: 20
                    font.pixelSize: 20
                    Layout.leftMargin: 20
                    font.bold: checked
                    color: area.containsMouse ? (checked ? "red" : "green")
                                              : "black"

                    MouseArea{
                        id: area
                        hoverEnabled: true
                        anchors.fill: parent
                        onClicked: {
                            parent.checked = !parent.checked
                            playerChecked(index, parent.checked)
                        }
                    }
                }
            }

            Button{
                id: btn
                text: isOccupied ? qsTr("End match") : qsTr("start")
//                anchors.top: rep.bottom
//                width: img.width
                Layout.alignment: Qt.AlignHCenter
                onClicked:{
                    isOccupied = !isOccupied
                    if(isOccupied) started()
                    else finished()
                }
            }
        }
    }
}

