import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: topLevelWindow

    width: 1280
    height: 720

    color: "#00000000"

    Rectangle {
        x: 0
        y: 0

        width: topLevelWindow.width / 10
        height: topLevelWindow.height / 10

        color: "Red"
    }
}
