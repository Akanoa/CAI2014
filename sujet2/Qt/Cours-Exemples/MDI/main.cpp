#include <QApplication>
#include <QtGui>
class MyMainWindow : public QMainWindow
{
  public:
   MyMainWindow()
   {
     QMdiArea *mdiArea = new QMdiArea;
     QTextEdit *textEdit1 = new QTextEdit;
     QTextEdit *textEdit2 = new QTextEdit;
     QMdiSubWindow *mdiSubWindow1 = mdiArea->addSubWindow(textEdit1);
     QMdiSubWindow *mdiSubWindow2 = mdiArea->addSubWindow(textEdit2);
// ou : QMdiArea::SubWindowView
mdiArea->setViewMode(QMdiArea::TabbedView);
     setCentralWidget(mdiArea);
   }
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MyMainWindow myMainWindow;
  myMainWindow.show();
  return app.exec();
}

