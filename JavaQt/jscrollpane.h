#ifndef JSCROLLPANE_H
#define JSCROLLPANE_H

#include <QScrollArea>
#include "border.h"
#include "jpanel.h"

class JScrollPane : public JPanel
{
  Q_OBJECT
 public:
  JScrollPane(QWidget* parent = nullptr);
  /*public*/ void setBorder(Border* newBorder);
  /*public*/ Border* getBorder();
  /*public*/ void setWidget(QWidget* w);
  /*public*/ void setWidgetResizable(bool b);

 private:
  QScrollArea* sa;
  Border* border = nullptr;
  void paintEvent(QPaintEvent * evt);

};

#endif // JSCROLLPANE_H
