#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QDateTime>
#include <QObject>
#include <QString>

class DataManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString moneySpentByDate READ moneySpentByDate WRITE setMoneySpentByDate NOTIFY
                   moneySpentByDateChanged)
public:
    DataManager();
    QString moneySpentByDate() const;
    void setMoneySpentByDate(const QString &moneySpent);

signals:
    void moneySpentByDateChanged(QString moneySpent);

public slots:
    void saveData(const QString &value);

private:
    QMap<QDateTime, QString> m_valueSpentToDate;
    QString m_moneySpentByDate;
};

#endif // DATAMANAGER_H
