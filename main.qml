import QtQuick 2.9
import QtQuick.Controls 2.2
import QtMultimedia 5.9
import baby.buttons.game 1.0

ApplicationWindow {
    id: mainWindow
    property var shortcuts: []

    visible: true
    visibility: "FullScreen"
    title: qsTr("Hello My Baby")
    Rectangle {
        id: mainBackground
        anchors.fill: parent
        color: "white"

        Grid {
            id: buttonsGrid
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 5
            Repeater {
                id: buttonsRepeater
                property int currentButtonIndex: -1
                model: shortcutsModel.buttons
                RoundButton {
                    property int myIndex: index
                    function buttonActionTriggered() {
                        soundSource.stop()
                        buttonsRepeater.currentButtonIndex = myIndex
                        soundSource.source = shortcutsModel.buttonSoundSource(myIndex)
                        soundSource.play()
                        image.source = shortcutsModel.buttonImageSource(myIndex)
                    }

                    background: Rectangle {
                        border.color: parent.down ? "#17a81a" : "#21be2b"
                        border.width: 1
                        radius: 2
                        color: index == buttonsRepeater.currentButtonIndex ? shortcutsModel.buttonColor(index) : "lightgrey"
                    }
                    radius: 5
                    text: shortcutsModel.buttonName(index)
                    Shortcut {
                        context: Qt.ApplicationShortcut
                        enabled: true
                        sequences: shortcutsModel.buttonShortcuts(index)
                        onActivated: {
                            buttonActionTriggered()
                        }
                    }
                    onClicked: {
                        buttonActionTriggered()
                    }
                }
            }
        } // Grid
        Image {
            id: image
            anchors.top: buttonsGrid.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit
            width: parent.width
        }
    } // main window item/rectangle

    MediaPlayer {
        id: soundSource
    }

    ShortcutsModel {
        id: shortcutsModel
    }
    Component.onCompleted: {
        shortcutsModel.loadShortcuts("")
    }
}
