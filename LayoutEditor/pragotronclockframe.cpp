#include "pragotronclockframe.h"
#include "instancemanager.h"
#include <QDateTime>
/**
 * Frame providing a simple clock showing Pragotron clock.
 * <p>
 * A Run/Stop button is built into this, but because I don't like the way it
 * looks, it's not currently displayed in the GUI.
 *
 * @author Petr Sidlo Copyright (C) 2019
 *
 * Based on Nixie clock by Bob Jacobsen.
 */
 // /*public*/ class PragotronClockFrame extends JmriJFrame implements java.beans.PropertyChangeListener {

    //"base" variables used to hold original gifs, other variables used with scaled images

     /*public*/ PragotronClockFrame::PragotronClockFrame(QWidget *parent) : JmriJFrame("Pragotron Clock")
     {
        //super(Bundle.getMessage("MenuItemPragotronClock"));

        //this->getContentPane()->setBackground(QColor("#3D3D3D"));    // set background to black
        this->getContentPane()->setStyleSheet("QWidget{background-color: #3D3D3D}" );

        clock = (Timebase*)InstanceManager::getDefault("Timebase");

        //Load the images (these are now the larger version of the original gifs
        for (int i = 0; i < 10; i++) {
            baseFoldingSheets10[i] = new NamedIcon("resources/icons/misc/Pragotron/M" + QString::number(i) + ".png", "resources/icons/misc/Pragotron/M" + QString::number(i) + ".png");
            foldingSheets10[i] = new NamedIcon("resources/icons/misc/Pragotron/M" + QString::number(i) + ".png", "resources/icons/misc/Pragotron/M" + QString::number(i) + ".png");
        }
        for (int i = 0; i < 24; i++) {
            baseFoldingSheets24[i] = new NamedIcon("resources/icons/misc/Pragotron/H" + QString::number(i) + ".png", "resources/icons/misc/Pragotron/H" + QString::number(i) + ".png");
            foldingSheets24[i] = new NamedIcon("resources/icons/misc/Pragotron/H" + QString::number(i) + ".png", "resources/icons/misc/Pragotron/H" + QString::number(i) + ".png");
        }
        colonIcon = new NamedIcon("resources/icons/misc/Pragotron/dot.png", "resources/icons/misc/Pragotron/dot.png");
        baseColon = new NamedIcon("resources/icons/misc/Pragotron/dot.png", "resources/icons/misc/Pragotron/dot.png");
        // set initial size the same as the original gifs
        for (int i = 0; i < 10; i++) {
            QImage scaledImage = baseFoldingSheets10[i]->getImage().scaled(32, 48/*, Image.SCALE_SMOOTH*/);  // 152 / 192
            foldingSheets10[i]->setImage(scaledImage);
        }
        for (int i = 0; i < 24; i++) {
            QImage scaledImage = baseFoldingSheets24[i]->getImage().scaled(80, 48/*, Image.SCALE_SMOOTH*/);  // 320 / 192
            foldingSheets24[i]->setImage(scaledImage);
        }
        QImage scaledImage = baseColon->getImage().scaled(10, 48/*, Image.SCALE_SMOOTH*/);  // 40 / 192
        colonIcon->setImage(scaledImage);

        // determine aspect ratio of a single digit graphic
        iconAspect10 = 152.0 / 192.0;       // 152 : 192
        iconAspect24 = 320.0 / 192.0;       // 320 : 192
        iconAspectDot = 40.0 / 192.0;       // 40 : 192

        // determine the aspect ratio of the 1 hour digit, dot and 2 minutes digit
        // this DOES NOT allow space for the Run/Stop button, if it is
        // enabled.  When the Run/Stop button is enabled, the layout will have to be changed
        if (!clock->getShowStopButton()) {
            aspect = (320.0 + 40.0 + 2 * 152.0) / 192.0; // pick up clock prefs choice: no button
        } else {
            aspect = (320.0 + 40.0 + 2 * 152.0 + 152.0) / 192.0; // pick up clock prefs choice: add 20. for a stop/start button
        }

        // listen for changes to the Timebase parameters
        clock->addPropertyChangeListener((PropertyChangeListener*)this);

        // init GUI
        m1 = new JLabel(foldingSheets10[0]);
        m2 = new JLabel(foldingSheets10[0]);
        h24 = new JLabel(foldingSheets24[0]);
        colon = new JLabel(colonIcon);

        getContentPane()->setLayout(new QHBoxLayout());//getContentPane(), BoxLayout.X_AXIS));
        getContentPane()->layout()->addWidget(h24);
        getContentPane()->layout()->addWidget(colon);
        getContentPane()->layout()->addWidget(m1);
        getContentPane()->layout()->addWidget(m2);

        getContentPane()->layout()->addWidget(b = new QPushButton(tr("Pause Clock")));
        PCButtonListener* bl = new PCButtonListener(this);
        //b->addActionListener(new ButtonListener());
        connect(bl, SIGNAL(clicked(bool)), bl, SLOT(actionPerformed()));
        // since Run/Stop button looks crummy, user may turn it on in clock prefs
        b->setVisible(clock->getShowStopButton()); // pick up clock prefs choice

        update();
        pack();

        // request callback to update time
        clock->addMinuteChangeListener(new PCMinuteChangeListener(this));
//        {
//            @Override
//             /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                update();
//            }
//        });
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
    }

    // Added method to scale the clock digit images to fit the
    // size of the display window
     /*public*/ void PragotronClockFrame::scaleImage() {
        int iconHeight10;
        int iconWidth10;
        int iconHeight24;
        int iconWidth24;
        int iconHeightDot;
        int iconWidthDot;
        int frameHeight = this->getContentPane()->size().height();
        int frameWidth = this->getContentPane()->size().width();
        if ((double) frameWidth / (double) frameHeight > aspect) {
            iconHeight10 = frameHeight;
            iconWidth10 = (int) (iconAspect10 * iconHeight10);
            iconHeight24 = frameHeight;
            iconWidth24 = (int) (iconAspect24 * iconHeight24);
            iconHeightDot = frameHeight;
            iconWidthDot = (int) (iconAspectDot * iconHeightDot);
        } else {
            // this DOES NOT allow space for the Run/Stop button, if it is enabled.
            // When the Run/Stop button is enabled, the layout will change accordingly.
            iconWidth10 = (int) (frameWidth / 664.0 * 152.0);
            iconHeight10 = (int) (iconWidth10 / iconAspect10);
            iconWidth24 = (int) (frameWidth / 664.0 * 320.0);
            iconHeight24 = (int) (iconWidth24 / iconAspect24);
            iconWidthDot = (int) (frameWidth / 664.0 * 40.0);
            iconHeightDot = (int) (iconWidthDot / iconAspectDot);
        }
        for (int i = 0; i < 10; i++) {
            QImage scaledImage = baseFoldingSheets10[i]->getImage().scaled(iconWidth10, iconHeight10/*, Image.SCALE_SMOOTH*/);
            foldingSheets10[i]->setImage(scaledImage);
        }
        for (int i = 0; i < 24; i++) {
            QImage scaledImage = baseFoldingSheets24[i]->getImage().scaled(iconWidth24, iconHeight24/*, Image.SCALE_SMOOTH*/);
            foldingSheets24[i]->setImage(scaledImage);
        }
        QImage scaledImage = baseColon->getImage().scaled(iconWidthDot , iconHeightDot/*, Image.SCALE_SMOOTH*/);
        colonIcon->setImage(scaledImage);

//      Ugly hack to force frame to redo the layout.
//      Without this the image is scaled but the label size and position doesn't change.
//      doLayout() doesn't work either
        this->setVisible(false);
        this->layout()->removeWidget(b);
        if (clock->getShowStopButton()) {
            this->getContentPane()->layout()->addWidget(b); // pick up clock prefs choice
        }
        this->setVisible(true);
        return;
    }

    //@SuppressWarnings("deprecation")
    void PragotronClockFrame::update() {
        QDateTime now = clock->getTime();
        int hours = now.time().hour();
        int minutes = now.time().minute();

        h24->setIcon(foldingSheets24[hours]);
        m1->setIcon(foldingSheets10[minutes / 10]);
        m2->setIcon(foldingSheets10[minutes - (minutes / 10) * 10]);
    }

    //@Override
     /*public*/ void PragotronClockFrame::dispose() {
        JmriJFrame::dispose();
    }

    /**
     * Handle a change to clock properties
     */
    //@Override
     /*public*/ void PragotronClockFrame::propertyChange(PropertyChangeEvent* e) {
        bool now = clock->getRun();
        if (now) {
            b->setText(tr("Pause Clock"));
        } else {
            b->setText(tr("Run Clock"));
        }
    }


//    private class ButtonListener implements ActionListener {

        //@Override
         /*public*/ void PCButtonListener::actionPerformed(/*ActionEvent a*/) {
            bool next = !frame->clock->getRun();
            frame->clock->setRun(next);
            if (next) {
                frame->b->setText(tr("Pause Clock"));
            } else {
                frame->b->setText(tr("Run Clock"));
            }
        }
    /*public*/ QString PragotronClockFrame::getClassName() {return "jmri.jmrit.pragotronclock.PragotronClockFrame";}
