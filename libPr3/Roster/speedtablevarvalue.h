#ifndef SPEEDTABLEVARVALUE_H
#define SPEEDTABLEVARVALUE_H
#include "variablevalue.h"
#include <QCheckBox>
#include "cvvalue.h"
#include "changeevent.h"
#include "actionevent.h"
#include "jslider.h"
#include "cvvalue.h"
#include "defaultboundedrangemodel.h"
class VarSlider;
class LIBPR3SHARED_EXPORT SpeedTableVarValue : public VariableValue
{
    Q_OBJECT
public:
    //explicit SpeedTableVarValue(QObject *parent = 0);
    /*public*/ SpeedTableVarValue(QString name, QString comment, QString cvName,
                              bool readOnly, bool infoOnly, bool writeOnly, bool opsOnly,
                              QString cvNum, QString mask, int minVal, int maxVal,
                              QMap<QString,CvValue*>* v, JLabel *status, QString stdname, int entries, bool mfxFlag, QObject *parent = 0);
    /*public*/ SpeedTableVarValue(QObject *parent = 0);
    /*public*/ QVariant rangeVal() override;
    /*public*/ QVector<CvValue*> usesCVs() override;
    void setModel(int i, int value) ;
    void forceMonotonic(int modifiedStepIndex, int value);
    void matchPoints(int modifiedStepIndex);
    void matchPointsLeft(int modifiedStepIndex);
    void matchPointsRight(int modifiedStepIndex);
    void enforceEndPointsMfx();
    /*public*/ int getState() ;
    /*public*/ QString getValueString() override;
    /*public*/ void setIntValue(int i) override;
    /*public*/ int getIntValue()  override;
    /*public*/ QVariant getValueObject() override;
    /*public*/ QWidget* getCommonRep() override;
    /*public*/ void setValue(int value);
    void setColor(QColor c);
    /*public*/ QWidget* getNewRep(QString format) override;
    void initStepCheckBoxes() ;
    /*public*/ void setCvState(int state) override;
    /*public*/ bool isChanged() override;
    /*public*/ void readChanges()  override;
    /*public*/ void writeChanges() override;
    /*public*/ void readAll() override;
    /*public*/ void writeAll()  override;
    void readNext();
    void writeNext() ;
    /*public*/ void dispose() override;
signals:

public slots:
    void doForceStraight(JActionEvent* e = 0);
    void doMatchEnds(JActionEvent* e = 0);
    void doRatioCurve(JActionEvent* e = 0);
    void doLogCurve(JActionEvent* e = 0);
    void doShiftLeft(JActionEvent* e = 0) ;
    void doShiftRight(JActionEvent* e = 0);
    /*public*/ void stateChanged(QWidget*);
    // handle incoming parameter notification
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;

private:
    static /*final*/ const QString VSTART_CV;// = 2;
    static /*final*/ const QString VHIGH_CV;// = 5;

    int nValues;
    int numCvs;
    QVector<QString>* cvList;
    QVector<BoundedRangeModel*>* models;
    int _min;
    int _max;
    int _range;
    bool mfx;

    QList<QCheckBox*> stepCheckBoxes;
    QColor _defaultColor;

    /**
     * IDLE if a read/write operation is not in progress.  During an operation, it
     * indicates the index of the CV to handle when the current programming operation
     * finishes.
     */
    /*private*/ int _progState = IDLE;

    /*private*/ static /*final*/ const int IDLE = -1;
    bool isReading;
    bool isWriting;

    /**
     * Count number of retries done
     */
    /*private*/ int retries = 0;

    /**
     * Define maximum number of retries of read/write operations before moving on
     */
    /*private*/ static /*final*/ const int RETRY_MAX = 2;

    bool onlyChanges;// = false;
    Logger* logit;
};

/* Internal class extends a JSlider so that its color is consistent with
 * an underlying CV; we return one of these in getNewRep.
 *<P>
 * Unlike similar cases elsewhere, this doesn't have to listen to
 * value changes.  Those are handled automagically since we're sharing the same
 * model between this object and others.  And this is listening to
 * a CV state, not a variable.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version
 */
/*public*/ class VarSlider : public JSlider
{
    Q_OBJECT
 public:
  VarSlider(BoundedRangeModel* m, CvValue* var, int step, QWidget* parent = 0) : JSlider(m, parent)
  {
   //super(m);
    _var = var;
    log  = new  Logger("VarSlider");
   // get the original color right
   setBackground(_var->getColor());
   // tooltip label
    setToolTip(tr("TextStep") +" "+QString::number(step)+" CV "+(var->number()));
   // listen for changes to original state
   //_var->addPropertyChangeListener(new PropertyChangeListener() {
    var->addPropertyChangeListener((PropertyChangeListener*)this);
    connect(var, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(originalPropertyChanged(PropertyChangeEvent*)));
//                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                    originalPropertyChanged(e);
//                }
//            });
  }
public slots:
  void propertyChange(PropertyChangeEvent* e)
  {
   originalPropertyChanged(e);
  }

  void originalPropertyChanged(PropertyChangeEvent* e )
  {
   if (log->isDebugEnabled()) log->debug(tr("VarSlider saw property change: ")+e->getPropertyName());
   // update this color from original state
   if (e->getPropertyName()==("State"))
   {
    setBackground(_var->getColor());
   }
   if (e->getPropertyName()==("Value"))
   {
    setValue(e->getNewValue().toInt());
   }
  }
private:
  CvValue* _var;
  QColor getBackground()
  {
   QColor c;
   QPalette p = palette();
   QString ss = styleSheet();
   c = p.color(QPalette::Background);
   if(ss == "")
     return c;
   int i = ss.indexOf("background-color");
   int j;
   if(i > 0)
   {
    i= ss.indexOf("rgb(")+4;
    j= ss.indexOf(",",i);
    int red =ss. mid(i,j-i).toInt();
    i=j+1;
    j = ss.indexOf(",",i);
    int green = ss.mid(i,j-i).toInt();
    i=j+1;
    j = ss.indexOf(")");
    int blue =  ss.mid(i,j-i).toInt();
    return QColor(red,green,blue);
   }
   return QColor();
  }
  void setBackground( QColor c )
  {
   QColor oldC = getBackground();
   if(oldC != c)
   {
    QString ss = QString("QSlider { background-color : rgb(%1,%2,%3);}").arg(c.red()).arg(c.green()).arg(c.blue());
    setStyleSheet(ss);
   }
  }
  Logger* log;
};  // end class definition

#endif // SPEEDTABLEVARVALUE_H
