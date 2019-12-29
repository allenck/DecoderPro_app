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
#include "joptionpane.h"
#include "loggerfactory.h"


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
/*public*/ IconItemPanel::IconItemPanel(DisplayFrame* parentFrame, QString type, Editor* editor, QWidget *parent) : ItemPanel(parentFrame, type, editor, parent)
{
 //super(parentFrame,  type, family, editor);
 setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
 log = new Logger("IconItemPanel");
 setObjectName("IconItemPanel");

 _level = Editor::ICONS;      // sub classes can override (e.g. Background)

}

/*public*/ void IconItemPanel::init()
{
 if (!_initialized)
 {
//        Thread.yield();
  thisLayout->addWidget(instructions());
  initIconFamiliesPanel();
  initLinkPanel();
  makeBottomPanel(nullptr);
  _catalog = makeCatalog();
  thisLayout->addWidget(_catalog);
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
/*private*/ CatalogPanel* IconItemPanel::makeCatalog() {
    CatalogPanel* catalog = CatalogPanel::makeDefaultCatalog(false, false, !_update);
    ImagePanel* panel = catalog->getPreviewPanel();
    if (!isUpdate()) {
        panel->setImage(_backgrounds->at(getParentFrame()->getPreviewBg()));
    } else {
        panel->setImage(_backgrounds->at(0));   //update always should be the panel background
        catalog->setParent(this);
    }
    catalog->setToolTip(tr("Drag an icon directly from the Catalog Pane to add it to the Control Panel"));
    catalog->setVisible(false);
    return catalog;
}

//@Override
/*protected*/ void IconItemPanel::setPreviewBg(int index) {
    if (_catalog != nullptr) {
        ImagePanel* iconPanel = _catalog->getPreviewPanel();
        if (iconPanel != nullptr) {
            iconPanel->setImage(_backgrounds->at(index));
        }
    }
    if (_iconPanel != nullptr) {
        _iconPanel->setImage(_backgrounds->at(index));
    }
}

//@Override
/*protected*/ void IconItemPanel::updateBackground0(BufferedImage* im) {
    _backgrounds->replace(0, im);
}

/**
* Plain icons have only one family, usually named "set"
* Override for plain icon & background and put all icons here
*/
/*protected*/ void IconItemPanel::initIconFamiliesPanel()
{
 if (_iconPanel == nullptr) { // create a new one
     _iconPanel = new ImagePanel();
//     _iconPanel.setBorder(BorderFactory.createLineBorder(Color.black));
     thisLayout->addWidget((QWidget*)makePreviewPanel(_iconPanel, nullptr)/*, 1*/);
//     _iconPanel->addMouseListener(new IconListener());
 }

 QMap<QString, QMap<QString, NamedIcon*>*>* families = ItemPalette::getFamilyMaps(_itemType);
 if (families != nullptr && families->size() > 0) {
     if (families->size() != 1) {
         log->warn(tr("ItemType \"%1\" has %2").arg(_itemType).arg(families->size()));
     }
     QStringListIterator iter(families->keys());
     while (iter.hasNext()) {
         QString family = iter.next();
         _iconMap = families->value(family);
         addIconsToPanel(_iconMap);
     }
 } else {
     // make create message
     log->error(tr("Item type \"%1\" has %2 families.").arg(_itemType).arg((families == nullptr ? "null" : QString::number(families->size()))));
 }
}

/**
*  Note caller must create _iconPanel before calling
*/
/*protected*/ void IconItemPanel::addIconsToPanel(QMap<QString, NamedIcon*>* iconMap)
{
 _iconPanel = new ImagePanel();
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

//@Override
/*protected*/ void IconItemPanel::setEditor(Editor* ed) {
    ItemPanel::setEditor(ed);
    if (_initialized) {
        addIconsToPanel(_iconMap);
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
/*public*/ void IconItemPanel::makeBottomPanel(ActionListener* doneAction) {
 QWidget* bottomPanel = new QWidget();
 bottomPanel->setLayout(new FlowLayout());

 _catalogButton = new QPushButton(tr("Show Catalog"));
// _catalogButton.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent a) {
//         if (_catalog.isVisible()) {
//             hideCatalog();
//         } else {
//             showCatalog();
//         }
//     }
// });
 _catalogButton->setToolTip(tr("Open the Icon Catalog and drag icons from there to the Panel"));
 bottomPanel->layout()->addWidget(_catalogButton);
 connect(_catalogButton, SIGNAL(clicked(bool)), this, SLOT(on_catalogButton_clicked()));

 if (doneAction == nullptr) {
     QPushButton* renameButton = new QPushButton(tr("Rename Icon"));
//     renameButton.addActionListener(new ActionListener() {
//         @Override
//         public void actionPerformed(ActionEvent a) {
//             renameIcon();
//         }
//     });
     connect(renameButton, SIGNAL(clicked(bool)), this, SLOT(renameIcon()));
     bottomPanel->layout()->addWidget(renameButton);

     QPushButton* addIconButton = new QPushButton(tr("Add Icon"));
//     addIconButton.addActionListener(new ActionListener() {
//         @Override
//         public void actionPerformed(ActionEvent a) {
//             addNewIcon();
//         }
//     });
     connect(addIconButton, SIGNAL(clicked(bool)), this, SLOT(addNewIcon()));
     addIconButton->setToolTip(tr("Add another icon to your Icon Set. Enter a name for it."));
     bottomPanel->layout()->addWidget(addIconButton);

     _deleteIconButton = new QPushButton(tr("Delete Icon"));
     //     _deleteIconButton.addActionListener(new ActionListener() {
     //         @Override
     //         public void actionPerformed(ActionEvent a) {
     //             deleteIcon();
     //         }
     //     });
     connect(_deleteIconButton, SIGNAL(clicked(bool)), this, SLOT(deleteIcon()));
     _deleteIconButton->setToolTip(tr("Delete an icon from your Icon Set. Select the icon to be deleted."));
     bottomPanel->layout()->addWidget(_deleteIconButton);
     _deleteIconButton->setEnabled(false);
 } else {
     QPushButton* updateButton = new QPushButton(tr("Update")); // custom update label
     //updateButton.addActionListener(doneAction);
     connect(updateButton, SIGNAL(clicked(bool)), doneAction, SLOT(actionPerformed(/*ActionEvent**/)));
     bottomPanel->layout()->addWidget(updateButton);
 }
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
  showCatalog();
 }
// repaint();
}

void IconItemPanel::hideCatalog() {
 QSize oldDim = size();
 bool isPalette = (qobject_cast<ItemPalette*>(_paletteFrame ));
 QSize totalDim;
 if (isPalette) {
     totalDim = ItemPalette::_tabPane->size();
 } else {
     totalDim = _paletteFrame->size();
 }
 _catalog->setVisible(false);
 _catalog->update();
 reSizeDisplay(isPalette, oldDim, totalDim);
 _catalogButton->setText(tr("Show Catalog"));
}

void IconItemPanel::showCatalog() {
    QSize oldDim = size();
    bool isPalette = (qobject_cast<ItemPalette*>(_paletteFrame));
    QSize totalDim;
    if (isPalette) {
        totalDim = ItemPalette::_tabPane->size();
    } else {
        totalDim = _paletteFrame->size();
    }
//        _catalog.setWidth(oldDim.width);
    _catalog->setVisible(true);
    _catalog->update();
    reSizeDisplay(isPalette, oldDim, totalDim);
    _catalogButton->setText(tr("Hide Catalog"));
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
 if (_selectedIcon == nullptr) {
     JOptionPane::showMessageDialog(_paletteFrame, tr("Select an Icon to rename or delete it."),
             tr("Reminder"), JOptionPane::INFORMATION_MESSAGE);
     return;
 }
 _iconMap->remove(_selectedIcon->getIconName());
 addIconsToPanel(_iconMap);
 _deleteIconButton->setEnabled(false);
 _selectedIcon = nullptr;
 update();
}

/*private*/ void IconItemPanel::renameIcon() {
        if (_selectedIcon != nullptr) {
            QString name = JOptionPane::showInputDialog(_paletteFrame, tr("Please enter a name for the Icon:"),
                    tr("Question"), JOptionPane::QUESTION_MESSAGE);
            if (name != "") {
                _iconMap->remove(_selectedIcon->_borderName);
                putIcon(name, _selectedIcon->getIcon());
                _deleteIconButton->setEnabled(false);
                deselectIcon();
            }
        } else {
            JOptionPane::showMessageDialog(_paletteFrame, tr("Select an Icon to rename or delete it."),
                    tr("Reminder"), JOptionPane::INFORMATION_MESSAGE);
        }
    }

/*protected*/ void IconItemPanel::setSelection(IconDisplayPanel* panel) {
        if (_selectedIcon != nullptr && panel != (_selectedIcon)) {
            deselectIcon();
            setDeleteIconButton(false);
        }
        if (panel->_borderName != "") {
//            panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.red, 2), panel._borderName));
            _selectedIcon = panel;
            _catalog->deselectIcon();
            setDeleteIconButton(true);
        } else {    // click not on an "icon"
            _selectedIcon = nullptr;
            setDeleteIconButton(false);
        }
    }

    /*public*/ void IconItemPanel::deselectIcon() {
        if (_selectedIcon != nullptr) {
//            _selectedIcon.setBorder(BorderFactory.createTitledBorder(
//                    BorderFactory.createLineBorder(QColor(Qt::black) 1), _selectedIcon->getIconName()))
            _selectedIcon = nullptr;
        }
    }

/*private*/ void IconItemPanel::setDeleteIconButton(bool set) {
    if (!_update) {
        _deleteIconButton->setEnabled(set);
    }
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
/*public*/ QByteArray IconDragJLabel::mimeData()
{
 QByteArray xmldata;
 QString url = ((NamedIcon*)getIcon())->getURL();
 PositionableLabel* l = new PositionableLabel(NamedIcon::getIconByName(url), /*_editor*/(Editor*)parent->_editor);
 l->setPopupUtility(NULL);        // no text
 l->setLevel(level);
 _dataFlavor = new DataFlavor(l, "PositionableLabel");
// _dataFlavor->setMimeTypeParameter("family", parent->_family);
 PositionableLabelXml* xml = new PositionableLabelXml();
 QDomElement e = xml->store((QObject*)l);
 xml->doc.appendChild(e);
 xmldata.append(xml->doc.toString());
 return xmldata;
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
//public class IconDisplayPanel extends JPanel implements MouseListener{
//        String _borderName;
//        NamedIcon _icon;

        /*public*/ IconDisplayPanel::IconDisplayPanel(QString borderName, NamedIcon* icon, IconItemPanel *iconItemPanel) {
            //super();
 this->iconItemPanel = iconItemPanel;
            _borderName = borderName;
            _icon = icon;
            setLayout(new QVBoxLayout()); //(this, BoxLayout.Y_AXIS));
//            setOpaque(false);
            if (borderName != "") {
                setBorderAndIcon(icon);
            }
//            addMouseListener(new IconListener());
        }

        QString IconDisplayPanel::getBorderName() {
            return _borderName;
        }

        NamedIcon* IconDisplayPanel::getIcon() {
            return _icon;
        }

        void IconDisplayPanel::setBorderAndIcon(NamedIcon* icon) {
            if (icon == nullptr) {
                iconItemPanel->log->error(tr("IconDisplayPanel: No icon for \"%1\"").arg( _borderName));
                return;
            }
            try {
                JLabel* image;
                if (iconItemPanel->_update) {
                    image = new JLabel();
                } else {
                    image = (JLabel*)new IconDragJLabel(new DataFlavor(Editor::POSITIONABLE_FLAVOR), iconItemPanel->_level, nullptr);
                }
//                image.setOpaque(false);
                image->setName(_borderName);
                image->setToolTip(icon->getName());
                double scale;
                if (icon->getIconWidth() < 1 || icon->getIconHeight() < 1) {
                    image->setText(tr("invisible Icon"));
// TODO:                    image->setForeground(QColor(Qt::lightGray));
                    scale = 0;
                } else {
                    scale = icon->reduceTo(CatalogPanel::ICON_WIDTH, CatalogPanel::ICON_HEIGHT, CatalogPanel::ICON_SCALE);
                }
                image->setIcon(icon);
//                image.addMouseListener(this);
                QWidget* iPanel = new QWidget();
                iPanel->setLayout(new QHBoxLayout());
//                iPanel.setOpaque(false);
                iPanel->layout()->addWidget(image);
                layout()->addWidget(iPanel);

                QString scaleMessage = tr("scale %1").arg(CatalogPanel::printDbl(scale, 2));
                JLabel* label = new JLabel(scaleMessage);
                JPanel* sPanel = new JPanel();
                sPanel->setLayout(new QHBoxLayout());
//                sPanel.setOpaque(false);
                sPanel->layout()->addWidget(label);
                layout()->addWidget(sPanel);
#if 0
                QFontMetrics fm = getFontMetrics(getFont());
                setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black), _borderName));
                int width = fm.stringWidth(_borderName) + 10;
                width = Math.max(fm.stringWidth(scaleMessage), Math.max(width, CatalogPanel.ICON_WIDTH+10));
                int height = getPreferredSize().height;
                setPreferredSize(new Dimension(width, height));
#endif
            } catch (ClassNotFoundException cnfe) {
                iconItemPanel->log->error(tr("Unable to find class supporting %1").arg( Editor::POSITIONABLE_FLAVOR +  cnfe.getMessage()));
            }
        }

        /*public*/ QString IconDisplayPanel::getIconName() {
            return _borderName;
        }
        //@Override
        /*public*/ void IconDisplayPanel::mouseClicked(QMouseEvent* event) {
#if 0
            if (event.getSource() instanceof JLabel) {
                setSelection(this);
            } else if (event.getSource() instanceof IconDisplayPanel) {
                IconDisplayPanel panel = (IconDisplayPanel)event.getSource();
                setSelection(panel);
            }
#endif
        }
        //@Override
        /*public*/ void IconDisplayPanel::mousePressed(QMouseEvent* event) {
        }
        //@Override
        /*public*/ void IconDisplayPanel::mouseReleased(QMouseEvent* event) {
        }
        //@Override
        /*public*/ void IconDisplayPanel::mouseEntered(QMouseEvent* event) {
        }
        //@Override
        /*public*/ void IconDisplayPanel::mouseExited(QMouseEvent* event) {
        }
//    }
  #if 0
    class IconListener implements MouseListener {
        @Override
        public void mouseClicked(MouseEvent event) {
            if (event.getSource() instanceof IconDisplayPanel) {
                IconDisplayPanel panel = (IconDisplayPanel)event.getSource();
                setSelection(panel);
            } else if(event.getSource() instanceof ImagePanel) {
                deselectIcon();
           }
        }
        @Override
        public void mousePressed(MouseEvent event) {
        }
        @Override
        public void mouseReleased(MouseEvent event) {
        }
        @Override
        public void mouseEntered(MouseEvent event) {
        }
        @Override
        public void mouseExited(MouseEvent event) {
        }
    }
#endif
//};
    /*private*/ /*final*/ /*static*/ Logger* IconItemPanel::log = LoggerFactory::getLogger("IconItemPanel");
