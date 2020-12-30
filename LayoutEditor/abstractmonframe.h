#ifndef ABSTRACTMONFRAME_H
#define ABSTRACTMONFRAME_H
#include "jmrijframe.h"
#include "jfilechooser.h"

class DateFormat;
class PrintStream;
class JActionEvent;
class QScrollArea;
//class DefaultUserMessagePreferences;
class JTextField;
class QCheckBox;
class JTextArea;
class JToggleButton;
class QPushButton;
class AbstractMonFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit AbstractMonFrame(QWidget *parent = 0);
    /*public*/ void dispose();
    /*public*/ void initComponents() throw (Exception);
    /*public*/ void nextLine(QString line, QString raw);

signals:

public slots:
    /*public*/ /*synchronized*/ void clearButtonActionPerformed(JActionEvent* e = 0);
    /*public*/ /*synchronized*/ void startLogButtonActionPerformed(JActionEvent* e = 0);
    /*public*/ /*synchronized*/ void stopLogButtonActionPerformed(JActionEvent* e = 0);
    /*public*/ void openFileChooserButtonActionPerformed(JActionEvent*e = 0);
    /*public*/ void enterButtonActionPerformed(JActionEvent* e = 0);
    /*public*/ /*synchronized*/ QString getFrameText();
    void On_alwaysOnTopCheckBox(bool);
    void On_autoScrollCheckBox();

private:
    QString rawDataCheck;// = this.getClass().getName()+".RawData";
    QString timeStampCheck;// = this.getClass().getName()+".TimeStamp";
    QString alwaysOnTopCheck;// = this.getClass().getName()+".alwaysOnTop";
    QString autoScrollCheck;// = this.getClass().getName()+".AutoScroll";
    UserPreferencesManager* p;

    // for locking
    AbstractMonFrame* self;

    // to find and remember the log file
    JFileChooser* logFileChooser;// = new JFileChooser(FileUtil.getUserFilesPath());
    QString newline;// = System.getProperty("line.separator");
    /*private*/ static /*final*/ Logger* log;// = Loggerfactory::getLogger("AbstractMonFrame");

    /*private*/ void doAutoScroll(/*final*/ JTextArea* ta, /*final*/ bool scroll);
    /*volatile*/ PrintStream* logStream;// = NULL;

    // to get a time string
    QString df;// = new SimpleDateFormat("HH:mm:ss.SSS");

    QString linesBuffer =  QString();
    static /*private*/ int MAX_LINES;// = 500 ;

protected:
    /*protected*/ /*abstract*/ virtual QString title() {return "";}   // provide the title for the frame
    /*protected*/ /*abstract*/ virtual void init() {}
    // member declarations
    /*protected*/ QPushButton*clearButton;// = new JButton();
    /*protected*/ JToggleButton* freezeButton;// = new JToggleButton();
    /*protected*/ QScrollArea* jScrollPane1;// = new JScrollPane();
    /*protected*/ JTextArea* monTextPane;// = new JTextArea();
    /*protected*/ QPushButton* startLogButton;// = new JButton();
    /*protected*/ QPushButton*stopLogButton;// = new JButton();
    /*protected*/ QCheckBox* rawCheckBox;// = new JCheckBox();
    /*protected*/ QCheckBox* timeCheckBox;// = new JCheckBox();
    /*protected*/ QCheckBox* alwaysOnTopCheckBox;// = new JCheckBox();
    /*protected*/ QCheckBox* autoScrollCheckBox;// = new JCheckBox();
    /*protected*/ QPushButton* openFileChooserButton;// = new JButton();
    /*protected*/ JTextField* entryField;// = new JTextField();
    /*protected*/ QPushButton* enterButton;// = new JButton();
    virtual /*protected*/ void setHelp();

};

class AMFWorker : public QObject
{
 Q_OBJECT

public:
 AMFWorker();
public slots:
 void process();

signals:
 void finished();

};
#endif // ABSTRACTMONFRAME_H
