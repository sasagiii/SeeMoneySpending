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

public slots:
    void addData(const QString &value);

private:
    QMap<QDateTime, QString> m_valueSpentByDate;
    QStringList m_moneySpentByDate;

    QQmlApplicationEngine *m_engine = nullptr;
};

#endif // DATAMANAGER_H
