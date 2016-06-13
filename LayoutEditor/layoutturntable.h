#ifndef LAYOUTTURNTABLE_H
#define LAYOUTTURNTABLE_H

#include <QObject>
#include <QPointF>
#include "namedbeanhandle.h"

class QGraphicsSceneMouseEvent;
class QGraphicsItemGroup;
class ActionEvent;
class QPushButton;
class QCheckBox;
class JmriJFrame;
class QMouseEvent;
class Logger;
class QLabel;
class JTextField;
class QGroupBox;
class QComboBox;
class DecimalFormat;
class BeanSelectCreatePanel;
class Turnout;
class LayoutTurntable;
class TrackSegment;
class QMenu;
class QPointF;
class LayoutEditor;
class RayTrack : public QObject
{
 Q_OBJECT
 // persistant instance variables
 double rayAngle;// = 0.0;
 TrackSegment* _connect;// = NULL;
 int connectionIndex;// = -1;
 LayoutTurntable* lt;
public:
 /*public*/  RayTrack(double angle, int index, LayoutTurntable* lt);
 // accessor routines
 /*public*/  TrackSegment* getConnect();
 /*public*/  void setConnect(TrackSegment* tr);
 /*public*/  double getAngle();
 /*public*/  void setAngle(double an);
 /*public*/  int getConnectionIndex();
 // initialization instance variable (used when loading a LayoutEditor)
 /*public*/  QString connectName;// = "";
 /*public*/  double normalizeAngle(double a);
 /*public*/  double diffAngle(double a, double b);
 /*public*/  void setTurnout(QString turnoutName, int state);
 /*public*/  void setPosition();
 /*public*/  Turnout* getTurnout() ;
 /*public*/  QString getTurnoutName();
 /*public*/  int getTurnoutState();
 /*public*/  QWidget* getPanel();
 ///*public*/  bool isTurnoutControlled();
 ///*public*/  void setTurnoutControlled(bool boo);
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 void on_deleteRayButton_clicked();

  private:
 Logger* log;
 NamedBeanHandle<Turnout*>* namedTurnout;
 //Turnout t;
 int turnoutState;
 ///*private*/ PropertyChangeListener mTurnoutListener;
 QGroupBox* panel;
 QWidget* turnoutPanel;
 BeanSelectCreatePanel* beanBox;
 //QGroupBox* border;
 QComboBox* turnoutStateCombo;
 QLabel* turnoutStateLabel;
 JTextField* angle;
 /*final*/ QList<int> turnoutStateValues;// = new int[]{Turnout.CLOSED, Turnout.THROWN};
 /*final*/ DecimalFormat* twoDForm;// = new DecimalFormat("#.00");
 void _delete();
 void updateDetails();
 void showTurnoutDetails();
 void dispose();
 friend class LayoutTurntable;
};

class LayoutTurntable : public QObject
{
 Q_OBJECT
public:
 //explicit LayoutTurntable(QObject *parent = 0);
 /*public*/  LayoutTurntable(QString id, QPointF c, LayoutEditor* myPanel, QObject *parent=0);

 /*public*/  void setObjects(LayoutEditor* p);
 /*public*/  QString getID();
 /*public*/  QPointF getCoordsCenter() ;
 /*public*/  double getRadius() ;
 /*public*/  void setRadius(double r);
 /*public*/  void setCoordsCenter(QPointF p) ;
 /*public*/  void scaleCoords(float xFactor, float yFactor);
 /*public*/  double normalizeAngle(double a);
 /*public*/  void addRayTrack(double angle, int index, QString name);
 /*public*/  TrackSegment* getRayConnectIndexed(int index);
 /*public*/  TrackSegment* getRayConnectOrdered(int i);
 /*public*/  void setRayConnect(TrackSegment* tr, int index);
 /*public*/  int getNumberRays();
 /*public*/  int getRayIndex(int i);
 /*public*/  double getRayAngle(int i);
 /*public*/  void setRayTurnout(int index, QString turnoutName, int state);
 /*public*/  QString getRayTurnoutName(int i);
 /*public*/  Turnout* getRayTurnout(int i);
 /*public*/  int getRayTurnoutState(int i);
 /*public*/  QPointF getRayCoordsIndexed(int index);
 /*public*/  QPointF getRayCoordsOrdered(int i);
 /*public*/  void setRayCoordsIndexed(double x, double y, int index);
 /*public*/  bool isMainlineIndexed(int index);
 /*public*/  bool isMainlineOrdered(int i);
 /*public*/  bool isTurnoutControlled();
 /*public*/  void setTurnoutControlled(bool boo);
 /*public*/  void setPosition(int index);
 /*public*/  int getPosition();
 /*public*/  double diffAngle(double a, double b);
 /*public*/  bool isActive();

signals:

public slots:
 void on_addRayTrack_clicked();
 void onEdit_triggered();
 void on_remove_triggered();
 void on_dccControled_clicked();

private:
 Logger* log;
 // defined constants
 // operational instance variables (not saved between sessions)
 /*private*/ LayoutTurntable* instance;// = null;
 /*private*/ LayoutEditor* layoutEditor;// = null;

 /*private*/ bool dccControlledTurnTable;// = false;

 // persistent instance variables (saved between sessions)
 /*private*/ QString ident;// = "";
 /*private*/ double radius;// = 25.0;
 /*private*/ QPointF center;// = new Point2D.Double(50.0, 50.0);
 /*private*/ QList<RayTrack*> rayList;// = new QList<RayTrack>(); // list of Ray Track objects.
 /*private*/ int lastKnownIndex;// = -1;
 double round(double x);
  QMenu* popup;// = null;
  /*private*/ int getNewIndex();
  QMenu* rayPopup;// = NULL;
  // variables for Edit Turntable pane
  JmriJFrame* editTurntableFrame;// = NULL;
  JTextField* radiusField;// = new JTextField(8);
  JTextField* angleField;// = new JTextField(8);
  QPushButton* turntableEditDone;
  QPushButton* turntableEditCancel;
  QPushButton* _addRayTrack;
  QPushButton* deleteRayTrack;
  QCheckBox* dccControlled;
  QString oldRadius;// = "";
  QWidget* rayPanel;
  bool editOpen;// = false;
  bool needsRedraw;// = false;
  /*private*/ void updateRayPanel();
  /*private*/ void saveRayPanelDetail();
  /*private*/ void addRayTrackPressed(ActionEvent* a = 0);
  void deleteRayTrackPressed(ActionEvent* a = 0);
  void deleteRay(RayTrack* closest);
  void dispose();
  void remove();
  bool active;// = true;
  QGraphicsItemGroup* item;

private slots:
  void turntableEditDonePressed(ActionEvent* a = 0);
  void turntableEditCancelPressed(ActionEvent* a = 0);

 protected:
  /*protected*/ RayTrack* addRay(double angle);
  /*protected*/ void showPopUp(QGraphicsSceneMouseEvent* e);
  /*protected*/ void showRayPopUp(QGraphicsSceneMouseEvent* e, int index);
  /*protected*/ void editTurntable(LayoutTurntable* x);
 friend class LayoutTurntable;
 friend class RayTrack;
 friend class LayoutEditor;
};

#endif // LAYOUTTURNTABLE_H
