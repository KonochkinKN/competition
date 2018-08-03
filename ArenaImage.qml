import QtQuick 2.0
import QtQuick.Layouts 1.1

Rectangle{
    property int number: 0;
    property double size: 100;

    color: "black"
    width: size
    height: size
    radius: size/2

    Rectangle{
        property double ssize: size*0.8

        color: "white"
        width: ssize
        height: ssize
        radius: ssize/2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Text{
            color: "red"
            text: number
            font.bold: true
            font.pixelSize: size/2;

            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
