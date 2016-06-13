#include "busyglasspane.h"
#include <QPainter>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QMainWindow>
#include <QStatusBar>
#include <QDebug>
#include <QApplication>
#include "jtogglebutton.h"

//BusyGlassPane::BusyGlassPane(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * Used to intercept inputs and to display a busy
 * cursor during reads and writes.
 *
 * Based in part on code from the Java Tutorial for glass panes (java.sun.com).
 *
 * Used in PaneProgFrame to control cursor operations during programming.
 *
 * @author  Howard G. Penny   Copyright (C) 2005
 * @version $Revision: 17977 $
 */
// /*public*/ class BusyGlassPane extends JComponent {


/*public*/ BusyGlassPane::BusyGlassPane(QList<QWidget*> components, QList<QRect> rectangles, QWidget* contentPane, QWidget* parent)
    : QWidget(parent)
{
//        listener = new CBListener(components, rectangles, this, contentPane, parent);
//        addMouseListener(listener);
//        addMouseMotionListener(listener);
//  setStyleSheet("background:transparent;");
//  setAttribute(Qt::WA_TranslucentBackground);
//  setWindowFlags(Qt::FramelessWindowHint);
 this->components = components;
 this->rectangles = rectangles;
 this->contentPane = contentPane;
 QVBoxLayout* layout;
 setLayout(layout = new QVBoxLayout);
 layout->addWidget(new QLabel("Processing..."), 0, Qt::AlignCenter);
 resize(contentPane->rect().width(), contentPane->height());
 QPoint p = contentPane->pos();
 move(p.x(), p.y());
 setMouseTracking(true);
}

/*public*/ void BusyGlassPane::dispose() {
//        this.removeMouseListener(listener);
//        this.removeMouseMotionListener(listener);
 setMouseTracking(false);
 close();
}
void BusyGlassPane::paintEvent(QPaintEvent* /*event*/)
{
  QColor backgroundColor = palette().light().color();
  backgroundColor.setAlpha(100);
  QPainter customPainter(this);
  customPainter.fillRect(rect(),backgroundColor);
}

#if 0
/**
 * Listen for all events that our components are likely to be
 * interested in.  Redispatch them to the appropriate component.
 */
class CBListener extends MouseInputAdapter {
    JFrame parentFrame;
    List<JComponent> liveComponents;
    List<Rectangle> liveRectangles;
    BusyGlassPane glassPane;
    Container contentPane;
    boolean inDrag = false;

    /*public*/ CBListener(List<JComponent> objects, List<Rectangle> rectangles,
                      BusyGlassPane glassPane, Container contentPane, JFrame parent) {
        this.parentFrame = parent;
        this.liveComponents = objects;
        this.liveRectangles = rectangles;
        this.glassPane = glassPane;
        this.contentPane = contentPane;
    }

    /*public*/ void mouseMoved(MouseEvent e) {
        redispatchMouseEvent(e);
    }

    /*
     * We must forward at least the mouse drags that started
     * with mouse presses over the button.  Otherwise,
     * when the user presses the button then drags off,
     * the button isn't disarmed -- it keeps its dark
     * gray background or whatever its L&F uses to indicate
     * that the button is currently being pressed.
     */
    /*public*/ void mouseDragged(MouseEvent e) {
        redispatchMouseEvent(e);
    }

    /*public*/ void mouseClicked(MouseEvent e) {
        redispatchMouseEvent(e);
    }

    /*public*/ void mouseEntered(MouseEvent e) {
        redispatchMouseEvent(e);
    }

    /*public*/ void mouseExited(MouseEvent e) {
        redispatchMouseEvent(e);
    }

    /*public*/ void mousePressed(MouseEvent e) {
        redispatchMouseEvent(e);
    }

    /*public*/ void mouseReleased(MouseEvent e) {
        redispatchMouseEvent(e);
        inDrag = false;
    }

    private void redispatchMouseEvent(MouseEvent e) {
        boolean inButton = false;
        Point glassPanePoint = e.getPoint();
        Component component = null;
        Container container = contentPane;
        Point containerPoint = SwingUtilities.convertPoint(glassPane,
                                                           glassPanePoint,
                                                           contentPane);
        int eventID = e.getID();

        //XXX: If the event is from a component in a popped-up menu,
        //XXX: then the container should probably be the menu's
        //XXX: JPopupMenu, and containerPoint should be adjusted
        //XXX: accordingly.
        component = SwingUtilities.getDeepestComponentAt(container,
                                                         containerPoint.x,
                                                         containerPoint.y);

        if (component == null) {
            return;
        }

        for (int i = 0; i < liveComponents.size(); i++) {
            if (component.equals(liveComponents.get(i))) {
                inButton = true;
                testForDrag(eventID);
            }
        }

        for (int i = 0; i < liveRectangles.size(); i++) {
            if (liveRectangles.get(i).contains(containerPoint)) {
                inButton = true;
                testForDrag(eventID);
            }
        }

        if (inButton || (inButton && inDrag)) {
            Point componentPoint = SwingUtilities.convertPoint(glassPane,
                                                               glassPanePoint,
                                                               component);
            parentFrame.setCursor(Cursor.getDefaultCursor());
            component.dispatchEvent(new MouseEvent(component,
                                                   eventID,
                                                   e.getWhen(),
                                                   e.getModifiers(),
                                                   componentPoint.x,
                                                   componentPoint.y,
                                                   e.getClickCount(),
                                                   e.isPopupTrigger()));
        } else {
            parentFrame.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
        }

    }

    private void testForDrag(int eventID) {
        if (eventID == MouseEvent.MOUSE_PRESSED) {
            inDrag = true;
        }
    }
#endif
void BusyGlassPane::mouseMoveEvent(QMouseEvent *event)
{
 redispatchMouseEvent(event);
}
void BusyGlassPane::mousePressEvent(QMouseEvent * event)
{
 redispatchMouseEvent(event);
}
void BusyGlassPane::mouseReleaseEvent(QMouseEvent * event)
{
 redispatchMouseEvent(event);
 if(inButton)   ((JToggleButton*)component)->animateClick();
}

void BusyGlassPane::redispatchMouseEvent(QMouseEvent *e)
{
 inButton = false;
 QPoint glassPanePoint = e->pos();
 component = NULL;
 QWidget* container = contentPane;
 QString t;

 QMainWindow* mw = (QMainWindow*)parent();

 component = container->childAt(glassPanePoint);
 if(component)
 {
  for(int i = 0; i < components.size(); i++)
  {
   if(components.at(i) == component)
   {
//    qDebug() << "found";
    t = "found";
    inButton = true;
   }
  }
 }
 mw->statusBar()->clearMessage();
 mw->statusBar()->showMessage(QString("pos: x=%1, y=%2 %3").arg(glassPanePoint.x()).arg( glassPanePoint.y()).arg(t));
 if(inButton)
 {
  setCursor(Qt::ArrowCursor);
 }\
 else
  setCursor(Qt::WaitCursor);
}
