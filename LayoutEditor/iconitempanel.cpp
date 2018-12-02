#include "iconitempanel.h"
#include <QThread>
#include "catalogpanel.h"
#include <QVBoxLayout>
#include "itempalette.h"
#include <QGroupBox>
#include <QPushButton>
#include <QMessageBox>
#include "fileutil.h"
#include "editor.h"
#include "inputdialog.h"
#include "dataflavor.h"
#include <QDrag>
#include "positionablelabelxml.h"

//IconItemPanel::IconItemPanel(QWidget *parent) :
//    ItemPanel(parent)
//{
//}
/**
*  ItemPanel for for plain icons and backgrounds
*/
// /*public*/ class IconItemPanel extends ItemPanel implements MouseListener {


/**
 * Constructor for plain icons and backgrounds
 */
/*public*/ IconItemPanel::IconItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, QWidget *parent) : ItemPanel(parentFrame, type, family, editor, parent)
{
 //super(parentFrame,  type, family, editor);
 setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
 log = new Logger("IconItemPanel");
}

/*public*/ void IconItemPanel::init()
{

 _level = Editor::ICONS;      // sub classes can override (e.g. Background)

 if (!_initialized)
 {
//        Thread.yield();
  QThread::yieldCurrentThread();
  thisLayout->addWidget(instructions());
  initIconFamiliesPanel();
  initButtonPanel();
  _catalog = CatalogPanel::makeDefaultCatalog();
  thisLayout->addWidget(_catalog);
  _catalog->setVisible(false);
  _catalog->setToolTip(tr("Drag an icon directly from the Catalog Panel to add it to the control panel  "));
  setMinimumSize(size());
  ItemPanel::init();
 }
}

/*protected*/ QWidget* IconItemPanel::instructions()
{
 //QWidget* blurb = new QWidget();
 QVBoxLayout* blurbLayout = new QVBoxLayout;
 //blurb->setLayout(blurbLayout = new QVBoxLayout(blurb/*, BoxLayout.Y_AXIS*/));
 //blurb.add(Box.createVerticalStrut(ItemPalette.STRUT_SIZE));
 blurbLayout->addStrut(ItemPalette::STRUT_SIZE);
 blurbLayout->addWidget(new QLabel(tr("To Add an Icon to your control panel:")));
 blurbLayout->addWidget(new QLabel(tr("--drag an icon from the display panel below to your control panel")));
 blurbLayout->addWidget(new QLabel(tr("--or press [%1] and drag an icon from the catalog to your control panel").arg(
                                    tr("Icon Catalog"))));
 //blurb.add(Box.createVerticalStrut(ItemPalette.STRUT_SIZE));
 blurbLayout->addStrut(ItemPalette::STRUT_SIZE);
 blurbLayout->addWidget(new QLabel(tr("To modify an icon in the display panel below, drag an icon from the catalog.")));
 blurbLayout->addWidget(new QLabel(tr("To change the name of an icon below, Double Click on the name.")));
 blurbLayout->addWidget(new QLabel(tr("To delete the icon, Click on the name, then press [%1].").arg( tr("deleteIcon"))));
 //blurb.add(Box.createVerticalStrut(ItemPalette.STRUT_SIZE));
 blurbLayout->addStrut(ItemPalette::STRUT_SIZE);
 QWidget* panel = new QWidget();
// panel->setLayout(new QVBoxLayout());
//    panel->layout()->addWidget(blurb);
 panel->setLayout(blurbLayout);
 return panel;
}

/**
* Plain icons have only one family, usually named "set"
* Override for plain icon & background and put all icons here
*/
/*protected*/ void IconItemPanel::initIconFamiliesPanel()
{
 QMap <QString, QMap<QString, NamedIcon*>*>* families = ItemPalette::getFamilyMaps(_itemType);
 if (families!=NULL && families->size()>0)
 {
  if (families->size()!=1)
  {
   log->warn("ItemType \""+_itemType+"\" has "+QString::number(families->size())+" families.");
  }
  //Iterator <String> iter = families.keySet().iterator();
  QStringListIterator iter(families->keys());
  while (iter.hasNext())
  {
   _family = iter.next();
  }
  _iconMap = families->value(_family);
  addIconsToPanel(_iconMap);
 }
 else
 {
  // make create message todo!!!
  log->error("Item type \""+_itemType+"\" has "+(families==NULL ? "NULL" : QString::number(families->size()))+" families.");
 }
}

/**
*  Note caller must create _iconPanel before calling
*/
/*protected*/ void IconItemPanel::addIconsToPanel(QMap<QString, NamedIcon*>* iconMap)
{
 _iconPanel = new QWidget();
 _iconPanel->setLayout(new QHBoxLayout());
 //Iterator<Entry<QString, NamedIcon*>*> it = iconMap.entrySet().iterator();
 QMapIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext())
 {
  //Entry<String, NamedIcon> entry = it.next();
  it.next();
  NamedIcon* icon = new NamedIcon(it.value());    // make copy for possible reduction
  QGroupBox* panel = new QGroupBox();
  panel->setLayout(new QVBoxLayout());
  QString borderName = ItemPalette::convertText(it.key());
  //panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black),
  //                                                 borderName));
  QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

  panel->setTitle(borderName);
  panel->setStyleSheet(gbStyleSheet);
  try
  {
   IconDragJLabel* label = new IconDragJLabel(new DataFlavor(Editor::POSITIONABLE_FLAVOR), _level, this);
   label->setName(borderName);
   //panel->layout()->addWidget(label);
   if (icon->getIconWidth()<1 || icon->getIconHeight()<1)
   {
    label->setText(tr("invisibleIcon"));
//               label->setForeground(QColor(Qt::lightGray);
   }
   else
   {
    icon->reduceTo(50, 80, 0.2);
   }
   label->setIcon(icon);
   label->setAlignment(Qt::AlignCenter);
   label->setMargin(6);

   int width = qMax(100, panel->minimumSize().width());
   panel->setMinimumSize(QSize(width, panel->minimumSize().height()));
   ((QBoxLayout*)panel->layout())->addWidget(label,0, Qt::AlignCenter);

  } catch (ClassNotFoundException cnfe) {
           //cnfe.printStackTrace();
  }
  _iconPanel->layout()->addWidget(panel);
 }
 thisLayout->addWidget(_iconPanel/*, 1*/);
 //_iconPanel->addMouseListener(this);
}

/*
 *  for plain icons and backgrounds, families panel is the icon panel of the one family
 */
/*protected*/ void IconItemPanel::removeIconFamiliesPanel() {
    if (_iconPanel != NULL) {
//        _iconPanel->removeMouseListener(this);
//        remove(_iconPanel);
    }
}

/*protected*/ void IconItemPanel::updateFamiliesPanel() {
    if (log->isDebugEnabled()) log->debug("updateFamiliesPanel for "+_itemType);
    removeIconFamiliesPanel();
    initIconFamiliesPanel();
//    validate();
}

/**
*  SOUTH Panel
*/
/*public*/ void IconItemPanel::initButtonPanel() {
    QWidget* bottomPanel = new QWidget();
    bottomPanel->setLayout(new /*FlowLayout()*/QHBoxLayout());  //new BoxLayout(p, BoxLayout.Y_AXIS)

    _catalogButton = new QPushButton(tr("Icon Catalog"));
//    _catalogButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                if (_catalog->isVisible()) {
//                    hideCatalog();
//                } else {
//                    _catalog->setVisible(true);
//                    _catalogButton.setText(tr("HideCatalog"));
//                }
//                repaint();
//            }
//    });
    _catalogButton->setToolTip(tr("Open the Icon Catalog and drag icons from it to the panel"));
    connect(_catalogButton, SIGNAL(clicked()), this, SLOT(on_catalogButton_clicked()));
    bottomPanel->layout()->addWidget(_catalogButton);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(_catalogButton->sizePolicy().hasHeightForWidth());
    _catalogButton->setSizePolicy(sizePolicy);
    QPushButton* addIconButton = new QPushButton(tr("Add Icon"));
//    addIconButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                addNewIcon();
//            }
//    });
    addIconButton->setToolTip(tr("Add another icon to your icon panel.  Enter a name for it.  "));
    connect(addIconButton, SIGNAL(clicked()), this, SLOT(addNewIcon()));
    bottomPanel->layout()->addWidget(addIconButton);
    addIconButton->setSizePolicy(sizePolicy);

    thisLayout->addWidget(bottomPanel);

    deleteIconButton = new QPushButton(tr("Delete Icon"));
//    deleteIconButton.addActionListener(new ActionListener() {
//            /*public*/ void actionPerformed(ActionEvent a) {
//                deleteIcon();
//            }
//    });
    deleteIconButton->setSizePolicy(sizePolicy);
    connect(deleteIconButton, SIGNAL(clicked()), this, SLOT(deleteIcon()));
    deleteIconButton->setToolTip(tr("Delete an icon from your icon panel. Select the icon to be deleted. "));
    bottomPanel->layout()->addWidget(deleteIconButton);
    deleteIconButton->setEnabled(false);

    thisLayout->addWidget(bottomPanel);
}
void IconItemPanel::on_catalogButton_clicked()
{
 if (_catalog->isVisible())
 {
  hideCatalog();
 }
 else
 {
  _catalog->setVisible(true);
  _catalogButton->setText(tr("Hide Catalog"));
 }
// repaint();
}

void IconItemPanel::hideCatalog() {
    _catalog->setVisible(false);
    _catalogButton->setText(tr("Icon Catalog"));
}

/**
* Action item for initButtonPanel
*/
/*protected*/ void IconItemPanel::addNewIcon() {
    if (log->isDebugEnabled()) log->debug("addNewIcon Action: iconMap.size()= "+QString::number(_iconMap->size()));
    QString name = tr("RedX");
    if (_iconMap->value(name)!=NULL) {
//        JOptionPane.showMessageDialog(this,
//                java.text.MessageFormat.format(tr("DuplicateIconName"), name),
//                ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(this, tr("Warning"), tr("Another icon is named %1.").arg(name));
        name = setIconName(name);
        if ( name==NULL || _iconMap->value(name)!= NULL) {
            return;
        }
    }
    QString fileName = FileUtil::getProgramPath()+"resources/icons/misc/X-red.gif";
    NamedIcon* icon = new NamedIcon(fileName, fileName);
    putIcon(name, icon);
}

/*private*/ void IconItemPanel::putIcon(QString name, NamedIcon* icon) {
    _iconMap->insert(name, icon);
    removeIconFamiliesPanel();
    addIconsToPanel(_iconMap);
    //validate();
}

/**
* Action item for initButtonPanel
*/
/*protected*/ void IconItemPanel::deleteIcon() {
    if (_selectedIcon == NULL) {
        return;
    }
//    if (_iconMap->remove(_selectedIcon->getName())!= NULL) {
//        removeIconFamiliesPanel();
//        addIconsToPanel(_iconMap);
//        validate();
//    }
}

/*protected*/ QString IconItemPanel::setIconName(QString name)
{
//    name = JOptionPane.showInputDialog(this,
//            tr("NoIconName"), name);
    InputDialog* dlg = new InputDialog(tr("Please enter a name for the Icon."),name);
    dlg->exec();
    name = dlg->value();
    if ( name.isEmpty()) {
        return "";
    }
    while (_iconMap->value(name)!=NULL)
    {
//        JOptionPane.showMessageDialog(this,
//                java.text.MessageFormat.format(tr("DuplicateIconName"), name),
//                ItemPalette.rb.getString("warnTitle"), JOptionPane.WARNING_MESSAGE);
        QMessageBox::warning(this, tr("Warning"), tr("Another icon is named %1.").arg(name));
//        name = JOptionPane.showInputDialog(this,
//                tr("NoIconName"), name);
        InputDialog* dlg = new InputDialog(tr("Please enter a name for the Icon."),name);
        dlg->exec();
        name = dlg->value();
        if ( name.isEmpty()) {
            return "";
        }
    }
    return name;
}

/*private*/ void IconItemPanel::clickEvent(QGraphicsSceneMouseEvent* event)
{
 //java.awt.Component[] comp = _iconPanel->getComponents();
 QObjectList comp = _iconPanel->children();
 for (int i=0; i<comp.length(); i++)
 {
  //if (comp[i] instanceof JPanel)
  if(qobject_cast<QWidget*>(comp.at(i))!= NULL)
  {
   QWidget* panel = (QWidget*)comp.at(i);
   //java.awt.Component[] com = panel.getComponents();
   QObjectList com = panel->children();
   for (int k=0; k<com.length(); k++)
   {
    //if (com[k] instanceof IconDragLabel)
    if(qobject_cast<IconDragJLabel*>(com.at(k)))
    {
     JLabel* icon = (JLabel*)com.at(k);
     //java.awt.Rectangle r = panel.getBounds();
     QRect r = panel->geometry();
     if (r.contains(QPoint(event->pos().x(), event->pos().y())))
     {
      //if (event->getClickCount() >1)
      {
       QString name = setIconName(icon->getName());
       if (name!=NULL)
       {
        _iconMap->remove(icon->getName());
        putIcon(name, (NamedIcon*)icon->getIcon());
       }
       return;
      }
#if 0
      if (icon==(_selectedIcon))
      {
       panel.setBorder(BorderFactory.createTitledBorder(
                    BorderFactory.createLineBorder(Color.black),
                    icon.getName()));
            _selectedIcon = NULL;
            deleteIconButton.setEnabled(false);
      }
      else
      {
       panel.setBorder(BorderFactory.createTitledBorder(
                    BorderFactory.createLineBorder(Color.red),
                    icon->getName()));
            deleteIconButton.setEnabled(true);
            _selectedIcon = icon;
      }
#endif
      return;
     }
    }
   }
  }
 }
}
/*public*/ void IconItemPanel::mouseClicked(QGraphicsSceneMouseEvent* event) { clickEvent(event); }
/*public*/ void IconItemPanel::mousePressed(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void IconItemPanel::mouseReleased(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void IconItemPanel::mouseEntered(QGraphicsSceneMouseEvent* /*event*/) {}
/*public*/ void IconItemPanel::mouseExited(QGraphicsSceneMouseEvent* /*event*/) {}

///*public*/ class IconJDragLabel extends DragJLabel implements DropTargetListener {

//    int level;

/*public*/ IconDragJLabel::IconDragJLabel(DataFlavor* flavor, int zLevel, QWidget* parent) : DragJLabel(flavor,parent) {
        //super(flavor);
        level = zLevel;
        log = new Logger("IconDragJLabel");
        this->parent = (IconItemPanel*)parent;

//        new DropTarget(this, DnDConstants.ACTION_COPY_OR_MOVE, this);
        //if (log->isDebugEnabled()) log->debug("DropQLabel ctor");
    }

/*public*/ QObject* IconDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) {
        if (!isDataFlavorSupported(flavor)) {
            return NULL;
        }
        QString url = ((NamedIcon*)getIcon())->getURL();
//        if (log->isDebugEnabled()) log->debug("DragJLabel.getTransferData url= "+url);
        PositionableLabel* l = new PositionableLabel(NamedIcon::getIconByName(url), /*_editor*/(Editor*)parent);
        l->setPopupUtility(NULL);        // no text
        l->setLevel(level);
        return l;
    }
/*public*/ QString IconDragJLabel::mimeData()
{
 QString url = ((NamedIcon*)getIcon())->getURL();
 PositionableLabel* l = new PositionableLabel(NamedIcon::getIconByName(url), /*_editor*/(Editor*)parent->_editor);
 l->setPopupUtility(NULL);        // no text
 l->setLevel(level);
 _dataFlavor = new DataFlavor(l, "PositionableLabel");
 _dataFlavor->setMimeTypeParameter("family", parent->_family);
 PositionableLabelXml* xml = new PositionableLabelXml();
 QDomElement e = xml->store((QObject*)l);
 xml->doc.appendChild(e);
 QString xmldata = xml->doc.toString();
 _dataFlavor->setMimeTypeParameter("xml", QString(QUrl::toPercentEncoding(xmldata)));
 return _dataFlavor->toString();
}

//    /*public*/ void dragExit(DropTargetEvent dte) {
void IconDragJLabel::dragLeaveEvent(QDragLeaveEvent *)
{
        if (log->isDebugEnabled()) log->debug("DropQLabel.dragExit ");
    }
//    /*public*/ void dragEnter(DropTargetDragEvent dtde) {
void IconDragJLabel::dragEnterEvent(QDragEnterEvent *)
{
        if (log->isDebugEnabled()) log->debug("DropQLabel.dragEnter ");
    }

//    /*public*/ void drop(DropTargetDropEvent e) {
void IconDragJLabel::dropEvent(QDropEvent *)
{
#if 0
        try {
            Transferable tr = e.getTransferable();
            if(e.isDataFlavorSupported(_dataFlavor)) {
                NamedIcon newIcon = new NamedIcon((NamedIcon)tr.getTransferData(_dataFlavor));
                accept(e, newIcon);
            } else if(e.isDataFlavorSupported(DataFlavor.stringFlavor)) {
                String text = (String)tr.getTransferData(DataFlavor.stringFlavor);
                if (log->isDebugEnabled()) log->debug("drop for stringFlavor "+text);
                NamedIcon newIcon = new NamedIcon(text, text);
                accept(e, newIcon);
            } else {
                if (log->isDebugEnabled()) log->debug("DropQLabel.drop REJECTED!");
                e.rejectDrop();
            }
        } catch(IOException ioe) {
            if (log->isDebugEnabled()) log->debug("DropPanel.drop REJECTED!");
            e.rejectDrop();
        } catch(UnsupportedFlavorException ufe) {
            if (log->isDebugEnabled()) log->debug("DropQLabel.drop REJECTED!");
            e.rejectDrop();
        }
#endif
    }
#if 0
    /*private*/ void accept(DropTargetDropEvent e, NamedIcon newIcon) {
        e.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
        DropTarget target = (DropTarget)e.getSource();
        IconDragJLabel label = (IconDragJLabel)target.getComponent();
        if (log->isDebugEnabled()) log->debug("accept drop for "+label.getName()+
                                             ", "+newIcon.getURL());
        if (newIcon==NULL || newIcon.getIconWidth()<1 || newIcon.getIconHeight()<1) {
            label.setText(tr("invisibleIcon"));
            label.setForeground(Color.lightGray);
        } else {
            newIcon.reduceTo(100, 100, 0.2);
            label.setText(NULL);
        }
        _iconMap.put(label.getName(), newIcon);
        if (!_update) {		// only prompt for save from palette
            ImageIndexEditor.indexChanged(true);
        }
        removeIconFamiliesPanel();
        addIconsToPanel(_iconMap);
        e.dropComplete(true);
        if (log->isDebugEnabled()) log->debug("DropQLabel.drop COMPLETED for "+label.getName()+
                                             ", "+(newIcon!=NULL ? newIcon.getURL().toString():" newIcon==NULL "));
    }
#endif
void IconDragJLabel::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
   QDrag *dr = new QDrag(this);
   QMimeData *data = new QMimeData;
   //data->setText(_dataFlavor->toString());
   QString url = ((NamedIcon*)getIcon())->getURL();
   //data->setText(mimeData());
   data->setText(url+";PositionableLabel");
   // Assign ownership of the QMimeData object to the QDrag object.
   dr->setMimeData(data);
   dr->start();
}

//};
