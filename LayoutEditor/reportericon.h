#ifndef REPORTERICON_H
#define REPORTERICON_H
#include "positionablelabel.h"
#include "reporter.h"
#include "positionablepopuputil.h"
#include "propertychangelistener.h"

// suppress inappropriate menu items
class AbstractReporter;
/*static*/ class ReporterPopupUtil : public PositionablePopupUtil
{
 Q_OBJECT
  public:
    ReporterPopupUtil(Positionable* parent, JComponent* textComp) : PositionablePopupUtil(parent, textComp)
    {
        //super(parent, textComp);
    }
    /*public*/ void setTextJustificationMenu(QMenu* /*popup*/) {}
    /*public*/ void setFixedTextMenu(QMenu* /*popup*/) {}
    /*public*/ void setTextMarginMenu(QMenu* /*popup*/)
    {
//        QMenu* colorMenu = new QMenu(tr("FontBackgroundColor"));
//        makeColorMenu(colorMenu, BACKGROUND_COLOR);
//        popup->addMenu(colorMenu);
    }

};


class LayoutEditor;
class ReporterIcon : public PositionableLabel, public PropertyChangeListener
{
    Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
public:
 //explicit ReporterIcon(QObject *parent = 0);
 /*public*/ ReporterIcon(Editor* editor = 0);
 /*public*/ ~ReporterIcon();
 /*public*/ void setReporter(QString pName);
 /*public*/ void setReporter(Reporter* r);
 /*public*/ Reporter* getReporter();
 // update icon as state changes
// /*public*/ void propertyChange(PropertyChangeEvent* e);
 /*public*/ QString getNameString() override;
 /*public*/ Positionable* deepClone() override ;
 /*public*/ Positionable* finishClone(Positionable* p) override;
    /*public*/ void dispose() override;
  QObject* self() override {return (QObject*)this;}
  QObject* pself() override{return (QObject*)this;}

signals:

public slots:
    //void on_propertyChange(AbstractReporter*,QString,QObject*,QObject*);
    void on_propertyChange(PropertyChangeEvent*e);
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;
    void editReporter();

private:
    // the associated Reporter object
    Reporter* reporter;// = null;
    void displayState();

Logger* log;
protected:
/*protected*/ void edit();

    
};

class AddReporterIconActionListener : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
 ReporterIcon* ri;
public:
 AddReporterIconActionListener(ReporterIcon* ri) {this->ri = ri;}
 QObject* self() override {return (QObject*)this;}

 public slots:
 void actionPerformed(JActionEvent */*e*/ = 0) override{ ri->editReporter();}
};

#endif // REPORTERICON_H
