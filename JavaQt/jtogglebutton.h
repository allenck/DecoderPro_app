#ifndef JTOGGLEBUTTON_H
#define JTOGGLEBUTTON_H

#include <QPushButton>
#include "javaqt_global.h"

class NamedIcon;
class JAVAQTSHARED_EXPORT JToggleButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit JToggleButton(QWidget *parent = 0);
    /*public*/ JToggleButton (QWidget *parent = 0);
    /*public*/ JToggleButton(QIcon icon, QWidget *parent = 0) ;
    /*public*/ JToggleButton(NamedIcon* icon, QWidget *parent = 0);
    /*public*/ JToggleButton(QIcon icon, bool _selected, QWidget *parent = 0) ;
    /*public*/ JToggleButton(QString text, NamedIcon* icon, QWidget *parent = 0);
    /*public*/ JToggleButton (QString text, QWidget *parent = 0);
    /*public*/ JToggleButton (QString text, bool _selected, QWidget *parent = 0);
//    /*public*/ JToggleButton(QAction* a);
    /*public*/ JToggleButton(QString text, QIcon icon, QWidget *parent = 0);
    /*public*/ JToggleButton (QString text, QIcon icon, bool _selected, QWidget *parent = 0);
    /*public*/ void updateUI() ;
    /*public*/ QString getUIClassID();
    bool shouldUpdateSelectedStateFromAction();
    //void paintEvent(QPaintEvent *e) {} // TODO
    /*public*/ bool isSelected();
    /*public*/ void setSelected(bool b);
    NamedIcon* getIcon();
    void setSelectedIcon(NamedIcon*);
    void setText(const QString &text);
    /*public*/ QPoint getLocationOnScreen();

signals:
//    void selected(bool);
public slots:
    void toggleSelect();
private:
    /*private*/ static const QString uiClassID;// = "ToggleButtonUI";
 //bool _selected;
 NamedIcon* icon;
 void init();

};

#endif // JTOGGLEBUTTON_H
