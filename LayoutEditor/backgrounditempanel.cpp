#include "backgrounditempanel.h"
#include <QThread>
#include <QVBoxLayout>
#include "itempalette.h"
#include <QPushButton>
#include "editor.h"
#include "QColorDialog"
#include "borderlayout.h"
#include "editor.h"
#include <QBrush>
#include "flowlayout.h"
#include "namedicon.h"

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
/*public*/ BackgroundItemPanel::BackgroundItemPanel(JmriJFrame* parentFrame, QString type, QString family, Editor* editor, QWidget* parent) : IconItemPanel(parentFrame, type, family, editor, parent)
{
 // super(parentFrame, type, family, editor);
  _level = Editor::BKG;
}

/*public*/ void BackgroundItemPanel::init()
{
 if (!_initialized)
 {
  QThread::yieldCurrentThread();
  IconItemPanel::init();
  layout()->addWidget(initBottomPanel()/*, 2*/);
  resize(sizeHint());
 }
}

/*protected*/ QWidget* BackgroundItemPanel::instructions()
{
 QWidget* panel = IconItemPanel::instructions();
//        QWidget* blurb = (QWidget*)panel->layout()->children().at(0);
//        blurb->setLayout(new QVBoxLayout);
 panel->layout()->addWidget(new QLabel(tr("To Choose a Color Background: Press [%1]").arg(                                                     tr("Background Color"))));
//        ((QVBoxLayout*)blurb->layout())->addStrut(ItemPalette::STRUT_SIZE);
 return panel;
}

/*private*/ QWidget* BackgroundItemPanel::initBottomPanel()
{
 QWidget* bottomPanel = new QWidget();
 bottomPanel->setLayout(new QHBoxLayout);
 QPushButton* backgroundButton = new QPushButton(tr("Background Color"));
 QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
 sizePolicy.setHorizontalStretch(0);
 sizePolicy.setVerticalStretch(0);
 sizePolicy.setHeightForWidth(backgroundButton->sizePolicy().hasHeightForWidth());
 backgroundButton->setSizePolicy(sizePolicy);
//        backgroundButton.addActionListener(new ActionListener() {
//                /*public*/ void actionPerformed(ActionEvent a) {
//                    hideCatalog();
//                    new ColorDialog(_editor);
//                }
//        });
 connect(backgroundButton, SIGNAL(clicked()), this, SLOT(backgroundButton_clicked()));
 backgroundButton->setToolTip(tr("Choose a color for the background panel"));
 bottomPanel->layout()->addWidget(backgroundButton);
 return bottomPanel;
}
void BackgroundItemPanel::backgroundButton_clicked()
{
 hideCatalog();
 ColorDialog dlg(_editor, this);
 dlg.exec();
}
void BackgroundItemPanel::colorChanged(QColor)
{

}


//    class ColorDialog extends JDialog implements ChangeListener {

//        JColorChooser _chooser;
//        Editor        _editor;
//        JPanel        _preview;

ColorDialog::ColorDialog(Editor* editor, BackgroundItemPanel* parent) : JDialog(parent)
{
    //super(_paletteFrame, ItemPalette.rbp.getString("ColorChooser"), true);
    _editor = editor;
    this->parent = parent;
    resize(300,400);

    //QWidget* panel = new QWidget();
//    BorderLayout* borderLayout = new BorderLayout(this);
//    setLayout(borderLayout);
    setLayout(new QVBoxLayout);
    setSizeGripEnabled(true);

    _chooser = new QColorDialog(_editor->getBackgroundColor());
    //_chooser.getSelectionModel().addChangeListener(this);
    connect(_chooser, SIGNAL(currentColorChanged(QColor)), this, SLOT(stateChanged()));
    _chooser->setOption(QColorDialog::NoButtons);
    _preview = new QWidget();
    //_preview->setLayout(new QVBoxLayout(preview/*, BoxLayout.Y_AXIS*/));
    //BorderLayout* previewLayout = new BorderLayout(_preview);
    //_preview->setLayout(previewLayout);
    _preview->setLayout(new QHBoxLayout);
    //_preview.setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black, 4),
//                                                     ItemPalette.rbp.getString("PanelColor")));
    _preview->setObjectName("myObject");
    _preview->setStyleSheet("#myObject { border: 2px solid black; }");
    QLabel* label = new QLabel();
    NamedIcon* icon =new NamedIcon("resources/logo.gif", "resources/logo.gif");
    label->setPixmap(QPixmap::fromImage(icon->getImage()));
    ((QBoxLayout*)_preview->layout())->addWidget(label,0,Qt::AlignHCenter/*, BorderLayout::Center*/);
    //_chooser.setPreviewPanel(_preview);
//    borderLayout->addWidget(_chooser, BorderLayout::Center);
//    borderLayout->addWidget(makeDoneButtonPanel(), BorderLayout::South);
    layout()->addWidget(_chooser);
    layout()->addWidget(makeDoneButtonPanel());
    layout()->addWidget(_preview);
    //setContentPane(panel);

//    _preview.setBackground(_editor.getBackground());
    //_preview->setStyleSheet("QWidget {background-color : rgb(137,255,236); font-size : 7pt; }");
    QColor c = _chooser->currentColor();
    _preview->setStyleSheet(QString("QWidget {background-color : rgb(%1,%2,%3); font-size : 7pt; }").arg(c.red()).arg(c.green()).arg(c.blue()));
//    _preview.getParent().setBackground(_editor.getBackground());
//    setSize(_paletteFrame.getSize().width, this.getPreferredSize().height);
//    setLocationRelativeTo(_paletteFrame);
    pack();
    setVisible(true);
}

/*protected*/ QWidget* ColorDialog::makeDoneButtonPanel() {
    QWidget* panel = new QWidget();
    panel->setLayout(new FlowLayout());
    QPushButton* doneButton = new QPushButton(tr("Done"));
//    doneButton.addActionListener(new ActionListener() {
//            ColorDialog dialog;
//            /*public*/ void actionPerformed(ActionEvent a) {
//                _editor.setBackgroundColor(_chooser.getColor());
//                dialog.dispose();
//            }
//            ActionListener init(ColorDialog d) {
//                dialog = d;
//                return this;
//            }
//    }.init(this));
    CDActionListener* l = new CDActionListener();
    l->init(this);
    connect(doneButton, SIGNAL(clicked()), l, SLOT(actionPerformed()));
    panel->layout()->addWidget(doneButton);

    QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//    cancelButton.addActionListener(new ActionListener() {
//            ColorDialog dialog;
//            /*public*/ void actionPerformed(ActionEvent a) {
//                dialog.dispose();
//            }
//            ActionListener init(ColorDialog d) {
//                dialog = d;
//                return this;
//            }
//    }.init(this));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    panel->layout()->addWidget(cancelButton);

    return panel;
}

/*public*/ void ColorDialog::stateChanged(ChangeEvent* e)
{
//    _preview->setBackground(_chooser->currentColor());
    QColor c = _chooser->currentColor();
//    _preview->getParent()->setBackground(_chooser->currentColor());
    _preview->setStyleSheet(QString("QWidget {background-color : rgb(%1,%2,%3); font-size : 7pt; }").arg(c.red()).arg(c.green()).arg(c.blue()));
}

/*public*/ void CDActionListener::actionPerformed(ActionEvent* a) {
    dialog->_editor->setBackgroundColor(dialog->_chooser->currentColor());
    dialog->close();
}
CDActionListener* CDActionListener::init(ColorDialog* d) {
    dialog = d;
    return this;
}

//};

