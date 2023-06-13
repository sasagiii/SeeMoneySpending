#include "datamanager.h"
#include <QDebug>

DataManager::DataManager()
{
    
}

void DataManager::saveData(const QString &value)
{
    m_valueSpentToDate.insert(QDateTime::currentDateTime(), value);
    m_moneySpentByDate.clear();
    for (auto it = m_valueSpentToDate.cbegin(); it != m_valueSpentToDate.cend(); ++it)
        m_moneySpentByDate += it.key().toString() + " : " + it.value() + "\n";

    emit moneySpentByDateChanged(m_moneySpentByDate);
}

QString DataManager::moneySpentByDate() const
{
    return m_moneySpentByDate;
}

void DataManager::setMoneySpentByDate(const QString &moneySpent)
{
    m_moneySpentByDate = moneySpent;
}
