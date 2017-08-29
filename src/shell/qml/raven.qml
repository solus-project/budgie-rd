import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    visible: true

    color: Qt.rgba(1, 1, 1, 0.5)


    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

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

        SwipeView {
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
