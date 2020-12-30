#ifndef LOADERPANE_H
#define LOADERPANE_H
#include "lnpanel.h"
#include "logger.h"
#include "runnable.h"
#include "memorycontents.h"
#include "libPr3_global.h"

class JFileChooser;
class FlowLayout;
class JActionEvent;
class QFileDialog;
class QLabel;
class JTextField;
class MemoryContents;
class QRadioButton;
class QProgressBar;
class QButtonGroup;
class QPushButton;
class LIBPR3SHARED_EXPORT LoaderPane : public LnPanel
{
 Q_OBJECT
public:
 Q_INVOKABLE explicit LoaderPane(QWidget *parent = 0);
 ~LoaderPane() {}
 LoaderPane(const LoaderPane&) : LnPanel() {}
 static int PXCT2SETUP;// = 0x00;
 static int PXCT2SENDADDRESS;// = 0x10;
 static int PXCT2SENDDATA;// = 0x20;
 static int PXCT2VERIFYDATA;// = 0x30;
 static int PXCT2ENDOPERATION;// = 0x40;
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();
 /*public*/ void initComponents(LocoNetSystemConnectionMemo* memo);
 /*public*/ bool parametersAreValid();
 enum SOFTWAREVERSIONS
 {
  DO_NOT_CHECK_SOFTWARE_VERSION = 0x00,
  CHECK_SOFTWARE_VERSION_LESS = 0x04
 };
 enum HARWAREVERSIONS
 {
  DO_NOT_CHECK_HARDWARE_VERSION = 0x00,
  REQUIRE_HARDWARE_VERSION_EXACT_MATCH = 0x01,
  ACCEPT_LATER_HARDWARE_VERSIONS = 0x03,

  SW_FLAGS_MSK = 0x04,
  HW_FLAGS_MSK = 0x03

 };

signals:

public slots:
 void on_selectButton_clicked();
 void on_bootload_focusLost();
 /*public*/ void on_mfg_focusLost();
 /*public*/ void on_developer_focusLost();
 /*public*/ void on_product_focusLost();
 /*public*/ void on_hardware_focusLost();
 /*public*/ void on_software_focusLost();
 /*public*/ void on_delay_focusLost();
 void on_memoryContentsException(MemoryContentsException, QString);

private:
 QLabel* inputFileName;// = new QLabel("");

 JTextField* bootload;// = new JTextField();
 JTextField* mfg;// = new JTextField();

 JTextField* developer;// = new JTextField();
 JTextField* product;// = new JTextField();
 JTextField* hardware;// = new JTextField();
 JTextField* software;// = new JTextField();
 JTextField* delay;// = new JTextField();
 JTextField* eestart;// = new JTextField();

 QRadioButton* checkhardwareno;// = new QRadioButton(tr("ButtonCheckHardwareNo"));
 QRadioButton* checkhardwareexact;// = new QRadioButton(tr("ButtonCheckHardwareExact"));
 QRadioButton* checkhardwaregreater;// = new QRadioButton(tr("ButtonCheckHardwareGreater"));
 QButtonGroup* hardgroup;// = new QButtonGroup();

 QRadioButton* checksoftwareno;// = new QRadioButton(tr("ButtonCheckSoftwareNo"));
 QRadioButton* checksoftwareless;// = new QRadioButton(tr("ButtonCheckSoftwareLess"));
 QButtonGroup* softgroup;// = new QButtonGroup();

 QPushButton* loadButton;
 QPushButton* verifyButton;
 QPushButton* abortButton;

 QRadioButton* address24bit;// = new QRadioButton(tr("Button24bit"));
 QRadioButton* address16bit;// = new QRadioButton(tr("Button16bit"));
 QButtonGroup* addressSizeButtonGroup;// = new QButtonGroup();

 QProgressBar* bar;
 QLabel* status;// = new QLabel("");
 //QWidget* inputFileNamePanel;
 FlowLayout* inputFileNamePanelLayout;


 MemoryContents* inputContent;// = new MemoryContents();
 /*private*/ int inputFileLabelWidth;
 /*private*/ static /*final*/ int PXCT1DOWNLOAD;// = 0x40;


 // some constant string declarations
 /*private*/ static /*final*/ QString MIN_VALUE_ZERO;// = "0";
 /*private*/ static /*final*/ QString MIN_EESTART_VALUE;// = "8";
 /*private*/ static /*final*/ QString MAX_VALUE_255;// = "255";
 /*private*/ static /*final*/ QString MAX_VALUE_65535;// = "65535";
 /*private*/ static /*final*/ QString MAX_EESTART_VALUE;// = "FFFFF8";
 /*private*/ static /*final*/ QString MIN_DELAY_VALUE;// = "5";
 /*private*/ static /*final*/ QString MAX_DELAY_VALUE;// = "500";
 JFileChooser* chooser;
 Logger* log;
 /*private*/ void doRead();
 /*private*/ void setOptionsRadiobuttons(QString text);  //throws NumberFormatException
 void enableDownloadVerifyButtons();
 /*private*/ void disableDownloadVerifyButtons();
 // boolean used to abort the threaded operation
 // access has to be synchronized to make sure
 // the Sender threads sees the value change from the
 // GUI thread
 /*private*/ bool abortOperation;
 /*private*/ bool isOperationAborted();
 /*private*/ int operation;
 /*private*/ void sendSequence();
 void sendOne(int pxct2, int d1, int d2, int d3, int d4,
              int d5, int d6, int d7, int d8);
 int startaddr;
 int endaddr;
 int delayval;
 int eestartval;
 /*private*/ void setDefaultFieldValues();
 /*private*/ bool intParameterIsValid(JTextField* jtf, int minOk, int maxOk);
 /*private*/ int computeOptionsValFromRadiobuttons();

private slots:
 /*private*/ void selectInputFile();
 /*public*/ void actionPerformed(JActionEvent* e = 0);
 /*private*/ void updateDownloadVerifyButtons();
 void doLoad();
 void doVerify();
 /*private*/ void setOperationAborted(bool state = true);
 void on_updateGui(int);
 void on_enableGui();

 friend class Sender;
};
/*private*/ class Sender : public  Runnable
{
 Q_OBJECT
    int totalmsgs;
    int sentmsgs;
    LoaderPane* self;
 public:
    Sender(LoaderPane* self);
    // send the next data, and a termination record when done
    //@Override
    /*public*/ void run();

    /**
     * Send a command to resume at another address
     */
    void setAddr(int location);

    /**
     * Wait the specified time.
     *
     * 16*10/16.44 = 14 msec is the time it takes to send the message.
     */
    void doWait(int address);
    /**
     * Signal GUI that it's the end of the download
     * <P>
     * Should be invoked on the Swing thread
     */
    void enableGUI() ;

    /**
     * Update the GUI for progress
     */
    void updateGUI(/*final*/ int value);
signals:
    void setEnableGui();
    void setUpdateGui(int);
};
Q_DECLARE_METATYPE(LoaderPane)
#endif // LOADERPANE_H
