#ifndef JFRAME_H
#define JFRAME_H

#include <QMainWindow>
#include "logger.h"
#include "javaqt_global.h"

class WindowListener;
class PropertyChangeEvent;
class JAVAQTSHARED_EXPORT JFrame : public QMainWindow
{
    Q_OBJECT
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
    virtual /*public*/ void windowClosing(QCloseEvent* e);

    explicit JFrame(QWidget *parent = 0);
    JFrame(QString _title, QWidget *parent = 0);
    ~JFrame();
    JFrame(const JFrame& ) : QMainWindow() {}
    /*public*/ QSize getPreferredSize();
    /*public*/ QSize getMaximumSize();
    void setLocation(int x, int y);
    void dispose();
    QWidget* getContentPane();
    void toFront();
    /*public*/ void setTitle(QString _title);
    /*public*/ QString title();
    /*public*/ void setDefaultCloseOperation(int operation);
    QPoint getLocationOnScreen();
    void setLocation(QPoint p);
    virtual QString getTitle();
    /*public*/ QWidget* getTopLevelAncestor();
    void setMenuBar(QMenuBar *menubar);
    void addWindowListener(WindowListener* l);
    void setAlwaysOnTop(bool checked);
#if QT_VERSION >= 0x050000
    void virtual languageChange() {}
#endif
    void reSizeToFitOnScreen();
signals:
    void propertyChange(PropertyChangeEvent*);
public slots:
    /*public*/ void pack();
    /*public*/ int getDefaultCloseOperation();

private:
 Logger* log;
 QString _title;
 int defaultCloseOperation;
 void closeEvent(QCloseEvent *);

protected:
    /*protected*/ void frameInit();
 QList<WindowListener*>* listeners;// = new QList<WindowListener*>*();
 virtual void handleModified() {}

 friend class ControlPanelEditorXml;
};
Q_DECLARE_METATYPE(JFrame)
#endif // JFRAME_H
