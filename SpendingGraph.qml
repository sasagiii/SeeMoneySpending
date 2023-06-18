import QtQuick
import QtQuick.Layouts

Rectangle {
    id: mainRectangle

    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: "lightsteelblue"
        }
        GradientStop {
            position: 1.0
            color: "steelblue"
        }
    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 6
        Rectangle {
            id: spacer
            color: 'transparent'
            Layout.fillWidth: true
            Layout.maximumHeight: 0
        }
        Rectangle {
            color: 'teal'
            Layout.fillWidth: true
            Layout.preferredHeight: mainRectangle.height * 2 / 3
            Text {
                anchors.centerIn: parent
                text: "Graph in coming here"
                font.bold: true
            }
        }
        Rectangle {
            color: "transparent"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                anchors.centerIn: parent
                text: "Filtering options in coming here"
                font.bold: true
            }
        }
    }
}
