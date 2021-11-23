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

 /*public*/ void setBorder(Border* newBorder) override;
 /*public*/ Border* getBorder()override;
 /*public*/ virtual QString getTitle() {return "";}
 /*public*/ void setBackground(QColor color)override;
 /*public*/ void removeAll();
 /*public*/ QColor getForeground()override;
 /*public*/ QColor getBackground()override;

 //void paintEvent(QPaintEvent*);
 /*public*/void virtual paintComponent(QPainter*) {}
 /*public*/ bool isOpaque()override{return _opaque;}
 /*public*/ /*public*/ void setOpaque(bool b)override{_opaque = b;}
 /*public*/ QFont getFont() override{return QFrame::font();}
 /*public*/ void setFont(QFont f) override{QFrame::setFont(f);}
 /*public*/ QWidget* jself() override{return (QWidget*)this;}
 /*public*/ void setEnabled(bool b ) override {QWidget::setEnabled(b);}
private:
 Border* border = nullptr;

 void paintEvent(QPaintEvent *evt)override;
 QLayout* findParentLayout(QWidget* w);
 QLayout* findParentLayout(QWidget* w, QLayout* topLevelLayout);

};
#endif // JPANEL_H
