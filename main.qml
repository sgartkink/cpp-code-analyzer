import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "view"

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Cpp Code Analyzer")

    Button {
        id: btnOpenFileBrowser

        anchors.centerIn: parent

        text: qsTr("open file browser")

        onClicked: fileBrowser.open()
    }

    ListView {
        id: list

        anchors {
            top: btnOpenFileBrowser.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        model: listFiles.listFiles
        clip: true

        delegate: Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            height: fileName.font.pointSize * 2

            Text {
                id: fileName

                text: modelData
            }
        }
    }

    FileBrowser {
        id: fileBrowser
    }
}
