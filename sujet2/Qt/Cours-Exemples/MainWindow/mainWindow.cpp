#include <QApplication>
#include <QtGui>
class MyMainWindow : public QMainWindow
{
   public:
      MyMainWindow() {
       QWidget *centralWidget = new QWidget();
       QLineEdit *login = new QLineEdit;
       QLineEdit *password = new QLineEdit;
       QFormLayout *formLayout = new QFormLayout;
       formLayout->addRow("Nom d'utilisateur : ", login);
       formLayout->addRow("Mot de passe : ", password);
       centralWidget->setLayout(formLayout);
       setCentralWidget(centralWidget);
     }
};
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MyMainWindow myMainWindow;
  myMainWindow.show();
  return app.exec();
}

