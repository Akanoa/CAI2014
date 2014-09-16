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
/*
   QWidget box;
   box.resize(200, 120);
   QLabel hello("Hello Statique !", &box);
   hello.resize(300, 50);
   hello.move(10, 30);
   hello.setFont( QFont("Times", 18, QFont::Bold) );
   box.show();
*/

/*
 QPushButton button;

 QStateMachine machine;
 QState *s1 = new QState();
 s1->assignProperty(&button, "text", "Click me");

 QFinalState *s2 = new QFinalState();
 s1->addTransition(&button, SIGNAL(clicked()), s2);

 machine.addState(s1);
 machine.addState(s2);
 machine.setInitialState(s1);
 machine.start();
*/
   QWidget box;
      QPushButton *button = new QPushButton("click");
 QLabel *label = new QLabel("nos state");
      QPushButton * quitButton = new QPushButton("quit");

QVBoxLayout *layout = new QVBoxLayout(&box);
     layout->addWidget(button);
     layout->addWidget(label);
    layout->addWidget(quitButton);

 QStateMachine machine;
     QState *s0 = new QState();
     QState *s1 = new QState(s0 );
     QState *s2 = new QState(s0 );
     QState *s3 = new QState(s0 );
     s1->addTransition(button, SIGNAL(clicked()), s2);
     s2->addTransition(button, SIGNAL(clicked()), s3);
     s3->addTransition(button, SIGNAL(clicked()), s1);
    machine.setInitialState(s1);
    machine.addState(s0);
/*
     machine.addState(s1);
     machine.addState(s2);
     machine.addState(s3);
*/ 


      QFinalState *s00 = new QFinalState();
     s1->addTransition(quitButton, SIGNAL(clicked()), s00);
     machine.addState(s00);


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

