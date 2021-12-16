#ifndef TWOPANETBWINDOW_H
#define TWOPANETBWINDOW_H

#include <QObject>
#include "jmrijframe.h"
#include <QSplitter>

class QLabel;
class Box;
class PropertyChangeSupport;
class TwoPaneTBWindow : public JmriJFrame
{
public:
 /*public*/ TwoPaneTBWindow(QString name, QString menubarFile, QString toolbarFile, QWidget* parent=nullptr);
 /*public*/ QWidget* getTop();
 /*public*/ QWidget* getBottom();
 /*public*/ QWidget* getToolBar();
 /*public*/ QWidget* getSplitPane();
 /*public*/ void resetTopToPreferredSizes();
 /*public*/ void hideBottomPane(bool hide);
 /*public*/ QMenuBar* getMenu();
 virtual /*abstract*/ /*public*/ void remoteCalls(QStringList args);
 /*public*/ void addToStatusBox(QLabel* title, QLabel* value);
 /*public*/ void addToStatusBox(QWidget* comp);
 /*public*/ void dispose();

 /*
  The property change listener is located here so that the menus can interact with the front end
  */
 PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);

private:
 QSplitter*  upDownSplitPane;
 QWidget* top;// = new JPanel();
 QWidget* bottom;// = new JPanel();
 QWidget* statusBar;// = new JPanel();
 QToolBar* toolBar;// = new JToolBar();
 QMenuBar* menuBar;// = new JMenuBar();
 QList<QMenu*> menus;// = JMenuUtil.loadMenu(menuFile, this, this);
 Box* statusBox;
 int statusBoxIndex;// = 0;	// index to insert extra stuff
 static /*final*/ int statusStrutWidth;// = 10;

protected:
 /*protected*/ void buildGUI(QString menubarFile, QString toolbarFile);
 /*protected*/ void configureFrame();
 /*protected*/ bool _hideBottomPane;// = false;
 /*protected*/ void addMainMenuBar(QString menuFile);
 /*protected*/ void addMainToolBar(QString toolBarFile);
 /*protected*/ void addMainStatusBar();
 /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);

 friend class RosterFrame;
};

#endif // TWOPANETBWINDOW_H
