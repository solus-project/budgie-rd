import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    id: root
    title: "Lol"
    width: 1920
    height: 42
    x: 0
    y: 1080-height
    visible: true
    flags: Qt.FramelessWindowHint

    Label {
        text: "Ermagahd dynamic QML window"
    }
}
