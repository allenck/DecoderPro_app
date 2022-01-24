#include "lightintensitypane.h"
#include "loggerfactory.h"
#include "variablelight.h"
#include <QBoxLayout>
#include "spinnernumbermodel.h"
#include "jtextfield.h"

LightIntensityPane::LightIntensityPane()
{

}
/**
 * Panel to display Light Intensity options.
 *
 * Code originally within LightTableAction.
 *
 * @author Dave Duchamp Copyright (C) 2004
 * @author Egbert Broerse Copyright (C) 2017
 * @author Steve Young Copyright (C) 2021
 */
// /*public*/ class LightIntensityPane extends JPanel {


/**
 * Create a new Light Intensity Panel.
 *
 * @param vertical true for vertical, false for horizontal display.
 */
/*public*/ LightIntensityPane::LightIntensityPane( bool vertical) :JPanel(){
    //super();
    init(vertical);
}


/*private*/ void LightIntensityPane::init(bool vertical){

    setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS ));
    minIntensity = new JSpinner();
    maxIntensity = new JSpinner();
    transitionTime = new JSpinner();
    JPanel* mainPanel = new JPanel();
    //mainPanel->setLayout(vertical?new QVBoxLayout():new QHBoxLayout() );
    if(vertical)
     mainPanel->setLayout(new QVBoxLayout);
    else
     mainPanel->setLayout(new QHBoxLayout());

    minPan = new JPanel(new FlowLayout());
    minPan->layout()->addWidget(new JLabel(" "));
    minPan->layout()->addWidget(new JLabel(tr("Minimum Intensity:")));
    minIntensity->setModel(
            new SpinnerNumberModel(QVariant(0.0), QVariant(0.0), QVariant(0.99), QVariant(0.01))); // 0 - 99%
    minIntensity->setEditor(new JSpinner::NumberEditor(minIntensity, "##0 %"));
    minIntensity->setToolTip(tr("0 to 100%, must be equal or less than max"));
    minIntensity->setValue(0.0); // reset JSpinner1
    minPan->layout()->addWidget(minIntensity);
    minPan->layout()->addWidget(new JLabel("   "));
    mainPanel->layout()->addWidget(minPan);

    maxPan = new JPanel(new FlowLayout());
    maxPan->layout()->addWidget(new JLabel(tr("Maximum Intensity:")));
    maxIntensity->setModel(
            new SpinnerNumberModel(QVariant(1.0), QVariant(0.01), QVariant(1.0), QVariant(0.01))); // 100 - 1%
    maxIntensity->setEditor(new JSpinner::NumberEditor(maxIntensity, "##0 %"));
    maxIntensity->setToolTip(tr("0 to 100%, must be equal or greater than min"));
    maxIntensity->setValue(1.0); // reset JSpinner2
    maxPan->layout()->addWidget(maxIntensity);
    maxPan->layout()->addWidget(new JLabel("   "));
    mainPanel->layout()->addWidget(maxPan);

    transitionPan = new JPanel(new FlowLayout());
    transitionPan->layout()->addWidget(new JLabel(tr("Transition Time:")));
    transitionTime->setModel(
            new SpinnerNumberModel(QVariant(0.), QVariant(0.), QVariant(1000000.), QVariant(0.01)));
    transitionTime->setEditor(new JSpinner::NumberEditor(transitionTime, "###0.00"));
    transitionTime->resize( JTextField(8).sizeHint());
    transitionTime->setToolTip(tr("Time in fast minutes to go from 0% to 100%"));
    transitionTime->setValue(0.0); // reset from possible previous use
    transitionPan->layout()->addWidget(transitionTime);
    transitionPan->layout()->addWidget(new JLabel(" "));
    mainPanel->layout()->addWidget(transitionPan);

    this->layout()->addWidget(mainPanel);

    JPanel* statusPanel = new JPanel(new FlowLayout());
    statusPanel->layout()->addWidget(status1);
    this->layout()->addWidget(statusPanel);

}

/**
 * Set the panel to match a Light.
 * @param light the Light to set Panel for.
 */
/*public*/ void LightIntensityPane::setToLight(Light* light){
    if (qobject_cast<VariableLight*>(light->self())) {
        minIntensity->setValue(((VariableLight*)light)->getMinIntensity()); // displayed as percentage
        maxIntensity->setValue(((VariableLight*)light)->getMaxIntensity());
        if (((VariableLight*)light)->isTransitionAvailable()) {
            transitionTime->setValue(((VariableLight*)light)->getTransitionTime()); // displays i18n decimal separator eg. 0,00 in _nl
        }
        setupVariableDisplay(true, ((VariableLight*)light)->isTransitionAvailable());
    } else {
        setupVariableDisplay(false, false);
    }
}

/**
 * Set a Light to match the Panel.
 * @param light The Light to edit details for.
 */
/*public*/ void LightIntensityPane::setLightFromPane(VariableLight* light){

    if ( minIntensity->getValue() >=  maxIntensity->getValue()) {
        log->error(tr("minInt value entered: %1").arg(minIntensity->getValue()));
        // do not set intensity
        status1->setText(tr("Warning: Intensity not set. Minimum must be lower than Maximum."));
        status1->setVisible(true);
    } else {
        light->setMinIntensity( minIntensity->getValue());
        light->setMaxIntensity( maxIntensity->getValue());
    }
    if (light->isTransitionAvailable()) {
        light->setTransitionTime( transitionTime->getValue());
    }

}

/**
 * Set up panel for Variable Options.
 *
 * @param showIntensity  true to show light intensity; false otherwise
 * @param showTransition true to show time light takes to transition between
 *                       states; false otherwise
 */
/*private*/ void LightIntensityPane::setupVariableDisplay(bool showIntensity, bool showTransition) {
    minPan->setVisible(showIntensity);
    maxPan->setVisible(showIntensity);
    transitionPan->setVisible(showTransition);
    setVisible(showIntensity || showTransition);
}

/*private*/ /*final*/ /*static*/ Logger* LightIntensityPane::log = LoggerFactory::getLogger("LightIntensityPane");
