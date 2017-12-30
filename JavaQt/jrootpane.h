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
 /**
  * Constant used for the windowDecorationStyle property. Indicates that
  * the <code>JRootPane</code> should not provide any sort of
  * Window decorations.
  *
  * @since 1.4
  */
 enum WINDOWDECORATIONSTYLE
 {
 NONE = 0,

 /**
  * Constant used for the windowDecorationStyle property. Indicates that
  * the <code>JRootPane</code> should provide decorations appropriate for
  * a Frame.
  *
  * @since 1.4
  */
 FRAME = 1,

 /**
  * Constant used for the windowDecorationStyle property. Indicates that
  * the <code>JRootPane</code> should provide decorations appropriate for
  * a Dialog.
  *
  * @since 1.4
  */
 PLAIN_DIALOG = 2,

 /**
  * Constant used for the windowDecorationStyle property. Indicates that
  * the <code>JRootPane</code> should provide decorations appropriate for
  * a Dialog used to display an informational message.
  *
  * @since 1.4
  */
 INFORMATION_DIALOG = 3,

 /**
  * Constant used for the windowDecorationStyle property. Indicates that
  * the <code>JRootPane</code> should provide decorations appropriate for
  * a Dialog used to display an error message.
  *
  * @since 1.4
  */
 ERROR_DIALOG = 4,

 /**
  * Constant used for the windowDecorationStyle property. Indicates that
  * the <code>JRootPane</code> should provide decorations appropriate for
  * a Dialog used to display a <code>JColorChooser</code>.
  *
  * @since 1.4
  */
 COLOR_CHOOSER_DIALOG = 5,
 /**
  * Constant used for the windowDecorationStyle property. Indicates that
  * the <code>JRootPane</code> should provide decorations appropriate for
  * a Dialog used to display a <code>JFileChooser</code>.
  *
  * @since 1.4
  */
 FILE_CHOOSER_DIALOG = 6,

 /**
  * Constant used for the windowDecorationStyle property. Indicates that
  * the <code>JRootPane</code> should provide decorations appropriate for
  * a Dialog used to present a question to the user.
  *
  * @since 1.4
  */
 QUESTION_DIALOG = 7,

 /**
  * Constant used for the windowDecorationStyle property. Indicates that
  * the <code>JRootPane</code> should provide decorations appropriate for
  * a Dialog used to display a warning message.
  *
  * @since 1.4
  */
 WARNING_DIALOG = 8
 };

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
