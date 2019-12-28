#include "colorchooserpaneltest.h"
#include "junitutil.h"
#include "colorchooserpanel.h"
#include "colormodel.h"
#include "assert1.h"
#include "jmrijframe.h"
#include <QBoxLayout>
#include "colorpanel.h"

ColorChooserPanelTest::ColorChooserPanelTest(QObject *parent) : QObject(parent)
{

}
/*public*/ void ColorChooserPanelTest::testCtor()
{
 ColorChooserPanel* p = new ColorChooserPanel(new ColorModel());
 p->buildChooser();
// ColorPanel* p = new ColorPanel(new ColorModel());
// p->buildPanel();
 JmriJFrame* f = new JmriJFrame();
 QWidget* centralWidget = f->getContentPane(false);
 QVBoxLayout* l = new QVBoxLayout(centralWidget);
 l->addWidget(p);
 f->show();
 f->pack();
 Assert::assertNotNull("color chooser panel", p, __FILE__, __LINE__);
 Assert::assertNull("color chooser panel", p, __FILE__, __LINE__);
}

//@Before
/*public*/ void ColorChooserPanelTest::setUp() {
    JUnitUtil::setUp();
}

//@After
/*public*/ void ColorChooserPanelTest::tearDown() {
    JUnitUtil::tearDown();
}
