#ifndef REPORTERICON_H
#define REPORTERICON_H
#include "positionablelabel.h"
#include "reporter.h"
#include "positionablepopuputil.h"

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
class ReporterIcon : public PositionableLabel
{
    Q_OBJECT
public:
 //explicit ReporterIcon(QObject *parent = 0);
 /*public*/ ReporterIcon(Editor* editor = 0);
 /*public*/ ~ReporterIcon();
 /*public*/ void setReporter(QString pName);
 /*public*/ void setReporter(Reporter* r);
 /*public*/ Reporter* getReporter();
 // update icon as state changes
// /*public*/ void propertyChange(PropertyChangeEvent* e);
 /*public*/ QString getNameString();
 /*public*/ Positionable* deepClone() ;
 /*public*/ Positionable* finishClone(Positionable* p);
    /*public*/ void dispose();

signals:

public slots:
    //void on_propertyChange(AbstractReporter*,QString,QObject*,QObject*);
    void on_propertyChange(PropertyChangeEvent*e);
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    void editReporter();

private:
    // the associated Reporter object
    Reporter* reporter;// = null;
    void displayState();

Logger* log;
protected:
/*protected*/ void edit();

    
};
class AddReporterIconActionListener : public ActionListener
{
 Q_OBJECT
 ReporterIcon* self;
public:
 AddReporterIconActionListener(ReporterIcon* self) {this->self = self;}
public slots:
 void actionPerformed(JActionEvent */*e*/ = 0) { self->editReporter();}
};

#endif // REPORTERICON_H
