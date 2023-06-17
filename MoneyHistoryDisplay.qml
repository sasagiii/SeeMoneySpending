import QtQuick 2.0
import QtQml

Rectangle {
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

    ListView {
        id: listView
        anchors.fill: parent
        topMargin: 7
        model: MoneyListModel {}
        delegate: contactDelegate
        focus: true
        spacing: 7
    }
    Component {
        id: contactDelegate
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: listView.width - 20
            height: 80
            border.color: "blue"
            border.width: 2
            color: "lightsteelblue"
            radius: 10
            smooth: true
            Text {
                x: parent.x + 7
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 50
                text: amont + " €"
                color: "#7B241C"
            }
            Text {
                x: parent.width - width - 7
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 17
                text: date
                color: "gray"
            }
        }
    }
}
