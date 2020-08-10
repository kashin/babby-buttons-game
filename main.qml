import QtQuick 2.9
import QtQuick.Controls 2.2
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
            spacing: 5
            Repeater {
                model: shortcutsModel.shortcuts
                RoundButton {
                    radius: 5
                    text: shortcutsModel.buttonName(index)
                    Shortcut {
                        context: Qt.ApplicationShortcut
                        enabled: true
                        sequence: modelData
                        onActivated: {
                            mainBackground.color = shortcutsModel.buttonColor(index)
                        }
                    }
                }
            }
        }
    }

    ShortcutsModel {
        id: shortcutsModel
    }
    Component.onCompleted: {
        shortcutsModel.loadShortcuts("")
    }
}
