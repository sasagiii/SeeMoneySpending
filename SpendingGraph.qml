import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtCharts 2.5

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
            color: 'transparent'
            Layout.fillWidth: true
            Layout.preferredHeight: mainRectangle.height * 2 / 3
            ChartView {
                id: chartView
                anchors.fill: parent
                antialiasing: true
                backgroundColor: 'transparent'
                legend.visible: false
                function setupChart() {
                    graphDesignHelper.update_chart(chartView)
                    graphDesignHelper.update_axes(chartView.axisX(),
                                                  chartView.axisY())
                }
                Component.onCompleted: {
                    setupChart()
                }
                Connections {
                    target: dataManager
                    function onMoneySpentByDateAdded(moneySpent) {
                        chartView.setupChart()
                    }
                }
                Connections {
                    target: dataManager
                    function onSpendingRemoved(index) {
                        chartView.setupChart()
                    }
                }
                LineSeries {
                    id: lineSeries
                    axisX: CategoryAxis {
                        id: axX
                        min: 0
                        max: 365
                    }
                    property var monthRanges: [{
                            "label": "Jan",
                            "days": 31
                        }, {
                            "label": "Feb",
                            "days": 28
                        }, {
                            "label": "Mar",
                            "days": 31
                        }, {
                            "label": "Apr",
                            "days": 30
                        }, {
                            "label": "May",
                            "days": 31
                        }, {
                            "label": "Jun",
                            "days": 30
                        }, {
                            "label": "Jul",
                            "days": 31
                        }, {
                            "label": "Aug",
                            "days": 31
                        }, {
                            "label": "Sep",
                            "days": 30
                        }, {
                            "label": "Oct",
                            "days": 31
                        }, {
                            "label": "Nov",
                            "days": 30
                        }, {
                            "label": "Dec",
                            "days": 31
                        }]
                    Component.onCompleted: {
                        var endValue = 0
                        monthRanges.map(function (monthRange) {
                            endValue += monthRange.days
                            axX.append(monthRange.label, endValue)
                        })
                    }
                }
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
