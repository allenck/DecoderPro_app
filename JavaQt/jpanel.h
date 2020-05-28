#ifndef JPANEL_H
#define JPANEL_H
#include <QFrame>
#include "border.h"
#include "flowlayout.h"

class JPanel : public QFrame
{
 Q_OBJECT
public:
 JPanel(QWidget* parent = nullptr);
 JPanel(QLayout* layout, QWidget* parent=nullptr);
 JPanel(FlowLayout* layout, QWidget* parent=nullptr);

 /*public*/ void setBorder(Border* newBorder);
 /*public*/ Border* getBorder();
 /*public*/ virtual QString getTitle() {return "";}
 /*public*/ void setBackground(QColor color);
 /*public*/ void removeAll();
 /*public*/ QColor getBackground();

// void paintEvent(QPaintEvent*);
// void virtual paintComponent(QPainter*);

private:
 Border* border = nullptr;

 void paintEvent(QPaintEvent *evt);
 QLayout* findParentLayout(QWidget* w);
 QLayout* findParentLayout(QWidget* w, QLayout* topLevelLayout);

};
#endif // JPANEL_H
