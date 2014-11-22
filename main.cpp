#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "testcaselistmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TestcaseListModel model;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("testcasemodel", &model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
