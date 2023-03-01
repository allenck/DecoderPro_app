#include "swingconfiguratorinterfacetestbase.h"
#include "conditionalngeditor.h"
#include "defaultconditionalng.h"
#include "jframeoperator.h"

SwingConfiguratorInterfaceTestBase::SwingConfiguratorInterfaceTestBase(QObject *parent)
    : QObject{parent}
{

}
/**
 * Base class for SwingConfiguratorInterface classes
 *
 * @author Daniel Bergqvist (C) 2020
 */
// /*public*/ class SwingConfiguratorInterfaceTestBase {

    /*protected*/ JDialogOperator* SwingConfiguratorInterfaceTestBase::editItem(
            DefaultConditionalNG* conditionalNG,
            QString title1, QString title2, int row) {

        ConditionalNGEditor* treeEdit = new ConditionalNGEditor(conditionalNG);
        treeEdit->initComponents();
        treeEdit->setVisible(true);

        JFrameOperator* treeFrame = new JFrameOperator(title1);
        JTreeOperator* jto = new JTreeOperator(treeFrame);
#if 0
        TreePath* tp = jto->getPathForRow(row);
        QMenu* jpm = jto->callPopupOnPath(tp);

        (new JPopupMenuOperator(jpm))->pushMenuNoBlock("Edit");
#endif
        JDialogOperator* editItemDialog = new JDialogOperator(title2);  // NOI18N

        return editItemDialog;
    }

