#include "previewpanel.h"
#include "loggerfactory.h"
#include "displayframe.h"
#include "imagepanel.h"
#include <QBoxLayout>
#include "borderfactory.h"
#include <QComboBox>

PreviewPanel::PreviewPanel()
{

}
/**
 * Companion class to DisplayFrame
 * @author peteCressman 2020
 *
 */
///*public*/ class PreviewPanel extends JPanel {


/*public*/ PreviewPanel::PreviewPanel(DisplayFrame* parent, ImagePanel* panel1, ImagePanel* panel2, bool hasComboBox)
{
    //super();
    _parent = parent;
    setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
    setBorder(BorderFactory::createTitledBorder(
            BorderFactory::createLineBorder(Qt::black, 1),
            tr("Preview"))); // "PreviewBorderTitle"
    if (hasComboBox) {
        layout()->addWidget(makeBgButtonPanel(panel1, panel2));

    }
    if (panel1 != nullptr) {
        layout()->addWidget(panel1);
    }
    if (panel2 != nullptr) {
        layout()->addWidget(panel2);
    }
}

/*public*/ void PreviewPanel::setBackgroundSelection(int index) {
    if (_bgColorBox != nullptr) {
        _bgColorBox->setCurrentIndex(index);
    }
}

/*private*/ JPanel* PreviewPanel::makeBgButtonPanel(ImagePanel* preview1, ImagePanel* preview2) {
    _bgColorBox = new QComboBox();
    _bgColorBox->addItem(tr("Panel Color")); // PanelColor key is specific for CPE, but too long for combo
    _bgColorBox->addItem(tr("White"));
    _bgColorBox->addItem(tr("Light Gray"));
    _bgColorBox->addItem(tr("Dark Gray"));
    _bgColorBox->addItem(tr("Checkers"));
    _bgColorBox->setCurrentIndex(_parent->getPreviewBg()); // Global field, starts as 0 = panel bg color

    JPanel* bkgdBoxPanel = new JPanel();
    bkgdBoxPanel->setLayout(new QVBoxLayout());//bkgdBoxPanel, BoxLayout.Y_AXIS));
    ((QVBoxLayout*)bkgdBoxPanel->layout())->addWidget(new JLabel(tr("setBackground"), 0, Qt::AlignRight));
    bkgdBoxPanel->layout()->addWidget(_bgColorBox);

    //_bgColorBox.addActionListener((ActionEvent e) -> {
    connect(_bgColorBox, &QComboBox::currentTextChanged, [=]{
        int previewBgSet = _bgColorBox->currentIndex();
        _parent->setPreviewBg(previewBgSet); // notify user choice in field on children override
        // load background image
        log->debug(tr("PreviewPanel coler #%1 set").arg(previewBgSet));
        if (preview1 != nullptr) {
            preview1->setImage(_parent->getPreviewBackground());
            preview1->update(); // force redraw
        }
        if (preview2 != nullptr) {
            preview2->setImage(_parent->getPreviewBackground());
            preview2->update(); // force redraw
        }
    });
    JPanel* panel = new JPanel(new QVBoxLayout());
    panel->layout()->addWidget(bkgdBoxPanel);
    return panel;
}

/*public*/DisplayFrame* PreviewPanel::getParent() {return _parent;}

/*private*/ /*final*/ /*static*/ Logger* PreviewPanel::log = LoggerFactory::getLogger("PreviewPanel");
