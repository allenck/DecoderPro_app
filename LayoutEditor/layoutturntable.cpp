#include "layoutturntable.h"
#include "turnout.h"
#include "instancemanager.h"
#include "beanselectcreatepanel.h"
#include "decimalformat.h"
#include "logger.h"
#include "tracksegment.h"
#include <math.h>
#include "layouteditor.h"
#include "layouteditorfinditems.h"
#include "jmrijframe.h"
#include "borderlayout.h"
#include <qmessagebox.h>
#include <QGroupBox>

//LayoutTurntable::LayoutTurntable(QObject *parent) :
//  QObject(parent)
//{
//}

/**
 * A LayoutTurntable is a representation used by LayoutEditor to display a
 * turntable.
 * <P>
 * A LayoutTurntable has a variable number of connection points, called
 * RayTracks, each radiating from the center of the turntable. Each of these
 * points should be connected to a TrackSegment.
 * <P>
 * Each radiating segment (RayTrack) gets its Block information from its
 * connected track segment.
 * <P>
 * Each radiating segment (RayTrack) has a unique connection index. The
 * connection index is set when the RayTrack is created, and cannot be changed.
 * This connection index is used to maintain the identity of the radiating
 * segment to its connected Track Segment as ray tracks are added and deleted by
 * the user.
 * <P>
 * The radius of the turntable circle is variable by the user.
 * <P>
 * Each radiating segment (RayTrack) connecting point is a fixed distance from
 * the center of the turntable. The user may vary the angle of the radiating
 * segment. Angles are measured from the vertical (12 o'clock) position in a
 * clockwise manner. For example, 30 degrees is 1 o'clock, 60 degrees is 2
 * o'clock, 90 degrees is 3 o'clock, etc.
 * <P>
 * Each radiating segment is drawn from its connection point to the turntable
 * circle in the direction of the turntable center.
 *
 * @author Dave Duchamp Copyright (c) 2007
 * @version $Revision: 28746 $
 */
///*public*/  class LayoutTurntable {

// Defined text resource
//ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.display.layoutEditor.LayoutEditorBundle");


/**
 * constructor method
 */
/*public*/  LayoutTurntable::LayoutTurntable(QString id, QPointF c, LayoutEditor* myPanel, QObject *parent) :
   QObject(parent)
{
 log = new Logger("LayoutTurntable");
 dccControlledTurnTable  = false;
 lastKnownIndex = -1;
 popup = NULL;
 rayPopup = NULL;

 instance = this;
 layoutEditor = myPanel;
 ident = id;
 center = c;
 radius = 25.0;
 rayList = QList<RayTrack*>(); // list of Ray Track objects.
 active = true;
 item = NULL;

 // variables for Edit Turntable pane
 editTurntableFrame = NULL;
 radiusField = new JTextField(8);
 angleField = new JTextField(8);
 turntableEditDone;
 oldRadius = "";
 editOpen = false;
 needsRedraw = false;
}

/**
 * Accessor methods
 */
/*public*/  QString LayoutTurntable::getID() {
    return ident;
}

/*public*/  QPointF LayoutTurntable::getCoordsCenter() {
    return center;
}

/*public*/  double LayoutTurntable::getRadius() {
    return radius;
}

/*public*/  void LayoutTurntable::setRadius(double r) {
    radius = r;
}

/*protected*/ RayTrack* LayoutTurntable::addRay(double angle)
{
 RayTrack* ray = new RayTrack(angle, getNewIndex(), this);
 // (ray!=NULL) {
 rayList.append(ray);
 //}
 return ray;
}

/*private*/ int LayoutTurntable::getNewIndex()
{
 int index = -1;
 if (rayList.size() == 0) {
     return 0;
 }
 bool found = true;
 while (found)
 {
  index++;
  found = false;
  for (int i = 0; (i < rayList.size()) && !found; i++)
  {
   if (index == rayList.at(i)->getConnectionIndex())
   {
       found = true;
   }
  }
 }
 return index;
}

// the following method is only for use in loading layout turntables
/*public*/  void LayoutTurntable::addRayTrack(double angle, int index, QString name) {
    RayTrack* ray = new RayTrack(angle, index, this);
    //if (ray!=NULL) {
    rayList.append(ray);
    ray->connectName = name;
    //}
}

/*public*/  TrackSegment* LayoutTurntable::getRayConnectIndexed(int index) {
    RayTrack* ray = NULL;
    for (int i = 0; (i < rayList.size()) && (ray == NULL); i++) {
        RayTrack* r = rayList.at(i);
        if (r->getConnectionIndex() == index) {
            ray = r;
        }
    }
    if (ray == NULL) {
        return NULL;
    }
    return ray->getConnect();
}

/*public*/  TrackSegment* LayoutTurntable::getRayConnectOrdered(int i) {
    if (i >= rayList.size()) {
        return NULL;
    }
    RayTrack* ray = rayList.at(i);
    if (ray == NULL) {
        return NULL;
    }
    return ray->getConnect();
}

/*public*/  void LayoutTurntable::setRayConnect(TrackSegment* tr, int index) {
    RayTrack* ray = NULL;
    for (int i = 0; (i < rayList.size()) && (ray == NULL); i++) {
        RayTrack* r = rayList.at(i);
        if (r->getConnectionIndex() == index) {
            ray = r;
        }
    }
    if (ray == NULL) {
        return;
    }
    ray->setConnect(tr);
}

/*public*/  int LayoutTurntable::getNumberRays() {
    return rayList.size();
}

/*public*/  int LayoutTurntable::getRayIndex(int i) {
    if (i >= rayList.size()) {
        return 0;
    }
    RayTrack* ray = rayList.at(i);
    return ray->getConnectionIndex();
}

/*public*/  double LayoutTurntable::getRayAngle(int i) {
    if (i >= rayList.size()) {
        return 0.0;
    }
    RayTrack* ray = rayList.at(i);
    return ray->getAngle();
}

/*public*/  void LayoutTurntable::setRayTurnout(int index, QString turnoutName, int state) {
    RayTrack* ray = NULL;
    for (int i = 0; (i < rayList.size()) && (ray == NULL); i++) {
        RayTrack* r = rayList.at(i);
        if (r->getConnectionIndex() == index) {
            ray = r;
        }
    }
    if (ray == NULL) {
        log->error("Attempt to add Turnout control to a non-existant ray track");
        return;
    }
    ray->setTurnout(turnoutName, state);
}

/*public*/  QString LayoutTurntable::getRayTurnoutName(int i) {
    if (i >= rayList.size()) {
        return NULL;
    }
    RayTrack* ray = rayList.at(i);
    return ray->getTurnoutName();
}

/*public*/  Turnout* LayoutTurntable::getRayTurnout(int i) {
    if (i >= rayList.size()) {
        return NULL;
    }
    RayTrack* ray = rayList.at(i);
    return ray->getTurnout();
}

/*public*/  int LayoutTurntable::getRayTurnoutState(int i) {
    if (i >= rayList.size()) {
        return 0;
    }
    RayTrack* ray = rayList.at(i);
    return ray->getTurnoutState();
}

/*public*/  QPointF LayoutTurntable::getRayCoordsIndexed(int index) {
    RayTrack* ray = NULL;
    for (int i = 0; (i < rayList.size()) && (ray == NULL); i++) {
        RayTrack* r = rayList.at(i);
        if (r->getConnectionIndex() == index) {
            ray = r;
        }
    }
    if (ray == NULL) {
        return QPointF(0.0, 0.0);
    }
    double angle = (ray->getAngle() / 180.0) * M_PI;
    // calculate coordinates
    return (QPointF(
            (center.x() + ((1.25 * radius) * qSin(angle))),
            (center.y() - ((1.25 * radius) * qCos(angle)))));
}

/*public*/  QPointF LayoutTurntable::getRayCoordsOrdered(int i) {
    if (i >= rayList.size()) {
        return QPointF(0.0, 0.0);
    }
    RayTrack* ray = rayList.at(i);
    if (ray == NULL) {
        return QPointF(0.0, 0.0);
    }
    double angle = (ray->getAngle() / 180.0) * M_PI;
    // calculate coordinates
    return (QPointF(
            (center.x() + ((1.25 * radius) * qSin(angle))),
            (center.y() - ((1.25 * radius) * qCos(angle)))));
}

/*public*/  void LayoutTurntable::setRayCoordsIndexed(double x, double y, int index) {
    RayTrack* ray = NULL;
    for (int i = 0; (i < rayList.size()) && (ray == NULL); i++) {
        RayTrack* r = rayList.at(i);
        if (r->getConnectionIndex() == index) {
            ray = r;
        }
    }
    if (ray == NULL) {
        log->error("Attempt to move a non-existant ray track");
        return;
    }
    // convert these coordinates to an angle
    double angle = /*Math.toDegrees*/(qAtan(qAbs(x - center.x())
            / qAbs(y - center.y()))) * 57.2958;
    if (x >= center.x()) {
        if (y > center.y()) {
            angle = 180.0 - angle;
        }
    } else {
        if (y > center.y()) {
            angle = 180.0 + angle;
        } else {
            angle = 360.0 - angle;
        }
    }
    ray->setAngle(angle);
}

/**
 * Methods to test if ray is a mainline track or not Returns true if
 * connecting track segment is mainline Defaults to not mainline if
 * connecting track segment is missing
 */
/*public*/  bool LayoutTurntable::isMainlineIndexed(int index) {
    RayTrack* ray = NULL;
    for (int i = 0; (i < rayList.size()) && (ray == NULL); i++) {
        RayTrack* r = rayList.at(i);
        if (r->getConnectionIndex() == index) {
            ray = r;
        }
    }
    if (ray == NULL) {
        return false;
    }
    TrackSegment* tr = ray->getConnect();
    if (tr == NULL) {
        return false;
    }
    return tr->getMainline();
}

/*public*/  bool LayoutTurntable::isMainlineOrdered(int i) {
    if (rayList.size() <= i) {
        return false;
    }
    RayTrack* ray = rayList.at(i);
    if (ray == NULL) {
        return false;
    }
    TrackSegment* tr = ray->getConnect();
    if (tr == NULL) {
        return false;
    }
    return tr->getMainline();
}

/**
 * Modify coordinates methods
 */
/*public*/  void LayoutTurntable::setCoordsCenter(QPointF p) {
    center = p;
}

/*public*/  void LayoutTurntable::scaleCoords(float xFactor, float yFactor) {
    QPointF pt = QPointF(round(center.x() * xFactor),
            round(center.y() * yFactor));
    center = pt;
}

double LayoutTurntable::round(double x) {
    int i = (int) (x + 0.5);
    return i;
}

/**
 * Initialization method The name of each track segment connected to a ray
 * track is initialized by by LayoutTurntableXml, then the following method
 * is called after the entire LayoutEditor is loaded to set the specific
 * TrackSegment objects.
 */
/*public*/  void LayoutTurntable::setObjects(LayoutEditor* p)
{
 for (int i = 0; i < rayList.size(); i++) {
     RayTrack* ray = rayList.at(i);
     ray->setConnect(p->getFinder()->findTrackSegmentByName(ray->connectName));
 }
}

/*public*/  bool LayoutTurntable::isTurnoutControlled() {
    return dccControlledTurnTable;
}

/*public*/  void LayoutTurntable::setTurnoutControlled(bool boo) {
    dccControlledTurnTable = boo;
}


/**
 * Display popup menu for information and editing
 */
/*protected*/ void LayoutTurntable::showPopUp(QGraphicsSceneMouseEvent* e) {
    if (popup != NULL) {
        popup->clear();
    } else {
        popup = new QMenu();
    }
    popup->addAction(new AbstractAction(tr("Turntable"),this));
    popup->addSeparator();//new JSeparator(JSeparator.HORIZONTAL));
    QAction*act;
    popup->addAction(act = new AbstractAction(tr("Edit"),this));
//    {
//        /**
//         *
//         */
//        /*private*/ static final long serialVersionUID = 3697868897248094986L;

//        /*public*/  void actionPerformed(ActionEvent e) {
//            editTurntable(instance);
//        }
//    });
    connect(act, SIGNAL(triggered()),this, SLOT(onEdit_triggered()));
    popup->addAction(new AbstractAction(tr("Remove"),this));
//    {
//        /**
//         *
//         */
//        ///*private*/ static final long serialVersionUID = -5542663629950241682L;

//        /*public*/  void actionPerformed(ActionEvent e) {
//            if (layoutEditor.removeTurntable(instance)) {
//                // Returned true if user did not cancel
//                remove();
//                dispose();
//            }
//        }
//    });
      connect(act, SIGNAL(triggered(bool)), this, SLOT(on_remove_triggered()));
    layoutEditor->setShowAlignmentMenu(popup);
    //popup.show(e.getComponent(), e.getX(), e.getY());
    popup->exec(QCursor::pos());
}

void LayoutTurntable::onEdit_triggered()
{
 editTurntable(instance);
}

void LayoutTurntable::on_remove_triggered()
{
 remove();
 dispose();
}

/*protected*/ void LayoutTurntable::showRayPopUp(QGraphicsSceneMouseEvent* e, int index) {
    if (rayPopup != NULL) {
        rayPopup->clear();
    } else {
        rayPopup = new QMenu();
    }
    RayTrack* ray = NULL;
    for (int i = 0; (i < rayList.size()) && (ray == NULL); i++) {
        RayTrack* r = rayList.at(i);
        if (r->getConnectionIndex() == index) {
            ray = r;
        }
    }
    if (ray == NULL) {
        //log->error("Attempt to set the position on a non-existant ray track");
        return;
    }
    rayPopup->addAction(new QAction(tr("Turntable Ray ") + QString::number(index),this));
    if (ray->getTurnout() != NULL) {
        rayPopup->addAction(new QAction(ray->getTurnout()->getDisplayName() + " (" + QString::number(ray->getTurnoutState()) + ")", this));
    }
    //rayPopup.show(e.getComponent(), e.getX(), e.getY());
    rayPopup->exec(QCursor::pos());
}

/*public*/  void LayoutTurntable::setPosition(int index)
{
 if (!isTurnoutControlled()) {
     return;
 }
 RayTrack* ray = NULL;
 for (int i = 0; (i < rayList.size()) && (ray == NULL); i++)
 {
  RayTrack* r = rayList.at(i);
  if (r->getConnectionIndex() == index)
  {
   ray = r;
  }
 }
 if (ray == NULL)
 {
  log->error("Attempt to set the position on a non-existant ray track");
  return;
 }
 lastKnownIndex = index;
 ray->setPosition();
 layoutEditor->update();
 layoutEditor->setDirty();
 needsRedraw = false;
}

/*public*/  int LayoutTurntable::getPosition() {
    return lastKnownIndex;
}


/**
 * Edit a Turntable
 */
/*protected*/ void LayoutTurntable::editTurntable(LayoutTurntable* x)
{
 if (editOpen)
 {
  editTurntableFrame->setVisible(true);
  return;
 }
 needsRedraw = false;
 // Initialize if needed
 if (editTurntableFrame == NULL)
 {
  editTurntableFrame = new JmriJFrame(tr("Edit Turntable"), false, true);
  editTurntableFrame->addHelpMenu("package.jmri.jmrit.display.EditTurntable", true);
  editTurntableFrame->move(50, 30);
  QWidget* contentPane = editTurntableFrame->getContentPane();
  QWidget* headerPane = new QWidget();
  QWidget* footerPane = new QWidget();
  headerPane->setLayout(new QVBoxLayout);//(headerPane, BoxLayout.Y_AXIS));
  footerPane->setLayout(new QVBoxLayout);//(footerPane, BoxLayout.Y_AXIS));
//  contentPane->setLayout(new BorderLayout());
//  ((BorderLayout*)contentPane->layout())->addWidget(headerPane, BorderLayout::North);
//  ((BorderLayout*)contentPane->layout())->addWidget(footerPane, BorderLayout::South);
  contentPane->setLayout(new QVBoxLayout);
  ((QVBoxLayout*)contentPane->layout())->addWidget(headerPane, 0, Qt::AlignTop);
  ((QVBoxLayout*)contentPane->layout())->addWidget(footerPane, 0, Qt::AlignBottom);
  // setup radius
  QWidget* panel1 = new QWidget();
  panel1->setLayout(new FlowLayout());
  QLabel* radiusLabel = new QLabel(tr("Turntable Radius"));
  panel1->layout()->addWidget(radiusLabel);
  panel1->layout()->addWidget(radiusField);
  radiusField->setToolTip(tr("Enter radius (screen units) of turntable circle."));
  headerPane->layout()->addWidget(panel1);
  // setup add ray track
  QWidget* panel2 = new QWidget();
  panel2->setLayout(new FlowLayout());
  QLabel* rayAngleLabel = new QLabel(tr("Ray Angle"));
  panel2->layout()->addWidget(rayAngleLabel);
  panel2->layout()->addWidget(angleField);
  angleField->setToolTip(tr("Enter angle of ray track to add or delete (12 o'clock = 0, 3 o'clock = 90 degrees, etc.)."));
  headerPane->layout()->addWidget(panel2);
  QWidget* panel3 = new QWidget();
  panel3->setLayout(new FlowLayout());
  panel3->layout()->addWidget(_addRayTrack = new QPushButton(tr("Add Ray Track")));
  _addRayTrack->setToolTip(tr("Click to add a new ray track at the angle entered above."));
//        _addRayTrack.addActionListener(new ActionListener() {
//            /*public*/  void actionPerformed(ActionEvent e) {
//                addRayTrackPressed(e);
//                updateRayPanel();
//            }
//        });
  connect(_addRayTrack, SIGNAL(clicked()), this, SLOT(on_addRayTrack_clicked()));
  panel3->layout()->addWidget(dccControlled = new QCheckBox(tr("DCC Controlled Turntable")));
  dccControlled->setChecked(isTurnoutControlled());
//        dccControlled.addActionListener(new ActionListener() {
//            /*public*/  void actionPerformed(ActionEvent e) {
//                setTurnoutControlled(dccControlled.isSelected());
//                for (RayTrack ray : rayList) {
//                    ray->showTurnoutDetails();
//                }
//                editTurntableFrame.pack();
//            }
//        });
  connect(dccControlled, SIGNAL(clicked(bool)), this, SLOT(on_dccControled_clicked()));
  headerPane->layout()->addWidget(panel3);
  // set up Done and Cancel buttons
  QWidget* panel5 = new QWidget();
  panel5->setLayout(new FlowLayout());
  panel5->layout()->addWidget(turntableEditDone = new QPushButton(tr("Done")));
//        turntableEditDone.addActionListener(new ActionListener() {
//            /*public*/  void actionPerformed(ActionEvent e) {
//                turntableEditDonePressed(e);
//            }
//        });
  connect(turntableEditDone, SIGNAL(clicked()), this, SLOT(turntableEditDonePressed()));
  turntableEditDone->setToolTip(tr("Click Done to accept any changes made above and dismiss this dialog."));
  // Cancel
  panel5->layout()->addWidget(turntableEditCancel = new QPushButton(tr("Cancel")));
//        turntableEditCancel.addActionListener(new ActionListener() {
//            /*public*/  void actionPerformed(ActionEvent e) {
//                turntableEditCancelPressed(e);
//            }
//        });
  connect(turntableEditCancel, SIGNAL(clicked()), this, SLOT(turntableEditCancelPressed()));
  turntableEditCancel->setToolTip(tr("Click Cancel to dismiss this dialog without making changes."));
  footerPane->layout()->addWidget(panel5);

  rayPanel = new QWidget();
  rayPanel->setLayout(new QVBoxLayout); //(rayPanel, BoxLayout.Y_AXIS));
  foreach (RayTrack* ray, rayList)
  {
   rayPanel->layout()->addWidget(ray->getPanel());
  }
  QScrollArea* rayScrollPane = new QScrollArea; //(rayPanel, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
  //((BorderLayout*)contentPane->layout())->addWidget(rayScrollPane, BorderLayout::Center);
  ((QVBoxLayout*)contentPane->layout())->addWidget(rayScrollPane, 0, Qt::AlignVCenter);
  rayScrollPane->setWidgetResizable(true);
  rayScrollPane->setWidget(rayPanel);
 }
 else
 {
  updateRayPanel();
 }
 // Set up for Edit
 radiusField->setText(" " + QString::number(radius));
 oldRadius = radiusField->text();
 angleField->setText("0");
//    editTurntableFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//        /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
//            turntableEditCancelPressed(NULL);
//        }
//    });
 editTurntableFrame->adjustSize();
 editTurntableFrame->setVisible(true);
 editOpen = true;
}

void LayoutTurntable::on_dccControled_clicked()
{
 setTurnoutControlled(dccControlled->isChecked());
 foreach (RayTrack* ray, rayList)
 {
  ray->showTurnoutDetails();
 }
 editTurntableFrame->adjustSize();
}

//Remove old rays and add them back in
/*private*/ void LayoutTurntable::updateRayPanel()
{
//    for (Component comp : rayPanel.getComponents()) {
//        rayPanel.remove(comp);
//    }
 QLayoutItem* item;
 if(rayPanel->layout()!= NULL)
 {
  while ( ( item = rayPanel->layout()->takeAt( 0 ) ) != NULL )
  {
   delete item->widget();
   delete item;
  }
  rayPanel->setLayout(new QVBoxLayout);//(rayPanel, BoxLayout.Y_AXIS));
 }

 foreach (RayTrack* ray, rayList)
 {
  ray->panel = NULL;
  rayPanel->layout()->addWidget(ray->getPanel());
 }
 rayPanel->update();
 rayPanel->repaint();
 editTurntableFrame->adjustSize();
}

void LayoutTurntable::on_addRayTrack_clicked()
{
 addRayTrackPressed();
 updateRayPanel();
}

/*private*/ void LayoutTurntable::saveRayPanelDetail()
{
 foreach (RayTrack* ray, rayList)
 {
  ray->updateDetails();
 }
}

/*private*/ void LayoutTurntable::addRayTrackPressed(ActionEvent* a)
{
 double ang = 0.0;
 bool ok;
 ang = angleField->text().toFloat(&ok);
 if(!ok)
 {
//     JOptionPane.showMessageDialog(editTurntableFrame, tr("EntryError") + ": "
//                                   + e + tr("TryAgain"), tr("Error"),
//                                   JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(editTurntableFrame, tr("Error"), tr("Error in entry, value not valid decimal number, try again"));
  return;
 }
 addRay(ang);
 layoutEditor->redrawPanel();
 layoutEditor->setDirty();
 needsRedraw = false;
}

void LayoutTurntable::deleteRayTrackPressed(ActionEvent* a) {
    double ang = 0.0;
    bool ok;
        ang = angleField->text().toFloat(&ok);
    if(!ok) {
//        JOptionPane.showMessageDialog(editTurntableFrame, tr("EntryError") + ": "
//                + e + tr("TryAgain"), tr("Error"),
//                JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(editTurntableFrame, tr("Error"), tr("Error in entry, value not valid decimal number, try again"));
        return;
    }
    // scan rays to find the one to delete
    RayTrack* closest = NULL;
    double bestDel = 360.0;
    for (int i = 0; i < rayList.size(); i++) {
        double del = diffAngle((rayList.at(i))->getAngle(), ang);
        if (del < bestDel) {
            bestDel = del;
            closest = rayList.at(i);
        }
    }
    if (bestDel > 30.0) {
//        JOptionPane.showMessageDialog(editTurntableFrame, tr("Error13"),
//                tr("Error"), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(editTurntableFrame, tr("Error"), tr("entered angle. Please try again with a more precise angle entry."));
        return;
    }
    deleteRay(closest);
}

void LayoutTurntable::deleteRay(RayTrack* closest) {
    TrackSegment* t = NULL;
    if (closest == NULL) {
        log->error("closest is NULL!");
    } else {
        t = closest->getConnect();
        rayList.removeAt(closest->getConnectionIndex());
        closest->dispose();
    }
    if (t != NULL) {
        layoutEditor->removeTrackSegment(t);
    }

    // update the panel
    layoutEditor->redrawPanel();
    layoutEditor->setDirty();
    needsRedraw = false;
}

void LayoutTurntable::turntableEditDonePressed(ActionEvent* a)
{
 // check if new radius was entered
 QString str = radiusField->text();
 if (str!=(oldRadius))
 {
  double rad = 0.0;
  bool ok;
  rad = str.toFloat(&ok);
  if(!ok)
  {
//            JOptionPane.showMessageDialog(editTurntableFrame, tr("EntryError") + ": "
//                    + e + tr("TryAgain"), tr("Error"),
//                    JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(editTurntableFrame, tr("Error"), tr("Error in entry, value not valid decimal number, try again"));
      return;
  }
  radius = rad;
  needsRedraw = true;
 }
 // clean up
 editOpen = false;
 editTurntableFrame->setVisible(false);
 editTurntableFrame->dispose();
 editTurntableFrame = NULL;
 saveRayPanelDetail();
 if (needsRedraw)
 {
  layoutEditor->redrawPanel();
  layoutEditor->setDirty();
 }
}

void LayoutTurntable::turntableEditCancelPressed(ActionEvent* a) {
    editOpen = false;
    editTurntableFrame->setVisible(false);
    editTurntableFrame->dispose();
    editTurntableFrame = NULL;
    if (needsRedraw) {
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
    }
}

/**
 * Clean up when this object is no longer needed. Should not be called while
 * the object is still displayed; see remove()
 */
void LayoutTurntable::dispose() {
    if (popup != NULL) {
        popup->clear();
    }
    popup = NULL;
    foreach (RayTrack* ray, rayList) {
        ray->dispose();
    }
}

/**
 * Removes this object from display and persistance
 */
void LayoutTurntable::remove() {
    // remove from persistance by flagging inactive
    active = false;
}


/**
 * "active" means that the object is still displayed, and should be stored.
 */
/*public*/  bool LayoutTurntable::isActive() {
    return active;
}

//class RayTrack {

 /*public*/  RayTrack::RayTrack(double angle, int index, LayoutTurntable* lt)
 {
 log = new Logger("RayTrack");
  this->lt = lt;
  rayAngle = lt->normalizeAngle(angle);
  _connect = NULL;
  connectionIndex = index;
  connectName = "";
  turnoutStateValues = QList<int>() << Turnout::CLOSED << Turnout::THROWN;
  twoDForm = new DecimalFormat("#.00");
  namedTurnout = NULL;
  panel = NULL;
 }

 // accessor routines
 /*public*/  TrackSegment* RayTrack::getConnect() {
     return _connect;
 }

 /*public*/  void RayTrack::setConnect(TrackSegment* tr) {
     _connect = tr;
 }

 /*public*/  double RayTrack::getAngle() {
     return rayAngle;
 }

 /*public*/  void RayTrack::setAngle(double an) {
     rayAngle = normalizeAngle(an);
 }

 /*public*/  int RayTrack::getConnectionIndex() {
     return connectionIndex;
 }

 /*public*/  double RayTrack::normalizeAngle(double a) {
     double angle = a;
     while (angle < 0.0) {
         angle += 360.0;
     }
     while (angle >= 360.0) {
         angle -= 360.0;
     }
     return angle;
 }

 /*public*/  double RayTrack::diffAngle(double a, double b) {
     double anA = normalizeAngle(a);
     double anB = normalizeAngle(b);
     if (anA >= anB) {
         if ((anA - anB) <= 180.0) {
             return (anA - anB);
         } else {
             return (anB + 360.0 - anA);
         }
     } else {
         if ((anB - anA) <= 180.0) {
             return (anB - anA);
         } else {
             return (anA + 360.0 - anB);
         }
     }
 }

 /*public*/  void RayTrack::setTurnout(QString turnoutName, int state) {
     Turnout* turnout = NULL;
//        if (mTurnoutListener == NULL) {
//            mTurnoutListener = new PropertyChangeListener() {
//                /*public*/  void propertyChange(PropertyChangeEvent e) {
//                    if (getTurnout().getKnownState() == turnoutState) {
//                        lastKnownIndex = connectionIndex;
//                        layoutEditor.redrawPanel();
//                        layoutEditor.setDirty();
//                    }
//                }
//            };
//        }
//        connect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     if (turnoutName != NULL) {
         turnout = InstanceManager::turnoutManagerInstance()->
                 getTurnout(turnoutName);
     }
     if (namedTurnout != NULL && namedTurnout->getBean() != turnout) {
         //namedTurnout->getBean().removePropertyChangeListener(mTurnoutListener);
      disconnect(namedTurnout->getBean()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     if (turnout != NULL && (namedTurnout == NULL || namedTurnout->getBean() != turnout)) {
         namedTurnout = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(turnoutName, turnout);
         //turnout.addPropertyChangeListener(mTurnoutListener, turnoutName, "Layout Editor Turntable");
         connect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

         lt->needsRedraw = true;
     }
     if (turnout == NULL) {
         namedTurnout = NULL;
     }

     if (this->turnoutState != state) {
         this->turnoutState = state;
         lt->needsRedraw = true;
     }
 }
 /*public*/ void RayTrack::propertyChange(PropertyChangeEvent* e)
 {
  if (getTurnout()->getKnownState() == turnoutState) {
      lt->lastKnownIndex = connectionIndex;
      lt->layoutEditor->redrawPanel();
      lt->layoutEditor->setDirty();
  }
 }
 /*public*/  void RayTrack::setPosition() {
     if (namedTurnout != NULL) {
         getTurnout()->setCommandedState(turnoutState);
     }
 }

 /*public*/  Turnout* RayTrack::getTurnout() {
     if (namedTurnout == NULL) {
         return NULL;
     }
     return namedTurnout->getBean();
 }

 /*public*/  QString RayTrack::getTurnoutName() {
     if (namedTurnout == NULL) {
         return NULL;
     }
     return namedTurnout->getName();
 }

 /*public*/  int RayTrack::getTurnoutState() {
     return turnoutState;
 }

/*public*/  QWidget* RayTrack::getPanel()
{
 if (panel == NULL)
 {
  QWidget* top = new QWidget();
  top->setLayout(new FlowLayout);
  /*JLabel lbl = new JLabel("Index :"+connectionIndex);
   top.add(lbl);*/
  top->layout()->addWidget(new JLabel(tr("RayAngle") + " : "));
  top->layout()->addWidget(angle = new JTextField(5));
//            angle.addFocusListener(
//                    new FocusListener() {
//                        /*public*/  void focusGained(FocusEvent e) {
//                        }

//                        /*public*/  void focusLost(FocusEvent e) {
//                            try {
//                                Float.parseFloat(angle.getText());
//                            } catch (Exception ex) {
//                                JOptionPane.showMessageDialog(editTurntableFrame, tr("EntryError") + ": "
//                                        + ex + tr("TryAgain"), tr("Error"),
//                                        JOptionPane.ERROR_MESSAGE);
//                                return;
//                            }
//                        }
//                    }
//            );
   panel = new QGroupBox();
   panel->setLayout(new QVBoxLayout);//(panel, BoxLayout.Y_AXIS));
   panel->layout()->addWidget(top);

   beanBox = new BeanSelectCreatePanel(InstanceManager::turnoutManagerInstance(), getTurnout());
   QString turnoutStateThrown = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getThrownText();
   QString turnoutStateClosed = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getClosedText();
   QStringList turnoutStates = QStringList() << turnoutStateClosed << turnoutStateThrown;

   turnoutStateCombo = new QComboBox(/*turnoutStates*/);
   turnoutStateCombo->addItems(turnoutStates);
   turnoutStateLabel = new JLabel(tr("Turnout State"));
   turnoutPanel = new QWidget();
   turnoutPanel->setLayout(new FlowLayout);
   //turnoutPanel.setBorder(new EtchedBorder());
   turnoutPanel->layout()->addWidget(beanBox);
   turnoutPanel->layout()->addWidget(turnoutStateLabel);
   turnoutPanel->layout()->addWidget(turnoutStateCombo);
   if (turnoutState == Turnout::CLOSED) {
       turnoutStateCombo->setCurrentIndex(turnoutStateCombo->findText(turnoutStateClosed));
   } else {
       turnoutStateCombo->setCurrentIndex(turnoutStateCombo->findText(turnoutStateThrown));
   }
   panel->layout()->addWidget(turnoutPanel);

   QPushButton* deleteRayButton;
   top->layout()->addWidget(deleteRayButton = new QPushButton(tr("Remove")));
   deleteRayButton->setToolTip(tr("Delete Ray Track"));
//            deleteRayButton.addActionListener(new ActionListener() {
//                /*public*/  void actionPerformed(ActionEvent e) {
//                    delete();
//                    updateRayPanel();
//                }
//            });
   connect(deleteRayButton, SIGNAL(clicked(bool)), this, SLOT(on_deleteRayButton_clicked()));
   //border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));

   //panel.setBorder(border);
   QString gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 5px; margin-top: 1ex; /* leave space at the top for the title */} "
                  "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

   panel->setStyleSheet(gbStyleSheet);
  }
  showTurnoutDetails();

  angle->setText(twoDForm->format(getAngle()));
  panel->setTitle("Ray : " + QString::number(connectionIndex));
  if (_connect == NULL) {
      panel->setTitle(tr("Unconnected") + " : " + QString::number(connectionIndex));
  } else if (_connect != NULL && _connect->getLayoutBlock() != NULL) {
      panel->setTitle(tr("Connected") + " : " + _connect->getLayoutBlock()->getDisplayName());
  }
  return panel;
 }

 void RayTrack::on_deleteRayButton_clicked()
 {
   _delete();
   lt->updateRayPanel();
 }
 void RayTrack::_delete() {
//        int n = JOptionPane.showConfirmDialog(NULL,
//                tr("Question7"),
//                tr("WarningTitle"),
//                JOptionPane.YES_NO_OPTION);
  int n = QMessageBox::question(NULL, tr("Warning"), tr("Are you sure you want to remove this ray from the turntable, along with any connected Track Segments?"), QMessageBox::Yes | QMessageBox::No);
     if (n == QMessageBox::No) {
         return;
     }
     lt->deleteRay(this);
 }

 void RayTrack::updateDetails()
 {
  if (beanBox == NULL || turnoutStateCombo == NULL)
  {
   return;
  }
  setTurnout(beanBox->getDisplayName(), turnoutStateValues[turnoutStateCombo->currentIndex()]);
  if (angle->text()!=(twoDForm->format(getAngle())))
  {
   bool ok;
   double ang = angle->text().toDouble(&ok);
   setAngle(ang);
   lt->needsRedraw = true;
   if(!ok)
   {
    log->error("Angle is not in correct format so will skip " + angle->text());
   }
  }
 }

 void RayTrack::showTurnoutDetails()
 {
  turnoutPanel->setVisible(lt->isTurnoutControlled());
  beanBox->setVisible(lt->isTurnoutControlled());
  turnoutStateCombo->setVisible(lt->isTurnoutControlled());
  turnoutStateLabel->setVisible(lt->isTurnoutControlled());
 }

 void RayTrack::dispose()
 {
  if (getTurnout() != NULL)
  {
      //getTurnout().removePropertyChangeListener(mTurnoutListener);
   disconnect(getTurnout()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  if (lt->lastKnownIndex == connectionIndex) {
      lt->lastKnownIndex = -1;
  }
 }
//}; // End class RayTrack

/*public*/  double LayoutTurntable::normalizeAngle(double a) {
 double angle = a;
 while (angle < 0.0) {
     angle += 360.0;
 }
 while (angle >= 360.0) {
     angle -= 360.0;
 }
 return angle;
}

/*public*/  double LayoutTurntable::diffAngle(double a, double b)
{
 double anA = normalizeAngle(a);
 double anB = normalizeAngle(b);
 if (anA >= anB) {
     if ((anA - anB) <= 180.0) {
         return (anA - anB);
     } else {
         return (anB + 360.0 - anA);
     }
 } else {
     if ((anB - anA) <= 180.0) {
         return (anB - anA);
     } else {
         return (anA + 360.0 - anB);
     }
 }
}

