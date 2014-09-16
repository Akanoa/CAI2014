#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

int main( int argc, char* argv[] )
{
  QApplication helloApp( argc, argv );

// composants
  QWidget *pWindow = new QWidget();
  QLabel * pLabelHello = new QLabel(QString::fromUtf8("<H1><center>Bonjour à tous</center></H1>"), pWindow );
  QPushButton* pButtonHello = new QPushButton("Quitter", pWindow);
// signals/slots
  QObject::connect(pButtonHello, SIGNAL(clicked()),
                   &helloApp, SLOT(quit()));
// layouts 
  QVBoxLayout* mainLayout = new QVBoxLayout(pWindow);
  mainLayout->addWidget(pLabelHello);
  mainLayout->addWidget(pButtonHello);
  pWindow->setLayout(mainLayout);
  pWindow->show();
  return helloApp.exec();
}

