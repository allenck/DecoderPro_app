#ifndef JROOTPANE_H
#define JROOTPANE_H

#include <QMainWindow>

class QStackedWidget;
class QPushButton;
class QMenuBar;
class JRootPane : public QMainWindow
{
 Q_OBJECT
public:
 explicit JRootPane(QWidget *parent = 0);
 /*public*/ QWidget* getContentPane();
 /*public*/ void setContentPane(QWidget* content);

signals:

public slots:
private:
 /*private*/ int windowDecorationStyle;

protected:

 /** The menu bar. */
 /*protected*/ QMenuBar* menuBar;

 /** The content pane. */
 /*protected*/ QWidget* contentPane;
 /** The layered pane that manages the menu bar and content pane. */
 /*protected*/ QStackedWidget* layeredPane;

 /**
  * The glass pane that overlays the menu bar and content pane,
  *  so it can intercept mouse movements and such.
  */
 /*protected*/ QWidget* glassPane;
 /**
  * The button that gets activated when the pane has the focus and
  * a UI-specific action like pressing the <b>Enter</b> key occurs.
  */
 /*protected*/ QPushButton* defaultButton;
 /*protected*/ QWidget* createContentPane();

};

#endif // JROOTPANE_H
