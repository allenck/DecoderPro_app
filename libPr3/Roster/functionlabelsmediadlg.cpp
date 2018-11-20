#include "functionlabelsmediadlg.h"
#include "ui_functionlabelsmediadlg.h"
#include "rosterentry.h"
#include "fileutil.h"
#include "Roster/roster.h"
#include "functionlabelspane.h"
#include "rostermedia.h"
#include "rosterframe.h"

FunctionLabelsMediaDlg::FunctionLabelsMediaDlg(RosterEntry* re, QWidget *parent) :
    JmriJFrame(parent),
    ui(new Ui::FunctionLabelsMediaDlg)
{
 ui->setupUi(this);
 log = new Logger("FunctionLabelsMediaDlg");
 this->re = re;
 FunctionLabelsPane* functionLabels = new FunctionLabelsPane(re);
 ui->tabWidget->clear();
 QFrame* labelFrame = new QFrame();
 QVBoxLayout* labelFrameLayout = new QVBoxLayout();
 labelFrame->setLayout(labelFrameLayout);
 labelFrameLayout->addWidget(functionLabels);
 QPushButton* store1 = new QPushButton(tr("Save to Roster"));
 labelFrameLayout->addWidget(store1);
 labelFrameLayout->setAlignment(store1, Qt::AlignHCenter);
 ui->tabWidget->addTab(labelFrame, tr("Function Labels"));
 connect(store1, SIGNAL(clicked()), this, SLOT(on_btnSave_clicked()));

 RosterMediaPane* mediaPane = new RosterMediaPane(re);
 QFrame* mediaFrame = new QFrame();
 QVBoxLayout* mediaFrameLayout = new QVBoxLayout();
 mediaFrame->setLayout(mediaFrameLayout);
 mediaFrameLayout->addWidget(mediaPane);
 QPushButton* store2 = new QPushButton(tr("Save to Roster"));
 mediaFrameLayout->addWidget(store2);
 mediaFrameLayout->setAlignment(store2, Qt::AlignHCenter);
 ui->tabWidget->addTab(mediaFrame, tr("Roster Media"));
 connect(store2, SIGNAL(clicked()), this, SLOT(on_btnSave_clicked()));

// ui->lbl0->setText(re->getFunctionLabel(0));
// ui->chkLock0->setChecked(re->getFunctionLockable(0));
// ui->iconOff0->setPixmap(QIcon(re->getFunctionImage(0)).pixmap(24,24));
// ui->iconOn0->setPixmap(QIcon(re->getFunctionSelectedImage(0)).pixmap(24,24));
// ui->lbl1->setText(re->getFunctionLabel(1));
// ui->chkLock1->setChecked(re->getFunctionLockable(1));

// ui->lbl2->setText(re->getFunctionLabel(2));
// ui->chkLock2->setChecked(re->getFunctionLockable(2));
// ui->lbl3->setText(re->getFunctionLabel(3));
// ui->chkLock3->setChecked(re->getFunctionLockable(3));
// ui->lbl4->setText(re->getFunctionLabel(4));
// ui->chkLock4->setChecked(re->getFunctionLockable(4));
// ui->lbl5->setText(re->getFunctionLabel(5));
// ui->chkLock5->setChecked(re->getFunctionLockable(5));
// ui->lbl6->setText(re->getFunctionLabel(6));
// ui->chkLock6->setChecked(re->getFunctionLockable(6));

// // tab 2
// QImage img(re->getImagePath());
// ui->lblMainImage->setPixmap(QPixmap::fromImage(img).scaledToWidth(ui->lblMainImage->width()));

 setWindowTitle(re->getId());
 addHelpMenu("package.jmri.jmrit.symbolicprog.tabbedframe.PaneProgFrame", true);

}

FunctionLabelsMediaDlg::~FunctionLabelsMediaDlg()
{
    delete ui;
}

void FunctionLabelsMediaDlg::on_btnSave_clicked()
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

 // NOTE: this doesn't save the loco file.
 Roster::writeRoster();
}

