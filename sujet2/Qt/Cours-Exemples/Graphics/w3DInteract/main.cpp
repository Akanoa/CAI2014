#include <QApplication>
#include <QGraphicsView>
#include "myScene.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyScene scene;
    scene.setSceneRect(-150, -150, 300, 300);

    QGraphicsView view(&scene);
    view.setWindowTitle("Ma premiere scene");
    view.show();
    return app.exec();
}

