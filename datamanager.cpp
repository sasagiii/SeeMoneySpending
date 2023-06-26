#include "datamanager.h"
#include <QBitArray>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

DataManager::DataManager(QQmlApplicationEngine *engine)
    : m_engine(engine)
{
    qRegisterMetaType<QMap<QString, QString>>("QMap<QDateTime, QString>");
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
    m_valueSpentByDate = variant.value<QMap<QString, QString>>();

    // creating the displayed version of the datas
    for (auto it = m_valueSpentByDate.cbegin(); it != m_valueSpentByDate.cend(); ++it)
        m_moneySpentByDate.append(it.key() + ";" + it.value());
}

void DataManager::addData(const QString &value)
{
    if (value.isEmpty())
        return;
    QDateTime currentDate = QDateTime::currentDateTime();
    m_valueSpentByDate.insert(currentDate.toString("dd.MM.yyyy hh:mm:ss"), value);
    QString addedValueByDate = currentDate.toString("dd.MM.yyyy hh:mm") + ";" + value;
    m_moneySpentByDate.append(addedValueByDate);

    emit moneySpentByDateAdded(addedValueByDate);
}

void DataManager::removeData(const QString &dateTime, int index)
{
    if (!m_valueSpentByDate.contains(dateTime))
        return;
    m_valueSpentByDate.remove(dateTime);
    emit spendingRemoved(index);
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
