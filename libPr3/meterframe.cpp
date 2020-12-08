#include "meterframe.h"
#include "loggerfactory.h"
#include "metermanager.h"
#include "instancemanager.h"
#include "runtimeexception.h"
#include "abstractaction.h"
#include "meter.h"
#include "defaultmeter.h"
#include <QMenuBar>
#include <QMenu>
#include "borderfactory.h"
#include "meterframemanager.h"
#include "insets.h"
#include <QStringList>
#include <QString>
#include <QChar>
#include "abstractmetermanager.h"

/**
 * Frame providing a simple LCD-based display of track voltage.
 * <p>
 * @author Ken Cameron        Copyright (C) 2007
 * @author Mark Underwood     Copyright (C) 2007
 * @author Andrew Crosland    Copyright (C) 2020
 * @author Daniel Bergqvist   Copyright (C) 2020
 * @author B. Milhaupt        Copyright (C) 2020
 *
 * Adapted from ammeter to display voltage and current.
 */
// /*public*/ class MeterFrame extends JmriJFrame {


    /*private*/ /*static*/ /*final*/ int MeterFrame::MAX_INTEGER_DIGITS = 7;
    /*private*/ /*static*/ /*final*/ int MeterFrame::MAX_DECIMAL_DIGITS = 3;


//    /*public*/ MeterFrame::MeterFrame() {
//        this(UUID.randomUUID());
//    }

    /*public*/ MeterFrame::MeterFrame(QUuid uuid, QWidget *parent) : JmriJFrame(tr("Voltage Meter"),parent){
        //super(Bundle.valueMessage("VoltageMeterTitle"));
        Unit::values->insert(Unit::Percent,  Unit(Unit::Percent));    // Not a unit, but here anyway
        Unit::values->insert(Unit::MicroVolt, Unit(Unit::MicroVolt));
        Unit::values->insert(Unit::MilliVolt, Unit(Unit::MilliVolt));
        Unit::values->insert(Unit::Volt, Unit(Unit::Volt ));
        Unit::values->insert(Unit::KiloVolt, Unit(Unit::KiloVolt ));
        Unit::values->insert(Unit::MicroAmpere, Unit(Unit::MicroAmpere));
        Unit::values->insert(Unit::MilliAmpere, Unit(Unit::MilliAmpere));
        Unit::values->insert(Unit::Ampere, Unit(Unit::Ampere));
        Unit::values->insert(Unit::KiloAmpere, Unit(Unit::KiloAmpere));

        Unit::factors->insert(Unit::Percent, 1.0);    // Not a unit, but here anyway
        Unit::factors->insert(Unit::MicroVolt, 1000*1000);
        Unit::factors->insert(Unit::MilliVolt, 1000);
        Unit::factors->insert(Unit::Volt, 1.0);
        Unit::factors->insert(Unit::KiloVolt, 1/1000.0);
        Unit::factors->insert(Unit::MicroAmpere, 1000*1000);
        Unit::factors->insert(Unit::MilliAmpere, 1000);
        Unit::factors->insert(Unit::Ampere, 1.0);
        Unit::factors->insert(Unit::KiloAmpere, 1/1000.0);

        Unit::names->insert(Unit::Percent, "Percent");    // Not a unit, but here anyway
        Unit::names->insert(Unit::MicroVolt, "MicroVolt");
        Unit::names->insert(Unit::MilliVolt, "MilliVolt");
        Unit::names->insert(Unit::Volt, "Volt");
        Unit::names->insert(Unit::KiloVolt, "KiloVolt");
        Unit::names->insert(Unit::MicroAmpere, "MicroAmpere");
        Unit::names->insert(Unit::MilliAmpere, "MilliAmpere");
        Unit::names->insert(Unit::Ampere, "Ampere");
        Unit::names->insert(Unit::KiloAmpere, "KiloAmpere");


        this->uuid = uuid;

        MeterManager* mm = (MeterManager*)InstanceManager::getNullableDefault("MeterManager");
        if (mm == nullptr) throw RuntimeException("No meter manager exists");

        addAllMeters();

        if (!voltageMeters.isEmpty()) {
            setMeter(voltageMeters.value(0));
        } else if (!currentMeters.isEmpty()) {
            setMeter(currentMeters.value(0));
        } else {
            setTitle(tr("Voltage Meter"));
        }

        MeterFrameManager::getInstance()->_register(this);
    }

    /**
     * Get the UUID of this frame.
     * <P>
     * The UUID is used if two different panel files are loaded with the same
     * meter frame.
     *
     * @return the UUID of this frame
     */
    /*public*/ QUuid MeterFrame::getUUID() {
        return uuid;
    }

    /**
     * Get the meter that is displayed
     * @return the meter
     */
    /*public*/ Meter* MeterFrame::getMeter() {
        return meter;
    }

    /**
     * Set the meter that is displayed.
     * @param m the meter or null if no meter is to be shown
     */
    /*public*/ void MeterFrame::setMeter(Meter* m) {
        if (lastSelectedMeterMenuItem != nullptr) lastSelectedMeterMenuItem->setChecked(false);

        if (meter != nullptr) {
            meter->disable();
            ((DefaultMeter*)meter->self())->removePropertyChangeListener(NamedBean::PROPERTY_STATE, propertyChangeListener);
        }

        meter = m;

        if (meter == nullptr) return;

        ((DefaultMeter*)meter->self())->addPropertyChangeListener(NamedBean::PROPERTY_STATE, propertyChangeListener);
        ((DefaultMeter*)meter->self())->enable();

        if (frameIsInitialized) {
            // Initially we want to scale the icons to fit the previously saved window size
            scaleImage();

            QAction* menuItem = meter_MenuItemMap.value(meter);
            menuItem->setCheckable(true);
            menuItem->setChecked(true);
            lastSelectedMeterMenuItem = menuItem;

            updateMenuUnits();
            initSelectedUnit();
        }

        if (qobject_cast<VoltageMeter*>(meter->self())) {
            setTitle(tr("Voltage Meter - %1").arg(((DefaultMeter*)meter)->getDisplayName()));
        } else {
            setTitle(tr("Current Meter - %1").arg(((DefaultMeter*)meter)->getDisplayName()));
        }
    }
    /*public*/ /*static*/ QMap<MeterFrame::Unit::UNITS, MeterFrame::Unit>* MeterFrame::Unit::values = new QMap<MeterFrame::Unit::UNITS, MeterFrame::Unit>();
    /*public*/ /*static*/ QMap<MeterFrame::Unit::UNITS, double>* MeterFrame::Unit::factors = new QMap<MeterFrame::Unit::UNITS, double>();
    /*public*/ /*static*/ QMap<MeterFrame::Unit::UNITS, QString>* MeterFrame::Unit::names = new QMap<MeterFrame::Unit::UNITS, QString>();

    //@Override
    /*public*/ void MeterFrame::initComponents() {
        MeterManager* mm = ((MeterManager*)InstanceManager::getNullableDefault("MeterManager"));
        if (mm == nullptr) {
            return;
        }
        mm->addDataListener(new /*MeterFrame::*/BeanListListener(this));
        // Create menu bar

        menuBar = new QMenuBar();
        voltageMetersMenu = new QMenu(tr("Voltage Meters"));
        menuBar->addMenu(voltageMetersMenu);
        for (Meter* m : voltageMeters) {
            QAction* item = new SelectMeterAction(((DefaultMeter*)m)->getDisplayName(), m, this);
            item->setCheckable(true);
            voltageMetersMenu->addAction(item);
            meter_MenuItemMap.insert(m, item);
        }

        currentMetersMenu = new QMenu(tr("Current Meters"));
        menuBar->addMenu(currentMetersMenu);
        for (Meter* m : currentMeters) {
            QAction* item = new SelectMeterAction(((DefaultMeter*)m)->getDisplayName(), m, this);
            item->setCheckable(true);
            currentMetersMenu->addAction(item);
            meter_MenuItemMap.insert(m, item);
        }

        QMenu* settingsMenu = new QMenu(tr("Meter Settings"));
        menuBar->addMenu(settingsMenu);

        //for (Unit unit : Unit::values())
        for(Unit unit : Unit::values->values())
        {
            /*final*/ MeterFrame::Unit::UNITS u = unit.u;
            AbstractAction* item = new AbstractAction(tr("Meter_")+unit.name,this);
            item->setCheckable(true);
//            {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
              connect(item, &AbstractAction::triggered, [=]{
                    units_MenuItemMap.value(selectedUnit.u)->setChecked(false);
                    unitLabels.value(selectedUnit.u)->setVisible(false);
                    units_MenuItemMap.value(u)->setChecked(true);
                    unitLabels.value(u)->setVisible(true);
                    selectedUnit = unit;
                    update();
//                }
            });
            units_MenuItemMap.insert(unit.u, item);
            settingsMenu->addAction(item);
        }

        settingsMenu->addSeparator();

        for (int i=1; i <= MAX_INTEGER_DIGITS; i++) {
            /*final*/ int ii = i;
            AbstractAction* item = new AbstractAction(tr("%1 integer digits").arg(i),this);
            item->setCheckable(true);
            connect(item, &AbstractAction::triggered, [=]{
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
                    integerDigits_MenuItemMap.value(numIntegerDigits)->setChecked(false);
                    numIntegerDigits = ii;
                    update();
//                }
            });
            integerDigits_MenuItemMap.insert(ii, item);
            settingsMenu->addAction(item);
            if (ii == numIntegerDigits) item->setChecked(true);
        }
        settingsMenu->addSeparator();
        for (int i=0; i <= MAX_DECIMAL_DIGITS; i++) {
            /*final*/ int ii = i;
            AbstractAction* item = new AbstractAction(tr("%1 decimal digits").arg(i),this);
            item->setCheckable(true);
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
            connect(item, &AbstractAction::triggered, [=]{
                    decimalDigits_MenuItemMap.value(numDecimalDigits)->setChecked(false);
                    decimalDigits_MenuItemMap.value(ii)->setChecked(true);
                    numDecimalDigits = ii;
                    update();
//                }
            });
            decimalDigits_MenuItemMap.insert(ii, item);
            settingsMenu->addAction(item);
            if (ii == numDecimalDigits) item->setChecked(true);
        }

        setMenuBar(menuBar);

        // clear the contents
        getContentPane()->removeAll();

        pane1 = new JPanel();
        pane1->setLayout(new QVBoxLayout());//pane1, BoxLayout.Y_AXIS));

        meterPane = new JPanel();
//        meterPane->setBorder(BorderFactory::createTitledBorder(
//            BorderFactory::createEtchedBorder()));

        // build the actual multimeter display.
        meterPane->setLayout(new QHBoxLayout());//meterPane, BoxLayout.X_AXIS));

        //Load the images (these are now the larger version of the original gifs
        for (int i = 0; i < 10; i++) {
            integerDigits[i] = new NamedIcon(QString("resources/icons/misc/LCD/Lcd_") + QString::number(i) + "b.GIF", QString("resources/icons/misc/LCD/Lcd_") + QString::number(i) + "b.GIF");
        }
        for (int i = 0; i < 10; i++) {
            decimalDigits[i] = new NamedIcon(QString("resources/icons/misc/LCD/Lcd_") + QString::number(i) + "b.GIF", QString("resources/icons/misc/LCD/Lcd_") + QString::number(i) + "b.GIF");
        }
        decimalIcon = new NamedIcon("resources/icons/misc/LCD/decimalb.gif", "resources/icons/misc/LCD/decimalb.gif");
        microVoltIcon = new NamedIcon("resources/icons/misc/LCD/uvoltb.gif", "resources/icons/misc/LCD/uvoltb.gif");
        milliVoltIcon = new NamedIcon("resources/icons/misc/LCD/mvoltb.gif", "resources/icons/misc/LCD/mvoltb.gif");
        voltIcon = new NamedIcon("resources/icons/misc/LCD/voltb.gif", "resources/icons/misc/LCD/voltb.gif");
        kiloVoltIcon = new NamedIcon("resources/icons/misc/LCD/kvoltb.gif", "resources/icons/misc/LCD/kvoltb.gif");
        microAmpIcon = new NamedIcon("resources/icons/misc/LCD/uampb.gif", "resources/icons/misc/LCD/uampb.gif");
        milliAmpIcon = new NamedIcon("resources/icons/misc/LCD/mampb.gif", "resources/icons/misc/LCD/mampb.gif");
        ampIcon = new NamedIcon("resources/icons/misc/LCD/ampb.gif", "resources/icons/misc/LCD/ampb.gif");
        kiloAmpIcon = new NamedIcon("resources/icons/misc/LCD/kampb.gif", "resources/icons/misc/LCD/kampb.gif");
        percentIcon = new NamedIcon("resources/icons/misc/LCD/percentb.gif", "resources/icons/misc/LCD/percentb.gif");
        errorIcon = new NamedIcon("resources/icons/misc/LCD/Lcd_Error.GIF", "resources/icons/misc/LCD/Lcd_Error.GIF");

        decimal = new JLabel(decimalIcon);
        unitLabels.insert(Unit::Percent, new JLabel(percentIcon));
        unitLabels.insert(Unit::MicroVolt, new JLabel(microVoltIcon));
        unitLabels.insert(Unit::MilliVolt, new JLabel(milliVoltIcon));
        unitLabels.insert(Unit::Volt, new JLabel(voltIcon));
        unitLabels.insert(Unit::KiloVolt, new JLabel(kiloVoltIcon));
        unitLabels.insert(Unit::MicroAmpere, new JLabel(microAmpIcon));
        unitLabels.insert(Unit::MilliAmpere, new JLabel(milliAmpIcon));
        unitLabels.insert(Unit::Ampere, new JLabel(ampIcon));
        unitLabels.insert(Unit::KiloAmpere, new JLabel(kiloAmpIcon));

        for (Unit unit : Unit::values->values())
         unitLabels.value(unit.u)->setVisible(false);

        integerDigitIcons = QVector<JLabel*>(MAX_INTEGER_DIGITS);
        for(int i = 0; i < MAX_INTEGER_DIGITS; i++) {
            integerDigitIcons.replace(i,new JLabel(integerDigits[i]));
            meterPane->layout()->addWidget(integerDigitIcons.value(i));
        }

        meterPane->layout()->addWidget(decimal);

        decimalDigitIcons = QVector<JLabel*>(MAX_DECIMAL_DIGITS);
        for(int i = 0; i < MAX_DECIMAL_DIGITS; i++) {
            decimalDigitIcons.replace(i,new JLabel(decimalDigits[i]));
            meterPane->layout()->addWidget(decimalDigitIcons.value(i));
        }

        for (JLabel* label : unitLabels.values()) meterPane->layout()->addWidget(label);

        iconHeight = integerDigits[0]->getIconHeight();
        digitIconWidth = integerDigits[0]->getIconWidth();
        decimalIconWidth = decimalIcon->getIconWidth();
        unitIconWidth = milliVoltIcon->getIconWidth();

        // Initially we want to scale the icons to fit the previously saved window size
        scaleImage();

        if (meter != nullptr) {
            meter->enable();
        }

        updateMenuUnits();
        initSelectedUnit();

        // Request callback to update time
        //propertyChangeListener = (PropertyChangeEvent e) -> {
            update();
        //};
        if (meter != nullptr) {
            ((DefaultMeter*)meter)->addPropertyChangeListener(NamedBean::PROPERTY_STATE, propertyChangeListener);
        }
#if 0 // TODO:
        // Add component listener to handle frame resizing event
        this->addComponentListener(
                new ComponentAdapter() {
            //@Override
            /*public*/ void componentResized(ComponentEvent e) {
                scaleImage();
            }
        });
#endif
        pane1->layout()->addWidget(meterPane);
        JPanel* cw = getContentPane();
        QLayout* lo = cw->layout();
        if(lo == nullptr)
         cw->setLayout(new QVBoxLayout());
        getContentPane()->layout()->addWidget(pane1);

        getContentPane()->resize(meterPane->sizeHint());

        pack();

        frameIsInitialized = true;
    }

    /*private*/ void MeterFrame::initSelectedUnit() {
        bool isPercent = (meter != nullptr) && (((DefaultMeter*)meter)->getUnit() == Meter::Unit::Percent);
        bool isVoltage = (meter != nullptr) && qobject_cast<VoltageMeter*>(meter->self()) && !isPercent;
        bool isCurrent = (meter != nullptr) && (qobject_cast<CurrentMeter*>(meter->self())) && !isPercent;

        units_MenuItemMap.value(selectedUnit.u)->setChecked(false);
        unitLabels.value(selectedUnit.u)->setVisible(false);

        if (isPercent) selectedUnit.u = Unit::Percent;
        else if (isVoltage && (((DefaultMeter*)meter)->getUnit() == Meter::Unit::Milli)) selectedUnit.u = Unit::MilliVolt;
        else if (isVoltage) selectedUnit.u = Unit::Volt;
        else if (isCurrent && (((DefaultMeter*)meter)->getUnit() == Meter::Unit::Milli)) selectedUnit.u = Unit::MilliAmpere;
        else selectedUnit.u = Unit::Ampere;

        units_MenuItemMap.value(selectedUnit.u)->setChecked(true);
        unitLabels.value(selectedUnit.u)->setVisible(true);
        update();
    }

    // Added method to scale the clock digit images to fit the
    // size of the display window
    /*synchronized*/ /*public*/ void MeterFrame::scaleImage() {

        int frameHeight = this->getContentPane()->getHeight()
                - meterPane->getInsets(new Insets())->top - meterPane->getInsets(new Insets())->bottom;
        int frameWidth = this->getContentPane()->width()
                - meterPane->getInsets(new Insets())->left - meterPane->getInsets(new Insets())->right;

        double hscale = ((double)frameHeight)/((double)iconHeight);
        double wscale = ((double)frameWidth)/((double)widthOfAllIconsToDisplay);
        double scale = hscale < wscale? hscale:wscale;

        for (int i = 0; i < 10; i++) {
            integerDigits[i]->scale(scale,this);
        }
        for (int i = 0; i < 10; i++) {
            decimalDigits[i]->scale(scale,this);
        }
        decimalIcon->scale(scale,this);
        microVoltIcon->scale(scale,this);
        milliVoltIcon->scale(scale,this);
        voltIcon->scale(scale,this);
        kiloVoltIcon->scale(scale,this);
        microAmpIcon->scale(scale,this);
        milliAmpIcon->scale(scale,this);
        ampIcon->scale(scale, this);
        kiloAmpIcon->scale(scale,this);
        percentIcon->scale(scale, this);
        errorIcon->scale(scale, this);

        meterPane->update();// revalidate();
        this->getContentPane()->update(); //revalidate();
    }

    /*private*/ void MeterFrame::updateMenuUnits() {
        bool isPercent = (meter != nullptr) && (((DefaultMeter*)meter->self())->getUnit() == Meter::Unit::Percent);
        bool isVoltage = (meter != nullptr) && (qobject_cast<VoltageMeter*>(meter->self())) && !isPercent;
        bool isCurrent = (meter != nullptr) && (qobject_cast<CurrentMeter*>(meter->self())) && !isPercent;

        units_MenuItemMap.value(Unit::Percent)->setVisible(isPercent);

        units_MenuItemMap.value(Unit::MicroVolt)->setVisible(isVoltage);
        units_MenuItemMap.value(Unit::MilliVolt)->setVisible(isVoltage);
        units_MenuItemMap.value(Unit::Volt)->setVisible(isVoltage);
        units_MenuItemMap.value(Unit::KiloVolt)->setVisible(isVoltage);

        units_MenuItemMap.value(Unit::MicroAmpere)->setVisible(isCurrent);
        units_MenuItemMap.value(Unit::MilliAmpere)->setVisible(isCurrent);
        units_MenuItemMap.value(Unit::Ampere)->setVisible(isCurrent);
        units_MenuItemMap.value(Unit::KiloAmpere)->setVisible(isCurrent);
    }

    /*private*/ void MeterFrame::showError() {
        for (int i=0; i < MAX_INTEGER_DIGITS; i++) {
            JLabel* label = integerDigitIcons.value(i);
            if (i < numIntegerDigits) {
                label->setIcon(errorIcon);
                label->setVisible(true);
            } else {
                label->setVisible(false);
            }
        }

        decimal->setVisible(numDecimalDigits > 0);

        for (int i=0; i < MAX_DECIMAL_DIGITS; i++) {
            JLabel* label = decimalDigitIcons.value(i);
            if (i < numDecimalDigits) {
                label->setIcon(errorIcon);
                label->setVisible(true);
            } else {
                label->setVisible(false);
            }
        }

        // Add width of integer digits
        widthOfAllIconsToDisplay = digitIconWidth * numIntegerDigits;

        // Add decimal point
        if (numDecimalDigits > 0) widthOfAllIconsToDisplay += decimalIconWidth;

        // Add width of decimal digits
        widthOfAllIconsToDisplay += digitIconWidth * numDecimalDigits;

        // Add one for the unit icon
        widthOfAllIconsToDisplay += unitIconWidth;

        if (widthOfAllIconsToDisplay != oldWidthOfAllIconsToDisplay){
            // clear the content pane and rebuild it.
            scaleImage();
            oldWidthOfAllIconsToDisplay = widthOfAllIconsToDisplay;
        }
    }

    /**
     * Update the displayed value.
     *
     * Assumes an integer value has an extra, non-displayed decimal digit.
     */
    /*synchronized*/ void MeterFrame::update() {
        if (meter == nullptr) {
            showError();
            return;
        }

        double meterValue = ((DefaultMeter*)meter)->getKnownAnalogValue() * selectedUnit.multiply;

        switch (((DefaultMeter*)meter)->getUnit()) {
            case Meter::Kilo:
                meterValue *= 1000.0;
                break;

            case Meter::Milli:
                meterValue /= 1000.0;
                break;

            case Meter::Micro:
                meterValue /= 1000000.0;
                break;

            case Meter::NoPrefix:
            case Meter::Percent:
            default:
             break;
                // Do nothing
        }

        // We want at least one decimal digit so we cut the last digit later.
        // The problem is that the format string %05.0f will not add the dot
        // and we always want the dot to be able to split the string by the dot.
        int numChars = numIntegerDigits + numDecimalDigits + 2;
        QString formatStr = tr("%%0%1.%2f").arg(numChars).arg(numDecimalDigits+1);
        QString valueStr1 = QString("%1").arg(meterValue, 0, 'f', numDecimalDigits+1);
        //QString valueStr = QString(formatStr).arg(meterValue);

        QStringList valueParts = valueStr1.split(".");

        // Show error if we don't have enough integer digits to show the result
        if (valueParts[0].length() > MAX_INTEGER_DIGITS) {
            showError();
            return;
        }

        for (int i=0; i < MAX_INTEGER_DIGITS; i++) {
            JLabel* label = integerDigitIcons.value(i);
            if (i < valueParts[0].length()) {
                label->setIcon(integerDigits[valueParts.at(0).at(i).toLatin1()-'0']);
                label->setVisible(true);
            } else {
                label->setVisible(false);
            }
        }

        decimal->setVisible(numDecimalDigits > 0);

        for (int i=0; i < MAX_DECIMAL_DIGITS; i++) {
            JLabel* label = decimalDigitIcons.value(i);
            if (i < valueParts[1].length()-1) {     // the decimal part has one digit too much
                label->setIcon(integerDigits[valueParts[1].at(i).toLatin1()-'0']);
                label->setVisible(true);
            } else {
                label->setVisible(false);
            }
        }


        // Add width of integer digits
        widthOfAllIconsToDisplay = digitIconWidth * valueParts[0].length();

        // Add decimal point
        if (numDecimalDigits > 0) widthOfAllIconsToDisplay += decimalIconWidth;

        // Add width of decimal digits
        widthOfAllIconsToDisplay += digitIconWidth * (valueParts[1].length()-1);

        // Add one for the unit icon
        widthOfAllIconsToDisplay += unitIconWidth;

        if (widthOfAllIconsToDisplay != oldWidthOfAllIconsToDisplay){
            // clear the content pane and rebuild it.
            scaleImage();
            oldWidthOfAllIconsToDisplay = widthOfAllIconsToDisplay;
        }
    }

    //@Override
    /*public*/ void MeterFrame::dispose() {
        if (meter != nullptr) {
            ((DefaultMeter*)meter)->disable();
            ((DefaultMeter*)meter)->removePropertyChangeListener(propertyChangeListener);
        }
        MeterFrameManager::getInstance()->deregister(this);
        JmriJFrame::dispose();
    }

    /**
     * Returns the number of integer digits.
     *
     * @return the number of integer digits
     */
    /*public*/ int MeterFrame::getNumIntegerDigits() {
        return numIntegerDigits;
    }

    /**
     * Sets the number of integer digits.
     *
     * @param digits the number of integer digits
     */
    /*public*/ void MeterFrame::setNumIntegerDigits(int digits) {
        integerDigits_MenuItemMap.value(numIntegerDigits)->setChecked(false);
        integerDigits_MenuItemMap.value(digits)->setChecked(true);
        numIntegerDigits = digits;
        update();
    }

    /**
     * Returns the number of integer digits.
     *
     * @return the number of integer digits
     */
    /*public*/ int MeterFrame::getNumDecimalDigits() {
        return numDecimalDigits;
    }

    /**
     * Sets the number of decimal digits.
     *
     * @param digits the number of decimal digits
     */
    /*public*/ void MeterFrame::setNumDecimalDigits(int digits) {
        decimalDigits_MenuItemMap.value(numDecimalDigits)->setChecked(false);
        decimalDigits_MenuItemMap.value(digits)->setChecked(true);
        numDecimalDigits = digits;
        update();
    }

    /**
     * Returns the Unit::
     *
     * @return the unit
     */
    /*public*/ MeterFrame::Unit MeterFrame::getUnit() {
        return selectedUnit;
    }

    /**
     * Sets the Unit::
     *
     * @param unit the unit
     */
    /*public*/ void MeterFrame::setUnit(MeterFrame::Unit unit) {
        units_MenuItemMap.value(selectedUnit.u)->setChecked(false);
        unitLabels.value(selectedUnit.u)->setVisible(false);
        units_MenuItemMap.value(unit.u)->setChecked(true);
        unitLabels.value(unit.u)->setVisible(true);
        selectedUnit = unit;
        update();
    }

    /**
     * updates the list of available meters
     */
    /*private*/ void MeterFrame::addAllMeters() {
        MeterManager* mm = (MeterManager*)InstanceManager::getNullableDefault("MeterManager");
        if (mm == nullptr) {
            return;
        }
        log->debug(tr("attempting to add all meters.  There are %1 meters to add.").arg(
                mm->getNamedBeanSet().size()));
        //mm->getNamedBeanSet().forEach((m) ->
        foreach(NamedBean* bean, mm->getNamedBeanSet())
        {
         DefaultMeter* m = (DefaultMeter*)bean;
         if ((m != nullptr) && (qobject_cast<VoltageMeter*>(m->self()))) {
             if (voltageMeters.contains(m)) {
                 log->debug(tr("meter %1 is already present").arg(((DefaultMeter*)m)->getDisplayName()));
             } else {
                 voltageMeters.append(m);
                 log->debug(tr("Added voltage meter %1").arg(((DefaultMeter*)m)->getSystemName()));
             }
         } else if ((m != nullptr) && (qobject_cast<CurrentMeter*>(m->self()))) {
             if (currentMeters.contains(m)) {
                 log->debug(tr("meter %1 is already present").arg(((DefaultMeter*)m)->getDisplayName()));
             } else {
                 currentMeters.append(m);
             }
         }
        }//);

        if ((menuBar != nullptr) && (voltageMetersMenu != nullptr)) {
            updateVoltageMeters(voltageMetersMenu);
        }

        if ((menuBar != nullptr) && (currentMetersMenu != nullptr)) {
            updateCurrentMeters(currentMetersMenu);
        }
    }

    /**
     * Update the list of menu items for available meters of a given "Voltage Meters"
     * @param voltageMetersMenu Menu which contains available voltage meters list
     */
    /*private*/ void MeterFrame::updateVoltageMeters(QMenu* voltageMetersMenu) {
        for (Meter* m : voltageMeters) {
            log->debug(tr("Need to add a new checkbox for voltmeter %1?").arg(((DefaultMeter*)meter)->getDisplayName()));
            bool found = false;

            if (voltageMetersMenu->actions().count() > 0) {
                for (int i =0; (i < voltageMetersMenu->actions().count()) && (!found);++i) {
                    QAction* jim = voltageMetersMenu->actions().at(i);
                    if (qobject_cast<QAction*>(jim)) {
                        if (jim->text().compare(((DefaultMeter*)meter)->getDisplayName()) == 0 ) {
                            log->debug(tr("item %1 is already in voltageMetersMenu").arg(((DefaultMeter*)meter)->getDisplayName()));
                            found = true;
                        } else {
                            log->debug(tr("item %1 is not already in voltageMetersMenu").arg(((DefaultMeter*)meter)->getDisplayName()));
                        }
                    }
                }
            }
            if (!found) {
                log->debug(tr("Adding item %1 to voltageMetersMenu").arg(((DefaultMeter*)meter)->getDisplayName()));
                QAction* item = new QAction(new SelectMeterAction(((DefaultMeter*)meter)->getDisplayName(), m, this));
                item->setCheckable(true);
                voltageMetersMenu->addAction(item);
                meter_MenuItemMap.insert(m, item);
            }
        }
    }

    /**
     * Update the list of menu items for available "Current Meters"
     * @param currentMetersMenu Menu which contains available current meters list

     */
    /*private*/ void MeterFrame::updateCurrentMeters(QMenu* currentMetersMenu) {
        for (Meter* m : currentMeters) {
            log->debug(tr("need to add a new checkbox for ammeter %1?").arg(((DefaultMeter*)meter)->getDisplayName()));
            bool found = false;

            if (currentMetersMenu->actions().count() > 0) {
                for (int i =0; (i < currentMetersMenu->actions().count()) && (!found);++i) {
                    QAction* jim = currentMetersMenu->actions().at(i);
                    if (qobject_cast<QAction*>(jim)) {
                        if (jim->text().compare(((DefaultMeter*)meter)->getDisplayName()) == 0 ) {
                            log->debug(tr("item %1 is already in currentMetersMenu").arg(((DefaultMeter*)meter)->getDisplayName()));
                            found = true;
                        } else {
                            log->debug(tr("item %1 is not already in currentMetersMenu").arg(((DefaultMeter*)meter)->getDisplayName()));
                        }
                    }
                }
            }
            if (!found) {
                log->debug(tr("Adding item %1 to currentMetersMenu").arg(((DefaultMeter*)meter)->getDisplayName()));
                QAction* item = new QAction(new SelectMeterAction(((DefaultMeter*)meter)->getDisplayName(), m,this));
                currentMetersMenu->addAction(item);
                meter_MenuItemMap.insert(m, item);
            }
        }
    }

    /**
     * Updates the menu items in the voltage meters and current meters menus.
     */
    /*private*/ void MeterFrame::updateCheckboxList() {
        log->debug("Updating the checkbox lists of meters.");
        addAllMeters();
        currentMetersMenu->update();//repaint();
        voltageMetersMenu->update();//.repaint();
        return;
    }
#if 0
    /**
     * Provides hooks so that menus of available meters may be updated "on-the-fly"
     * as new meters are created and/or old meters are disposed of.
     */
    /*private*/ static class BeanListListener implements Manager.ManagerDataListener<Meter> {

        /*private*/ BeanListListener(MeterFrame mf) {
            this.mf = mf;
        }
        MeterFrame mf = null;

        @Override
        /*public*/ void contentsChanged(Manager.ManagerDataEvent<Meter> e) {
            log.warn("contents of the bean list changed.");
            mf.updateCheckboxList();
        }

        @Override
        /*public*/ void intervalRemoved(Manager.ManagerDataEvent<Meter> e) {
            mf.updateCheckboxList();
        }

        @Override
        /*public*/ void intervalAdded(Manager.ManagerDataEvent<Meter> e) {
            mf.updateCheckboxList();
        }
    }

    /**
     * Mechanism for acting upon selection of a meter from one of the menu items.
     */
    /*public*/ class SelectMeterAction extends AbstractAction {

        /*private*/ /*final*/ Meter m;

        /*public*/ SelectMeterAction(String actionName, Meter meter) {
            super(actionName);
            this.m = meter;
        }

        @Override
        /*public*/ void actionPerformed(ActionEvent e) {
            setMeter(m);

            JMenuItem selectedItem = (JMenuItem) e.valueSource();
            selectedItem.setSelected(true);
            lastSelectedMeterMenuItem = selectedItem;
        }
    }

#endif
    /*private*/ /*final*/ /*static*/ Logger* MeterFrame::log = LoggerFactory::getLogger("MeterFrame");
