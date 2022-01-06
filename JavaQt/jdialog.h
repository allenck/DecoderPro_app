#ifndef JDIALOG_H
#define JDIALOG_H

#include <QDialog>
#include "logger.h"
#include "javaqt_global.h"

class WindowListener;
class JAVAQTSHARED_EXPORT JDialog : public QDialog
{
    Q_OBJECT
public:
    explicit JDialog(QWidget *parent = 0);
    /*public*/ JDialog(QWidget* owner, bool modal);
    /*public*/ JDialog(QWidget* owner, QString title, bool modal);
    /*public*/ ~JDialog();
    /*public*/ enum ModalityType {
      MODELESS, DOCUMENT_MODAL, APPLICATION_MODAL, TOOLKIT_MODAL};

    static /*public*/ JDialog* findDialog(QString title);
    /**
     * The do-nothing default window close operation.
     */
    /*public*/ static /*final*/ int DO_NOTHING_ON_CLOSE;// = 0;

    /**
     * The hide-window default window close operation
     */
    /*public*/ static /*final*/ int HIDE_ON_CLOSE;// = 1;
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
    /*public*/ static /*final*/ int DISPOSE_ON_CLOSE;// = 2;

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
    /*public*/ static /*final*/ int EXIT_ON_CLOSE;// = 3;
    /*public*/ QWidget* getContentPane();
    /*public*/ void pack();
    void setSize(int w, int h);
    void toFront();
    void setLocation(int x, int y);
    void reSizeToFitOnScreen();
    /*public*/ QSize getPreferredSize();
    /*public*/ QSize getMaximumSize();
    void setTitle(QString t);
    QPoint getLocationOnScreen();
    void setLocation(QPoint p);
    /*public*/ void setDefaultCloseOperation(int operation);
    /*public*/ int getDefaultCloseOperation();
    /*public*/ void windowClosing(QCloseEvent* /*e*/);
    void addWindowListener(WindowListener* l);
    void setLocationRelativeTo(QWidget*) {}
    virtual void dispose();
    /*public*/ void setContentPane(QWidget* pane);

signals:

public slots:
private:
    /**
     * Key into the AppContext, used to check if should provide decorations
     * by default.
     */
    /*private*/ static /*final*/ QString defaultLookAndFeelDecoratedKey;// = QString("JDialog.defaultLookAndFeelDecorated");

    /*private*/ int defaultCloseOperation;// = HIDE_ON_CLOSE;
    Logger * log;
    void closeEvent(QCloseEvent* /*e*/);
    bool modal;
protected:
    /**
     * @see #getRootPane
     * @see #setRootPane
     */
    /*protected*/ /*JRootPane*/QWidget* rootPane;

    /**
     * If true then calls to {@code add} and {@code setLayout}
     * will be forwarded to the {@code contentPane}. This is initially
     * false, but is set to true when the {@code JDialog} is constructed.
     *
     * @see #isRootPaneCheckingEnabled
     * @see #setRootPaneCheckingEnabled
     * @see javax.swing.RootPaneContainer
     */
    /*protected*/ bool rootPaneCheckingEnabled;// = false;
    /*protected*/ void dialogInit();
 QList<WindowListener*>* _listeners;
 virtual void handleModified() {}

 static QList<JDialog*> dialogList;

};

#endif // JDIALOG_H
