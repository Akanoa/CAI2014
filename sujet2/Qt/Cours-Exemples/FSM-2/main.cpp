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
 QState *s1 = new QState();
 QState *s11 = new QState(s1);
 QState *s12 = new QState(s1);
 QState *s13 = new QState(s1);
 s1->setInitialState(s11);
 sm->addState(s1);
 sm->setInitialState(s1);
 QFinalState *s2 = new QFinalState( );
 sm->addState(s2);
 s1->addTransition(quitButton, SIGNAL(clicked()), s2);
// s12->addTransition(quitButton, SIGNAL(clicked()), s12);
 QObject::connect(sm, SIGNAL(finished()), QApplication::instance(), SLOT(quit()));

 sm->start();

 s11->assignProperty(button, "text", "Click me");
 s11->addTransition(button, SIGNAL(clicked( )), s12);
 s12->addTransition(button, SIGNAL(clicked( )), s13);
 s13->addTransition(button, SIGNAL(clicked( )), s11);

 s11->assignProperty(label, "text", "In state s1");
 s12->assignProperty(label, "text", "In state s2");
 s13->assignProperty(label, "text", "In state s3");

// sm->addState(s11);
// sm->addState(s12);
// sm->addState(s13);
 sm->start();

 QWidget *box = new QWidget();
 QVBoxLayout *layout = new QVBoxLayout(box);
 layout->addWidget(button);
 layout->addWidget(label);
 layout->addWidget(quitButton);

 QObject::connect(s13, SIGNAL(entered()), box, SLOT(showMaximized()) );
 QObject::connect(s13, SIGNAL(exited()),  box, SLOT(showMinimized()) );

 box->show();
 button->show();
 label->show();
 return app.exec();
}

