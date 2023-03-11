#include "conditionalngeditor.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "defaultconditionalng.h"

/**
 * Editor of ConditionalNG
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class ConditionalNGEditor extends TreeEditor {

    /**
     * Construct a ConditionalEditor.
     * <p>
     * This is used by JmriUserPreferencesManager since it tries to create an
     * instance of this class.
     */
    /*public*/  ConditionalNGEditor::ConditionalNGEditor(QWidget *parent) :
        TreeEditor((AbstractFemaleSocket*)((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->
                   createFemaleSocket(nullptr, new CNGEFemaleSocketListener()
//    {
//            //@Override
//            /*public*/  void connected(FemaleSocket socket) {
//                throw new UnsupportedOperationException("Not supported");
//            }

//            //@Override
//            /*public*/  void disconnected(FemaleSocket socket) {
//                throw new UnsupportedOperationException("Not supported");
//            }
//        }
          , "A"),
                EnableClipboard::EnableClipboard,
                EnableRootRemoveCutCopy::EnableRootRemoveCutCopy,
                EnableRootPopup::EnableRootPopup,
                EnableExecuteEvaluate::EnableExecuteEvaluate
        , parent){
        setObjectName("ConditionalNGEditor");
        _conditionalNG = nullptr;
    }

    /**
     * Construct a ConditionalEditor.
     *
     * @param conditionalNG the ConditionalNG to be edited
     */
    /*/*public*/  ConditionalNGEditor::ConditionalNGEditor(/*@Nonnull*/ DefaultConditionalNG* conditionalNG, QWidget* parent) :
        TreeEditor((AbstractFemaleSocket*)conditionalNG->getFemaleSocket()->bself(),
                EnableClipboard::EnableClipboard,
                EnableRootRemoveCutCopy::EnableRootRemoveCutCopy,
                EnableRootPopup::EnableRootPopup,
                EnableExecuteEvaluate::EnableExecuteEvaluate, parent
        ){

        _conditionalNG = conditionalNG;

        if (_conditionalNG->AbstractNamedBean::getUserName() == nullptr) {
            this->setTitle(
                    tr("Edit ConditionalNG %1").arg(
                            _conditionalNG->AbstractNamedBean::getSystemName()));
        } else {
            this->setTitle(
                   tr("Edit ConditionalNG %1 - %2").arg(
                            _conditionalNG->AbstractNamedBean::getSystemName(),
                            _conditionalNG->AbstractNamedBean::getUserName()));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ConditionalNGEditor::closeEvent(QCloseEvent *e) {
        logixNGData.clear();
        logixNGData.insert("Finish", _conditionalNG->AbstractNamedBean::getSystemName());  // NOI18N
        fireLogixNGEvent();
    }

    /*public*/  void ConditionalNGEditor::addLogixNGEventListener(ConditionalNGEventListener* listener) {
        listenerList.append(listener);
    }

    /**
     * Notify the listeners to check for new data.
     */
    void ConditionalNGEditor::fireLogixNGEvent() {
        for (ConditionalNGEventListener* l : listenerList) {
            l->conditionalNGEventOccurred();
        }
    }


//    /*public*/  interface ConditionalNGEventListener extends EventListener {

//        /*public*/  void conditionalNGEventOccurred();
//    }
void ConditionalNGEditor::contextMenuEvent(QContextMenuEvent* evt)
{
  TEPopupMenu* menu = new TEPopupMenu(this);
  menu->setObjectName("TEPopupMenu");
  menu->init();
  menu->openPopupMenu(evt);

}

//    private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(ConditionalNGEditor.class);


