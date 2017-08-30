import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1

Rectangle {
    visible: true

    color: Qt.rgba(0, 0, 0, 0.5)

    Material.theme: Material.Dark
    Material.accent: Material.LightBlue

    Row {
        anchors.fill: parent

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
