import QtQuick 2.7

Rectangle {

    color: "black"
    
    Image {
        id: backDrop

        // TODO: Expose this as property so we can change wallpapers
        source: "file:///usr/share/backgrounds/solus/Cliffs_of_Moher.png"

        width: parent.width
        height: parent.height

        // TODO: Expose this as a property to change wallpaper modes
        fillMode: Image.PreserveAspectCrop
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        OpacityAnimator {
            id: backDropAnim
            target: backDrop
            from: 0
            to: 1
            duration: 1500
        }

        // Once our initial load is complete, fade in our wallpaper
        Component.onCompleted: {
            backDropAnim.running = true
        }
    }
}
