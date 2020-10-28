#ifndef JCOMPONENT_H
#define JCOMPONENT_H

#include <QWidget>
#include "insets.h"

class Border;
class JComponent // : public QWidget
{
 //Q_OBJECT
public:
 //explicit JComponent(QWidget *parent = nullptr);
 //virtual void dispose() {}
 virtual bool isOpaque() = 0;
 virtual QColor getForeground() = 0;
 virtual QColor getBackground() =0;
 virtual void setBackground(QColor) = 0;
 virtual void setOpaque(bool) =0;
 virtual QFont getFont() =0;
 virtual void setFont(QFont) =0;
 virtual QObject* jself() = 0;
 /*public*/ void setInheritsPopupMenu(bool value) {
         inheritsPopupMenu = value;
     }

     /*public*/ bool getInheritsPopupMenu() {
         return inheritsPopupMenu;
     }
 int getWidth() {return ((QWidget*)jself())->width();}
 int getHeight() {return ((QWidget*)jself())->height();}
 Insets* getInsets(Insets* insets) {return insets;}
 virtual void setBorder(Border*) =0;
 virtual Border* getBorder() =0;
 virtual QFontMetrics getFontMetrics(QFont f) {return QFontMetrics (f);}
 virtual void setEnabled(bool) =0;

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
