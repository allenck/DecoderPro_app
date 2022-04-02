#include "defaultmaledigitalexpressionsocketswing.h"
#include "defaultmaledigitalexpressionsocket.h"

DefaultMaleDigitalExpressionSocketSwing::DefaultMaleDigitalExpressionSocketSwing(QObject *parent) : AbstractMaleSocketSwing(parent)
{
 setObjectName("DefaultMaleDigitalExpressionSocketSwing");
}
/**
 * Configures an DefaultMaleDigitalActionSocket object with a Swing JPanel.
 */
// /*public*/ class DefaultMaleDigitalExpressionSocketSwing extends AbstractMaleSocketSwing {


    //@Override
    /*protected*/ JPanel* DefaultMaleDigitalExpressionSocketSwing::getSubPanel(/*@CheckForNull*/ Base* object) {
        if ((object != nullptr) && (! (qobject_cast<DefaultMaleDigitalExpressionSocket*>(object->bself())))) {
            throw new IllegalArgumentException(QString("object is not an DefaultMaleDigitalExpressionSocket: ") + object->bself()->metaObject()->className());
        }

        _panel = new JPanel();
        _listenCheckBox = new JCheckBox();
        _listenCheckBox->setSelected(true);  // Listen should be true if not changed by the user

        DefaultMaleDigitalExpressionSocket* maleSocket = (DefaultMaleDigitalExpressionSocket*)object->bself();
        if (maleSocket != nullptr) {
            _listenCheckBox->setSelected(maleSocket->getListen());
        }

        _listenLabel->setLabelFor(_listenCheckBox);
        _panel->layout()->addWidget(_listenLabel);
        _panel->layout()->addWidget(_listenCheckBox);

        return _panel;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultMaleDigitalExpressionSocketSwing::updateObjectForSubPanel(/*@Nonnull*/ Base* object) {
        Base* obj = object;
        while (((qobject_cast<MaleSocket*>(obj->bself()))) && (! (qobject_cast<DefaultMaleDigitalExpressionSocket*>(obj->bself())))) {
            obj = ((MaleSocket*)obj->bself())->getObject();
        }
        if (! (qobject_cast<DefaultMaleDigitalExpressionSocket*>(obj->bself()))) {
            throw new IllegalArgumentException(QString("object is not an DefaultMaleDigitalExpressionSocket: ") + object->bself()->metaObject()->className());
        }

        DefaultMaleDigitalExpressionSocket* maleSocket = (DefaultMaleDigitalExpressionSocket*)obj->bself();
        maleSocket->setListen(_listenCheckBox->isSelected());
    }
