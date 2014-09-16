#include <QWidget>
#include <QMouseEvent>
class MyWidget : public QWidget {
public:
   MyWidget() {}
//   MyWidget(QWidget * w) {}
protected:
   void mousePressEvent(QMouseEvent*);
   void paintEvent(QPaintEvent* e );
};

