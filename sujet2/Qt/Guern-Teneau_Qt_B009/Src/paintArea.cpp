#include "enums.h"
#include "paintArea.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent) {
  qDebug() << "PaintArea::PaintArea(void)";
  _startPoint = _endPoint = QPoint(0,0);
  _buffer = new QPixmap(parent->size());
  _buffer->fill(Qt::white);
  _release=false;
  _escapeState=false;
  _enterState=false;

  _bufferForm = new QPixmap(parent->size());
  _bufferForm->fill(Qt::white);
}

void PaintArea::mousePressEvent(QMouseEvent* evt) {
  qDebug() << "PaintArea::mousePressEvent(void)";
  _release=false;
  _startPoint = _endPoint = evt->pos();
}

void PaintArea::mouseMoveEvent(QMouseEvent* evt) 
{
// qDebug() << "PaintArea::mouseMoveEvent(void)";
  _endPoint = evt->pos(); 
  update();
}

void PaintArea::mouseReleaseEvent(QMouseEvent* evt) 
{
  qDebug() << "PaintArea::mouseReleaseEvent(void)";
  _release=true;
  update();

}

void PaintArea::mouseDoubleClickEvent (QMouseEvent* evt) {
  qDebug() << "PaintArea::mouseDoubleClickEvent(void)";
}

void PaintArea::paintEvent(QPaintEvent* evt) 
{
  qDebug() << "PaintArea::paintEvent(void)";
  qDebug() << _currentTool;
  QPainter paintWindow(this);
  QPainter paintBuffer(_buffer);
  QPainter paintBufferForm(_bufferForm);

  paintWindow.drawPixmap(0,0, *_buffer);
  //paintWindow.drawPixmap(0,0, *_bufferForm);

  QPen penColored(_currentColor);
  paintWindow.setPen(penColored);
  paintBuffer.setPen(penColored);
  paintBufferForm.setPen(penColored);

  if(_filled){
      paintWindow.setBrush(QBrush(_fillColor));
      paintBuffer.setBrush(QBrush(_fillColor));
      paintBufferForm.setBrush(QBrush(_fillColor));
      switch(_currentTool) {
        case TOOLS_ID_FREEHAND :
          paintBuffer.drawPoint(_endPoint);
          paintWindow.drawPoint(_endPoint);
          break;
        case TOOLS_ID_LINE :
          qDebug() << "PaintArea:: draw Line";
          if (_release) paintBuffer.drawLine(_startPoint,_endPoint);
          paintWindow.drawLine(_startPoint,_endPoint);
          break;
        case TOOLS_ID_POLYGON:
          if (_release){
              paintBufferForm.drawLine(_startPoint,_endPoint);
          }
          paintWindow.drawLine(_startPoint,_endPoint);
          break;
        case TOOLS_ID_RECTANGLE :
          qDebug() << "PaintArea:: draw Rect";
          if (_release) paintBuffer.fillRect(QRect(_startPoint,_endPoint), _fillColor);
          paintWindow.fillRect(QRect(_startPoint,_endPoint), _fillColor);
          break;
       case TOOLS_ID_CIRCLE :
          qDebug() << "PaintArea:: draw CIRCLE";
          if (_release) paintBuffer.drawEllipse(QRect(_startPoint,_endPoint));
          paintWindow.drawEllipse(QRect(_startPoint,_endPoint));
          break;
        default :
          break;
    }
  }
  else{
      switch(_currentTool) {
        case TOOLS_ID_FREEHAND :
          paintBuffer.drawPoint(_endPoint);
          paintWindow.drawPoint(_endPoint);
          break;
        case TOOLS_ID_LINE :
          qDebug() << "PaintArea:: draw Line";
          if (_release) paintBuffer.drawLine(_startPoint,_endPoint);
          paintWindow.drawLine(_startPoint,_endPoint);
          break;
        case TOOLS_ID_POLYGON:
          if (_release){
              paintBufferForm.drawLine(_startPoint,_endPoint);
          }
          paintWindow.drawLine(_startPoint,_endPoint);
          break;
        case TOOLS_ID_RECTANGLE :
          qDebug() << "PaintArea:: draw Rect";
          if (_release) paintBuffer.drawRect(QRect(_startPoint,_endPoint));
          paintWindow.drawRect(QRect(_startPoint,_endPoint));
          break;
       case TOOLS_ID_CIRCLE :
          qDebug() << "PaintArea:: draw CIRCLE";
          if (_release) paintBuffer.drawEllipse(QRect(_startPoint,_endPoint));
          paintWindow.drawEllipse(QRect(_startPoint,_endPoint));
          break;
        default :
          break;
    }
  }

  /* TODO */
  if (_escapeState && false) {
      qDebug() << "Delete bufferForm";
      _bufferForm->fill(Qt::white);
      setEscapeState(false);
  }
  if (_enterState && false) {
    qDebug() << "Draw buffer Form";
    paintBuffer.drawPixmap(0,0, *_bufferForm);
    setEnterState(false);
    _bufferForm->fill(Qt::white);
  }

}

void PaintArea::setCurrentTool(int tool) {
  _currentTool = tool;
}

void PaintArea::setFilled(bool value){
    qDebug()<< "filled" << value;
    _filled = value;
}

void PaintArea::setCurrentColor(QColor color){
    _currentColor = color;
}

void PaintArea::setFillColor(QColor color){
    _fillColor = color;
}

QPixmap* PaintArea::getBuffer(void){
  return _buffer;
}
void PaintArea::setEnterState(bool value){
    qDebug() << "Enter state :" <<value;
    _enterState = value;
}

void PaintArea::setEscapeState(bool value){
    qDebug() << "Escape state :" <<value;
    _escapeState = value;
}
