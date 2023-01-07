#ifndef JTABBEDPANE_H
#define JTABBEDPANE_H
#include <QTableWidget>
#include "jcomponent.h"

class QToolButton;
class JTabbedPane : public QTabWidget, public JComponent
{
 Q_OBJECT
  Q_INTERFACES(JComponent)
public:
 JTabbedPane(QWidget *parent = nullptr);
 ~JTabbedPane() {}
 JTabbedPane(const JTabbedPane&): QTabWidget() {}
 void setTabButton(int, QToolButton*);
 /*public*/ int indexOfTab(QIcon &icon);
 /*public*/ void add(QWidget* component, QString s, int i);
 /*public*/ void addTab(QString title, QIcon icon, QWidget* component, QString tip);
 /*public*/ void addTab(QString title, QIcon icon, QWidget* component);
 /*public*/ void addTab(QString title, QWidget* component);
 /*public*/ void insertTab(QString title, QIcon icon, QWidget* component, QString tip, int index);
 /*public*/ int indexOfComponent(QWidget* component);
 /*public*/ void removeTabAt(int index);
 /*public*/ QWidget* getComponentAt(int index);
 /*public*/ void setSelectedIndex(int index);
 /*public*/ int indexOfTab(QString title);
 /*public*/ void setEnabledAt(int tabIndex, bool enabled);
 /*public*/ void setToolTipTextAt(int i, QString txt);
 /*public*/ void setSelectedComponent(QWidget* w);
 /*public*/ QWidget* getSelectedComponent();
 bool isOpaque() override {return true;};
 QColor getForeground() override  {return Qt::black;}
 QColor getBackground() override  {return Qt::gray;}
 void setBackground(QColor) override  {}
 void setOpaque(bool) override  {}
 QFont getFont()  override {return QFont();}
 void setFont(QFont) override  {}
 void setBorder(Border*) {}
 Border* getBorder() {return  nullptr;}
 QFontMetrics getFontMetrics(QFont f) {return QFontMetrics (f);}
 QFontMetrics getFontMetrics() {return QFontMetrics (getFont());}void setEnabled(bool) {}
 void setSize(int, int) {}
 QString toString() {
   if(!jself()->objectName().isEmpty()) return jself()->objectName();
   else return jself()->metaObject()->className();
  }
 QWidget* jself() override {return  this;}
};

#endif // JTABBEDPANE_H
