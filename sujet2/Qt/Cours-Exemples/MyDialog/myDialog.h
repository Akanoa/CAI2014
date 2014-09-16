#include <QApplication>
#include <QtGui>
#include <QDebug>
class MyDialog : public QDialog
{
 Q_OBJECT
 public:
   MyDialog(QWidget *parent);

 private slots:
   void changeStyle(const QString &styleName);
};


