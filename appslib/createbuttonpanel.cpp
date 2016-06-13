#include "createbuttonpanel.h"
#include "createbuttonmodel.h"

//CreateButtonPanel::CreateButtonPanel(QWidget *parent) :
//    AbstractActionPanel(parent)
//{
//}
/**
 * Provide a GUI for configuring start-up actions.
 * <P>
 * Configures CreateButtonModel objects. A CreateButtonModel object creates
 * appropriate buttons when the program is started.
 *
 * <P>
 * @author	Bob Jacobsen Copyright 2003
 * @version $Revision: 28056 $
 * @see apps.CreateButtonModel
 */
// /*public*/ class CreateButtonPanel extends AbstractActionPanel {

/**
 *
 */
//private static final long serialVersionUID = 1652489978153384059L;

/*public*/ CreateButtonPanel::CreateButtonPanel(QWidget *parent)
    : AbstractActionPanel(tr("Add Button"), tr("Remove Button"),parent)
{
 //super("ButtonButtonAdd", "ButtonButtonRemove");
 setObjectName("CreateButtonPanel");
}
/*public*/ CreateButtonPanel::CreateButtonPanel(const CreateButtonPanel & that)
    : AbstractActionPanel(tr("Add Button"), tr("Remove Button"))
{
 //this->removeButtonKey = that.removeButtonKey;
 setObjectName("CreateButtonPanel");
}

//@Override
template<class T>
QList<T> CreateButtonPanel::rememberedObjects() {
    return CreateButtonModel::rememberedObjects();
}

//@Override
AbstractActionModel* CreateButtonPanel::getNewModel() {
    return new CreateButtonModel();
}

//@Override
/*public*/ QString CreateButtonPanel::getTabbedPreferencesTitle() {
    return tr("Buttons"); // NOI18N
}

//@Override
/*public*/ QString CreateButtonPanel::getLabelKey() {
    return tr("Select any buttons you'd like to have appear on the main screen."); // NOI18N
}
