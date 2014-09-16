#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QMainWindow>

namespace Ui {
class PaintWindow;
}

class PaintWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PaintWindow(QWidget *parent = 0);
    ~PaintWindow();
    
private:
    Ui::PaintWindow *ui;
};

#endif // PAINTWINDOW_H
