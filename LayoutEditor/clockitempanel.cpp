#include "clockitempanel.h"
#include <QVBoxLayout>
#include "itempalette.h"
#include <QGroupBox>
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
/*public*/ ClockItemPanel::ClockItemPanel(DisplayFrame* parentFrame, QString type, Editor* editor, QWidget *parent) : IconItemPanel(parentFrame, type, editor,parent)
{
 //super(parentFrame,  type, family, editor);
 setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
 setObjectName("ClockItemPanel");
}

/*protected*/ QWidget* ClockItemPanel::instructions()
{
 QWidget* blurb = new QWidget();
 QVBoxLayout* blurbLayout;
 blurb->setLayout(blurbLayout = new QVBoxLayout());//(blurb, BoxLayout.Y_AXIS));
 blurbLayout->addWidget(Box::createVerticalStrut(ItemPalette::STRUT_SIZE));
 blurbLayout->addWidget(new QLabel(tr("Drag the icon below to add a %1 to your Control Panel.").arg( tr("FastClock"))));
 blurbLayout->addWidget(Box::createVerticalStrut(ItemPalette::STRUT_SIZE));
 QWidget* panel = new QWidget();
 QHBoxLayout* panelLayout = new QHBoxLayout(panel);
 panelLayout->addWidget(blurb);
 return panel;
}

/*protected*/ void ClockItemPanel::addIconsToPanel(QHash<QString, NamedIcon*>* iconMap)
{
 if (_iconPanel == nullptr) {
     _iconPanel = new ImagePanel();
     _iconPanel->setBorder(BorderFactory::createLineBorder(Qt::black));
 } else {
     //_iconPanel.removeAll();
  QObjectList ol = _iconPanel->layout()->children();
  foreach(QObject* obj, ol)
  {
   if(qobject_cast<QWidget*>(obj))
    _iconPanel->layout()->removeWidget(qobject_cast<QWidget*>(obj));
//   if(qobject_cast<QLayout*>(obj))
//    delete obj;
  }
 }
// _iconPanel->setLayout(new QHBoxLayout);
 //Iterator<Entry<String, NamedIcon*>> it = iconMap.entrySet().iterator();
 QHashIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext())
 {
  //Entry<String, NamedIcon> entry = it.next();
  it.next();
  NamedIcon* icon = new NamedIcon(it.value());    // make copy for possible reduction
  JPanel* panel = new JPanel();
  panel->setLayout(new QHBoxLayout);
  QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

  QString borderName = ItemPalette::convertText(it.key());
  panel->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black),
                                                   borderName));
  //panel->setTitle(borderName);
  panel->setStyleSheet(gbStyleSheet);
  EditScene* scene = new EditScene(QRectF(0,0,200,200));
  connect(scene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this,SLOT(sceneClicked(QGraphicsSceneMouseEvent*)));
  QGraphicsView* view = new QGraphicsView(scene);

  try
  {
   ClockDragJLabel* label = new ClockDragJLabel(new DataFlavor(Editor::POSITIONABLE_FLAVOR),this);
   //JLabel* label = new JLabel("to be implemented"); //new AnalogClock2Display((Editor*)parent());
   ((AnalogClock2Display*)label)->setOpaque(false);
   ((AnalogClock2Display*)label)->update();
   ((AnalogClock2Display*)label)->setLevel(Editor::CLOCK);
   ((AnalogClock2Display*)label)->setLocation(0,0);

//   if (icon->getIconWidth()<1 || icon->getIconHeight()<1)
//   {
//    label->setText(tr("invisible Icon"));
//               //label->setForeground(QColor(Qt::lightGray));
//   }
//   else
//   {
//    icon->reduceTo(100, 100, 0.2);
//   }
//   label->setIcon(icon);
   label->setName(borderName);
   scene->setSceneRect(0, 0, ((AnalogClock2Display*)label)->getFaceWidth(), ((AnalogClock2Display*)label)->getFaceHeight());
   ((AnalogClock2Display*)label)->paint(scene);
   ((QBoxLayout*)panel->layout())->addWidget(view,0,Qt::AlignCenter);
  }
  catch (ClassNotFoundException cnfe) {
           //cnfe.printStackTrace();
  }
  _iconPanel->layout()->addWidget(panel);
 }
 layout()->addWidget(_iconPanel/*, 1*/);
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

