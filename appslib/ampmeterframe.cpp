#include "ampmeterframe.h"
#include "instancemanager.h"
#include <QBoxLayout>
#include <QPushButton>
#include "abstractmultimeter.h"


/**
 * Frame providing a simple lcd-based display of track current.
 * <p>
 * A Run/Stop button is built into this, but because I don't like the way it
 * looks, it's not currently displayed in the GUI.
 *
 * @author Ken Cameron Copyright (C) 2007
 * @author Mark Underwood Copyright (C) 2007
 *
 * This was a direct steal form the LCDClock code by Ken Cameron, which was a
 * direct steal from the Nixie clock code, ver 1.2. Thank you Bob Jacobsen and
 * Ken Cameron.
 */
///*public*/ class AmpMeterFrame extends JmriJFrame implements java.beans.PropertyChangeListener {



/*public*/ AmpMeterFrame::AmpMeterFrame(QWidget* parent)
    : JmriJFrame(tr("Track Current Meter"), parent){
    //super(Bundle.getMessage("TrackCurrentMeterTitle"));
     digits = QVector<NamedIcon*>(10);

    meter = (AbstractMultiMeter*)InstanceManager::getDefault("MultiMeter");
}

//@Override
/*public*/ void AmpMeterFrame::initComponents() {
    //Load the images (these are now the larger version of the original gifs
    for (int i = 0; i < 10; i++) {
        digits[i] = new NamedIcon(QString("resources/icons/misc/LCD/Lcd_") + QString::number(i) + "b.GIF", QString("resources/icons/misc/LCD/Lcd_") + QString::number(i) + "b.GIF");
    }
    percentIcon = new NamedIcon("resources/icons/misc/LCD/percentb.gif", "resources/icons/misc/LCD/percentb.gif");
    decimalIcon = new NamedIcon("resources/icons/misc/LCD/decimalb.gif", "resources/icons/misc/LCD/decimalb.gif");
    milliAmpIcon = new NamedIcon("resources/icons/misc/LCD/milliampb.gif", "resources/icons/misc/LCD/milliampb.gif");
    ampIcon = new NamedIcon("resources/icons/misc/LCD/ampb.gif", "resources/icons/misc/LCD/ampb.gif");

    // determine aspect ratio of a single digit graphic
    iconAspect = 24. / 32.;

    // determine the aspect ratio of the 4 digit base graphic plus a half digit for the colon
    // this DOES NOT allow space for the Run/Stop button, if it is
    // enabled.  When the Run/Stop button is enabled, the layout will have to be changed
    aspect = (4.5 * 24.) / 32.; // used to be 4.5??

    // listen for changes to the meter parameters
    meter->addPropertyChangeListener((PropertyChangeListener*)this);

    // init GUI
    digitIcons = QList<JLabel*>(/*3*/); // 1 decimal place precision.
    digitIcons.reserve(3);
    for(int i = 0;i<3;i++) {
       digitIcons.insert(i,new JLabel(digits[0]));
    }
    percent = new JLabel(percentIcon);
    decimal = new JLabel(decimalIcon);
    milliAmp = new JLabel(milliAmpIcon);
    amp = new JLabel(ampIcon);

    buildContents();

    meter->enable();

    update();

    // request callback to update time
    // Again, adding updates.
//        java.beans.PropertyChangeListener du_listener = new java.beans.PropertyChangeListener() {
//            @Override
//            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                update();
//            }
//        };
    meter->addPropertyChangeListener(MultiMeter::CURRENT, /*du_listener*/(PropertyChangeListener*)this);

#if 0
    // Add component listener to handle frame resizing event
    this.addComponentListener(
            new ComponentAdapter() {
        @Override
        /*public*/ void componentResized(ComponentEvent e) {
            scaleImage();
        }
    });
#endif
 startHeight = this->getContentPane()->size().height();
 startWidth = this->getContentPane()->size().width();
 initDone = true;
}

void AmpMeterFrame::resizeEvent(QResizeEvent */*e*/)
{
    if(!initDone)
        return;
 scaleImage();
}

// Added method to scale the clock digit images to fit the
// size of the display window
/*synchronized*/ /*public*/ void AmpMeterFrame::scaleImage() {
    int frameHeight = this->getContentPane()->size().height();
    int frameWidth = this->getContentPane()->size().width();

    double hscale = ((double)frameHeight)/((double)startHeight);
    double wscale = ((double)frameWidth)/((double)startWidth);
    double scale = hscale < wscale? hscale:wscale;

    for (int i = 0; i < 10; i++) {
        digits[i]->scale(scale,this);
    }
    percentIcon->scale(scale,this);
    decimalIcon->scale(scale,this);
    ampIcon->scale(scale, this);
    milliAmpIcon->scale(scale,this);
}

/*private*/ void AmpMeterFrame::buildContents(){
    // clear the contents
    if(qobject_cast<JPanel*>(getContentPane()))
    ((JPanel*)getContentPane())->removeAll();

    // build the actual multimeter display.
    getContentPane()->setLayout(new QHBoxLayout());//getContentPane(), BoxLayout.X_AXIS));

    for(int i=0;i<digitIcons.size()-1;i++){
        getContentPane()->layout()->addWidget(digitIcons.at(i));
    }
    switch (meter->getCurrentUnits()) {
        case MultiMeter::CURRENT_UNITS_MILLIAMPS:
            getContentPane()->layout()->addWidget(milliAmp);
            break;
        case MultiMeter::CURRENT_UNITS_AMPS:
            getContentPane()->layout()->addWidget(decimal);
            getContentPane()->layout()->addWidget(digitIcons.at(digitIcons.size()-1));
            getContentPane()->layout()->addWidget(amp);
            break;
        case MultiMeter::CURRENT_UNITS_PERCENTAGE:
        default:
            getContentPane()->layout()->addWidget(decimal);
            getContentPane()->layout()->addWidget(digitIcons.at(digitIcons.size()-1));
            getContentPane()->layout()->addWidget(percent);
            break;
    }

    getContentPane()->layout()->addWidget(b = new QPushButton(tr("Stop")));
//        b.addActionListener(new ButtonListener());
    connect(b, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
    // since Run/Stop button looks crummy, don't display for now
    b->setVisible(false);

    pack();
}

/*synchronized*/ void AmpMeterFrame::update() {
    float val = meter->getCurrent();
    int value = (int)qFloor(val *10); // keep one decimal place.
    bool scaleChanged = false;
    // autoscale the array of labels.
    while( (value) > (qPow(10,digitIcons.size()-1))) {
       digitIcons.insert(0,new JLabel(digits[0]));
       scaleChanged = true;
    }

    if (scaleChanged){
        // clear the content pane and rebuild it.
        buildContents();
    }

    value = (int)qFloor(val *10); // keep one decimal place.
    for(int i = digitIcons.size()-1; i>=0; i--){
        digitIcons.at(i)->setIcon(digits[value%10]);
        value = value / 10;
    }
}

//@Override
/*public*/ void AmpMeterFrame::dispose() {
    meter->disable();
    meter->removePropertyChangeListener(MultiMeter::CURRENT, (PropertyChangeListener*)this);
    meter->removePropertyChangeListener((PropertyChangeListener*)this);
    JmriJFrame::dispose();
}

/**
 * Handle a change to clock properties
 */
//@Override
///*public*/ void propertyChange(PropertyChangeEvent* e) {
    /*
    boolean now = clock.getRun();
    if (now) {
        b.setText("Stop");
    } else {
        b.setText("Run");
    }
     */
//}


//    static private class ButtonListener implements ActionListener {

//        @Override
//        /*public*/ void actionPerformed(ActionEvent a) {
void AmpMeterFrame::on_button_clicked()
{
    /*
    bool next = !clock.getRun();
    clock.setRun(next);
    if (next) {
        b.setText("Stop");
    } else {
        b.setText("Run ");
    }
     */
}

