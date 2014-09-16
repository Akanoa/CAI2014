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
 QWidget box;
 QPushButton *button = new QPushButton("click");
 QLabel *label = new QLabel("nos state");
 QPushButton * quitButton = new QPushButton("quit");

 QVBoxLayout *layout = new QVBoxLayout(&box);
 layout->addWidget(button);
 layout->addWidget(label);
 layout->addWidget(quitButton);

 QStateMachine machine;
 QState *s1 = new QState();
 QState *s11 = new QState(s0);
 QState *s12 = new QState(s0);
 QState *s13 = new QState(s0);
 s1->setInitialState(s11);
 machine.addState(s1);
 QFinalState *s2 = new QFinalState( );
 s1->addTransition(quitButton, SIGNAL(clicked()), s2);
 s12->addTransition(quitButton, SIGNAL(clicked()), s12);
 machine.addState(s2);
 QObject::connect(&machine, SIGNAL(finished()), QApplication::instance(), SLOT(quit()));
machine.start();
s1->assignProperty(label, "text", "In state s1");
s2->assignProperty(label, "text", "In state s2");
s3->assignProperty(label, "text", "In state s3");

QObject::connect(s3, SIGNAL(entered()), &box, SLOT(showMaximized()));
QObject::connect(s3, SIGNAL(exited()), &box, SLOT(showMinimized()));
     QObject::connect(&machine, SIGNAL(finished()), QApplication::instance(), SLOT(quit()));
box.show();
button->show();
label->show();
return app.exec();
}

