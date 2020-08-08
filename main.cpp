#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "shortcutsmodel.h"

void registerAllTypes();

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    registerAllTypes();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

void registerAllTypes()
{
    qmlRegisterType<ShortcutsModel>("baby.buttons.game", 1, 0, "ShortcutsModel");
}
