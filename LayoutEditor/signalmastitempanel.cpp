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
#include "imagepanel.h"
#include "jpanel.h"
#include "borderfactory.h"
#include "joptionpane.h"

//SignalMastItemPanel::SignalMastItemPanel(QWidget *parent) :
//    TableItemPanel(parent)
//{
//}
///*public*/ class SignalMastItemPanel extends TableItemPanel implements ListSelectionListener {


/*public*/ SignalMastItemPanel::SignalMastItemPanel(DisplayFrame* parentFrame, QString  type, QString family, PickListModel* model, Editor *editor, QWidget *parent)
 : TableItemPanel(parentFrame, type, family, model, editor,parent)
{
 //super(parentFrame, type, family, model, editor);
 _mast = NULL;
 setObjectName("SignalMastItemPanel");
}

void SignalMastItemPanel::init()
{
 if(!_initialized)
 {
  TableItemPanel::init();
  //_table.getSelectionModel().addListSelectionListener(this);
  connect(_table, SIGNAL(clicked(QModelIndex)), this, SLOT(valueChanged()));
  _showIconsButton->setEnabled(false);
  _showIconsButton->setToolTip(tr("Select a row from the table to show the icons for the item"));
  initIconFamiliesPanel();
  layout()->addWidget(_iconFamilyPanel/*, 1*/);
 }
}
#if 0
void SignalMastItemPanel::init(ActionListener* doneAction, QMap<QString, NamedIcon*>* iconMap)
{
 TableItemPanel::init(doneAction, iconMap);
// _table->getSelectionModel().addListSelectionListener(this);
 _previewPanel->setVisible(false);
}
#endif
/*protected*/ QWidget* SignalMastItemPanel::instructions()
{
 _blurb = new QWidget();
 _blurb->setLayout(new QVBoxLayout(_blurb/*, BoxLayout.Y_AXIS*/));
 ((QBoxLayout*)_blurb->layout())->addStrut(ItemPalette::STRUT_SIZE);
    _blurb->layout()->addWidget(new JLabel(tr("To Add an Icon to your control panel:")));
    _blurb->layout()->addWidget(new JLabel(tr("--drag an icon from the display panel below to your control panel")));
    ((QBoxLayout*)_blurb->layout())->addStrut(ItemPalette::STRUT_SIZE);
    _blurb->layout()->addWidget(new JLabel(tr("Select a row from the table to show the icons for the item")));
    ((QBoxLayout*)_blurb->layout())->addStrut(ItemPalette::STRUT_SIZE);
    QWidget* panel = new QWidget();
    panel->setLayout(new QVBoxLayout());
    panel->layout()->addWidget(_blurb);
    return panel;
}

//@Override
/*protected*/ void SignalMastItemPanel::initIconFamiliesPanel()
{
 _iconFamilyPanel = new JPanel();
 _iconFamilyPanel->setLayout(new QVBoxLayout());//_iconFamilyPanel, BoxLayout.Y_AXIS));
 if (!_update) {
     _iconFamilyPanel->layout()->addWidget(instructions());
 }
 if (_table != nullptr) {
     int row = _table->getSelectedRow();
     getIconMap(row);        // sets _currentIconMap & _mast, if they exist.
 }
 _dragIconPanel = new JPanel(new FlowLayout);
 makeDndIconPanel(nullptr, QString());
 _iconPanel = new JPanel();
 addIconsToPanel(_currentIconMap);
 _iconFamilyPanel->layout()->addWidget(_dragIconPanel);
 JPanel* panel = new JPanel(new FlowLayout());
 if (_mast != nullptr) {
     panel->layout()->addWidget(new JLabel(tr("Icon Set Name:") + " "
             + _mast->getSignalSystem()->getSystemName()));
 }
 _iconFamilyPanel->layout()->addWidget(panel);
 _iconFamilyPanel->layout()->addWidget(_iconPanel);
 _iconPanel->setVisible(false);
 hideIcons();
}

/*protected*/ void SignalMastItemPanel::makeDndIconPanel(QMap<QString, NamedIcon*>* /*iconMap*/, QString displayKey) {
    if (_update) {
        return;
    }
    _dragIconPanel->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));

    NamedIcon* icon = getDragIcon();
    JPanel* panel = new JPanel(new FlowLayout);
    QString borderName = ItemPalette::convertText("dragToPanel");
    panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
            borderName));
    JLabel* label;
    try {
        label = getDragger(new DataFlavor(Editor::POSITIONABLE_FLAVOR));
        label->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
    } catch (ClassNotFoundException cnfe) {
//        cnfe.printStackTrace();
        label = new JLabel();
    }
    label->setIcon(icon);
    label->setName(borderName);
    panel->layout()->addWidget(label);
    int width = qMax(100, panel->sizeHint().width());
    panel->resize(QSize(width, panel->sizeHint().height()));
    panel->setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
    _dragIconPanel->layout()->addWidget(panel);
}

//@Override
    /*protected*/ void SignalMastItemPanel::makeBottomPanel(ActionListener* doneAction) {
    QWidget* panel = new QWidget();
    FlowLayout* panelLayout = new FlowLayout(panel);
    _showIconsButton = new QPushButton(tr("Hide Icons"));
//    _showIconsButton.addActionListener(new ActionListener() {
//        @Override
//        public void actionPerformed(ActionEvent a) {
//            if (_iconPanel.isVisible()) {
//                hideIcons();
//            } else {
//                showIcons();
//            }
//        }
//    });
    connect(_showIconsButton, SIGNAL(clicked(bool)), this, SLOT(_showIconsButton_clicked()));
    _showIconsButton->setToolTip(tr("Press to display the icons for the current Icon Set"));
    panelLayout->addWidget(_showIconsButton);
    _bottom1Panel = new JPanel(/*new FlowLayout()*/);
    FlowLayout* _bottom1PanelLayout = new FlowLayout(_bottom1Panel);
    _bottom1PanelLayout->addWidget(panel);
    if (doneAction != nullptr) {
        addUpdateButtonToBottom(doneAction);
    }
    initIconFamiliesPanel(); // (if null: creates and) adds a new _iconFamilyPanel for the new mast map
    thisLayout->addWidget(_bottom1Panel);
}

void SignalMastItemPanel::_showIconsButton_clicked()
{
 if (_iconPanel->isVisible()) {
    hideIcons();
 } else {
    showIcons();
 }
}

/*private*/ void SignalMastItemPanel::getIconMap(int row)
{
    if (row < 0) {
        _iconMastMap = nullptr;
        _family = "";
        return;
    }
    NamedBean* bean = _model->getBySystemName( _table->getValueAt(row, 0).toString());


    if (bean == nullptr) {
        log->debug(tr("getIconMap: NamedBean is null at row %1").arg(row));
        _mast = nullptr;
        _iconMastMap = nullptr;
        _family = "";
        return;
    }

    try {
        _mast = static_cast<SignalMastManager*>( InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(bean->getDisplayName());
    } catch (IllegalArgumentException ex) {
        log->error(tr("getIconMap: No SignalMast called %1").arg(bean->getDisplayName()));
        _iconMastMap = nullptr;
        return;
    }
    _family = _mast->getSignalSystem()->getSystemName();
    _iconMastMap = new QMap<QString, NamedIcon*>();
    SignalAppearanceMap* appMap = _mast->getAppearanceMap();
    QStringListIterator e (_mast->getAppearanceMap()->getAspects());
    while (e.hasNext()) {
        QString aspect = e.next();
        QString s = appMap->getImageLink(aspect, _family);
        if (s !="" ) {
            if (!s.contains("preference:")) {
                s = s.mid(s.indexOf("resources"));
            }
            NamedIcon* n = new NamedIcon(s, s);
            _iconMastMap->insert(aspect, n);
        }
    }
    if (log->isDebugEnabled()) {
        log->debug(tr("getIconMap for %1  size= %2").arg(_family).arg(_iconMastMap->size()));
    }
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
#if 0
//@Override
    /*protected*/ void SignalMastItemPanel::setFamily(QString family) {
        _family = family;
        //_iconPanel.removeAll(); // just clear contents
        QList<QWidget*> widgets = _iconPanel->findChildren<QWidget*>();
        foreach(QWidget* widget, widgets)
        {
         _iconPanel->layout()->removeWidget(widget);
         widget->deleteLater();
        }
        QMap<QString, NamedIcon*>* map = ItemPalette::getIconMap(_itemType, _family);
        if (map != nullptr) {
            _iconMastMap = map;
        } else {
            log->warn(tr("Family \"%1\" for type \"%2\" for not found in Catalog.").arg( _family).arg(_itemType));
        }
        if (!_suppressDragging) {
            makeDragIconPanel(0);
            makeDndIconPanel(_iconMastMap, ""); // empty key OK, this uses getDragIcon()
        }
        if (_iconMastMap != nullptr) {
            addIconsToPanel(_iconMastMap, _iconPanel, false);
        }
    }

    //@Override
    /*protected*/ void SignalMastItemPanel::showIcons() {
        if (log->isDebugEnabled()) {
            log->debug(tr("showIcons for= %1, %2").arg(_itemType).arg(_family));
        }
        bool isPalette = (qobject_cast<ItemPalette*>(_frame));
        QSize totalDim;
        if (isPalette) {
            totalDim = ItemPalette::_tabPane->size();
        } else {
            totalDim = _frame->size();
        }
        QSize oldDim = size();
        _iconPanel->setVisible(true);
        _iconPanel->update();
        _previewPanel->setVisible(true);
        _previewPanel->update();
        if (!_update) {
//            _dragIconPanel.removeAll();
         QList<QWidget*> widgets = _dragIconPanel->findChildren<QWidget*>();
         foreach(QWidget* widget, widgets)
         {
          _dragIconPanel->layout()->removeWidget(widget);
          widget->deleteLater();
         }
            _dragIconPanel->setVisible(false);
            _dragIconPanel->update();
            _blurb->setVisible(false);
            _blurb->update();

        }
        reSizeDisplay(isPalette, oldDim, totalDim);
        _showIconsButton->setText(tr("Show Icons"));
    }

    //@Override
    /*protected*/ void SignalMastItemPanel::hideIcons() {
        if (log->isDebugEnabled()) {
            log->debug(tr("hideIcons for= %1, %2").arg(_itemType).arg(_family));
        }
        bool isPalette = (qobject_cast<ItemPalette*>(_frame));
        QSize totalDim;
        if (isPalette) {
            totalDim = ItemPalette::_tabPane->size();
        } else {
            totalDim = _frame->size();
        }
        QSize oldDim = size();
        _iconPanel->setVisible(false);
        _iconPanel->update();
        if (!_update) {
            _dragIconPanel->setVisible(true);
            makeDndIconPanel(nullptr, nullptr);
            _dragIconPanel->update();
            _blurb->setVisible(true);
            _blurb->update();
            _previewPanel->setVisible(true);
            _previewPanel->update();
        } else {
            _previewPanel->setVisible(false);
            _previewPanel->update();
        }
        reSizeDisplay(isPalette, oldDim, totalDim);
        _showIconsButton->setText(tr("Hide Icons"));
    }
#endif
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

 // update the family icons
 //_iconPanel.removeAll();
 QList<QWidget*> widgets = _iconPanel->findChildren<QWidget*>();
 foreach(QWidget* widget, widgets)
 {
  _iconPanel->layout()->removeWidget(widget);
  widget->deleteLater();
 }
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
 initIconFamiliesPanel(); // (if null: creates and) adds a new _iconFamilyPanel for the new mast map
 update();

}

/*protected*/ NamedBean* SignalMastItemPanel::getNamedBean() {
    if (_table == nullptr) {
        return nullptr;
    }
    int row = _table->getSelectedRow();
    if (log->isDebugEnabled()) {
        log->debug("getNamedBean: from table \"" + _itemType + "\" at row " + QString::number(row));
    }
    if (row < 0) {
        return nullptr;
    }
    return _model->getBeanAt(row);
}

/*protected*/ JLabel* SignalMastItemPanel::getDragger(DataFlavor* flavor) {
 return new SMIconDragJLabel(flavor,this);
}

// /*protected*/ class SMIconDragJLabel extends DragJLabel {

/*public*/ SMIconDragJLabel::SMIconDragJLabel(DataFlavor* flavor, SignalMastItemPanel* self)
  : DragJLabel(flavor, self)
{
 //super(flavor);
 this->self = self;
    log = new Logger("SMIconDragJLabel");
}
//@Override
/*protected*/ bool SMIconDragJLabel::okToDrag() {
    NamedBean* bean = self->getDeviceNamedBean();
    if (bean == nullptr) {
        JOptionPane::showMessageDialog(this, tr("Select a row in the table to provide a device for this icon."),
                tr("Warning"), JOptionPane::WARNING_MESSAGE);
        return false;
    }
    return true;
}

/*public*/ QObject* SMIconDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException)
{
 if (!isDataFlavorSupported(flavor))
 {
  return NULL;
 }
 NamedBean* bean = self->getNamedBean();
 if (bean == nullptr) {
     JOptionPane::showMessageDialog(nullptr, tr("Select a row in the table to provide a device for this icon."),
             tr("Warning"), JOptionPane::WARNING_MESSAGE);
     return nullptr;
 }

 SignalMastIcon* sm = new SignalMastIcon(self->_editor);
 sm->setSignalMast(bean->getDisplayName());
 sm->setLevel(Editor::SIGNALS);
 return sm;
}

QByteArray SMIconDragJLabel::mimeData()
{
 NamedBean* bean = self->getDeviceNamedBean();
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
 QByteArray xmldata;
 xmldata.append(xml->doc.toString());
 return xmldata;
}
//};
