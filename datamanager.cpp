#include "datamanager.h"
#include <QBitArray>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

DataManager::DataManager()
{
    qRegisterMetaType<QMap<QDateTime, QString>>("QMap<QDateTime, QString>");
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
                              + "/saves.sms";
    QFile file(appDataLocation);
    QVariant variant;
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream stream(&file);
        stream >> variant;
        file.close();
    } else {
        qDebug() << "Could not read dataArrays";
    }
    m_valueSpentToDate = variant.value<QMap<QDateTime, QString>>();

    // creating the displayed version of the datas
    for (auto it = m_valueSpentToDate.cbegin(); it != m_valueSpentToDate.cend(); ++it)
        m_moneySpentByDate += it.key().toString("dd.MM.yyyy hh:mm:ss.z") + " : " + it.value()
                              + "\n";
    emit moneySpentByDateChanged(m_moneySpentByDate);
}

void DataManager::addData(const QString &value)
{
    if (value.isEmpty())
        return;
    QDateTime currentDate = QDateTime::currentDateTime();
    m_valueSpentToDate.insert(currentDate, value);
    m_moneySpentByDate += currentDate.toString("dd.MM.yyyy hh:mm:ss.z") + " : " + value + "\n";

    emit moneySpentByDateChanged(m_moneySpentByDate);
}

DataManager::~DataManager()
{
    qRegisterMetaType<QMap<QDateTime, QString>>("QMap<QDateTime, QString>");
    QVariant spendingHistory = QVariant::fromValue(m_valueSpentToDate);
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFile file(appDataLocation + "/saves.sms");
    if (file.open(QIODevice::WriteOnly)) {
        // We're going to streaming text to the file
        QDataStream stream(&file);
        stream << spendingHistory;
        file.close();
    } else {
        qDebug() << "Could not save dataArrays";
    }
}

QString DataManager::moneySpentByDate() const
{
    return m_moneySpentByDate;
}

void DataManager::setMoneySpentByDate(const QString &moneySpent)
{
    m_moneySpentByDate = moneySpent;
}
