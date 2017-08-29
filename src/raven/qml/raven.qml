import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    visible: true

    color: Qt.rgba(1, 1, 1, 0.5)


    ColumnLayout {
        width: parent.width
        height: parent.height
        anchors.fill: parent

        TabBar {
            id: navBar

            Layout.fillWidth: true

            TabButton {
                text: "Applets"
            }

            TabButton {
                text: "Notifications"
            }
        }

        StackLayout {
            width: parent.width
            currentIndex: navBar.currentIndex

            Layout.fillWidth: true

            Item {
                id: appletsPage

                ColumnLayout {
                    anchors.fill: parent

                    Label {
                        text: "Nothing to see here"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }

            Item {
                id: notificationsPage

                ColumnLayout {
                    anchors.fill: parent

                    Label {
                        text: "No new notifications"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }
        }
    }
}
