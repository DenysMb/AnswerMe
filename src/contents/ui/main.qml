// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2023 Denys Madureira <denysmb@zoho.com>

import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.15
import org.kde.kirigami 2.19 as Kirigami
import org.kde.AnswerMe 1.0

Kirigami.ApplicationWindow {
    id: root

    title: i18n("AnswerMe")

    minimumWidth: Kirigami.Units.gridUnit * 20
    minimumHeight: Kirigami.Units.gridUnit * 20

    onClosing: App.saveWindowGeometry(root)

    onWidthChanged: saveWindowGeometryTimer.restart()
    onHeightChanged: saveWindowGeometryTimer.restart()
    onXChanged: saveWindowGeometryTimer.restart()
    onYChanged: saveWindowGeometryTimer.restart()

    Component.onCompleted: {
        App.restoreWindowGeometry(root)
        // App.generateAnswer(answer)
        }

    // This timer allows to batch update the window size change to reduce
    // the io load and also work around the fact that x/y/width/height are
    // changed when loading the page and overwrite the saved geometry from
    // the previous session.
    Timer {
        id: saveWindowGeometryTimer
        interval: 1000
        onTriggered: App.saveWindowGeometry(root)
    }

    property int counter: 0

    globalDrawer: Kirigami.GlobalDrawer {
        title: i18n("AnswerMe")
        titleIcon: "applications-graphics"
        isMenu: !root.isMobile
        actions: [
            Kirigami.Action {
                text: i18n("Answer Me")
                icon.name: "comment-symbolic"
                onTriggered: {
                    App.generateAnswer(answer)
                }
            },
            Kirigami.Action {
                text: i18n("About AnswerMe")
                icon.name: "help-about"
                onTriggered: pageStack.layers.push('qrc:About.qml')
            },
            Kirigami.Action {
                text: i18n("Quit")
                icon.name: "application-exit"
                onTriggered: Qt.quit()
            }
        ]
    }

    contextDrawer: Kirigami.ContextDrawer {
        id: contextDrawer
    }

    pageStack.initialPage: page

    Kirigami.Page {
        id: page

        Layout.fillWidth: true

        title: i18n("Answer Me")

        actions.main: Kirigami.Action {
            text: i18n("Give me an answer")
            icon.name: "comment-symbolic"
            tooltip: i18n("Give me a new answer")
            onTriggered: {
                App.generateAnswer(answer)
            }
        }

        ColumnLayout {
            width: page.width

            anchors.centerIn: parent

            Kirigami.Heading {
                id: answer

                Layout.alignment: Qt.AlignCenter
                text: i18n("I am waiting for you question...")
                color: "grey"
            }
        }
    }
}
