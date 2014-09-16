//
// Demonstrate QRubberBand oddity (Qt4-Beta1, linux)
//

#include <QApplication>
#include <QMouseEvent>
#include <QRubberBand>
#include <QWidget>

#include <cmath>

class BandWidget : public QWidget
{
public:

	//! Attempt to put QRubberBand in this widget's coordinate system
	BandWidget()
		: QWidget()
		, theBand(QRubberBand::Rectangle)
	{
		// this "almost" works - but results in buggy display during drawing.
		theBand.setParent(this);
	}

protected:

	virtual void mousePressEvent(QMouseEvent* qme)
	{
		theBand.show();
		//
		// Would be nice to have a method here like:
		//
		// theBand.setStartPoint(qme->pos());
		//
		// instead of:
		//
		theStart = qme->pos();
		theBand.setGeometry(QRect(theStart, theStart));
	}

	virtual void mouseMoveEvent(QMouseEvent* qme)
	{
		//
		// Would be nice to have a method here like:
		//
		// theBand.setEndPoint(qme->pos());
		//
		// instead of:
		//
		int const xMin = (theStart.x() < qme->x()) ? theStart.x() : qme->x() ;
		int const yMin = (theStart.y() < qme->y()) ? theStart.y() : qme->y() ;
		int const wide = abs(qme->x() - theStart.x());
		int const tall = abs(qme->y() - theStart.y());
		theBand.setGeometry(QRect(xMin, yMin, wide, tall));
	}

	virtual void mouseReleaseEvent(QMouseEvent* qme)
	{
//		theBand.hide();
	}

private:

	QRubberBand  theBand;
	QPoint       theStart;   //!< Would be nice to NOT need this

};


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
// widget with mouse tracking rubber band graphic.
//	app.setMainWidget(new BandWidget);
	BandWidget* rubber = new BandWidget();
//	app.mainWidget()->show();
	rubber->show();
	int stat = app.exec();
	return stat;
}


