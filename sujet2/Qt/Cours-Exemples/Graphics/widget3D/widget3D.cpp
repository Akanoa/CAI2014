#include <QApplication>
#include <QtGui>
#include <QtWebKit/QWebView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWebView *web = new QWebView();
    web->load(QUrl("http://www.developpez.com"));
    web->show();

    QGraphicsScene scene;
    scene.setSceneRect(0 , 0, 1000, 800);

    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
    proxy->setWidget(web);
    scene.addItem(proxy);

    QTransform matrix;
    matrix.rotate(45, Qt::YAxis);
    proxy->setTransform(matrix);

    QGraphicsView view(&scene);
    view.show();

    view.setWindowTitle("Ma premiere scene");
    return app.exec();
}

