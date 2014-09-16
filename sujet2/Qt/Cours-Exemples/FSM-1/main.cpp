#include <QApplication>
#include <QPushButton>
#include <QStateMachine>
#include <QFinalState>
#include <QFont>
#include <QLabel>
#include <QVBoxLayout>

int main(int argc, char **argv)
{
 QApplication app(argc, argv);
 QPushButton *button = new QPushButton("click");
 QLabel *label = new QLabel("Machine a etats");
 QPushButton * quitButton = new QPushButton("quit");


 QStateMachine* sm= new QStateMachine();
 QState *s1 = new QState( );
 QState *s2 = new QState( );
 QState *s3 = new QState( );
 s1->assignProperty(button, "text", "Click me");
 s1->addTransition(button, SIGNAL(clicked( )), s2);
 s2->addTransition(button, SIGNAL(clicked( )), s3);
 s3->addTransition(button, SIGNAL(clicked( )), s1);

 s1->assignProperty(label, "text", "In state s1");
 s2->assignProperty(label, "text", "In state s2");
 s3->assignProperty(label, "text", "In state s3");

 sm->addState(s1);
 sm->addState(s2);
 sm->addState(s3);
 sm->setInitialState(s1);
 sm->start();

 QWidget *box = new QWidget();
 QVBoxLayout *layout = new QVBoxLayout(box);
 layout->addWidget(button);
 layout->addWidget(label);
 layout->addWidget(quitButton);

 QObject::connect(s3, SIGNAL(entered()), box, SLOT(showMaximized()) );
 QObject::connect(s3, SIGNAL(exited()),  box, SLOT(showMinimized()) );

 box->show();
 button->show();
 label->show();
 return app.exec();
}

