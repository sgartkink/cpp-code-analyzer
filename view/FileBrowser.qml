import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.15

Popup {
    id: root

    parent: ApplicationWindow.overlay
    anchors.centerIn: parent

    implicitWidth: parent.width * 0.8
    implicitHeight: parent.height * 0.8

    contentItem: Rectangle {

        anchors.fill: parent
        anchors.margins: 10

        ListView {
            id: list

            height: 500
            width: 500

            anchors {
                top: parent.top
                bottom: bottomButtons.top
                left: parent.left
                right: parent.right
            }

            model: dirModel.dirList
            clip: true
            currentIndex: -1

            delegate: Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                height: fileName.font.pointSize * 2
                color: index === list.currentIndex ? "blue" : "white"

                Text {
                    id: fileName

                    text: modelData
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        list.currentIndex = index
                        dirModel.currentFile = modelData
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOn
            }
        }

        RowLayout {
            id: bottomButtons

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            Layout.preferredHeight: 80
            Layout.preferredWidth: 100

            Button {
                id: btn

                text: qsTr("open")
                Layout.fillWidth: true

                enabled: dirModel.isCurrentDir

                onClicked: dirModel.openCurrentDir()
            }

            Button {
                id: btn2

                text: qsTr("choose")
                Layout.fillWidth: true

                enabled: dirModel.currentFile.length !== 0

                onClicked: listFiles.appendNewFiles(dirModel.currentPath + dirModel.currentFile)
            }

            Button {
                id: btn3

                text: qsTr("close")
                Layout.fillWidth: true

                onClicked: root.close()
            }
        }
    }
}
