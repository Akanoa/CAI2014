#include "myDialog.h"

MyDialog::MyDialog(QWidget *parent) : QDialog(parent)
   {
     QComboBox *styleComboBox = new QComboBox(this);
     styleComboBox->addItems(QStyleFactory::keys());
     qDebug() << QStyleFactory::keys();
     QLabel *styleLabel = new QLabel(tr("&Style :"),this);
     styleLabel->setBuddy(styleComboBox);
     connect(styleComboBox, SIGNAL(activated(QString)), this, SLOT(changeStyle(QString)));
     styleComboBox->show();
styleLabel->show();
   }

void
MyDialog::changeStyle(const QString &styleName)
  {
   QApplication::setStyle(QStyleFactory::create(styleName));
   QApplication::setPalette(QApplication::style()->standardPalette());
  }


