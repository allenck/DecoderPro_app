#include "multisensoriconframe.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "multiiconeditor.h"
#include "multisensoricon.h"
#include "editor.h"
#include "jtextfield.h"
#include "layouteditor.h"
#include "catalogtreemodel.h"

//MultiSensorIconFrame::MultiSensorIconFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * Provides a simple editor for creating a MultiSensorIcon object
 * <p>
 * To work right, the MultiSensorIcon needs to have all
 * images the same size, but this is not enforced here.
 * It should be.
 *
 * @author  Bob Jacobsen  Copyright (c) 2007
 * @version $Revision: 18255 $
 */

///*public*/ class MultiSensorIconFrame extends JmriJFrame {


MultiSensorIconFrame::MultiSensorIconFrame(LayoutEditor* p, QWidget *parent) : JmriJFrame(tr("Enter MultiSensor"),true,parent)
{
 //super("Enter MultiSensor");
 content = new QWidget();
 updown = new QRadioButton("Up - Down");
 rightleft = new QRadioButton("Right - Left");
 group = new QButtonGroup();

 layoutEditor = p;

 addHelpMenu("package.jmri.jmrit.display.MultiSensorIconFrame", true);
}

/*public*/ void MultiSensorIconFrame::initComponents()
{
 JmriJFrame::initComponents();

 //this.getContentPane().setLayout(new BoxLayout(this.getContentPane(), BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget();
 centralWidget->setLayout(new QVBoxLayout());
 setCentralWidget(centralWidget);

 QWidget* p = new QWidget();
 p->setLayout(new QHBoxLayout(p/*, BoxLayout.X_AXIS*/));
 p->layout()->addWidget(new QLabel(tr("Icon checks click: ")));
 group->addButton(updown);
 group->addButton(rightleft);
 rightleft->setChecked(true);
 p->layout()->addWidget(rightleft);
 p->layout()->addWidget(updown);
 centralWidget->layout()->addWidget(p);

 centralWidget->layout()->addWidget(content);
 content->setLayout(new QVBoxLayout(content/*, BoxLayout.Y_AXIS*/));
 // start with three Entrys; there's no reason to have less
 content->layout()->addWidget(new Entry(content, this, "program:resources/icons/USS/plate/levers/l-left.gif"));
 content->layout()->addWidget(new Entry(content, this, "program:resources/icons/USS/plate/levers/l-vertical.gif"));
 content->layout()->addWidget(new Entry(content, this, "program:resources/icons/USS/plate/levers/l-right.gif"));

//    centralWidget->layout()->addWIdget(new JSeparator());
 QPushButton* b = new QPushButton(tr("Add Additional Sensor to Icon"));
//    ActionListener a = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            // remove this entry
//            self->layout()->addWidget(new Entry(self, frame, "resources/icons/USSpanels/Plates/lever-v.gif"));
//            frame.pack();
//        }
//        JPanel self;
//        JmriJFrame frame;
//        ActionListener init(JPanel self, JmriJFrame frame) {
//            this.frame = frame;
//            this.self = self;
//            return this;
//        }
//    }.init(content, this);
 AddSensorActionListener* a = new AddSensorActionListener();
 a->init(content, this);
 connect(b, SIGNAL(clicked()), a, SLOT(actionPerformed()));

//    b->layout()->addWidgetActionListener(a);
 this->centralWidget()->layout()->addWidget(b);

//    this.getContentPane()->layout()->addWidget(new JSeparator());
 b = new QPushButton(tr("Set icons for inactive, ..."));
 defaultIcons = new MultiIconEditor(3);
 defaultIcons->setIcon(0, "Unknown:","program:resources/icons/USS/plate/levers/l-inactive.gif");
 defaultIcons->setIcon(1, "Inconsistent:","program:resources/icons/USS/plate/levers/l-unknown.gif");
 defaultIcons->setIcon(2, "Inactive:","program:resources/icons/USS/plate/levers/l-inconsistent.gif");
 defaultIcons->complete();
 //defaultIcons->catalog()->model->setFilter(QDir::AllDirs | QDir::Files);

 defaultsFrame = new JmriJFrameX("", false, true);
 if(defaultsFrame->centralWidget() == NULL)
 {
  QWidget* cw = new QWidget();
  cw-> setLayout(new QVBoxLayout());
  defaultsFrame->setCentralWidget(cw);
 }
 defaultsFrame->centralWidget()->layout()->addWidget(new QLabel(tr("  Select new file, then click on icon to change  ")/*,BorderLayout.NORTH*/));
 defaultsFrame->centralWidget()->layout()->addWidget(defaultIcons);
 defaultsFrame->pack();
 defaultsFrame->addHelpMenu("package.jmri.jmrit.display.MultiSensorIconDefaultsFrame", true);
//    b->addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent a){
//            defaultsFrame.setVisible(true);
//        }
//    });
 connect(b, SIGNAL(clicked()), this, SLOT(on_setIcons()));
 this->centralWidget()->layout()->addWidget(b);

//    this.getContentPane()->layout()->addWidget(new JSeparator());
    b = new QPushButton(tr("Create and Add Icon To Panel"));
//    b->addActionListener(new ActionListener(){
//        /*public*/ void actionPerformed(ActionEvent a){
//            make();
//            removeWindows();
//        }
//    });
    connect(b, SIGNAL(clicked()), this, SLOT(on_createAndAdd()));
    this->centralWidget()->layout()->addWidget(b);

}
void MultiSensorIconFrame::on_addSensor()
{
 //defaultIcons->catalog()->model->setFilter(QDir::AllDirs | QDir::Files);
 defaultsFrame->setVisible(true);
}
void MultiSensorIconFrame::on_setIcons()
{
 //defaultIcons->catalog()->model->setFilter(QDir::AllDirs | QDir::Files);
 defaultsFrame->setVisible(true);
}
AddSensorActionListener* AddSensorActionListener::init(QWidget *self, JmriJFrame *frame)
{
 this->frame = frame;
 this->self = self;
 return this;
}

void AddSensorActionListener::actionPerformed()
{
// add this entry
self->layout()->addWidget(new Entry(self, frame, "resources/icons/USSpanels/Plates/lever-v.gif"));
frame->adjustSize();
}
void MultiSensorIconFrame::on_createAndAdd()
{
 make();
 removeWindows();
}

// Remove an Entry from the panel,
// and therefore from the eventual sensor
void MultiSensorIconFrame::remove(Entry* e)
{
 content->layout()->removeWidget(e);
 this->adjustSize();
}

void MultiSensorIconFrame::make()
{
 MultiSensorIcon* m = new MultiSensorIcon(layoutEditor);
 m->setUnknownIcon(defaultIcons->getIcon(0));
 m->setInconsistentIcon(defaultIcons->getIcon(1));
 m->setInactiveIcon(defaultIcons->getIcon(2));

 //for (int i = 0; i< content->getComponentCount(); i++)
 for(int i =0; i < content->layout()->children().count(); i++)
 {
  //Entry* e = (Entry*)content->getComponent(i);
  Entry* e = (Entry*)content->layout()->children().at(i);
  m->addEntry(e->sensor->text(), e->ed->getIcon(0));
 }
 m->setUpDown(updown->isChecked());
 m->setDisplayLevel(Editor::SENSORS);

 layoutEditor->addMultiSensor(m);

}

void MultiSensorIconFrame::removeWindows()
{
 for (int i = 0; i<content->layout()->children().count(); i++) \
 {
     ((Entry*)content->layout()->children().at(i))->dispose();
 }
 defaultsFrame->dispose();
 JmriJFrame::dispose();
}

//class Entry extends JPanel {


/*public*/ QString Entry::toString() {
    return ed->getIcon(0)->toString();
}

Entry::Entry(QWidget* self, JmriJFrame* frame, QString name)
{
 sensor = new JTextField(5);
 ed = new MultiIconEditor(1);
 edf = new JmriJFrameX("", false, true);
 if(edf->centralWidget() == NULL)
 {
  QWidget* cw = new QWidget();
  cw-> setLayout(new QVBoxLayout());
  edf->setCentralWidget(cw);
 }

 this->self = self;
 this->setLayout(new QHBoxLayout());
 this->layout()->addWidget(new QLabel(tr("Sensor:")));
 this->layout()->addWidget(sensor);

 ed->setIcon(0, "Active:", name);
 ed->complete();
 edf->centralWidget()->layout()->addWidget(new QLabel(tr("  Select new file, then click on icon to change  "))/*,BorderLayout.NORTH*/);
 edf->centralWidget()->layout()->addWidget(ed);
 edf->pack();

 QPushButton* b = new QPushButton(tr("Set Icon..."));
//    b->layout()->addWIdgetActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            edf.setVisible(true);
//        }
//    });
 connect(b, SIGNAL(clicked()), this, SLOT(on_setIcon()));
 this->layout()->addWidget(b);

 // button to remove this entry from it's parent
 b = new QPushButton(tr("Delete"));
//    ActionListener a = new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent a) {
//            // remove this entry
//            self.remove(entry);
//            frame.pack();
//        }
//        Entry entry;
//        JPanel self;
//        JmriJFrame frame;
//        ActionListener init(Entry entry, JPanel self, JmriJFrame frame) {
//            this.entry = entry;
//            this.self = self;
//            this.frame = frame;
//            return this;
//        }
//    }.init(this, self, frame);
//    b->addActionListener(a);
 MSIFDeleteActionListener* a = new MSIFDeleteActionListener();

 connect(b, SIGNAL(clicked()), a, SLOT(actionPerformed()));
 a->init(this, self, frame);
 this->layout()->addWidget(b);
}
void Entry::on_setIcon()
{
 edf->setVisible(true);
}

MSIFDeleteActionListener* MSIFDeleteActionListener::init(Entry *entry, QWidget *self, JmriJFrame *frame)
{
 this->entry = entry;
 this->self = self;
 this->frame = frame;
 return this;
}

void MSIFDeleteActionListener::actionPerformed()
{
 // remove this entry
 self->layout()->removeWidget(entry);
 entry->~Entry();
 frame->adjustSize();
}
Entry::~Entry()
{
 dispose();
}

/*public*/ void Entry::dispose() {
    edf->dispose();
}

//}
/*public*/ QString MultiSensorIconFrame::getClassName()
{
 return "jmri.jmrit.display.layouEditor.MultiSensorIconFrame";
}
