import QtQuick
import QtQuick.Controls 2.15

Rectangle {
    id: spendMoney
    Rectangle {
        y: parent.height / 6
        anchors.horizontalCenter: parent.horizontalCenter
        height: childrenRect.height
        width: childrenRect.width
        Rectangle {
            id: textInputBorder
            border.color: "blue"
            border.width: 5
            radius: 120
            smooth: true
            height: 50
            width: 300
            anchors.left: parent.left
            clip: true
            TextEdit {
                id: textInput
                property string standardText: "Enter value"
                text: standardText
                font.pixelSize: 25
                width: parent.width - 30
                clip: true
                color: focus ? "black" : "gray"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                Keys.onEnterPressed: {
                    textInput.focus = false
                }
                onFocusChanged: {
                    if (textInput.standardText == textInput.text)
                        textInput.text = ""
                    else if ("" == textInput.text)
                        textInput.text = textInput.standardText
                }
            }
        }
        Text {
            id: currency
            text: qsTr("€")
            font.pixelSize: textInput.font.pixelSize
            anchors.left: textInputBorder.right
            anchors.verticalCenter: textInputBorder.verticalCenter
            anchors.leftMargin: 2
        }
        RoundButton {
            text: qsTr("Spend")
            font.pixelSize: textInput.font.pixelSize
            y: textInputBorder.height + 16
            anchors.horizontalCenter: textInputBorder.horizontalCenter
            palette {
                button: "#7B241C"
            }
            visible: (textInput.text !== ""
                      && textInput.text !== textInput.standardText)
        }
    }
}
