#include "abstractcolorchooserpanel.h"
#include <QIcon>

// /*public*/ /*abstract*/ class AbstractColorChooserPanel extends JPanel {


/*public*/ AbstractColorChooserPanel::AbstractColorChooserPanel(QWidget *parent) {
    // compiled code
}

/*public*/ /*abstract*/ void AbstractColorChooserPanel::updateChooser() {}

/*protected*/ /*abstract*/ void AbstractColorChooserPanel::buildChooser() {}

/*public*/ /*abstract*/ QString AbstractColorChooserPanel::getDisplayName() {return "";}

/*public*/ int AbstractColorChooserPanel::getMnemonic() {
    // compiled code
}

/*public*/ int AbstractColorChooserPanel::getDisplayedMnemonicIndex() {
    // compiled code
}

/*public*/ /*abstract*/ QIcon AbstractColorChooserPanel::getSmallDisplayIcon() {return QIcon();}

/*public*/ /*abstract*/ QIcon AbstractColorChooserPanel::getLargeDisplayIcon() {return QIcon();}

/*public*/ void AbstractColorChooserPanel::installChooserPanel(JColorChooser* enclosingChooser) {
    // compiled code
}

/*public*/ void AbstractColorChooserPanel::uninstallChooserPanel(JColorChooser* enclosingChooser) {
    // compiled code
}

/*public*/ ColorSelectionModel* AbstractColorChooserPanel::getColorSelectionModel() {
    // compiled code
}

/*protected*/ QColor AbstractColorChooserPanel::getColorFromModel() {
    // compiled code
}

void AbstractColorChooserPanel::setSelectedColor(QColor arg0) {
    // compiled code
}

///*public*/ void AbstractColorChooserPanel::paint(Graphics g) {
//    // compiled code
//}

int AbstractColorChooserPanel::getInt(QObject* arg0, int arg1) {
    // compiled code
}
