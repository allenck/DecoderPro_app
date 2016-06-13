#include "performactionpanel.h"
#include "performactionmodel.h"

//PerformActionPanel::PerformActionPanel(QWidget *parent) :
//    AbstractActionPanel(parent)
//{
//}
/**
 * Provide a GUI for configuring PerformActionModel objects.
 * <P>
 * A PerformModel object invokes a Swing Action when the program is started.
 * <P>
 *
 * <P>
 * @author	Bob Jacobsen Copyright 2003
 * @version $Revision: 28056 $
 * @see apps.PerformActionModel
 */
// /*public*/ class PerformActionPanel extends AbstractActionPanel {

/**
 *
 */
//private static final long serialVersionUID = 8339294658454017607L;

/*public*/ PerformActionPanel::PerformActionPanel(QWidget *parent)
    :   AbstractActionPanel("Add Action", "Remove Action", parent)
{
 //super("ButtonActionAdd", "ButtonActionRemove");
 setObjectName("PerformActionPanel");
}
/*public*/ PerformActionPanel::PerformActionPanel(const PerformActionPanel & that)
    : AbstractActionPanel(tr("Add Action"), tr("Remove Action"))
{
 setObjectName("PerformActionPanel");
 this->removeButtonKey = that.removeButtonKey;
}

//@Override
QList<PerformActionModel*> PerformActionPanel::rememberedObjects() {
    return PerformActionModel::rememberedObjects();
}

//@Override
AbstractActionModel* PerformActionPanel::getNewModel() {
    return new PerformActionModel();
}

//@Override
/*public*/ QString PerformActionPanel::getTabbedPreferencesTitle() {
    return tr("Actions"); // NOI18N
}

//@Override
/*public*/ QString PerformActionPanel::getLabelKey() {
    return tr("Select any actions you'd like to have happen when the program starts."); // NOI18N
}
