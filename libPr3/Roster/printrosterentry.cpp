
#include "printrosterentry.h"
#include <QLabel>
#include "programmer.h"
#include "resettablemodel.h"
#include "xmlfile.h"
#include "cvtablemodel.h"
#include "variabletablemodel.h"
#include "rosterentry.h"
#include "decoderindexfile.h"
#include "decoderfile.h"
#include "paneprogpane.h"
#include "jframe.h"
#include <QBoxLayout>
#include <QCheckBox>
#include "functionlabelpane.h"
#include <QList>
#include "flowlayout.h"
#include "rostermediapane.h"
#include "hardcopywriter.h"
#include "imageicon.h"
#include <QImage>
#include "jlabel.h"
#include "instancemanager.h"

//PrintRosterEntry::PrintRosterEntry(QObject *parent) :
//    PaneContainer(parent)
//{
//}
// /*public*/ class PrintRosterEntry implements PaneContainer {



/*public*/ PrintRosterEntry::PrintRosterEntry(RosterEntry* rosterEntry, JmriJFrame* parent, QString filename)
{
 _paneList        = QList<JPanel*>();
 _flPane         = NULL;
 _rMPane         = NULL;
 _parent         = NULL;
 _rosterEntry = rosterEntry;
 _flPane = new FunctionLabelPane(rosterEntry);
 _rMPane = new RosterMediaPane(rosterEntry);
 _parent = parent;
 log = new Logger("PrintRosterEntry");
 JLabel* progStatus   = new JLabel(tr("Idle"));
 Programmer* mProgrammer   = NULL;
 ResetTableModel* resetModel    = new ResetTableModel(progStatus, mProgrammer);

 XmlFile* pf = new XmlFile();
 QDomElement base = QDomElement();
 try
 {
  QDomElement root = pf->rootFromName(filename);
  if(root.isNull())
  {
   log->error("Programmer file name incorrect " + filename);
   return;
  }
  if ( (base = root.firstChildElement("programmer")).isNull())
  {
   log->error("xml file top element is not programmer");
   return;
  }
 }
 catch (Exception e)
 {
  log->error("exception reading programmer file: "+filename, e);
  // provide traceback too
  //e.printStackTrace();
  return;
 }

 CvTableModel* cvModel       = new CvTableModel(progStatus, mProgrammer);
 //IndexedCvTableModel* iCvModel      = new IndexedCvTableModel(progStatus, mProgrammer);

 QStringList nameList = QStringList() << "name" << "Value";
 VariableTableModel* variableModel = new VariableTableModel(progStatus, nameList, cvModel/*, iCvModel*/);

 QString decoderModel = _rosterEntry->getDecoderModel();
 QString decoderFamily = _rosterEntry->getDecoderFamily();

 if (log->isDebugEnabled()) log->debug("selected loco uses decoder "+decoderFamily+" "+decoderModel);
 // locate a decoder like that.
 QList<DecoderFile*> l = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList(NULL, decoderFamily, NULL, NULL, NULL, decoderModel);
 if (log->isDebugEnabled()) log->debug("found "+QString(l.size())+" matches");
 if (l.size() == 0)
 {
  log->debug("Loco uses "+decoderFamily+" "+decoderModel+" decoder, but no such decoder defined");
  // fall back to use just the decoder name, not family
  l = ((DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile"))->matchingDecoderList(NULL, NULL, NULL, NULL, NULL, decoderModel);
  if (log->isDebugEnabled()) log->debug("found "+QString::number(l.size())+" matches without family key");
 }
 DecoderFile* d=NULL;
 if (l.size() > 0)
 {
  d = l.at(0);
 }
 else
 {
  if (decoderModel==(""))
   log->debug("blank decoderModel requested, so nothing loaded");
  else
   log->warn("no matching \""+decoderModel+"\" decoder found for loco, no decoder info loaded");
 }

 if (d==NULL)
  return;
 QDomElement decoderRoot;
 try
 {
  decoderRoot = d->rootFromName(DecoderFile::fileLocation+d->getFileName());

 }
 catch (JDOMException exj)
 {
  log->error("could not parse "+d->getFileName()+": "+exj.getMessage());
  return;
 }
 catch (IOException exj)
 {
  log->error("could not read "+d->getFileName()+": "+exj.getMessage());
  return;
 }

 d->loadVariableModel(decoderRoot.firstChildElement("decoder"), variableModel);

 d->loadResetModel(decoderRoot.firstChildElement("decoder"), resetModel);

 //@SuppressWarnings("unchecked")
 QDomNodeList rawPaneList = base.elementsByTagName("pane");
 for (int i=0; i<rawPaneList.size(); i++)
 {
  // load each pane
  QString name = rawPaneList.at(i).toElement().attribute("name");
  PaneProgPane* p = new PaneProgPane(this, name, rawPaneList.at(i).toElement(), cvModel, /*iCvModel,*/ variableModel, d->getModelElement(), _rosterEntry);
  _paneList.append(p);
 }
}

/*public*/ BusyGlassPane* PrintRosterEntry::getBusyGlassPane() { return NULL; }

/*public*/ void  PrintRosterEntry::prepGlassPane(QAbstractButton* /*activeButton*/){}

/*public*/ void  PrintRosterEntry::enableButtons(bool /*enable*/){}

/*public*/ void  PrintRosterEntry::paneFinished(){}

/*public*/ bool  PrintRosterEntry::isBusy() { return false; }

/*public*/  PrintRosterEntry::PrintRosterEntry(RosterEntry* rosterEntry, QList<JPanel*> paneList, FunctionLabelPane* flPane,RosterMediaPane* rMPane, JmriJFrame* parent)
{
 _rosterEntry = rosterEntry;
 _paneList = paneList;
 _flPane = flPane;
 _rMPane = rMPane;
 _parent = parent;
 log = new Logger("PrintRosterEntry");

}

/*public*/ void  PrintRosterEntry::doPrintPanes(bool preview)
{
#if 1
 //choosePrintItems();
 HardcopyWriter* w = NULL;
// try
// {
  w = new HardcopyWriter((JFrame*)_parent, _rosterEntry->getId(), 10, .8, .5, .5, .5, preview);
// }
// catch (HardcopyWriter::PrintCanceledException ex)
// {
//  log->debug("Print cancelled");
//  return;
// }
 printInfoSection(w);

 if (_flPane->includeInPrint())
  _flPane->printPane(w);
 for (int i=0; i<_paneList.size(); i++)
 {
  if (log->isDebugEnabled()) log->debug("start printing page "+i);
  PaneProgPane* pane = (PaneProgPane*)_paneList.at(i);
  if (pane->includeInPrint())
   pane->printPane(w);
 }
 w->write(w->getCurrentLineNumber(),0,w->getCurrentLineNumber(),w->getCharactersPerLine() + 1);
 w->close();
#endif
}

/*public*/ void  PrintRosterEntry::printPanes(/*final*/ bool preview)
{
 this->preview = preview;
 /*final*/ frame = new JFrame("Select Items to Print");
 QWidget* centralWidget = new QWidget;
 frame->setCentralWidget(centralWidget);
 QVBoxLayout* frameLayout = new QVBoxLayout;
 centralWidget->setLayout(frameLayout);
 QWidget* p1 = new QWidget();
 QVBoxLayout* p1Layout;
 p1->setLayout(p1Layout = new QVBoxLayout);//(p1, BoxLayout.PAGE_AXIS));
 QLabel* l1 = new QLabel(tr("Select the items that you"));
 p1Layout->addWidget(l1);
 l1 = new QLabel(tr("wish to appear in the printout"));
 p1Layout->addWidget(l1);
 QWidget* select = new QWidget();
  printList =  QHash<QCheckBox*, PaneProgPane*>();
 QVBoxLayout* selectLayout;
 select->setLayout(selectLayout =new QVBoxLayout); //(select, BoxLayout.PAGE_AXIS));
 funct = new QCheckBox("Function List");
// funct.addActionListener(new java.awt.event.ActionListener()
// {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            _flPane.includeInPrint(funct.isSelected());
//        }
//    });
 connect(funct, SIGNAL(clicked(bool)), _flPane, SLOT(includeInPrint(bool)));
 _flPane->includeInPrint(false);
 selectLayout->addWidget(funct);
 for (int i=0; i<_paneList.size(); i++)
 {
  PaneProgPane* pane = (PaneProgPane*) _paneList.at(i);
  pane->includeInPrint(false);
  QCheckBox* item = new QCheckBox(((PaneProgPane*)_paneList.at(i))->getName());
  printList.insert(item, pane);
//  item.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//                pane.includeInPrint(item.isSelected());
//            }
//        });
  connect(item, SIGNAL(toggled(bool)), pane, SLOT(includeInPrint(bool)));
  selectLayout->addWidget(item);
 }
 QCheckBox* selectAll = new QCheckBox("Select All");
//    selectAll.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//            _flPane.includeInPrint(selectAll.isSelected());
//            funct.setSelected(selectAll.isSelected());
//            Enumeration<QCheckBox> en = printList.keys();
//            while (en.hasMoreElements()) {
//                QCheckBox check = en.nextElement();
//                printList.get(check).includeInPrint(selectAll.isSelected());
//                check.setSelected(selectAll.isSelected());
//            }
//        }
//    });
 connect(selectAll, SIGNAL(toggled(bool)),this, SLOT(On_selectAll_toggled(bool)));
 selectLayout->addWidget(selectAll);
 QPushButton* cancel = new QPushButton("Cancel");
 QPushButton* ok = new QPushButton("Okay");

//    cancel.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//                frame.dispose();
//            }
//        });
 connect(cancel, SIGNAL(clicked()), frame, SLOT(close()));
//    ok.addActionListener(new java.awt.event.ActionListener() {
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent evt) {
//                doPrintPanes(preview);
//                frame.dispose();
//            }
//        });
 connect(ok, SIGNAL(clicked()), this, SLOT(On_ok_clicked()));
 QWidget* buttons = new QWidget();
 FlowLayout* buttonsLayout = new FlowLayout;
 buttons->setLayout(buttonsLayout);
 buttonsLayout->addWidget(cancel);
 buttonsLayout->addWidget(ok);
 p1Layout->addWidget(select);
 p1Layout->addWidget(buttons);

 frameLayout->addWidget(p1);
 frame->pack();
 frame->setVisible(true);

}
void PrintRosterEntry::On_ok_clicked()
{
 doPrintPanes(preview);
 frame->dispose();
}

/*public*/ void PrintRosterEntry::printInfoSection(HardcopyWriter* w)
{
 ImageIcon* icon = new ImageIcon(/*ClassLoader.getSystemResource(*/ ":/resources/decoderpro.gif", ":/resources/decoderpro.gif");
 // we use an ImageIcon because it's guaranteed to have been loaded when ctor is complete
#if 1
 w->write(icon->getImage(), new JLabel());
 w->setFontWeight(QFont::Bold);
 //Add a number of blank lines
 int height = icon->getImage().height();
 int blanks = (height - w->getLineAscent())/w->getLineHeight();
 try
 {
  for(int i = 0; i<blanks; i++)
  {
   QString s = "\n";
   w->write(s,0,s.length());
  }
 }
 catch (IOException e)
 {
  log->warn("error during printing: "+e.getMessage());
 }
 _rosterEntry->printEntry(w);
 w->setFontWeight(QFont::Normal);
#endif
}
void PrintRosterEntry::On_selectAll_toggled(bool b)
{
 _flPane->includeInPrint(b);
 funct->setChecked(b);
 QListIterator<QCheckBox*> en(printList.keys());
 while (en.hasNext())
 {
  QCheckBox* check = en.next();
  printList.value(check)->includeInPrint(b);
  check->setChecked(b);
 }
}
