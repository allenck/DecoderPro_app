#include "clipboardeditor.h"
#include "instancemanager.h"
#include "logixng_manager.h"
#include "femalesocket.h"

/**
 * Editor of the clipboard
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class ClipboardEditor extends TreeEditor {


    /**
     * Construct a ConditionalEditor.
     */
    /*public*/  ClipboardEditor::ClipboardEditor(QWidget *parent)
        : TreeEditor((FemaleSocket*)((LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager"))->getClipboard()->getFemaleSocket(),
                EnableClipboard::DisableClipboard,
                EnableRootRemoveCutCopy::EnableRootRemoveCutCopy,
                EnableRootPopup::DisableRootPopup,
                EnableExecuteEvaluate::DisableExecuteEvaluate,
              parent){


        this->setTitle(tr("ClipboardEditor"));

        this->setRootVisible(false);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ClipboardEditor::windowClosed(QCloseEvent* e) {
        clipboardData.clear();
        clipboardData.insert("Finish", "Clipboard");  // NOI18N
        fireClipboardEvent();
    }

    /*public*/  void ClipboardEditor::addClipboardEventListener(ClipboardEventListener* listener) {
        listenerList.append(listener);
    }

    /**
     * Notify the listeners to check for new data.
     */
    void ClipboardEditor::fireClipboardEvent() {
        for (ClipboardEventListener* l : listenerList) {
            l->clipboardEventOccurred();
        }
    }


//    /*public*/  /*interface*/ ClipboardEventListener extends EventListener {

//        /*public*/  void clipboardEventOccurred();
//    }
