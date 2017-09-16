import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    visible: true

    color: "#FFB6C1"

    Row {
        anchors.fill: parent

        Image {
            source: "image://icon-theme/start-here"
        }

        ToolButton {
            Layout.fillHeight: true
            text: "Menu"
        }

        ToolSeparator {}

        ToolButton {
            text: "Some Window"
        }
    }

}
