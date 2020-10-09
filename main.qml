import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
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

        GridLayout {
            id: buttonsGrid
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            Repeater {
                id: buttonsRepeater
                property int currentButtonIndex: -1
                model: shortcutsModel.buttons
                RoundButton {
                    function buttonActionTriggered() {
                        soundSource.stop()
                        buttonsRepeater.currentButtonIndex = index
                        imageText.text = shortcutsModel.buttonName(index)
                        soundSource.source = shortcutsModel.buttonSoundSource(index)
                        soundSource.play()
                        shortcutsModel.say(shortcutsModel.buttonVoiceLine(index))
                        image.source = shortcutsModel.buttonImageSource(index)
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
        Text {
            id:imageText
            font.pointSize: 40
            anchors.top: buttonsGrid.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Image {
            id: image
            anchors.top: imageText.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit
            width: parent.width
        }
    } // main window item/rectangle

    MediaPlayer {
        id: soundSource
        loops: MediaPlayer.Infinite
        onError: {
            console.warn(errorString)
        }
    }

    ShortcutsModel {
        id: shortcutsModel
    }
    Shortcut {
        // rotate 'clicked' buttons by space
        context: Qt.ApplicationShortcut
        enabled: true
        sequence: "space"
        onActivated: {
            imageText.forceActiveFocus()
            soundSource.stop()
            buttonsRepeater.currentButtonIndex++
            if (buttonsRepeater.currentButtonIndex > buttonsRepeater.count) {
                buttonsRepeater.currentButtonIndex = 0
            }
            imageText.text = shortcutsModel.buttonName(buttonsRepeater.currentButtonIndex)
            soundSource.source = shortcutsModel.buttonSoundSource(buttonsRepeater.currentButtonIndex)
            soundSource.play()
            shortcutsModel.say(shortcutsModel.buttonVoiceLine(buttonsRepeater.currentButtonIndex))
            image.source = shortcutsModel.buttonImageSource(buttonsRepeater.currentButtonIndex)
        }
    }
    Component.onCompleted: {
        shortcutsModel.loadShortcuts("")
    }
}
