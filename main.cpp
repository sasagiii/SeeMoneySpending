#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "GraphDesignHelper.h"
#include "datamanager.h"

int main(int argc, char *argv[])
{
#ifndef WIN32
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
#endif

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/SeeMoneySpending/main.qml"_qs);
    // load context
    DataManager dataManager(&engine);
    GraphDesignHelper graphDesignHelper(&dataManager);
    engine.rootContext()->setContextProperty("dataManager", &dataManager);
    engine.rootContext()->setContextProperty("graphDesignHelper", &graphDesignHelper);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
