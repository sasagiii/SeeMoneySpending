#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "datamanager.h"


int main(int argc, char *argv[])
{
#ifndef WIN32
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/SeeMoneySpending/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // load context
    DataManager dataManager;
    engine.rootContext()->setContextProperty("dataManager", &dataManager);

    return app.exec();
}
