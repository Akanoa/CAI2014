#include <QObject> 

class SigSlot : public QObject {
Q_OBJECT
  public:
    SigSlot(): _val(0) {}
    int  value() const { return _val; }
  public slots:
    void setValue( int );  
  signals:
    void valueChanged( int );
  private:
    int  _val;
};

