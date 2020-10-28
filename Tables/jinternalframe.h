#ifndef JINTERNALFRAME_H
#define JINTERNALFRAME_H

#include <QMdiSubWindow>
#include "propertychangelistener.h"
#include "rosterentry.h"
#include "jcomponent.h"

class InternalFrameListener;
class QVBoxLayout;
class JDesktopIcon;
class JRootPane;
class JInternalFrame : public QMdiSubWindow, public JComponent
{
 Q_OBJECT
    Q_INTERFACES(JComponent)
public:
 explicit JInternalFrame(QWidget *parent = 0);
 /*public*/ JInternalFrame(QString title, QWidget *parent = 0);
 /*public*/ JInternalFrame(QString title, bool resizable, QWidget* parent);
 /*public*/ JInternalFrame(QString title, bool resizable, bool closable, QWidget*parent = 0);
 /*public*/ JInternalFrame(QString title, bool resizable, bool closable,
                       bool maximizable, QWidget*parent = 0);
 /*public*/ JInternalFrame(QString title, bool resizable, bool closable,
                             bool maximizable, bool iconifiable, QWidget *parent = 0);
 /*public*/ void updateUI();
 /** Bound property name. */
 /*public*/ /*final*/ static QString CONTENT_PANE_PROPERTY;// = "contentPane";
 /** Bound property name. */
 /*public*/ /*final*/ static QString MENU_BAR_PROPERTY;// = "JMenuBar";
 /** Bound property name. */
 /*public*/ /*final*/ static QString TITLE_PROPERTY;// = "title";
 /** Bound property name. */
 /*public*/ /*final*/ static QString LAYERED_PANE_PROPERTY;// = "layeredPane";
 /** Bound property name. */
 /*public*/ /*final*/ static QString ROOT_PANE_PROPERTY;// = "rootPane";
 /** Bound property name. */
 /*public*/ /*final*/ static QString GLASS_PANE_PROPERTY;// = "glassPane";
 /** Bound property name. */
 /*public*/ /*final*/ static QString FRAME_ICON_PROPERTY;// = "frameIcon";

 /**
  * Constrained property name indicated that this frame has
  * selected status.
  */
 /*public*/ /*final*/ static QString IS_SELECTED_PROPERTY;// = "selected";
 /** Constrained property name indicating that the internal frame is closed. */
 /*public*/ /*final*/ static QString IS_CLOSED_PROPERTY;// = "closed";
 /** Constrained property name indicating that the internal frame is maximized. */
 /*public*/ /*final*/ static QString IS_MAXIMUM_PROPERTY;// = "maximum";
 /** Constrained property name indicating that the internal frame is iconified. */
 /*public*/ /*final*/ static QString IS_ICON_PROPERTY;// = "icon";
  /*public*/ void setContentPane(QWidget* c);
 /*public*/ JRootPane* getRootPane();
 /*public*/ QWidget* getContentPane();
 /*public*/ void setLocation(int x, int y);
 /*public*/ void addInternalFrameListener(InternalFrameListener* l) ;
 /*public*/ void removeInternalFrameListener(InternalFrameListener* l);
 /*public*/ void moveToFront();
 /*public*/ QString getName();
 /*public*/ void setName(QString name);
 /*public*/ QString getTitle();
 /*public*/ void setTitle(QString title);
 /*public*/ void setSelected(bool selected) /*throws PropertyVetoException*/;
 /*public*/ bool isSelected();
 /*public*/ void restoreSubcomponentFocus();
 /*public*/ bool isIcon();
 /*public*/ void setIcon(bool b) /*throws PropertyVetoException*/;
 /*public*/ void pack();
 /*public*/ bool isMaximum();
 /*public*/ void setMaximum(bool b) /*throws PropertyVetoException*/;
 /*public*/ void doDefaultCloseAction();
 /*public*/ void setDefaultCloseOperation(int operation);
 /*public*/ int getDefaultCloseOperation();
 /*public*/ virtual void dispose();
 /*public*/ void toFront();
 /*public*/ void toBack();
 /*public*/ void moveToBack();

    void setEnabled(bool b) override {setEnabled(b);}
    bool isOpaque() {return true;}
    QColor getForeground()  {return Qt::black;}
    QColor getBackground() {return Qt::lightGray;}
    void setBackground(QColor){return;}
    void setOpaque(bool) {}
    QFont getFont() {return font();}
    void setFont(QFont f) {QWidget::setFont(f);}
    QObject* jself() {(QObject*)this;}
    void setBorder(Border* b) {}
    Border* getBorder() {return nullptr;}

signals:
 void propertyChange(PropertyChangeEvent*);

public slots:

private:
 /*private*/ static /*final*/ QString uiClassID;// = "InternalFrameUI";
 /*private*/ QCursor lastCursor;

 /*private*/ bool opened;

 /*private*/ QRect normalBounds;// = null;

 /*private*/ int defaultCloseOperation;// = DISPOSE_ON_CLOSE;
 /*private*/ static /*final*/ QString  PROPERTY_CHANGE_LISTENER_KEY;// =

 /*private*/ static void addPropertyChangeListenerIfNecessary();

 /**
  * Contains the Component that focus is to go when
  * <code>restoreSubcomponentFocus</code> is invoked, that is,
  * <code>restoreSubcomponentFocus</code> sets this to the value returned
  * from <code>getMostRecentFocusOwner</code>.
  */
 /*private*/ QWidget* lastFocusOwner;
 void common(QString title, bool resizable, bool closable,
 bool maximizable, bool iconifiable, QWidget* parent);
 /*private*/ static void updateLastFocusOwner(QWidget* component);
 QVBoxLayout* thisLayout;
 void firePropertyChange(QString property, QVariant oldv, QVariant newv);
 QString name;
 bool nameExplicitlySet;
 void closeEvent(QCloseEvent *closeEvent);

private slots:
 void on_windowStateChanged(Qt::WindowStates,Qt::WindowStates);

protected:
 /**
  * The <code>JRootPane</code> instance that manages the
  * content pane
  * and optional menu bar for this internal frame, as well as the
  * glass pane.
  *
  * @see JRootPane
  * @see RootPaneContainer
  */
 /*protected*/ JRootPane* rootPane;
 /**
  * If true then calls to <code>add</code> and <code>setLayout</code>
  * will be forwarded to the <code>contentPane</code>. This is initially
  * false, but is set to true when the <code>JInternalFrame</code> is
  * constructed.
  *
  * @see #isRootPaneCheckingEnabled
  * @see #setRootPaneCheckingEnabled
  * @see javax.swing.RootPaneContainer
  */
 /*protected*/ bool rootPaneCheckingEnabled;// = false;

 /** The frame can be closed. */
 /*protected*/ bool closable;
 /** The frame has been closed. */
 /*protected*/ bool _isClosed;
 /** The frame can be expanded to the size of the desktop pane. */
 /*protected*/ bool maximizable;
 /**
  * The frame has been expanded to its maximum size.
  * @see #maximizable
  */
 /*protected*/ bool _isMaximum;
 /**
  * The frame can "iconified" (shrunk down and displayed as
  * an icon-image).
  * @see JInternalFrame.JDesktopIcon
  * @see #setIconifiable
  */
 /*protected*/ bool _iconable;
 /**
  * The frame has been iconified.
  * @see #isIcon()
  */
 /*protected*/ bool _isIcon;
 /** The frame's size can be changed. */
 /*protected*/ bool _resizable;
 /** The frame is currently selected. */
 /*protected*/ bool _isSelected;
 /** The icon shown in the top-left corner of this internal frame. */
 /*protected*/ QIcon frameIcon;
 /** The title displayed in this internal frame's title bar. */
 /*protected*/ QString  title;
 /**
  * The icon that is displayed when this internal frame is iconified.
  * @see #iconable
  */
 /*protected*/ JDesktopIcon* desktopIcon;
 /*protected*/ JRootPane* createRootPane();
 /*protected*/ void setRootPane(JRootPane* root);
 /** A list of event listeners for this component. */
 /*protected*/ /*EventListenerList*/QList<EventListener*> listenerList;// = new EventListenerList();
 /*protected*/ void fireInternalFrameEvent(int id);

 friend class FocusPropertyChangeListener;
};
/*private*/ /*static*/ class FocusPropertyChangeListener : public PropertyChangeListener
{
 Q_OBJECT
 JInternalFrame* frame;
public:
 FocusPropertyChangeListener(JInternalFrame* frame) { this->frame = frame;}
 /*public*/ void propertyChange(PropertyChangeEvent* e)
 {
  if (e->getPropertyName() == "permanentFocusOwner")
  {
   frame->updateLastFocusOwner(VPtr<QWidget>::asPtr(e->getNewValue()));
  }
 }
};

#endif // JINTERNALFRAME_H
