#include "signalmastitempanel.h"
#include "signalmast.h"
#include <QVBoxLayout>
#include "itempalette.h"
#include <QTableView>
#include <QGroupBox>
#include "picklistmodel.h"
#include "instancemanager.h"
#include "defaultsignalmastmanager.h"
#include "fileutil.h"
#include "signalmasticon.h"
#include "editor.h"
#include "signalmastmanager.h"
#include "dataflavor.h"
#include "flowlayout.h"
#include "abstractsignalmast.h"
#include "signalmasticonxml.h"

//SignalMastItemPanel::SignalMastItemPanel(QWidget *parent) :
//    TableItemPanel(parent)
//{
//}
///*public*/ class SignalMastItemPanel extends TableItemPanel implements ListSelectionListener {


/*public*/ SignalMastItemPanel::SignalMastItemPanel(DisplayFrame* parentFrame, QString  type, QString family, PickListModel* model, Editor* editor, QWidget *parent) : TableItemPanel(parentFrame, type, family, model, editor,parent)
{
 //super(parentFrame, type, family, model, editor);
 _mast = NULL;

}

void SignalMastItemPanel::init()
{
 TableItemPanel::init();
 //_table.getSelectionModel().addListSelectionListener(this);
 connect(_table, SIGNAL(clicked(QModelIndex)), this, SLOT(valueChanged()));
 _showIconsButton->setEnabled(false);
 _showIconsButton->setToolTip(tr("Select a row from the table to show the icons for the item"));
}
void SignalMastItemPanel::init(ActionListener* doneAction, QHash<QString, NamedIcon*>* iconMap)
{
 TableItemPanel::init(doneAction, iconMap);
}

/*protected*/ QWidget* SignalMastItemPanel::instructions()
{
 QWidget* blurb = new QWidget();
 blurb->setLayout(new QVBoxLayout(blurb/*, BoxLayout.Y_AXIS*/));
 ((QBoxLayout*)blurb->layout())->addStrut(ItemPalette::STRUT_SIZE);
    blurb->layout()->addWidget(new JLabel(tr("To Add an Icon to your control panel:")));
    blurb->layout()->addWidget(new JLabel(tr("--drag an icon from the display panel below to your control panel")));
    ((QBoxLayout*)blurb->layout())->addStrut(ItemPalette::STRUT_SIZE);
    blurb->layout()->addWidget(new JLabel(tr("Select a row from the table to show the icons for the item")));
    ((QBoxLayout*)blurb->layout())->addStrut(ItemPalette::STRUT_SIZE);
    QWidget* panel = new QWidget();
    panel->setLayout(new QVBoxLayout());
    panel->layout()->addWidget(blurb);
    return panel;
}

/*protected*/ void SignalMastItemPanel::initIconFamiliesPanel()
{
 _iconFamilyPanel = new QWidget();
 QVBoxLayout* iconFamilyPanelLayout;
 _iconFamilyPanel->setLayout(iconFamilyPanelLayout = new QVBoxLayout(_iconFamilyPanel/*, BoxLayout.Y_AXIS*/));
 if (!_update)
 {
  iconFamilyPanelLayout->addWidget(instructions());
 }
 if (_table!=NULL)
 {
  int row = /*_table.getSelectedRow();*/ _table->currentIndex().row();
  getIconMap(row);        // sets _currentIconMap & _mast, if they exist.
 }
 _dragIconPanel = new QWidget();
 makeDndIconPanel(NULL, "");
 _iconPanel = new QWidget();
 addIconsToPanel(_currentIconMap);
 iconFamilyPanelLayout->addWidget(_dragIconPanel,0,Qt::AlignCenter);
 QWidget* panel = new QWidget();
 panel->setLayout(new QVBoxLayout());
 if (_mast!=NULL)
 {
  panel->layout()->addWidget(new JLabel(tr("Icon Set Name:")+" "+((AbstractSignalMast*)_mast)->getSignalSystem()->getSystemName()));
 }
 iconFamilyPanelLayout->addWidget(panel);
 iconFamilyPanelLayout->addWidget(_iconPanel);
 _iconPanel->setVisible(false);
}

/*protected*/ void SignalMastItemPanel::makeDndIconPanel(QHash<QString, NamedIcon*>* /*iconMap*/, QString /*displayKey*/) {
    if (_update) {
        return;
    }
    _dragIconPanel->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));

    NamedIcon* icon = getDragIcon();
    QGroupBox* panel = new QGroupBox();
    panel->setLayout(new QVBoxLayout);
    QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";
    QString borderName = ItemPalette::convertText("dragToPanel");
    //panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black),
//                                                     borderName));
    panel->setTitle(borderName);
    panel->setStyleSheet(gbStyleSheet);

    DragJLabel* label;
    try {
        label = getDragger(new DataFlavor(Editor::POSITIONABLE_FLAVOR));
        label->setToolTip(tr("ToolTipDragIcon"));
    } catch (ClassNotFoundException cnfe) {
        //cnfe.printStackTrace();
        label = new DragJLabel(NULL);
    }
    label->setIcon(icon);
    label->setName(borderName);
    label->setAlignment(Qt::AlignCenter);
    label->setMargin(6);
    ((QBoxLayout*)panel->layout())->addWidget(label,0, Qt::AlignCenter);
    int width = qMax(100, panel->minimumSize().width());
    panel->setMinimumSize(QSize(width, panel->minimumSize().height()));
    panel->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
    if(_dragIconPanel->layout() == NULL)
        _dragIconPanel->setLayout(new FlowLayout);
    _dragIconPanel->layout()->addWidget(panel);
}

/*protected*/ QWidget* SignalMastItemPanel::makeBottom1Panel() {
    QWidget* bottomPanel = new QWidget();
    bottomPanel->setLayout(new QHBoxLayout());
    _showIconsButton = new QPushButton(tr("Show Icons"));
//    _showIconsButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                if (_iconPanel.isVisible()) {
//                    hideIcons();
//                } else {
//                    showIcons();
//                }
//            }
//        });
    connect(_showIconsButton, SIGNAL(clicked()), this, SLOT(_showIconsButton_clicked()));
    _showIconsButton->setToolTip(tr("ToolTipShowIcons"));
    bottomPanel->layout()->addWidget(_showIconsButton);
    return bottomPanel;
}
void SignalMastItemPanel::_showIconsButton_clicked()
{
 if (_iconPanel->isVisible()) {
    hideIcons();
 } else {
    showIcons();
 }
}

/*protected*/ QWidget* SignalMastItemPanel::makeBottom2Panel() {
    return new QWidget();
}
/*private*/ void SignalMastItemPanel::getIconMap(int row)
{
 if (row<0)
 {
  _currentIconMap = NULL;
  _family = "";
  return;
 }
 NamedBean* bean = _model->getBeanAt(row);

 if (bean==NULL)
 {
  if (log->isDebugEnabled()) log->debug("getIconMap: NamedBean is NULL at row "+QString::number(row));
  _currentIconMap = NULL;
   _family = "";
   return;
 }
 _mast = ((DefaultSignalMastManager*)InstanceManager::signalMastManagerInstance())->provideSignalMast(bean->getDisplayName());
 if (_mast == NULL)
 {
  log->error("getIconMap: No SignalMast called "+bean->getDisplayName());
  _currentIconMap = NULL;
  return;
 }
 _family = _mast->getSignalSystem()->getSystemName();
 _currentIconMap = new QHash<QString, NamedIcon*>();  QStringListIterator e(_mast->getAppearanceMap()->getAspects());
 while (e.hasNext())
 {
  QString s = _mast->getAppearanceMap()->getProperty(e.next(), "imagelink");
  s = s.mid(s.indexOf("resources"));
  NamedIcon* n = new NamedIcon(s,s);
  _currentIconMap->insert(s, n);
 }
 if (log->isDebugEnabled()) log->debug("getIconMap: for "+_family+
                                        " size= "+QString::number(_currentIconMap->size()));
}

/*private*/ NamedIcon* SignalMastItemPanel::getDragIcon()
{
 if (_currentIconMap!=NULL)
 {
  if (_currentIconMap->contains("Stop"))
  {
   return _currentIconMap->value("Stop");
  }
  QStringListIterator e(_currentIconMap->keys());
  if (e.hasNext())
  {
   return _currentIconMap->value(e.next());
  }
 }
 QString fileName = FileUtil::getProgramPath()+ "resources/icons/misc/X-red.gif";
 return new NamedIcon(fileName, fileName);
}


/**
*  ListSelectionListener action
*/
/*public*/ void SignalMastItemPanel::valueChanged(ListSelectionEvent* /*e*/)
{
 if (_table == NULL)
 {
  return;
 }
 int row = _table->currentIndex().row();
 if (log->isDebugEnabled()) log->debug("Table valueChanged: row= "+QString::number(row));
 //remove(_iconFamilyPanel);
 layout()->removeWidget(_iconFamilyPanel);
 delete _iconFamilyPanel;
 initIconFamiliesPanel();
 ((QVBoxLayout*)layout())->insertWidget(1,_iconFamilyPanel/*, 1*/);
 if (row >= 0)
 {
  if (_updateButton!=NULL)
  {
   _updateButton->setEnabled(true);
   _updateButton->setToolTip("");
  }
  _showIconsButton->setEnabled(true);
  _showIconsButton->setToolTip("");
 }
 else
 {
  if (_updateButton!=NULL)
  {
   _updateButton->setEnabled(false);
   _updateButton->setToolTip(tr("Select an item from the table and an icon set to update the panel"));
  }
  _showIconsButton->setEnabled(false);
  _showIconsButton->setToolTip(tr("Select a row from the table to show the icons for the item"));
 }
//    validate();
}

/*protected*/ DragJLabel* SignalMastItemPanel::getDragger(DataFlavor* flavor) {
    return new SMIconDragJLabel(flavor, this);
}

// /*protected*/ class SMIconDragJLabel extends DragJLabel {

/*public*/ SMIconDragJLabel::SMIconDragJLabel(DataFlavor* flavor, SignalMastItemPanel* self):DragJLabel(flavor, self)
{
 //super(flavor);
 this->self = self;
    log = new Logger("SMIconDragJLabel");
}
/*public*/ QObject* SMIconDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException)
{
 if (!isDataFlavorSupported(flavor))
 {
  return NULL;
 }
 NamedBean* bean = self->getNamedBean();
 if (bean==NULL)
 {
  self->log->error("IconDragJLabel.getTransferData: NamedBean is NULL!");
  return NULL;
 }

 SignalMastIcon* sm  = new SignalMastIcon(self->_editor);
 sm->setSignalMast(bean->getDisplayName());
 sm->setLevel(Editor::SIGNALS);
 return sm;
}

QString SMIconDragJLabel::mimeData()
{
 NamedBean* bean = self->getNamedBean();
 if (bean==NULL)
 {
  log->error("IconDragJLabel.getTransferData: NamedBean is NULL!");
  return NULL;
 }
 SignalMastIcon* icon; _dataFlavor = new DataFlavor(icon = new SignalMastIcon(self->_editor), "SignalMastIcon");
 icon->setSignalMast(bean->getDisplayName());
 icon->setFamily(self->_family);
 icon->setLevel(Editor::SIGNALS);

 SignalMastIconXml* xml = new SignalMastIconXml();
 QDomElement e = xml->store((QObject*)icon);
 xml->doc.appendChild(e);
 QString xmldata = xml->doc.toString();
 _dataFlavor->setMimeTypeParameter("xml", QString(QUrl::toPercentEncoding(xmldata)));

 return _dataFlavor->toString();
}
//};
