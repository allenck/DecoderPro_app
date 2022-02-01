#include "conditionalngeditor.h"
#include "digitalactionmanager.h"
#include "instancemanager.h"

#include "conditionalng.h"
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
        TreeEditor(((DigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->
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

        _conditionalNG = nullptr;
    }

    /**
     * Construct a ConditionalEditor.
     *
     * @param conditionalNG the ConditionalNG to be edited
     */
    /*/*public*/  ConditionalNGEditor::ConditionalNGEditor(/*@Nonnull*/ ConditionalNG* conditionalNG, QWidget* parent) :
        TreeEditor(conditionalNG->getFemaleSocket(),
                EnableClipboard::EnableClipboard,
                EnableRootRemoveCutCopy::EnableRootRemoveCutCopy,
                EnableRootPopup::EnableRootPopup,
                EnableExecuteEvaluate::EnableExecuteEvaluate
        ){

        _conditionalNG = conditionalNG;

        if (_conditionalNG->NamedBean::getUserName() == nullptr) {
            this->setTitle(
                    tr("Edit ConditionalNG %1").arg(
                            _conditionalNG->NamedBean::getSystemName()));
        } else {
            this->setTitle(
                   tr("Edit ConditionalNG %1 - %2").arg(
                            _conditionalNG->NamedBean::getSystemName(),
                            _conditionalNG->NamedBean::getUserName()));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ConditionalNGEditor::windowClosed(QCloseEvent* e) {
        logixNGData.clear();
        logixNGData.insert("Finish", _conditionalNG->NamedBean::getSystemName());  // NOI18N
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


//    private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(ConditionalNGEditor.class);


