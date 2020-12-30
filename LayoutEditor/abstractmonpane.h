#ifndef ABSTRACTMONPANE_H
#define ABSTRACTMONPANE_H
#include "jmripanel.h"
#include "logger.h"
#include "runnable.h"
#include "liblayouteditor_global.h"
//#include "jmrijframe.h"

class Message;
class QFile;
class JLabel;
class QFileDialog;
class QTextStream;
class JActionEvent;
class QScrollArea;
class UserPreferencesManager;
class JTextField;
class QCheckBox;
class JTextArea;
class JToggleButton;
class QPushButton;
class LIBLAYOUTEDITORSHARED_EXPORT AbstractMonPane : public JmriPanel
{
    Q_OBJECT
public:
    explicit AbstractMonPane(QWidget *parent = nullptr);
 ~AbstractMonPane();
 AbstractMonPane(const AbstractMonPane&) : JmriPanel() {}//JmriPanel() {}
    /*public*/ void dispose();
    /*public*/ void initComponents() throw (Exception);
    /*public*/ void nextLine(QString line, QString raw);
    /*public*/ void setFixedWidthFont();
    /*public*/ QString getHelpTarget();
    /*public*/ virtual QString getClassName();
 /*public*/ void logMessage(Message* message);
 /*public*/ void logMessage(QString messagePrefix,Message* message);
 /*public*/ void logMessage(QString messagePrefix, QString rawPrefix, Message *message);

signals:

public slots:
    /*public*/ /*synchronized*/ void clearButtonActionPerformed(JActionEvent* e = nullptr);
    /*public*/ /*synchronized*/ void startLogButtonActionPerformed(JActionEvent* e = nullptr);
    /*public*/ /*synchronized*/ void stopLogButtonActionPerformed(JActionEvent* e = nullptr);
    /*public*/ void openFileChooserButtonActionPerformed(JActionEvent*e = nullptr);
    /*public*/ void enterButtonActionPerformed(JActionEvent* e = nullptr);
    /*public*/ /*synchronized*/ QString getFrameText();
    void OnAutoScrollCheckBox(bool);
    void OnAlwaysOnTopCheckBox(bool);
    void OnRawCheckBox(bool);
    void OnTimestampCheck(bool);

private:
    QString rawDataCheck;// = this.getClass().getName()+".RawData";
    QString timeStampCheck;// = this.getClass().getName()+".TimeStamp";
    QString alwaysOnTopCheck;// = this.getClass().getName()+".alwaysOnTop";
    QString autoScrollCheck;// = this.getClass().getName()+".AutoScroll";
    QString filterFieldCheck;// = this.getClass().getName()+".FilterField";
    UserPreferencesManager* p;

    // for locking
    AbstractMonPane* self;

    // to find and remember the log file
    QFileDialog* logFileChooser;// = new JFileChooser(FileUtil.getUserFilesPath());
    QFile* data;
    QString newline;// = System.getProperty("line.separator");
    Logger* log;
//    /*private*/ void doAutoScroll(/*final*/ JTextArea* ta, /*final*/ bool scroll);
    /*volatile*/ QTextStream* logStream;// = NULL;

    // to get a time string
    QString df;// = new SimpleDateFormat("HH:mm:ss.SSS");

    QString linesBuffer;// =  QString();
    static /*private*/ int MAX_LINES;// = 500 ;
    bool isMultipleInstances() { return false;}

protected:
    /*protected*/ /*abstract*/ virtual QString getTitle() {return "";}    // provide the title for the frame
    /*protected*/ /*abstract*/ virtual void init() {}
    // member declarations
    /*protected*/ QPushButton*clearButton;// = new JButton();
    /*protected*/ JToggleButton* freezeButton;// = new JToggleButton();
//    /*protected*/ QScrollArea* jScrollPane1;// = new JScrollPane();
    /*protected*/ JTextArea* monTextPane;// = new JTextArea();
    /*protected*/ QPushButton* startLogButton;// = new JButton();
    /*protected*/ QPushButton*stopLogButton;// = new JButton();
    /*protected*/ QCheckBox* rawCheckBox;// = new JCheckBox();
    /*protected*/ QCheckBox* timeCheckBox;// = new JCheckBox();
    /*protected*/ QCheckBox* alwaysOnTopCheckBox;// = new JCheckBox();
    /*protected*/ QCheckBox* autoScrollCheckBox;// = new JCheckBox();
    /*protected*/ JTextField* filterField;// = new JTextField();
    /*protected*/ JLabel* filterLabel;// = new JLabel("Filter Bytes:", JLabel.LEFT);
    /*protected*/ QPushButton* openFileChooserButton;// = new JButton();
    /*protected*/ JTextField* entryField;// = new JTextField();
    /*protected*/ QPushButton* enterButton;// = new JButton();
    /*protected*/ void addHelpMenu();
 friend class AMPRunnable;
};
#if 0
class AMPRunnable : public Runnable
{
    Q_OBJECT
    AbstractMonPane* pane;
public:
    AMPRunnable(AbstractMonPane* pane);
    /*public*/ void run();
};
#endif
#endif // ABSTRACTMONPANE_H
