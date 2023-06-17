#include "datamanager.h"
#include <QBitArray>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

DataManager::DataManager(QQmlApplicationEngine *engine)
    : m_engine(engine)
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
    m_valueSpentByDate = variant.value<QMap<QDateTime, QString>>();

    // creating the displayed version of the datas
    for (auto it = m_valueSpentByDate.cbegin(); it != m_valueSpentByDate.cend(); ++it)
        m_moneySpentByDate << it.key().toString("dd.MM.yyyy hh:mm:ss.z") + ";" + it.value();
}

void DataManager::addData(const QString &value)
{
    if (value.isEmpty())
        return;
    QDateTime currentDate = QDateTime::currentDateTime();
    m_valueSpentByDate.insert(currentDate, value);
    QString addedValueByDate = currentDate.toString("dd.MM.yyyy hh:mm:ss.z") + ";" + value + "\n";
    m_moneySpentByDate << addedValueByDate;

    emit moneySpentByDateAdded(addedValueByDate);
}

DataManager::~DataManager()
{
    qRegisterMetaType<QMap<QDateTime, QString>>("QMap<QDateTime, QString>");
    QVariant spendingHistory = QVariant::fromValue(m_valueSpentByDate);
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

QStringList DataManager::moneySpentHistory()
{
    return m_moneySpentByDate;
}
