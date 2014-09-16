#include <QApplication>
#include <QLabel>
int main(int argc, char **argv)
{
   QApplication* app = new QApplication(argc, argv);
   QLabel* hello = new QLabel("Hello Dynamique !");
   hello->show( );
   return app->exec( );
}

