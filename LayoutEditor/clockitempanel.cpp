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
/*public*/ ClockItemPanel::ClockItemPanel(JmriJFrame* parentFrame, QString type, QString family, Editor* editor, QWidget *parent) : IconItemPanel(parentFrame, type, family,editor,parent)
{
 //super(parentFrame,  type, family, editor);
 setToolTip(tr("Drag an icon from this panel to add it to the control panel"));
}

/*protected*/ QWidget* ClockItemPanel::instructions()
{
 //QWidget* blurb = new QWidget();
 QVBoxLayout* blurbLayout = new QVBoxLayout;
 //blurb->setLayout(new QVBoxLayout(blurb/*, BoxLayout.Y_AXIS*/));
    //blurb.add(Box.createVerticalStrut(ItemPalette.STRUT_SIZE));
 blurbLayout->addStrut(ItemPalette::STRUT_SIZE);
    blurbLayout->addWidget(new QLabel(tr("Drag the icon below to add a fast clock to your control panel.")));
    //blurb.add(Box.createVerticalStrut(ItemPalette.STRUT_SIZE));
 blurbLayout->addStrut(ItemPalette::STRUT_SIZE);
 QWidget* panel = new QWidget();
 //panel->setLayout(new QVBoxLayout);
 //panel->layout()->addWidget(blurb);
 panel->setLayout(blurbLayout);
 return panel;
}

/*protected*/ void ClockItemPanel::addIconsToPanel(QHash<QString, NamedIcon*>* iconMap)
{
 _iconPanel = new QWidget();
 _iconPanel->setLayout(new QHBoxLayout);
 //Iterator<Entry<String, NamedIcon*>> it = iconMap.entrySet().iterator();
 QHashIterator<QString, NamedIcon*> it(*iconMap);
 while (it.hasNext())
 {
  //Entry<String, NamedIcon> entry = it.next();
  it.next();
  NamedIcon* icon = new NamedIcon(it.value());    // make copy for possible reduction
  QGroupBox* panel = new QGroupBox();
  panel->setLayout(new QHBoxLayout);
  QString     gbStyleSheet = "QGroupBox { border: 2px solid gray; border-radius: 3px;} QGroupBox::title { /*background-color: transparent;*/  subcontrol-position: top left; /* position at the top left*/  padding:0 0px;} ";

  QString borderName = ItemPalette::convertText(it.key());
  //panel.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black),
  //                                                 borderName));
  panel->setTitle(borderName);
  panel->setStyleSheet(gbStyleSheet);
  EditScene* scene = new EditScene(QRectF(0,0,200,200));
  connect(scene, SIGNAL(sceneMouseRelease(QGraphicsSceneMouseEvent*)), this,SLOT(sceneClicked(QGraphicsSceneMouseEvent*)));
  QGraphicsView* view = new QGraphicsView(scene);

  try
  {
   //JLabel* label = new ClockDragJLabel(new DataFlavor(Editor::POSITIONABLE_FLAVOR),this);
   JLabel* label = new AnalogClock2Display((Editor*)parent());
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
        AnalogClock2Display* c = new AnalogClock2Display((Editor*)parent());
        c->setOpaque(false);
        c->update();
        c->setLevel(Editor::CLOCK);
        return c;
    }
//};

