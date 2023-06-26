#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QDateTime>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QString>

class DataManager : public QObject
{
    Q_OBJECT
public:
    ~DataManager();
    DataManager(QQmlApplicationEngine *engine);
    QString moneySpentByDate() const;
    void setMoneySpentByDate(const QString &moneySpent);
    Q_INVOKABLE QStringList moneySpentHistory();

signals:
    void moneySpentByDateAdded(QString moneySpent);
    void spendingRemoved(int index);

public slots:
    void addData(const QString &value);
    void removeData(const QString &dateTime, int index);

private:
    QMap<QString, QString> m_valueSpentByDate; // <dateTime, amount>
    QStringList m_moneySpentByDate;

    QQmlApplicationEngine *m_engine = nullptr;
};

#endif // DATAMANAGER_H
