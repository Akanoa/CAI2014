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
  _filled = false;
  _haveUndo = false;
  _currentText = new QString("");
  _editing = false;
  _endEdition = false;
  _font = QFont("Helvetica [Cronyx]", 10);
}

void PaintArea::mousePressEvent(QMouseEvent* evt) {
  qDebug() << "PaintArea::mousePressEvent(void)";
  _release=false;
  _startPoint = _endPoint = evt->pos();
  if(_currentTool == TOOLS_ID_POLYGON){
      _listPointsPolygon.push_back(QPoint(evt->pos()));
  }
  _haveUndo = false;
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
  qDebug() << evt;
  _release=true;
  if(_currentTool == TOOLS_ID_POLYGON){
      _listPointsPolygon.push_back(QPoint(evt->pos()));
  }
  update();
}

void PaintArea::mouseDoubleClickEvent (QMouseEvent* evt) {
  qDebug() << "PaintArea::mouseDoubleClickEvent(void)";
  qDebug() << evt;
}

void PaintArea::setFont(QFont font)
{
  _font = font;
}

void PaintArea::contextMenuEvent(QContextMenuEvent *evt)
{
    emit popUpAsked(evt->globalPos());
}

void PaintArea::paintEvent(QPaintEvent* evt) 
{
  qDebug() << "PaintArea::paintEvent(void)";
  qDebug() << _currentTool;
  QPainter paintWindow(this);
  QPainter paintBuffer(_buffer);

  paintWindow.drawPixmap(0,0, *_buffer);

  QPen penColored(_currentColor);
  paintWindow.setPen(penColored);
  paintBuffer.setPen(penColored);
  paintBuffer.setFont(_font);
  paintWindow.setFont(_font);

  if (!_escapeState){
      if(_filled){
          paintWindow.setBrush(QBrush(_fillColor));
          paintBuffer.setBrush(QBrush(_fillColor));
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
              qDebug() << "Drawing polygon";
              if (_release){
                  //paintBufferForm.drawLine(_startPoint,_endPoint);
              }
              if (_listPointsPolygon.size() != 0)
              {
                  QPolygon _polygonToDraw;
                  for (unsigned int i=0; i < _listPointsPolygon.size() ; i++)
                  {
                      _polygonToDraw << _listPointsPolygon.at(i);
                  }
                  if (_enterState)
                  {
                      paintWindow.drawPolygon(_polygonToDraw, Qt::FillRule(Qt::OddEvenFill) );
                      paintBuffer.drawPolygon(_polygonToDraw, Qt::FillRule(Qt::OddEvenFill) );
                      //clear Polygon
                      _listPointsPolygon.clear();
                  }
                  else
                  {
                      paintWindow.drawPolyline(_polygonToDraw);
                      qDebug() << _listPointsPolygon.at(_listPointsPolygon.size()-1);
                      qDebug() << _endPoint;
                      if (!_haveUndo) paintWindow.drawLine(_listPointsPolygon.at(_listPointsPolygon.size()-1),_endPoint);
                  }
              }
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
           case TOOLS_ID_TEXT :
              qDebug() << "PaintArea:: draw TEXT";
              if (!_editing) _editing=true;
              paintWindow.drawText(_startPoint, *_currentText);
              qDebug() << "*current text: "<<*_currentText;
              if (_endEdition)
              {
                paintBuffer.drawText(_startPoint, *_currentText);
                _currentText->clear();
                _endEdition=false;
              }
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
              qDebug() << "Drawing polygon";
              if (_release){
                  //paintBufferForm.drawLine(_startPoint,_endPoint);
              }
              if (_listPointsPolygon.size() != 0)
              {
                  QPolygon _polygonToDraw;
                  for (unsigned int i=0; i < _listPointsPolygon.size() ; i++)
                  {
                      _polygonToDraw << _listPointsPolygon.at(i);
                  }
                  if (_enterState)
                  {
                      paintWindow.drawPolygon(_polygonToDraw);
                      paintBuffer.drawPolygon(_polygonToDraw);
                      //clear Polygon
                      _listPointsPolygon.clear();
                  }
                  else
                  {
                      paintWindow.drawPolyline(_polygonToDraw);
                      qDebug() << _listPointsPolygon.at(_listPointsPolygon.size()-1);
                      qDebug() << _endPoint;
                      if (!_haveUndo) paintWindow.drawLine(_listPointsPolygon.at(_listPointsPolygon.size()-1),_endPoint);
                  }
              }

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
           case TOOLS_ID_TEXT :
              qDebug() << "PaintArea:: draw TEXT";
              if (!_editing) _editing=true;
              paintWindow.drawText(_startPoint, *_currentText);
              qDebug() << "*current text: "<<*_currentText;
              if (_endEdition)
              {
                paintBuffer.drawText(_startPoint, *_currentText);
                _currentText->clear();
                _endEdition=false;
              }
              break;
            default :
              break;
        }
      }
  }
  else
  {
      _startPoint = _endPoint;
      _listPointsPolygon.clear();
  }
  if (_escapeState) {
      qDebug() << "Delete bufferForm - escape state";
      setEscapeState(false);
  }
  if (_enterState) {
    qDebug() << "Draw buffer Form ";
    setEnterState(false);
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

void PaintArea::clearDrawArea(void){
    qDebug() << "cleaning draw area :";
     _startPoint = _endPoint;
    this->getBuffer()->fill(Qt::white);
    _listPointsPolygon.clear();
    update();
}

void PaintArea::setEnterState(bool value){
    qDebug() << "Enter state :" <<value;
    _enterState = value;
    update();
}

void PaintArea::setEscapeState(bool value){
    qDebug() << "Escape state :" <<value;
    _escapeState = value;
    update();
}

void PaintArea::undo(void)
{
    qDebug() << "undo paint area" ;
    if(_currentTool == TOOLS_ID_POLYGON && _listPointsPolygon.size() !=0 ){
        qDebug() << "undo current polygon draw ";
        _listPointsPolygon.pop_back();
        _haveUndo = true;
    }

    update();
}

void PaintArea::setCurrentText(QString letter)
{
  qDebug() << "new letter "<<letter;
  _currentText->append(letter);
  update();
}

bool PaintArea::getEditing()
{
  return _editing;
}

void PaintArea::setEndEdition()
{
  _editing = false;
  _endEdition = true;
}