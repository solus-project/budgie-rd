import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1

Rectangle {
    visible: true
    id: visibleArea

    color: Qt.rgba(1, 1, 1, 0.5)

    Material.theme: Material.Light
    Material.accent: Material.LightBlue

    signal dismiss()

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

        // Just separate it visually. TODO: Use our own RavenSeparator
        MenuSeparator {
            Layout.fillWidth: true
        }

        SwipeView {
            width: parent.width
            currentIndex: navBar.currentIndex

            Layout.fillWidth: true

            Item {
                id: appletsPage

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 12

                    Label {
                        text: "I could be a pretty calendar"
                        font.weight: Font.Medium
                        Layout.alignment: Qt.AlignLeft
                        Layout.leftMargin: 24
                    }

                    MenuSeparator {
                        Layout.fillWidth: true
                    }

                    Button {
                        text: "Dismiss"
                        onClicked: visibleArea.dismiss()
                        Layout.leftMargin: 24
                    }
                }
            }

            Item {
                id: notificationsPage

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 12

                    Switch {
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignRight
                        background: Rectangle {
                            color: Qt.rgba(0, 0, 0, 0.05)
                        }
                        text: "Do not disturb"
                    }


                    Label {
                        text: "No new notifications"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
            }
        }
    }
}
