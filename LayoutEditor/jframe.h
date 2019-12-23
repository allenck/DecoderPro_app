#ifndef JFRAME_H
#define JFRAME_H

#include <QMainWindow>
#include "logger.h"
#include "javaqt_global.h"
#include "jcomponent.h"

class WindowListener;
class PropertyChangeEvent;
class JAVAQTSHARED_EXPORT JFrame : public QMainWindow, public JComponent
{
 Q_OBJECT
 Q_INTERFACES(JComponent)
public:
 enum ACTIONS
 {
    DO_NOTHING_ON_CLOSE = 0,

    /**
     * The hide-window default window close operation
     */
    HIDE_ON_CLOSE = 1,

    /**
     * The dispose-window default window close operation.
     * <p>
     * <b>Note</b>: When the last displayable window
     * within the Java virtual machine (VM) is disposed of, the VM may
     * terminate.  See <a href="../../java/awt/doc-files/AWTThreadIssues.html">
     * AWT Threading Issues</a> for more information.
     * @see java.awt.Window#dispose()
     * @see JInternalFrame#dispose()
     */
    DISPOSE_ON_CLOSE = 2,

    /**
     * The exit application default window close operation. Attempting
     * to set this on Windows that support this, such as
     * <code>JFrame</code>, may throw a <code>SecurityException</code> based
     * on the <code>SecurityManager</code>.
     * It is recommended you only use this in an application.
     *
     * @since 1.4
     * @see JFrame#setDefaultCloseOperation
     */
    EXIT_ON_CLOSE = 3
 };
 Q_ENUM(ACTIONS)
    //virtual /*public*/ void windowClosing(QCloseEvent* e);

    explicit JFrame(QWidget *parent = nullptr);
    JFrame(QString _title, QWidget *parent = nullptr);
    ~JFrame();
    JFrame(const JFrame& ) : QMainWindow() {}
    /*public*/ QSize getPreferredSize();
    /*public*/ QSize getMaximumSize();
    QPoint getLocation();
    void setLocation(int x, int y);
    virtual void dispose();
    virtual QWidget* getContentPane(bool addLayout = true);
    void toFront();
    virtual /*public*/ void setTitle(QString _title);
    /*public*/ QString title();
    /*public*/ void setDefaultCloseOperation(int operation);
    QPoint getLocationOnScreen();
    void setLocation(QPoint p);
    virtual QString getTitle();
    /*public*/ QWidget* getTopLevelAncestor();
    void setMenuBar(QMenuBar *menubar);
    void addWindowListener(WindowListener* l);
    /*public*/ /*synchronized*/ void removeWindowListener(WindowListener* l);
    QVector<WindowListener*> getWindowListeners();
    bool isOpaque();
    QColor getBackground();
    void setBackground(QColor);
    void setOpaque(bool);
    QFont getFont();
    void setFont(QFont);
    QObject* jself() {return (QObject*)this;}

    void setAlwaysOnTop(bool checked);
#if QT_VERSION >= 0x050000
    void virtual languageChange() {}
#endif
    void reSizeToFitOnScreen();
    /*public*/ virtual void pack();
    void setVisible(bool visible);


signals:
    void propertyChange(PropertyChangeEvent*);

public slots:
    /*public*/ int getDefaultCloseOperation();

private:
 Logger* log;
 QString _title;
 int defaultCloseOperation;
 void closeEvent(QCloseEvent *);
 //void resizeEvent(QResizeEvent *);
 void hideEvent(QHideEvent *);
 //void moveEvent(QMoveEvent*);
 /*public*/ virtual void componentMoved(QMoveEvent* ) {}
 /*public*/ virtual void componentResized(QResizeEvent* ) {}


protected:
    /*protected*/ void frameInit();
 QList<WindowListener*>* listeners;// = new QList<WindowListener*>*();
 //virtual void handleModified() {}
// /*protected*/ bool reuseFrameSavedPosition;// = true;
// /*protected*/ bool reuseFrameSavedSized;// = true;
 friend class ControlPanelEditorXml;
};
Q_DECLARE_METATYPE(JFrame)
#endif // JFRAME_H
