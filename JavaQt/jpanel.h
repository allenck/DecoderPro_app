#ifndef JPANEL_H
#define JPANEL_H
#include <QFrame>
#include "border.h"
#include "flowlayout.h"
#include "jcomponent.h"

class JPanel : public QFrame, public JComponent
{
 Q_OBJECT
 Q_INTERFACES(JComponent)
public:
 JPanel(QWidget* parent = nullptr);
 JPanel(QLayout* layout, QWidget* parent=nullptr);
 JPanel(FlowLayout* layout, QWidget* parent=nullptr);

 /*public*/ void setBorder(Border* newBorder);
 /*public*/ Border* getBorder();
 /*public*/ virtual QString getTitle() {return "";}
 /*public*/ void setBackground(QColor color);
 /*public*/ void removeAll();
 /*public*/ QColor getForeground();
 /*public*/ QColor getBackground();

 //void paintEvent(QPaintEvent*);
 /*public*/void virtual paintComponent(QPainter*) {}
 /*public*/ bool isOpaque(){return _opaque;}
 /*public*/ /*public*/ void setOpaque(bool b){_opaque = b;}
 /*public*/ QFont getFont() {return QFrame::font();}
 /*public*/ void setFont(QFont f) {QFrame::setFont(f);}
 /*public*/ QObject* jself() {return (QObject*)this;}
 /*public*/ void setEnabled(bool b ) override {QWidget::setEnabled(b);}
private:
 Border* border = nullptr;

 void paintEvent(QPaintEvent *evt);
 QLayout* findParentLayout(QWidget* w);
 QLayout* findParentLayout(QWidget* w, QLayout* topLevelLayout);

};
#endif // JPANEL_H
