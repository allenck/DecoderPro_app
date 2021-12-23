#include "clockitempanel.h"
#include <QVBoxLayout>
#include "itempalette.h"
#include <QLabel>
#include "namedicon.h"
#include "exceptions.h"
#include "dragjlabel.h"
#include "analogclock2display.h"
#include "editor.h"
#include "dataflavor.h"
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDrag>
#include <QMimeData>
#include "borderlayout.h"
#include "box.h"
#include "borderfactory.h"
#include "positionablelabelxml.h"
#include "analogclock2displayxml.h"

//ClockItemPanel::ClockItemPanel(QWidget *parent) :
//    IconItemPanel(parent)
//{
//}
/**
*  ItemPanel for for plain icons and backgrounds
*/
// /*public*/ class ClockItemPanel extends IconItemPanel {


/**
 * Constructor for plain icons and backgrounds
 */
/*public*/ ClockItemPanel::ClockItemPanel(DisplayFrame* parentFrame, QString type, Editor *editor, QWidget *parent)
 : IconItemPanel(parentFrame, type, editor, parent)
{
 //super(parentFrame,  type, family, editor);
 setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
 setObjectName("ClockItemPanel");
}

/*protected*/ JPanel* ClockItemPanel::instructions(bool)
{
 JPanel* blurb = new JPanel();
 QVBoxLayout* blurbLayout;
 blurb->setLayout(blurbLayout = new QVBoxLayout());//(blurb, BoxLayout.Y_AXIS));
 blurbLayout->addWidget(Box::createVerticalStrut(ItemPalette::STRUT_SIZE));
 blurbLayout->addWidget(new QLabel(tr("Drag the icon below to add a %1 to your Control Panel.").arg( tr("FastClock"))));
 blurbLayout->addWidget(Box::createVerticalStrut(ItemPalette::STRUT_SIZE));
 JPanel* panel = new JPanel();
 QHBoxLayout* panelLayout = new QHBoxLayout(panel);
 panelLayout->addWidget(blurb);
 return panel;
}

/*protected*/ void ClockItemPanel::addIconsToPanel(QMap<QString, NamedIcon*>* iconMap)
{
 _iconPanel = new ImagePanel();
 _iconPanel->setLayout(new QHBoxLayout());
 QMapIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext())
 {
  /*Entry<String, NamedIcon> entry =*/ it.next();
  NamedIcon* icon = new NamedIcon(it.value());    // make copy for possible reduction
  JPanel* panel = new JPanel(new FlowLayout());
  QString borderName = ItemPalette::convertText(it.key());
  panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
          borderName));

  try {
      DragJLabel* label = new ClockDragJLabel(new DataFlavor(Editor::POSITIONABLE_FLAVOR),this);
      if (icon->getIconWidth() < 1 || icon->getIconHeight() < 1) {
          label->setText(tr("invisible Icon"));
          label->setForeground(Qt::lightGray);
      } else {
          icon->reduceTo(100, 100, 0.2);
      }
      //label->setIcon(icon);
      label->icon = icon;
      ((JLabel*)label)->setIcon(icon);
      label->setName(borderName);
      panel->layout()->addWidget(label);
  } catch (ClassNotFoundException* cnfe) {
//         cnfe.printStackTrace();
  }
  _iconPanel->layout()->addWidget(panel);
 }
 thisLayout->insertWidget(1, _iconPanel);
}

void ClockItemPanel::sceneClicked(QGraphicsSceneMouseEvent *)
{
 QDrag *dr = new QDrag(this);
 QMimeData *data = new QMimeData;
 data->setText("null;AnalogClock2Display");
    // Assign ownership of the QMimeData object to the QDrag object.
 dr->setMimeData(data);
 dr->start();
}

/**
*  SOUTH Panel
*/
/*public*/ void ClockItemPanel::initButtonPanel() {
}

// /*public*/ class ClockDragJLabel extends DragJLabel {

/*public*/ ClockDragJLabel::ClockDragJLabel(DataFlavor* flavor, QWidget* parent) : DragJLabel(flavor, parent) {
        //super(flavor);
    log = new Logger("ClockDragJLabel");
    this->panel = (ClockItemPanel*)parent;
    }
/*public*/ QObject* ClockDragJLabel::getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) {
    if (!isDataFlavorSupported(flavor)) {
        return NULL;
    }
//        QString url = ((NamedIcon*)getIcon())->getURL();
//        if (log->isDebugEnabled()) log->debug("DragJLabel.getTransferData url= "+url);
    AnalogClock2Display* c;
    QString link = ((ClockItemPanel*)parent())->_linkName->text().trimmed();
    if (link.length() == 0) {
        c = new AnalogClock2Display(((ClockItemPanel*)parent())->_editor);
    } else {
        c = new AnalogClock2Display(((ClockItemPanel*)parent())->_editor, link);
    }
    c->setOpaque(false);
    c->update();
    c->setLevel(Editor::CLOCK);
    return c;
}
//};

/*public*/ QByteArray ClockDragJLabel::mimeData()
{
 QByteArray xmldata;
 QString url = ((NamedIcon*)getIcon())->getURL();
 AnalogClock2Display* l = new AnalogClock2Display(panel->_editor);
 l->setPopupUtility(NULL);        // no text
 l->setLevel(Editor::CLOCK);
 _dataFlavor = new DataFlavor(l, "PositionableLabel");
// _dataFlavor->setMimeTypeParameter("family", parent->_family);
 AnalogClock2DisplayXml* xml = new AnalogClock2DisplayXml();
 QDomElement e = xml->store((QObject*)l);
 xml->doc.appendChild(e);
 xmldata.append(xml->doc.toString());
 return xmldata;
}
