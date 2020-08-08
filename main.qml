import QtQuick 2.9
import QtQuick.Controls 2.2
import baby.buttons.game 1.0

ApplicationWindow {
    id: mainWindow
    property var shortcuts: []

    visibility: "FullScreen"
    title: qsTr("Hello My Baby")
    Rectangle {
        anchors.fill: parent
        color: "darkblue"
    }

    ShortcutsModel {
        id: model
    }

    Repeater {
        count: model.shortcuts.length
        Item {
            Shortcut {
                context: Qt.ApplicationShortcut
                enabled: true
                sequence: modelData
            }
        }
    }
}
