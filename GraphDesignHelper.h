#ifndef GRAPHDESIGNHELPER_H
#define GRAPHDESIGNHELPER_H

#include <QChart>
#include <QLineSeries>
#include <QtQuick>
#include <QtWidgets>
#include "datamanager.h"

static double maxYValue = 0;
static double minYValue = 0;

class GraphDesignHelper : public QObject
{
    Q_OBJECT
public:
    GraphDesignHelper(DataManager *dataManager) { m_dataManager = dataManager; }

    void updateSeries(QLineSeries *series)
    {
        QMap<double, double> moneyByDay = m_dataManager->moneySpentByday();
        series->clear();
        maxYValue = minYValue = moneyByDay.first();
        for (auto it = moneyByDay.cbegin(); it != moneyByDay.cend(); ++it) {
            series->append(it.key(), it.value());
            if (it.value() > maxYValue)
                maxYValue = it.value();
            if (it.value() < minYValue)
                minYValue = it.value();
        }
    }

    Q_INVOKABLE void update_chart(QQuickItem *item)
    {
        QGraphicsScene *scene = item->findChild<QGraphicsScene *>();
        if (!scene)
            return;
        for (QGraphicsItem *it : scene->items()) {
            if (!dynamic_cast<QChart *>(it))
                continue;
            QChart *chart = dynamic_cast<QChart *>(it);
            QLineSeries *series = dynamic_cast<QLineSeries *>(chart->series().first());
            updateSeries(series);
            QPen pen(QRgb(0xfdb157));
            pen.setWidth(5);
            series->setPen(pen);
            // Customize plot area background
            QLinearGradient plotAreaGradient;
            plotAreaGradient.setStart(QPointF(0, 1));
            plotAreaGradient.setFinalStop(QPointF(1, 0));
            plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
            plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
            plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
            chart->setPlotAreaBackgroundBrush(plotAreaGradient);
            chart->setPlotAreaBackgroundVisible(true);
        }
    }
    Q_INVOKABLE void update_axes(QAbstractAxis *axisX, QAbstractAxis *axisY)
    {
        if (!axisX || !axisY)
            return;
        // Customize axis colors
        QPen axisPen(QRgb(0xd18952));
        axisPen.setWidth(2);
        axisX->setLinePen(axisPen);
        axisY->setLinePen(axisPen);
        axisY->setRange(minYValue - minYValue * 0.1, maxYValue + maxYValue * 0.1);
        axisX->setLabelsEditable(true);
        // Customize grid lines and shades
        axisY->setShadesPen(Qt::NoPen);
        axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
    }

private:
    DataManager *m_dataManager = nullptr;
};

#endif // GRAPHDESIGNHELPER_H
