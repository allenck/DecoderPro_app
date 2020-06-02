#include "lengthpanel.h"
#include "jtextfield.h"
#include "jtogglebutton.h"
#include "oblock.h"
#include "circuitbuilder.h"
#include "joptionpane.h"

/**
 * A simple panel to collect lengths with units bring either inches or centimeters
 *
 * @author Pete Cressman Copyright: Copyright (c) 2019
 *
 */

//public class LengthPanel extends JPanel
//{
    LengthPanel::LengthPanel(OBlock* block, QString label, QObject* parent)
    {
     setLayout(new QVBoxLayout());
        _block = block;

        JPanel* pp = new JPanel(new FlowLayout);
        _lengthField = new JTextField();

        _lengthField->setText("0.0");
        pp->layout()->addWidget(CircuitBuilder::makeTextBoxPanel(
                false, _lengthField, label, true, tr("Enter a length for the above named path.")));
        _lengthField->resize(QSize(100, _lengthField->sizeHint().height()));
        _units = new JToggleButton("", !_block->isMetric());
        _units->setToolTip(tr("Click to switch the unit of length between metric and imperial."));
        //_units.addActionListener((ActionEvent event) -> {
        connect(_units, &JToggleButton::toggled, [=]{
            changeUnits();
        });
        pp->layout()->addWidget(_units);
        layout()->addWidget(pp);
    }

    /*protected*/ void LengthPanel::changeUnits() {
        QString len = _lengthField->text();
        if (len == "" || len.length() == 0) {
            if (_block != nullptr && _block->isMetric()) {
                _units->setText("cm");
            } else {
                _units->setText("in");
            }
            return;
        }
        try {
         bool ok;
            float f = len.toFloat(&ok);
            if(!ok) throw NumberFormatException();
            if (_units->isChecked()) {
                _lengthField->setText(QString::number(f / 2.54f));
                _units->setText("in");
            } else {
                _lengthField->setText(QString::number(f * 2.54f));
                _units->setText("cm");
            }
        } catch (NumberFormatException nfe) {
            JOptionPane::showMessageDialog(this, tr("%1 is an invalid number. Must be a positive decimal number.").arg(len),
                    tr("Make Path"), JOptionPane::INFORMATION_MESSAGE);
        }
    }

    /**
     * Display
     * @param len length in millimeters
     */
    /*protected*/ void LengthPanel::setLength(float len) {
        _length = len;
        if (_units->isChecked()) {
            _lengthField->setText(QString::number(len / 25.4f));
        } else {
            _lengthField->setText(QString::number(len / 10));
        }
    }

    /*protected*/ float LengthPanel::getLength() {
        QString num = "";
        float f = -1;
        bool ok;
            num = _lengthField->text();
            if (num == "" || num.length() == 0) {
                num = "0.0";
            }
            f = num.toFloat(&ok);
        if(!ok) {
        }
        if (f < 0.0f) {
            JOptionPane::showMessageDialog(this, tr("%1 is an invalid number. Must be a positive decimal number.").arg(num),
                    tr("Make Path"), JOptionPane::INFORMATION_MESSAGE);
        } else {
            if (_units->isChecked()) {
                _length = f * 25.4f;
            } else {
                _length = f * 10.f;
            }
        }
        return _length;
    }

    /*protected*/ bool LengthPanel::isChanged(float len) {
        return qAbs(getLength() - len) > .5;
    }
