#ifndef JTABBEDPANE_H
#define JTABBEDPANE_H
#include <QTableWidget>

class QToolButton;
class JTabbedPane : public QTabWidget
{
 Q_OBJECT
public:
 JTabbedPane(QWidget *parent = nullptr);
 void setTabButton(int, QToolButton*);
 /*public*/ int indexOfTab(QIcon &icon);
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

};

#endif // JTABBEDPANE_H
