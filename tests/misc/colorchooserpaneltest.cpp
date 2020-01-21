#include "colorchooserpaneltest.h"
#include "junitutil.h"
#include "colorchooserpanel.h"
#include "colormodel.h"
#include "assert1.h"
#include "jmrijframe.h"
#include <QBoxLayout>
#include "colorpanel.h"
#include "defaultswatchchooserpanel.h"
#include "splitbuttoncolorchooserpanel.h"
#include "jcolorchooser.h"
#include "defaultcolorselectionmodel.h"
ColorChooserPanelTest::ColorChooserPanelTest(QObject *parent) : QObject(parent)
{

}
/*public*/ void ColorChooserPanelTest::testCtor()
{
 JColorChooser* p = new JColorChooser(QColor(Qt::red));
 QVector<AbstractColorChooserPanel*> txtColorPanels = QVector<AbstractColorChooserPanel*>()
   << (new SplitButtonColorChooserPanel())
   << (new DefaultSwatchChooserPanel())
   << (new ColorChooserPanel());
 p->setChooserPanels(&txtColorPanels);
// ColorPanel* p = new ColorPanel(new ColorModel());
// p->buildPanel();
// ColorChooserPanel* p = new ColorChooserPanel(/*new ColorModel()*/);
// p->buildChooser();
 JmriJFrame* f = new JmriJFrameX("ColorChooserPanelTest");
 QWidget* centralWidget = f->getContentPane(false);
 QVBoxLayout* l = new QVBoxLayout();
 centralWidget->setLayout(l);
 l->addWidget(p);
 f->show();
 f->pack();
 Assert::assertNotNull("color chooser panel", p, __FILE__, __LINE__);
 //Assert::assertNull("color chooser panel", p, __FILE__, __LINE__);
}

//@Before
/*public*/ void ColorChooserPanelTest::setUp() {
    JUnitUtil::setUp();
}

//@After
/*public*/ void ColorChooserPanelTest::tearDown() {
    JUnitUtil::tearDown();
}
