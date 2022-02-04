#ifndef JCOMPONENT_H
#define JCOMPONENT_H

#include <QWidget>
#include "insets.h"
#include <QFontMetrics>

class JPanel;
class Border;
class JComponent // : public QWidget
{
 //Q_OBJECT
public:
 //explicit JComponent(QWidget *parent = nullptr);
 //virtual void dispose() {}
  virtual bool isOpaque() {return true;};
  virtual QColor getForeground() {return Qt::black;}
 virtual QColor getBackground() {return Qt::gray;}
  virtual void setBackground(QColor) {}
  virtual void setOpaque(bool) {}
  virtual QFont getFont() {return QFont();}
  virtual void setFont(QFont) {}
 virtual QWidget* jself() = 0;
 /*public*/ void setInheritsPopupMenu(bool value) {
     inheritsPopupMenu = value;
 }

 /*public*/ bool getInheritsPopupMenu() {
     return inheritsPopupMenu;
 }
 int getWidth() {return ((QWidget*)jself())->width();}
 int getHeight() {return ((QWidget*)jself())->height();}
 Insets* getInsets(Insets* insets) {return insets;}
 virtual void setBorder(Border*) {}
 virtual Border* getBorder() {return  nullptr;}
 virtual QFontMetrics getFontMetrics(QFont f) {return QFontMetrics (f);}
 virtual QFontMetrics getFontMetrics() {return QFontMetrics (getFont());}
 virtual void setEnabled(bool) {}
 virtual void setSize(int, int) {}
 virtual QString toString() {
  if(!jself()->objectName().isEmpty()) return jself()->objectName();
  else return jself()->metaObject()->className();
 }
signals:

public slots:
private:
 bool _opaque = true;
 bool inheritsPopupMenu;

 friend class JFrame;
 friend class DiagramComponent;
 friend class JPanel;
};
Q_DECLARE_INTERFACE(JComponent, "JComponent")
#endif // JCOMPONENT_H
