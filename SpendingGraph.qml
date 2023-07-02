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
                title: "2023"
                legend.visible: false
                Component.onCompleted: {
                    graphDesignHelper.update_chart(chartView)
                    graphDesignHelper.update_axes(chartView.axisX(),
                                                  chartView.axisY())
                }
                LineSeries {
                    id: lineSeries
                    axisX: CategoryAxis {
                        min: 0
                        max: 12 * 30
                        CategoryRange {
                            label: "Jan"
                            endValue: 30
                        }
                        CategoryRange {
                            label: "Feb"
                            endValue: 2 * 30
                        }
                        CategoryRange {
                            label: "Mar"
                            endValue: 3 * 30
                        }
                        CategoryRange {
                            label: "Apr"
                            endValue: 4 * 30
                        }
                        CategoryRange {
                            label: "Mai"
                            endValue: 5 * 30
                        }
                        CategoryRange {
                            label: "Jun"
                            endValue: 6 * 30
                        }
                        CategoryRange {
                            label: "Jul"
                            endValue: 7 * 30
                        }
                        CategoryRange {
                            label: "Aug"
                            endValue: 8 * 30
                        }
                        CategoryRange {
                            label: "Sep"
                            endValue: 9 * 30
                        }
                        CategoryRange {
                            label: "Oct"
                            endValue: 10 * 30
                        }
                        CategoryRange {
                            label: "Nov"
                            endValue: 11 * 30
                        }
                        CategoryRange {
                            label: "Dec"
                            endValue: 12 * 30
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
}
