#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "grille.h"

using namespace std;

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    int h = 4, w = 4;

    Grille G(h, w);
    srand(time(0));

    for (int i = 0;i < 2; i++){
        G.Insert();
    }

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("vueGrille", &G);

    G.start();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
