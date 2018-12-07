#include "functionlabelspane.h"
#include "ui_functionlabelspane.h"
#include "roster.h"
#include "rosterentry.h"
#include "fileutil.h"
#include "hardcopywriter.h"
#include <QFileDialog>
#include "namedicon.h"
#include "fileutil.h"

FunctionLabelsPane::FunctionLabelsPane(RosterEntry* re, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FunctionLabelsPane)
{
    ui->setupUi(this);
    print = false;
    maxfunction = 28;
    log = new Logger("FunctionLabelsPane");

    this->re = re;
    ui->lbl0->setText(re->getFunctionLabel(0));
    ui->chkLock0->setChecked(re->getFunctionLockable(0));
    //ui->iconOff0->setPixmap(QIcon(re->getFunctionImage(0)).pixmap(32, 32));
    ui->iconOff0->setIconFn(re->getFunctionImage(0),QSize(32, 32));
    connect(ui->iconOff0, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff0_changed(QString)));
    connect(ui->iconOff0, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->iconOn0->setIconFn(re->getFunctionSelectedImage(0),QSize(32, 32));
    connect(ui->iconOn0, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn0_changed(QString)));
    connect(ui->iconOn0, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl1->setText(re->getFunctionLabel(1));
    ui->chkLock1->setChecked(re->getFunctionLockable(1));
    ui->iconOff1->setIconFn(re->getFunctionImage(1),QSize(32, 32));
    connect(ui->iconOff1, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff1_changed(QString)));
    connect(ui->iconOff1, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->iconOn1->setIconFn(re->getFunctionSelectedImage(1),QSize(32, 32));
    connect(ui->iconOn1, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn1_changed(QString)));
    connect(ui->iconOn1, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl2->setText(re->getFunctionLabel(2));
    ui->chkLock2->setChecked(re->getFunctionLockable(2));
    ui->iconOff2->setIconFn(re->getFunctionImage(2),QSize(32, 32));
    connect(ui->iconOff2, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff2_changed(QString)));
    connect(ui->iconOff2, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff2_changed(QString)));
    ui->iconOn2->setIconFn(re->getFunctionSelectedImage(2),QSize(32, 32));
    connect(ui->iconOn2, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn2_changed(QString)));
    connect(ui->iconOn2, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl3->setText(re->getFunctionLabel(3));
    ui->chkLock3->setChecked(re->getFunctionLockable(3));
    ui->iconOff3->setIconFn(re->getFunctionImage(3),QSize(32, 32));
    connect(ui->iconOff3, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff3_changed(QString)));
    connect(ui->iconOff3, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff3_changed(QString)));
    ui->iconOn3->setIconFn(re->getFunctionSelectedImage(3),QSize(32, 32));
    connect(ui->iconOn3, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn3_changed(QString)));
    connect(ui->iconOn3, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl4->setText(re->getFunctionLabel(4));
    ui->chkLock4->setChecked(re->getFunctionLockable(4));
    ui->iconOff4->setIconFn(re->getFunctionImage(4),QSize(32, 32));
    connect(ui->iconOff4, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff4_changed(QString)));
    connect(ui->iconOff4, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff4_changed(QString)));
    ui->iconOn4->setIconFn(re->getFunctionSelectedImage(4),QSize(32, 32));
    connect(ui->iconOn4, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn4_changed(QString)));
    connect(ui->iconOn4, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl5->setText(re->getFunctionLabel(5));
    ui->chkLock5->setChecked(re->getFunctionLockable(5));
    ui->iconOff5->setIconFn(re->getFunctionImage(5),QSize(32, 32));
    connect(ui->iconOff5, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff5_changed(QString)));
    connect(ui->iconOff5, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff5_changed(QString)));
    ui->iconOn5->setIconFn(re->getFunctionSelectedImage(5),QSize(32, 32));
    connect(ui->iconOn5, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn5_changed(QString)));
    connect(ui->iconOn5, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl6->setText(re->getFunctionLabel(6));
    ui->chkLock6->setChecked(re->getFunctionLockable(6));
    ui->iconOff6->setIconFn(re->getFunctionImage(6),QSize(32, 32));
    connect(ui->iconOff6, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff6_changed(QString)));
    connect(ui->iconOff6, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff6_changed(QString)));
    ui->iconOn6->setIconFn(re->getFunctionSelectedImage(6),QSize(32, 32));
    connect(ui->iconOn6, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn6_changed(QString)));
    connect(ui->iconOn6, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl7->setText(re->getFunctionLabel(7));
    ui->chkLock7->setChecked(re->getFunctionLockable(7));
    ui->iconOff7->setIconFn(re->getFunctionImage(7),QSize(32, 32));
    connect(ui->iconOff7, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff7_changed(QString)));
    connect(ui->iconOff7, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff7_changed(QString)));
    ui->iconOn7->setIconFn(re->getFunctionSelectedImage(7),QSize(32, 32));
    connect(ui->iconOn7, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn7_changed(QString)));
    connect(ui->iconOn7, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl8->setText(re->getFunctionLabel(8));
    ui->chkLock8->setChecked(re->getFunctionLockable(8));
    ui->iconOff8->setIconFn(re->getFunctionImage(8),QSize(32, 32));
    connect(ui->iconOff8, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff8_changed(QString)));
    connect(ui->iconOff8, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff8_changed(QString)));
    ui->iconOn8->setIconFn(re->getFunctionSelectedImage(7),QSize(32, 32));
    connect(ui->iconOn8, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn8_changed(QString)));
    connect(ui->iconOn8, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl9->setText(re->getFunctionLabel(9));
    ui->chkLock9->setChecked(re->getFunctionLockable(9));
    ui->iconOff9->setIconFn(re->getFunctionImage(9),QSize(32, 32));
    connect(ui->iconOff9, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff9_changed(QString)));
    connect(ui->iconOff9, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff9_changed(QString)));
    ui->iconOn9->setIconFn(re->getFunctionSelectedImage(9),QSize(32, 32));
    connect(ui->iconOn9, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn9_changed(QString)));
    connect(ui->iconOn9, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl10->setText(re->getFunctionLabel(10));
    ui->chkLock10->setChecked(re->getFunctionLockable(10));
    ui->iconOff10->setIconFn(re->getFunctionImage(10),QSize(32, 32));
    connect(ui->iconOff10, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff10_changed(QString)));
    connect(ui->iconOff10, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff10_changed(QString)));
    ui->iconOn10->setIconFn(re->getFunctionSelectedImage(10),QSize(32, 32));
    connect(ui->iconOn10, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn10_changed(QString)));
    connect(ui->iconOn10, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl11->setText(re->getFunctionLabel(11));
    ui->chkLock11->setChecked(re->getFunctionLockable(11));
    ui->iconOff11->setIconFn(re->getFunctionImage(11),QSize(32, 32));
    connect(ui->iconOff11, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff11_changed(QString)));
    connect(ui->iconOff11, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff11_changed(QString)));
    ui->iconOn11->setIconFn(re->getFunctionSelectedImage(11),QSize(32, 32));
    connect(ui->iconOn11, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn11_changed(QString)));
    connect(ui->iconOn11, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl12->setText(re->getFunctionLabel(12));
    ui->chkLock12->setChecked(re->getFunctionLockable(12));
    ui->iconOff12->setIconFn(re->getFunctionImage(12),QSize(32, 32));
    connect(ui->iconOff12, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff12_changed(QString)));
    connect(ui->iconOff12, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff12_changed(QString)));
    ui->iconOn12->setIconFn(re->getFunctionSelectedImage(12),QSize(32, 32));
    connect(ui->iconOn12, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff12_changed(QString)));
    connect(ui->iconOn12, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl13->setText(re->getFunctionLabel(13));
    ui->chkLock13->setChecked(re->getFunctionLockable(13));
    ui->iconOff13->setIconFn(re->getFunctionImage(13),QSize(32, 32));
    connect(ui->iconOff13, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff13_changed(QString)));
    connect(ui->iconOn13, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->iconOn13->setIconFn(re->getFunctionSelectedImage(13),QSize(32, 32));
    connect(ui->iconOn13, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn13_changed(QString)));
    connect(ui->iconOff13, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff13_changed(QString)));
    ui->lbl14->setText(re->getFunctionLabel(14));
    ui->chkLock14->setChecked(re->getFunctionLockable(14));
    ui->iconOff14->setIconFn(re->getFunctionImage(14),QSize(32, 32));
    connect(ui->iconOff14, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff14_changed(QString)));
    connect(ui->iconOff14, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff14_changed(QString)));
    ui->iconOn14->setIconFn(re->getFunctionSelectedImage(14),QSize(32, 32));
    connect(ui->iconOn14, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn14_changed(QString)));
    connect(ui->iconOn14, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl15->setText(re->getFunctionLabel(15));
    ui->chkLock15->setChecked(re->getFunctionLockable(15));
    ui->iconOff15->setIconFn(re->getFunctionImage(15),QSize(32, 32));
    connect(ui->iconOff15, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff15_changed(QString)));
    connect(ui->iconOff15, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff15_changed(QString)));
    ui->iconOn15->setIconFn(re->getFunctionSelectedImage(15),QSize(32, 32));
    connect(ui->iconOn15, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn15_changed(QString)));
    connect(ui->iconOn15, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));
    ui->lbl16->setText(re->getFunctionLabel(16));
    ui->chkLock16->setChecked(re->getFunctionLockable(16));
    ui->iconOff16->setIconFn(re->getFunctionImage(16),QSize(32, 32));
    connect(ui->iconOff16, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff16_changed(QString)));
    connect(ui->iconOff16, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOff16_changed(QString)));
    ui->iconOn16->setIconFn(re->getFunctionSelectedImage(16),QSize(32, 32));
    connect(ui->iconOn16, SIGNAL(fileNameChanged(QString)), this, SLOT(OnIconOn16_changed(QString)));
    connect(ui->iconOn16, SIGNAL(rightClick(DropJLabel*)), this, SLOT(onRightClick(DropJLabel*)));

    ui->lbl0->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl1->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl2->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl3->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl4->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl5->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl6->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl7->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl8->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl9->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl10->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl11->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl12->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl13->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl14->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl15->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl16->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl17->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl18->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl19->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl20->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl21->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl22->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl23->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl24->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl25->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl26->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl27->setStyleSheet("QLineEdit{border: 1px solid blue}");
    ui->lbl28->setStyleSheet("QLineEdit{border: 1px solid blue}");


    QVector<QRadioButton*> shunterMode = QVector<QRadioButton*>() << ui->radioButton_0 << ui->radioButton_1 << ui->radioButton_2 << ui->radioButton_3 << ui->radioButton_4 << ui->radioButton_5 << ui->radioButton_6 << ui->radioButton_7 << ui->radioButton_8 << ui->radioButton_9 << ui->radioButton_10 << ui->radioButton_11 << ui->radioButton_12 << ui->radioButton_13 << ui->radioButton_14 << ui->radioButton_15 << ui->radioButton_16 << ui->radioButton_17 << ui->radioButton_18 << ui->radioButton_19 << ui->radioButton_20 << ui->radioButton_21 << ui->radioButton_22 << ui->radioButton_23 << ui->radioButton_24 << ui->radioButton_25 << ui->radioButton_26 << ui->radioButton_27 << ui->radioButton_28;

    shunterModeMapper = new QSignalMapper(this);
    for(int i=0; i <= 28; i++)
    {
     QRadioButton* rb = shunterMode.at(i);
     shunterModeMapper->setMapping(rb,i);
     connect(rb, SIGNAL(clicked()), shunterModeMapper, SLOT(map()));
    }
    connect(shunterModeMapper, SIGNAL(mapped(int)), this, SLOT(on_shunterRbClicked(int)));
    QString fn = re->getShuntingFunction();
    bool bOk;
    if(!fn.isEmpty() && fn.at(0)== 'F')
    {
     int f = fn.mid(1).toInt(&bOk);
     if(bOk)
      shunterMode.at(f)->setChecked(true);
    }

    setWindowTitle(re->getId());
}

FunctionLabelsPane::~FunctionLabelsPane()
{
    delete ui;
}
void FunctionLabelsPane::on_lbl0_editingFinished()
{
 QString text = ui->lbl0->text();
 re->setFunctionLabel(0,text);
}
void FunctionLabelsPane::on_lbl1_editingFinished()
{
 QString text = ui->lbl1->text();
 re->setFunctionLabel(1,text);
}
void FunctionLabelsPane::on_lbl2_editingFinished()
{
 QString text = ui->lbl2->text();
 re->setFunctionLabel(2,text);
}
void FunctionLabelsPane::on_lbl3_editingFinished()
{
 QString text = ui->lbl3->text();
 re->setFunctionLabel(3,text);
}
void FunctionLabelsPane::on_lbl4_editingFinished()
{
 QString text = ui->lbl4->text();
 re->setFunctionLabel(4,text);
}
void FunctionLabelsPane::on_lbl5_editingFinished()
{
 QString text = ui->lbl5->text();
 re->setFunctionLabel(5,text);
}
void FunctionLabelsPane::on_lbl6_editingFinished()
{
 QString text = ui->lbl6->text();
 re->setFunctionLabel(6,text);
}
void FunctionLabelsPane::on_lbl7_editingFinished()
{
 QString text = ui->lbl7->text();
 re->setFunctionLabel(7,text);
}
void FunctionLabelsPane::on_lbl8_editingFinished()
{
 QString text = ui->lbl8->text();
 re->setFunctionLabel(8,text);
}
void FunctionLabelsPane::on_lbl9_editingFinished()
{
 QString text = ui->lbl9->text();
 re->setFunctionLabel(9,text);
}
void FunctionLabelsPane::on_lbl10_editingFinished()
{
 QString text = ui->lbl10->text();
 re->setFunctionLabel(10,text);
}
void FunctionLabelsPane::on_lbl11_editingFinished()
{
 QString text = ui->lbl11->text();
 re->setFunctionLabel(11,text);
}
void FunctionLabelsPane::on_lbl12_editingFinished()
{
 QString text = ui->lbl12->text();
 re->setFunctionLabel(12,text);
}
void FunctionLabelsPane::on_lbl13_editingFinished()
{
 QString text = ui->lbl13->text();
 re->setFunctionLabel(13,text);
}
void FunctionLabelsPane::on_lbl14_editingFinished()
{
 QString text = ui->lbl14->text();
 re->setFunctionLabel(14,text);
}
void FunctionLabelsPane::on_lbl15_editingFinished()
{
 QString text = ui->lbl15->text();
 re->setFunctionLabel(15,text);
}
void FunctionLabelsPane::on_lbl16_editingFinished()
{
 QString text = ui->lbl16->text();
 re->setFunctionLabel(16,text);
}
void FunctionLabelsPane::OnIconOff0_changed(QString s) { re->setFunctionImage(0,s);}
void FunctionLabelsPane::OnIconOff1_changed(QString s) { re->setFunctionImage(1,s);}
void FunctionLabelsPane::OnIconOff2_changed(QString s) { re->setFunctionImage(2,s);}
void FunctionLabelsPane::OnIconOff3_changed(QString s) { re->setFunctionImage(3,s);}
void FunctionLabelsPane::OnIconOff4_changed(QString s) { re->setFunctionImage(4,s);}
void FunctionLabelsPane::OnIconOff5_changed(QString s) { re->setFunctionImage(5,s);}
void FunctionLabelsPane::OnIconOff6_changed(QString s) { re->setFunctionImage(6,s);}
void FunctionLabelsPane::OnIconOff7_changed(QString s) { re->setFunctionImage(7,s);}
void FunctionLabelsPane::OnIconOff8_changed(QString s) { re->setFunctionImage(8,s);}
void FunctionLabelsPane::OnIconOff9_changed(QString s) { re->setFunctionImage(9,s);}
void FunctionLabelsPane::OnIconOff10_changed(QString s) { re->setFunctionImage(10,s);}
void FunctionLabelsPane::OnIconOff11_changed(QString s) { re->setFunctionImage(11,s);}
void FunctionLabelsPane::OnIconOff12_changed(QString s) { re->setFunctionImage(12,s);}
void FunctionLabelsPane::OnIconOff13_changed(QString s) { re->setFunctionImage(13,s);}
void FunctionLabelsPane::OnIconOff14_changed(QString s) { re->setFunctionImage(14,s);}
void FunctionLabelsPane::OnIconOff15_changed(QString s) { re->setFunctionImage(15,s);}
void FunctionLabelsPane::OnIconOff16_changed(QString s) { re->setFunctionImage(16,s);}

void FunctionLabelsPane::OnIconOn0_changed(QString s) { re->setFunctionSelectedImage(0,s);}
void FunctionLabelsPane::OnIconOn1_changed(QString s) { re->setFunctionSelectedImage(1,s);}
void FunctionLabelsPane::OnIconOn2_changed(QString s) { re->setFunctionSelectedImage(2,s);}
void FunctionLabelsPane::OnIconOn3_changed(QString s) { re->setFunctionSelectedImage(3,s);}
void FunctionLabelsPane::OnIconOn4_changed(QString s) { re->setFunctionSelectedImage(4,s);}
void FunctionLabelsPane::OnIconOn5_changed(QString s) { re->setFunctionSelectedImage(5,s);}
void FunctionLabelsPane::OnIconOn6_changed(QString s) { re->setFunctionSelectedImage(6,s);}
void FunctionLabelsPane::OnIconOn7_changed(QString s) { re->setFunctionSelectedImage(7,s);}
void FunctionLabelsPane::OnIconOn8_changed(QString s) { re->setFunctionSelectedImage(8,s);}
void FunctionLabelsPane::OnIconOn9_changed(QString s) { re->setFunctionSelectedImage(9,s);}
void FunctionLabelsPane::OnIconOn10_changed(QString s) { re->setFunctionSelectedImage(10,s);}
void FunctionLabelsPane::OnIconOn11_changed(QString s) { re->setFunctionSelectedImage(11,s);}
void FunctionLabelsPane::OnIconOn12_changed(QString s) { re->setFunctionSelectedImage(12,s);}
void FunctionLabelsPane::OnIconOn13_changed(QString s) { re->setFunctionSelectedImage(13,s);}
void FunctionLabelsPane::OnIconOn14_changed(QString s) { re->setFunctionSelectedImage(14,s);}
void FunctionLabelsPane::OnIconOn15_changed(QString s) { re->setFunctionSelectedImage(15,s);}
void FunctionLabelsPane::OnIconOn16_changed(QString s) { re->setFunctionSelectedImage(16,s);}

void FunctionLabelsPane::on_btnSave_clicked()
{
// QDomDocument doc;
// QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
// doc.appendChild(xmlProcessingInstruction);
// xmlProcessingInstruction = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/xsl\" href=\"/xml/XSLT/locomotive.xsl\"");
// doc.appendChild(xmlProcessingInstruction);
// QDomElement root =  doc.createElement("locomotive-config");
// root.setAttribute("xsi:noNamespaceSchemaLocation", "http://jmri.org/xml/schema/locomotive-config.xsd");
// doc.appendChild(root);
// root.appendChild(re->store(doc));
// QString sXml = doc.toString();

// QFile file(QDir::homePath()+"/.jmri/roster/"+re->getFileName());
// makeBackupFile(file.fileName());
// file.open(QIODevice::WriteOnly);
// QTextStream stream (&file);
// stream.setCodec("UTF-8");
// doc.save(stream,2);
 Roster::getDefault()->writeRoster();
}

/**
 * Move original file to a backup. Use this before writing out a new version
 * of the file.
 *
 * @param name Last part of file pathname i.e. subdir/name, without the
 * pathname for either the xml or preferences directory.
 */
/*public*/ void FunctionLabelsPane::makeBackupFile(QString name)
{
 QFile* file = findFile(name);
 if (file == NULL)
 {
  log->info("No " + name + " file to backup");
 }
 else
 {
  QFileInfo info(file->fileName());

  QString backupName = backupFileName(name);
  QFile* backupFile = findFile(backupName);
  if (backupFile != NULL)
  {
   if (backupFile->remove())
   {
    log->debug("deleted backup file " + backupName);
   }
  }
  if (file->rename(backupName))
  {
   log->debug("created new backup file " + backupName);
  }
  else
  {
   log->error("could not create backup file " + backupName);
  }
 }
}
/**
 * Return a File object for a name. This is here to implement the search
 * rule: <OL> <LI>Look in user preferences directory, located by
 * {@link jmri.util.FileUtil#getUserFilesPath()} <li>Look in current working
 * directory (usually the JMRI distribution directory) <li>Look in program
 * directory, located by {@link jmri.util.FileUtil#getProgramPath()}
 * <LI>Look in XML directory, located by {@link #xmlDir} <LI>Check for
 * absolute name. </OL>
 *
 * @param name Filename perhaps containing subdirectory information (e.g.
 * "decoders/Mine.xml")
 * @return NULL if file found, otherwise the located File
 */
/*protected*/ QFile* FunctionLabelsPane::findFile(QString name)
{
 QFile* fp =  new QFile(FileUtil::getUserFilesPath() + name);
 if (fp->exists())
 {
  return fp;
 }
 fp = new QFile(name);
 if (fp->exists())
 {
  return fp;
 }
 fp = new QFile(FileUtil::getProgramPath() + name);
 if (fp->exists())
 {
  return fp;
 }
 fp = new QFile(FileUtil::getPreferencesPath()+"roster/" + name);
 if (fp->exists())
 {
  return fp;
 }
 return NULL;
}
/**
 * Return the name of a new, unique backup file. This is here so it can be
 * overridden during tests. File to be backed-up must be within the
 * preferences directory tree.
 *
 * @param name Filename without preference path information, e.g.
 * "decoders/Mine.xml".
 * @return Complete filename, including path information into preferences
 * directory
 */
/*public*/ QString FunctionLabelsPane::backupFileName(QString name) {
 QString f = name + ".bak";
 if (log->isDebugEnabled())
 {
  log->debug("backup file name is: " + f);
 }
 return f;
}
/*public*/ bool FunctionLabelsPane::includeInPrint() {
    return print;
}
/*public*/ void FunctionLabelsPane::includeInPrint(bool inc)
{
 print = inc;
}
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*public*/ void FunctionLabelsPane::printPane(HardcopyWriter* w)
{
 // if pane is empty, don't print anything
 //if (varList.size() == 0 && cvList.size() == 0) return;
 // future work needed her to print indexed CVs

 // Define column widths for name and value output.
 // Make col 2 slightly larger than col 1 and reduce both to allow for
 // extra spaces that will be added during concatenation
 int col1Width = w->getCharactersPerLine() / 2 - 3 - 5;
 int col2Width = w->getCharactersPerLine() / 2 - 3 + 5;

 try
 {
  //Create a string of spaces the width of the first column
  QString spaces = "";
  for (int i = 0; i < col1Width; i++)
  {
   spaces = spaces + " ";
  }
  // start with pane name in bold
  QString heading1 = "Function";
  QString heading2 = "Description";
  QString s;
  int interval = spaces.length() - heading1.length();
  w->setFontWeight(QFont::Bold);
  w->setFontStyle(QFont::StyleNormal);
  // write the section name and dividing line
  s = "FUNCTION LABELS";
  w->write(s, 0, s.length());
  w->writeBorders();
  //Draw horizontal dividing line for each Pane section
  w->write(w->getCurrentLineNumber(), 0, w->getCurrentLineNumber(), w->getCharactersPerLine() + 1);
  s = "\n";
  w->write(s, 0, s.length());

  //w.setFontStyle(Font.BOLD + Font.ITALIC);
  w->setFontStyle(QFont::StyleItalic);
  w->setFontWeight(QFont::Bold);
  s = "   " + heading1 + spaces.mid(0, interval) + "   " + heading2;
  w->write(s, 0, s.length());
  w->writeBorders();
  s = "\n";
  w->write(s, 0, s.length());
  w->setFontStyle(QFont::StyleNormal);
  w->setFontWeight(QFont::Normal);
  // index over variables
  for (int i = 0; i <= maxfunction; i++)
  {
   QString name = QString::number(i);
   if (re->getFunctionLockable(i))
   {
    name = name + " (locked)";
   }
   QString value = re->getFunctionLabel(i);
   //Skip Blank functions
   if (value != "")
   {
    //define index values for name and value substrings
    int nameLeftIndex = 0;
    int nameRightIndex = name.length();
    int valueLeftIndex = 0;
    int valueRightIndex = value.length();
    QString trimmedName;
    QString trimmedValue;

    // Check the name length to see if it is wider than the column.
    // If so, split it and do the same checks for the Value
    // Then concatenate the name and value (or the split versions thereof)
    // before writing - if split, repeat until all pieces have been output
    while ((valueLeftIndex < value.length()) || (nameLeftIndex < name.length()))
    {
     // name split code
     if (name.mid(nameLeftIndex).length() > col1Width)
     {
      for (int j = 0; j < col1Width; j++)
      {
       QString delimiter = name.mid(nameLeftIndex + col1Width - j - 1, nameLeftIndex + col1Width - j);
       if (delimiter==(" ") || delimiter==(";") || delimiter==(","))
       {
        nameRightIndex = nameLeftIndex + col1Width - j;
        break;
       }
      }
      trimmedName = name.mid(nameLeftIndex, nameRightIndex);
      nameLeftIndex = nameRightIndex;
      int space = spaces.length() - trimmedName.length();
      s = "   " + trimmedName + spaces.mid(0, space);
     }
     else
     {
      trimmedName = name.mid(nameLeftIndex);
      int space = spaces.length() - trimmedName.length();
      s = "   " + trimmedName + spaces.mid(0, space);
      name = "";
      nameLeftIndex = 0;
     }
     // value split code
     if (value.mid(valueLeftIndex).length() > col2Width)
     {
      for (int j = 0; j < col2Width; j++)
      {
       QString delimiter = value.mid(valueLeftIndex + col2Width - j - 1, valueLeftIndex + col2Width - j);
       if (delimiter==(" ") || delimiter==(";") || delimiter==(","))
       {
        valueRightIndex = valueLeftIndex + col2Width - j;
        break;
       }
      }
      trimmedValue = value.mid(valueLeftIndex, valueRightIndex);
      valueLeftIndex = valueRightIndex;
      s = s + "   " + trimmedValue;
     }
     else
     {
      trimmedValue = value.mid(valueLeftIndex);
      s = s + "   " + trimmedValue;
      valueLeftIndex = 0;
      value = "";
     }
     w->write(s, 0, s.length());
     w->writeBorders();
     s = "\n";
     w->write(s, 0, s.length());
    }
    // handle special cases
   }
  }
  s = "\n";
  w->writeBorders();
  w->write(s, 0, s.length());
  w->writeBorders();
  w->write(s, 0, s.length());
 }
 catch (IOException e)
 {
  log->warn("error during printing: " + e.getMessage());
 }
}
void FunctionLabelsPane::onRightClick(DropJLabel * l)
{
// QString iconPath;
// NamedIcon* icon;
//  icon = l->icon();
// if(icon != NULL)
//  iconPath = icon->getURL();
 QString newPath = QFileDialog::getOpenFileName(this, tr("Select image"),FileUtil::getUserResourcePath(),"Image files (*.png *.jpg *.gif);;All files (*.*)");
 if(newPath != "")
 {
  l->setIconFn(newPath, QSize(32,32));
  emit l->fileNameChanged(newPath);
 }
}

void FunctionLabelsPane::on_shunterRbClicked(int i)
{
 re->setShuntingFunction(QString("F%1").arg(i));
}
