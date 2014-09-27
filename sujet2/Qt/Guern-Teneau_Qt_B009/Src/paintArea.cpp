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

  //Init vars
  _currentTool = TOOLS_ID_LINE;
  _currentStylePen = Qt::SolidLine;
  _currentCapPen = Qt::SquareCap;
  _currentJoinPen = Qt::BevelJoin;
  _currentStyleBrush = Qt::NoBrush;
  _currentColor =  Qt::black;
  _fillColor = Qt::black;
  _currentWidthPen = 0;
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
  qDebug() << evt;
  qDebug() << _currentTool;
  QPainter paintWindow(this);
  QPainter paintBuffer(_buffer);

  paintWindow.drawPixmap(0,0, *_buffer);

  //QPen penColored(_currentColor);
  QPen currentPen;
  currentPen.setColor(_currentColor);
  currentPen.setStyle(_currentStylePen);
  currentPen.setWidth(_currentWidthPen);
  currentPen.setCapStyle(_currentCapPen);
  currentPen.setJoinStyle(_currentJoinPen);

  QBrush currentBrush;
  currentBrush.setStyle(_currentStyleBrush);
  currentBrush.setColor(_fillColor);

  paintWindow.setPen(currentPen);
  paintBuffer.setPen(currentPen);
  paintWindow.setBrush(currentBrush);
  paintBuffer.setBrush(currentBrush);
  paintBuffer.setFont(_font);
  paintWindow.setFont(_font);

  if (!_escapeState)
  {
    switch(_currentTool)
    {
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
  else
  {
      _startPoint = _endPoint;
      _listPointsPolygon.clear();
  }
  if (_escapeState) {
      qDebug() << " escape state";
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


void PaintArea::setCurrentStylePen(int stylePen) {
    switch(stylePen) {
        case STYLE_PEN_ID_SOLID :
            _currentStylePen = Qt::SolidLine;
            break;
        case STYLE_PEN_ID_DASH :
            _currentStylePen = Qt::DashLine;
            break;

        case STYLE_PEN_ID_DOT :
            _currentStylePen = Qt::DotLine;
            break;

        case STYLE_PEN_ID_DASHDOT :
            _currentStylePen = Qt::DashDotLine;
            break;

        case STYLE_PEN_ID_DASHDOTNOT :
            _currentStylePen = Qt::DashDotDotLine;
            break;

        case STYLE_PEN_ID_NONE :
            _currentStylePen = Qt::NoPen;
            break;

        default :
            break;
    }
}


void PaintArea::setCurrentCapPen(int capPen) {
    switch(capPen) {
        case CAP_PEN_ID_FLAT :
            _currentCapPen = Qt::FlatCap;
            break;
        case CAP_PEN_ID_SQUARE :
            _currentCapPen = Qt::SquareCap;
            break;
        case CAP_PEN_ID_ROUND :
            _currentCapPen = Qt::RoundCap;
            break;
        default :
            break;
    }
  //_currentCapPen = capPen;
}


void PaintArea::setCurrentJoinPen(int joinPen) {
    switch(joinPen) {
        case JOIN_PEN_ID_MITER :
            _currentJoinPen = Qt::MiterJoin;
            break;
        case JOIN_PEN_ID_BEVEL :
            _currentJoinPen = Qt::BevelJoin;
            break;
        case JOIN_PEN_ID_ROUND :
            _currentJoinPen = Qt::RoundJoin;
            break;
        default :
            break;
    }
}


void PaintArea::setCurrentStyleBrush(int styleBrush) {
    switch(styleBrush) {
        case STYLE_BRUSH_ID_LINEARGRADIENT :
            _currentStyleBrush = Qt::LinearGradientPattern;
            break;
        case STYLE_BRUSH_ID_RADIALGRADIENT :
            _currentStyleBrush = Qt::RadialGradientPattern;
            break;

        case STYLE_BRUSH_ID_CONICALGRADIENT :
            _currentStyleBrush = Qt::ConicalGradientPattern;
            break;

        case STYLE_BRUSH_ID_TEXTURE :
            _currentStyleBrush = Qt::TexturePattern;
            break;

        case STYLE_BRUSH_ID_SOLID :
            _currentStyleBrush = Qt::SolidPattern;
            break;

        case STYLE_BRUSH_ID_HORIZONTAL :
            _currentStyleBrush = Qt::HorPattern;
            break;

        case STYLE_BRUSH_ID_VERTICAL :
            _currentStyleBrush = Qt::VerPattern;
            break;
        case STYLE_BRUSH_ID_CROSS :
            _currentStyleBrush = Qt::CrossPattern;
            break;

        case STYLE_BRUSH_ID_BACKWARDDIAGONAL :
            _currentStyleBrush = Qt::BDiagPattern;
            break;

        case STYLE_BRUSH_ID_FORWARDDIAGONAL :
            _currentStyleBrush = Qt::FDiagPattern;
            break;

        case STYLE_BRUSH_ID_DIAGONALCROSS :
            _currentStyleBrush = Qt::DiagCrossPattern;
            break;

        case STYLE_BRUSH_ID_DENSE1 :
            _currentStyleBrush = Qt::Dense1Pattern;
            break;

        case STYLE_BRUSH_ID_DENSE2 :
            _currentStyleBrush = Qt::Dense2Pattern;
            break;
        case STYLE_BRUSH_ID_DENSE3 :
            _currentStyleBrush = Qt::Dense3Pattern;
            break;

        case STYLE_BRUSH_ID_DENSE4 :
            _currentStyleBrush = Qt::Dense4Pattern;
            break;

        case STYLE_BRUSH_ID_DENSE5 :
            _currentStyleBrush = Qt::Dense5Pattern;
            break;

        case STYLE_BRUSH_ID_DENSE6 :
            _currentStyleBrush = Qt::Dense6Pattern;
            break;

        case STYLE_BRUSH_ID_DENSE7 :
            _currentStyleBrush = Qt::Dense7Pattern;
            break;

        case STYLE_BRUSH_ID_NONE :
            _currentStyleBrush = Qt::NoBrush;
            break;

        default :
            break;
    }
  //_currentStyleBrush = styleBrush;
}

void PaintArea::setCurrentColor(QColor color){
    _currentColor = color;
}

void PaintArea::setFillColor(QColor color){
    _fillColor = color;
}

void PaintArea::setCurrentWidthPen(int widthPen){
    switch(widthPen) {
        case WIDTH_PEN_ID_MIN :
            _currentWidthPen = 0;
            break;
        case WIDTH_PEN_ID_SEL1 :
            _currentWidthPen = 3;
            break;
        case WIDTH_PEN_ID_SEL2 :
            _currentWidthPen = 5;
            break;
        case WIDTH_PEN_ID_SEL3 :
            _currentWidthPen = 7;
            break;
        case WIDTH_PEN_ID_MAX :
            _currentWidthPen = 10;
            break;
        default :
            break;
    }
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
