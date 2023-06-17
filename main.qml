import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.Controls 2.15
import QtQuick.Layouts
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    title: qsTr("Spending Money")

    header: ToolBar {
        TabBar {
            id: mainTabBar
            anchors.left: parent.left
            Material.background: "transparent"
            TabButton {
                text: qsTr("Spend")
                font.pointSize: 15
                width: implicitWidth
            }
            TabButton {
                text: qsTr("Spent")
                font.pointSize: 15
                width: implicitWidth
            }
            TabButton {
                text: qsTr("Graph")
                font.pointSize: 15
                width: implicitWidth
            }
        }
        RoundButton {
            text: qsTr("Exit")
            font.pointSize: 15
            width: implicitWidth
            height: parent.height
            anchors.right: parent.right
            onClicked: Qt.exit(0)
        }
    }

    StackLayout {
        anchors.fill: parent
        currentIndex: mainTabBar.currentIndex
        y: mainTabBar.height

        SpendMoney {}

        MoneyHistoryDisplay {}

        Item {
            id: graph
            Text {
                text: "Just a casual graphics of the money spent"
                font.pointSize: 15
                y: parent.height / 3
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
