import QtQuick.Window 2.2
import QtQuick 2.7
import QtQuick.Controls 2.2

Window {
    id: root
    title: "Lol"
    color: Qt.rgba(0, 0, 0, 0.8)
    width: 1920
    height: 42
    x: 0
    y: 1080-height
    visible: true
    flags: Qt.FramelessWindowHint | Qt.WA_TranslucentBackground

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        Button {
            text: "Legit Menu Button"
            anchors.verticalCenter: parent.verticalCenter
        }
    }


    Label {
        text: "Ermagahd dynamic QML window"
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Label {
        text: "Legit Clock "
        color: "white"
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
    }
}
