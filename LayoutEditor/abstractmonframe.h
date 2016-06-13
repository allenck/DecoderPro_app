#ifndef ABSTRACTMONFRAME_H
#define ABSTRACTMONFRAME_H
#include "jmrijframe.h"

class QFileDialog;
class DateFormat;
class PrintStream;
class ActionEvent;
class QScrollArea;
class DefaultUserMessagePreferences;
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
    /*public*/ /*synchronized*/ void clearButtonActionPerformed(ActionEvent* e = 0);
    /*public*/ /*synchronized*/ void clearButtonActionPerformed(ActionEvent* e = 0);
    /*public*/ /*synchronized*/ void startLogButtonActionPerformed(ActionEvent* e = 0);
    /*public*/ /*synchronized*/ void stopLogButtonActionPerformed(ActionEvent* e = 0);
    /*public*/ void openFileChooserButtonActionPerformed(ActionEvent*e = 0);
    /*public*/ void enterButtonActionPerformed(ActionEvent* e = 0);
    /*public*/ /*synchronized*/ QString getFrameText();

private:
    QString rawDataCheck;// = this.getClass().getName()+".RawData";
    QString timeStampCheck;// = this.getClass().getName()+".TimeStamp";
    QString alwaysOnTopCheck;// = this.getClass().getName()+".alwaysOnTop";
    QString autoScrollCheck;// = this.getClass().getName()+".AutoScroll";
    DefaultUserMessagePreferences* p;

    // for locking
    AbstractMonFrame* self;

    // to find and remember the log file
    QFileDialog* logFileChooser = new JFileChooser(FileUtil.getUserFilesPath());
    QString newline;// = System.getProperty("line.separator");
    Logger* log;
    /*private*/ void doAutoScroll(/*final*/ JTextArea* ta, /*final*/ bool scroll);
    /*volatile*/ PrintStream* logStream;// = NULL;

    // to get a time string
    DateFormat* df;// = new SimpleDateFormat("HH:mm:ss.SSS");

    QString linesBuffer =  QString();
    static /*private*/ int MAX_LINES;// = 500 ;

protected:
    /*protected*/ /*abstract*/ QString title();    // provide the title for the frame
    /*protected*/ /*abstract*/ virtual void init();
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
    /*protected*/ void addHelpMenu();

};

#endif // ABSTRACTMONFRAME_H
