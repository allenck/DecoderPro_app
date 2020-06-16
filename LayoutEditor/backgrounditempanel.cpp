#include "backgrounditempanel.h"
#include <QThread>
#include <QVBoxLayout>
#include "itempalette.h"
#include <QPushButton>
#include "editor.h"
#include "borderlayout.h"
#include "editor.h"
#include <QBrush>
#include "flowlayout.h"
#include "namedicon.h"
#include "displayframe.h"
#include "drawsquares.h"
#include "colordialog.h"
#include "jcolorchooser.h"
#include "box.h"
#include "colorselectionmodel.h"
#include "borderfactory.h"

//BackgroundItemPanel::BackgroundItemPanel(QWidget *parent) :
//    IconItemPanel(parent)
//{

//}
/**
*  JPanels for the various item types that come from tool Tables - e.g. Sensors, Turnouts, etc.
*/
///*public*/ class BackgroundItemPanel extends IconItemPanel {

/**
* Constructor for plain icons and backgrounds
*/
/*public*/ BackgroundItemPanel::BackgroundItemPanel(DisplayFrame* parentFrame, QString type, Editor *editor, QWidget* parent)
 : IconItemPanel(parentFrame, type, editor, parent)
{
 // super(parentFrame, type, family, editor);
  _level = Editor::BKG;
  setObjectName("BackgroundItemPanel");
}

/*public*/ void BackgroundItemPanel::init()
{
 if (!_initialized) {
             //Thread.yield();
   IconItemPanel::init(true);
   thisLayout->insertWidget(2, initBottomPanel());
   resize(sizeHint());
   _initialized = true;
 }
}

/*protected*/ JPanel* BackgroundItemPanel::instructions(bool isBackGround)
{
 JPanel* panel = IconItemPanel::instructions(isBackGround);
 QList<QWidget*> lst = panel->findChildren<QWidget*>();
 JPanel* blurb = (JPanel*) panel->findChildren<QWidget*>().at(0);
 blurb->layout()->addWidget(new JLabel(tr("To Choose a Color Background: Press [%1]").arg("Background Color")));
 blurb->layout()->addWidget(Box::createVerticalStrut(ItemPalette::STRUT_SIZE));
 return panel;
}

/*private*/ JPanel* BackgroundItemPanel::initBottomPanel()
{
    JPanel* bottomPanel = new JPanel(new FlowLayout());
    QPushButton* backgroundButton = new QPushButton(tr("Background Color"));
//    backgroundButton.addActionListener(new ActionListener() {
//        public void actionPerformed(ActionEvent a) {
    connect(backgroundButton, &QPushButton::clicked, [=]{
            hideCatalog();
            new BGIPColorDialog(_editor, this);
//        }
    });
    backgroundButton->setToolTip(tr("Choose a color for the background panel"));
    bottomPanel->layout()->addWidget(backgroundButton);
    return bottomPanel;
}

//void BackgroundItemPanel::colorChanged()
//{
//// QColor c = _editor->getTargetPanel()->getBackground();
//// QBrush b = _editor->editPanel->backgroundBrush();
//// if(b == Qt::NoBrush)
////  c = QColor(Qt::white);
//// c = b.color();
//// BufferedImage* im = DrawSquares::getImage(500, 400, 10, c, c);
//// _paletteFrame->updateBackground0(im);
// _color = _chooser->getColor();
// _iconPanel->setImage(DrawSquares::getImage(500, 400, 10, _color, _color));
// _iconPanel->update();
//}


//    class ColorDialog extends JDialog implements ChangeListener {

//        JColorChooser _chooser;
//        Editor        _editor;
//        JPanel        _preview;
#if 1
BGIPColorDialog::BGIPColorDialog(Editor* editor, BackgroundItemPanel* parent) : JDialog(parent)
{
    //super(_paletteFrame, ItemPalette.rbp.getString("ColorChooser"), true);
    _editor = editor;
    this->parent = parent;
    resize(300,400);

    /*public*/JPanel* panel = new JPanel();
    panel->setLayout(new QVBoxLayout());// new BorderLayout(5, 5));

    _chooser = new JColorChooser(editor->getTargetPanel()->getBackground());
    _chooser->getSelectionModel()->addChangeListener((ChangeListener*)this);
    _preview = new JPanel(new FlowLayout());
    _preview->setBorder(BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black, 4),
            tr("Control Panel Color")));
    ((QVBoxLayout*)_preview->layout())->addWidget(new JLabel(new NamedIcon("resources/logo.gif", "resources/logo.gif")), 0, Qt::AlignVCenter);//BorderLayout.CENTER);
    _chooser->setPreviewPanel(_preview);
    ((QVBoxLayout*)panel->layout())->addWidget(_chooser, 0, Qt::AlignVCenter);//BorderLayout.CENTER);
    ((QVBoxLayout*)panel->layout())->addWidget(makeDoneButtonPanel(), 0, Qt::AlignBottom);//BorderLayout.SOUTH);

    //setContentPane(panel);
    setLayout(new QVBoxLayout());
    this->layout()->addWidget(panel);
    _preview->setBackground(_editor->getBackground());
    ((JPanel*)_preview->parent())->setBackground(_editor->getBackground());
    resize(parent->_paletteFrame->size().width(), this->getPreferredSize().height());
    setLocationRelativeTo(parent->_paletteFrame);
    pack();
    setVisible(true);
}

/*protected*/ QWidget* BGIPColorDialog::makeDoneButtonPanel() {
 JPanel* panel = new JPanel();
 panel->setLayout(new FlowLayout());
 QPushButton* doneButton = new QPushButton(tr("Done"));
// doneButton.addActionListener(new ActionListener() {
//     ColorDialog dialog;

//     public void actionPerformed(ActionEvent a) {
 connect(doneButton, &QPushButton::clicked, [=]{
         _editor->setBackgroundColor(_chooser->getColor());
         /*dialog.*/dispose();
         accept();
     });

//     ActionListener init(ColorDialog d) {
//         dialog = d;
//         return this;
//     }
// }.init(this));
 panel->layout()->addWidget(doneButton);

 QPushButton* cancelButton = new QPushButton(tr("Cancel"));
// cancelButton.addActionListener(new ActionListener() {
//     ColorDialog dialog;

//     public void actionPerformed(ActionEvent a) {
 connect(cancelButton, &QPushButton::clicked, [=]{
         //dialog.dispose();
  reject();
     });

//     ActionListener init(ColorDialog d) {
//         dialog = d;
//         return this;
//     }
// }.init(this));
 panel->layout()->addWidget(cancelButton);

 return panel;
}

/*public*/ void BGIPColorDialog::stateChanged(ChangeEvent* e)
{
 _preview->setBackground(_chooser->getColor());
 ((JPanel*)_preview->parent())->setBackground(_chooser->getColor());
}

#endif
//};

