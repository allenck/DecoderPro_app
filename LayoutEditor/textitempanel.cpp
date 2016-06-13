#include "textitempanel.h"
#include "decoratorpanel.h"
#include "itempalette.h"
#include <QVBoxLayout>
#include "flowlayout.h"

//TextItemPanel::TextItemPanel(QWidget *parent) :
//    ItemPanel(parent)
//{
//}
/**
*  ItemPanel for text labels
*/
///*public*/ class TextItemPanel extends ItemPanel /*implements ActionListener */{

//    JTextField _text;

/*public*/ TextItemPanel::TextItemPanel(ItemPalette* parentFrame, QString  type, QString family, Editor* editor, QWidget *parent) : ItemPanel(parentFrame, type, family,editor,parent) {
        //super(parentFrame,  type, family, editor);
        setToolTip(tr("Drag the label from the Preview panel to add it to the control panel"));
    }

/*public*/ void TextItemPanel::init() {
    if (!_initialized) {
        QThread::yieldCurrentThread();
        QWidget* panel = new QWidget();
        panel->setLayout(new QVBoxLayout(panel/*, BoxLayout.Y_AXIS*/));
        panel->layout()->addWidget(new JLabel(tr("Enter text and choose attributes for the label in the Preview panel.  Then")));
        panel->layout()->addWidget(new JLabel(tr("Drag the label from the Preview panel to add it to the control panel")));
        QWidget* p = new QWidget();
        p->setLayout(new FlowLayout);
        p->layout()->addWidget(panel);
        layout()->addWidget(p);
        _decorator = new DecoratorPanel(_editor);
        _decorator->initDecoratorPanel(NULL);
        layout()->addWidget(_decorator);
        _paletteFrame->pack();
        ItemPanel::init();
    }
}
