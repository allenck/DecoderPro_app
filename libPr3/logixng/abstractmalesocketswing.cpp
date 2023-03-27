#include "abstractmalesocketswing.h"
#include "abstractmalesocket.h"
#include "gridbaglayout.h"
#include "gridbagconstraints.h"
/**
 * Abstract class for SwingConfiguratorInterface
 */
///*public*/  abstract class AbstractMaleSocketSwing extends AbstractSwingConfigurator {



    /*protected*/ JPanel* AbstractMaleSocketSwing::getSubPanel(/*@CheckForNull*/ Base* object) {
        return nullptr;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  BaseManager/*<? extends NamedBean>*/* AbstractMaleSocketSwing::getManager() {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*final*/ JPanel* AbstractMaleSocketSwing::getConfigPanel(/*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(nullptr, buttonPanel);
        return panel;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*final*/ JPanel* AbstractMaleSocketSwing::getConfigPanel(/*@Nonnull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) /*throws IllegalArgumentException*/ {
        createPanel(object, buttonPanel);
        return panel;
    }

    /*protected*/ /*final*/ void AbstractMaleSocketSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && (! (dynamic_cast<AbstractMaleSocket*>(object->bself())))) {
            throw new IllegalArgumentException(QString("object is not an AbstractMaleSocket: ") + object->bself()->metaObject()->className());
        }

        panel = new JPanel();

        AbstractMaleSocket* maleSocket = nullptr;
        if(object) maleSocket = (AbstractMaleSocket*)object->bself();

        GridBagLayout* panelLayout;
        panel->setLayout(panelLayout =new GridBagLayout());
        GridBagConstraints c = GridBagConstraints();
        c.gridwidth = 1;
        c.gridheight = 1;
        c.gridx = 0;
        c.gridy = 0;
        c.anchor = GridBagConstraints::EAST;
        panelLayout->addWidget(errorHandlingLabel, c);

        c.gridx = 1;
        errorHandlingComboBox = new JComboBox();
        for (ErrorHandlingType::TYPES type : ErrorHandlingType::values()) {
            errorHandlingComboBox->addItem(ErrorHandlingType::toString(type), type);
            if ((maleSocket != nullptr) && (maleSocket->getErrorHandlingType() == type)) {
                errorHandlingComboBox->setSelectedItem(type);
            }
        }
//        JComboBoxUtil::setupComboBoxMaxRows(errorHandlingComboBox);

        panelLayout->addWidget(errorHandlingComboBox, c);

        c.gridx = 0;
        c.gridy = 1;
        panelLayout->addWidget(catchAbortExecutionLabel, c);

        c.gridx = 1;
        c.fill = GridBagConstraints::HORIZONTAL;
        catchAbortExecutionCheckBox = new JCheckBox();
        if (maleSocket != nullptr) {
            catchAbortExecutionCheckBox->setSelected(maleSocket->getCatchAbortExecution());
        }
//        catchAbortExecutionCheckBox.setAlignmentX(0);
        catchAbortExecutionLabel->setLabelFor(catchAbortExecutionCheckBox);
        panelLayout->addWidget(catchAbortExecutionCheckBox, c);

        subPanel = getSubPanel(object);
        if (subPanel != nullptr) {
            JPanel* thisPanel = panel;
            panel = new JPanel();
            panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
            panel->layout()->addWidget(thisPanel);
            panel->layout()->addWidget(subPanel);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*final*/ bool AbstractMaleSocketSwing::validate(/*@Nonnull*/ QList<QString> *errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* AbstractMaleSocketSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        // Male sockets of this type is created by the system, not by the user
        throw new UnsupportedOperationException("Not supported");
    }

    /*protected*/ void AbstractMaleSocketSwing::updateObjectForSubPanel(/*@Nonnull*/ Base* object) {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*final*/ void AbstractMaleSocketSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (dynamic_cast<AbstractMaleSocket*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object is not an AbstractMaleSocket: ") + object->bself()->metaObject()->className());
        }

        AbstractMaleSocket* maleSocket = (AbstractMaleSocket*)object->bself();
        //maleSocket->setErrorHandlingType(errorHandlingComboBox->getItemAt(errorHandlingComboBox->getSelectedIndex()));
        maleSocket->setErrorHandlingType(ErrorHandlingType::valueOf(errorHandlingComboBox->currentText()));
        maleSocket->setCatchAbortExecution(catchAbortExecutionCheckBox->isSelected());

        updateObjectForSubPanel(object);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractMaleSocketSwing::getExampleSystemName() {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractMaleSocketSwing::getAutoSystemName() {
        throw new UnsupportedOperationException("Not supported");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AbstractMaleSocketSwing::toString() {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  /*final*/ void AbstractMaleSocketSwing::dispose() {
    }

    /**
     * Dispose the sub panel and remove all the listeners that this class may
     * have registered.
     *./
    public  void AbstractMaleSocketSwing::disposeSubPanel() {
    }
*/
