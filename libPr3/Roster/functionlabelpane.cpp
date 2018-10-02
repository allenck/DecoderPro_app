#include "functionlabelpane.h"
#include "loggerfactory.h"
#include "rosterentry.h"
#include "gridbagconstraints.h"
#include "gridbaglayout.h"
#include "hardcopywriter.h"

/**
 * Display and edit the function labels in a RosterEntry.
 *
 * @author Bob Jacobsen Copyright (C) 2008
 * @author Randall Wood Copyright (C) 2014
 */
///*public*/ class FunctionLabelPane extends javax.swing.JPanel {


    /**
     * This constructor allows the panel to be used in visual bean editors, but
     * should not be used in code.
     */
    /*public*/ FunctionLabelPane::FunctionLabelPane(QWidget *parent) : QWidget(parent){
        //super();
        maxfunction = 28;
        print = false;

    }

    /*public*/ FunctionLabelPane::FunctionLabelPane(RosterEntry* r, QWidget *parent) : QWidget(parent){
        //super();
        maxfunction = 28;
        print = false;

        re = r;

        GridBagLayout* gbLayout = new GridBagLayout();
        GridBagConstraints cL =  GridBagConstraints();
        setLayout(gbLayout);

        labels =  QVector<JTextField*>(maxfunction + 1);
        lockable = QVector<QCheckBox*>(maxfunction + 1);
        shunterMode = QVector<QRadioButton*>(maxfunction + 1);
        shunterModeGroup = new QButtonGroup();
        _imageFilePath = QVector<EditableResizableImagePanel*>(maxfunction + 1);
        _imagePressedFilePath = QVector<EditableResizableImagePanel*>(maxfunction + 1);

        cL.gridx = 0;
        cL.gridy = 0;
        cL.ipadx = 3;
        cL.anchor = GridBagConstraints::NORTHWEST;
        cL.insets = new Insets(0, 0, 0, 15);
        cL.fill = GridBagConstraints::HORIZONTAL;
        cL.weighty = 1.0;
        int nextx = 0;

        // first column
        gbLayout->addWidget(new QLabel(tr("fn")), cL);
        cL.gridx++;
        gbLayout->addWidget(new QLabel(tr("label")), cL);
        cL.gridx++;
        gbLayout->addWidget(new QLabel(tr("lock")), cL);
        cL.gridx++;
        gbLayout->addWidget(new QLabel(tr("off")), cL);
        cL.gridx++;
        gbLayout->addWidget(new QLabel(tr("on")), cL);
        cL.gridx++;
        gbLayout->addWidget(new QLabel(tr("shunt")), cL);
        cL.gridx++;
        // second column
        gbLayout->addWidget(new QLabel(tr("fn")), cL);
        cL.gridx++;
        gbLayout->addWidget(new QLabel(tr("label")), cL);
        cL.gridx++;
        gbLayout->addWidget(new QLabel(tr("lock")), cL);
        cL.gridx++;
        gbLayout->addWidget(new QLabel(tr("off")), cL);
        cL.gridx++;
        gbLayout->addWidget(new QLabel(tr("on")), cL);
        cL.gridx++;
        gbLayout->addWidget(new QLabel(tr("shunt")), cL);
        cL.gridx++;

        cL.gridx = 0;
        cL.gridy = 1;
        for (int i = 0; i <= maxfunction; i++) {
            // label the row
            gbLayout->addWidget(new QLabel("" + i), cL);
            cL.gridx++;

            // gbLayout->addWidget the label
            labels[i] = new JTextField(20);
            if (r->getFunctionLabel(i) != NULL) {
                labels[i]->setText(r->getFunctionLabel(i));
            }
            gbLayout->addWidget(labels[i], cL);
            cL.gridx++;

            // gbLayout->addWidget the checkbox
            lockable[i] = new QCheckBox();
            lockable[i]->setChecked(r->getFunctionLockable(i));
            gbLayout->addWidget(lockable[i], cL);
            cL.gridx++;

            // gbLayout->addWidget the function buttons
            _imageFilePath[i] = new EditableResizableImagePanel(r->getFunctionImage(i), 20, 20);
            _imageFilePath[i]->setDropFolder(LocoFile::getFileLocation());
            _imageFilePath[i]->setBackground(QColor(0, 0, 0, 0));
            _imageFilePath[i]->setToolTip(tr("Image for function button"));
// TODO:           _imageFilePath[i].setBorder(BorderFactory.createLineBorder(java.awt.Color.blue));
            _imageFilePath[i]->setStyleSheet("QLineEdit{border: 1px solid blue}");
            gbLayout->addWidget(_imageFilePath[i], cL);
            cL.gridx++;

            _imagePressedFilePath[i] = new EditableResizableImagePanel(r->getFunctionSelectedImage(i), 20, 20);
            _imagePressedFilePath[i]->setDropFolder(LocoFile::getFileLocation());
            _imagePressedFilePath[i]->setBackground(QColor(0, 0, 0, 0));
            _imagePressedFilePath[i]->setToolTip(tr("Image for activated function button"));
// TODO:           _imagePressedFilePath[i].setBorder(BorderFactory.createLineBorder(java.awt.Color.blue));
            _imagePressedFilePath[i]->setStyleSheet("QLineEdit{border: 1px solid blue}");
            gbLayout->addWidget(_imagePressedFilePath[i], cL);
            cL.gridx++;

            shunterMode[i] = new QRadioButton();
            shunterModeGroup->addButton(shunterMode[i]);
            if (("F" + QString::number(i)) == (r->getShuntingFunction())) {
                shunterMode[i]->setChecked(true);
            }
            gbLayout->addWidget(shunterMode[i], cL);
            cL.gridx++;

            // advance position
            cL.gridy++;
            if (cL.gridy - 1 == ((maxfunction + 1) / 2) + 1) {
                cL.gridy = 1;  // skip titles
                nextx = nextx + 6;
            }
            cL.gridx = nextx;
        }
    }

    /**
     * Check if panel contents differ with a RosterEntry.
     *
     * @param r the roster entry to check
     * @return true if panel contents differ; false otherwise
     */
    /*public*/ bool FunctionLabelPane::guiChanged(RosterEntry* r) {
        if (!labels.isEmpty()) {
            for (int i = 0; i < labels.length(); i++) {
                if (labels[i] != NULL) {
                    if (r->getFunctionLabel(i) == NULL && labels[i]->text() != ("")) {
                        return true;
                    }
                    if (r->getFunctionLabel(i) != NULL && r->getFunctionLabel(i) != (labels[i]->text())) {
                        return true;
                    }
                }
            }
        }
        if (!lockable.isEmpty()) {
            for (int i = 0; i < lockable.length(); i++) {
                if (lockable[i] != NULL) {
                    if (r->getFunctionLockable(i) && !lockable[i]->isChecked()) {
                        return true;
                    }
                    if (!r->getFunctionLockable(i) && lockable[i]->isChecked()) {
                        return true;
                    }
                }
            }
        }
        if (!_imageFilePath.isEmpty()) {
            for (int i = 0; i < _imageFilePath.length(); i++) {
                if (_imageFilePath[i] != NULL) {
                    if (r->getFunctionImage(i) == NULL && _imageFilePath[i]->getImagePath() != NULL) {
                        return true;
                    }
                    if (r->getFunctionImage(i) != NULL && r->getFunctionImage(i) !=(_imageFilePath[i]->getImagePath())) {
                        return true;
                    }
                }
            }
        }
        if (!_imagePressedFilePath.isEmpty()) {
            for (int i = 0; i < _imagePressedFilePath.length(); i++) {
                if (_imagePressedFilePath[i] != NULL) {
                    if (r->getFunctionSelectedImage(i) == NULL && _imagePressedFilePath[i]->getImagePath() != NULL) {
                        return true;
                    }
                    if (r->getFunctionSelectedImage(i) != NULL && r->getFunctionSelectedImage(i) != (_imagePressedFilePath[i]->getImagePath())) {
                        return true;
                    }
                }
            }
        }
        if (!shunterMode.isEmpty()) {
            QString shunFn = "";
            for (int i = 0; i < shunterMode.length(); i++) {
                if ((shunterMode[i] != NULL) && (shunterMode[i]->isChecked())) {
                    shunFn = "F" + i;
                }
            }
            if (shunFn != (r->getShuntingFunction())) {
                return true;
            }
        }
        return false;
    }

    /**
     * Update a RosterEntry object from panel contents.
     *
     *
     * @param r the roster entry to update
     */
    /*public*/ void FunctionLabelPane::update(RosterEntry* r) {
        if (!labels.isEmpty()) {
            QString shunFn = "";
            for (int i = 0; i < labels.length(); i++) {
                if (labels[i] != NULL && labels[i]->text() != ("")) {
                     r->setFunctionLabel(i, labels[i]->text());
                     r->setFunctionLockable(i, lockable[i]->isChecked());
                     r->setFunctionImage(i, _imageFilePath[i]->getImagePath());
                     r->setFunctionSelectedImage(i, _imagePressedFilePath[i]->getImagePath());
                } else if (labels[i] != NULL && labels[i]->text() == ("")) {
                    if ( r->getFunctionLabel(i) != NULL) {
                         r->setFunctionLabel(i, NULL);
                         r->setFunctionImage(i, NULL);
                         r->setFunctionSelectedImage(i, NULL);
                    }
                }
                if ((shunterMode[i] != NULL) && (shunterMode[i]->isChecked())) {
                    shunFn = "F" + QString::number(i);
                }
            }
             r->setShuntingFunction(shunFn);
        }
    }

    /*public*/ void FunctionLabelPane::dispose() {
        if (log->isDebugEnabled()) {
            log->debug("dispose");
        }
    }

    /*public*/ bool FunctionLabelPane::includeInPrint() {
        return print;
    }

    /*public*/ void FunctionLabelPane::includeInPrint(bool inc) {
        print = inc;
    }

    /*public*/ void FunctionLabelPane::printPane(HardcopyWriter* w) {
        // if pane is empty, don't print anything
        //if (varList.size() == 0 && cvList.size() == 0) return;
        // future work needed her to print indexed CVs

        // Define column widths for name and value output.
        // Make col 2 slightly larger than col 1 and reduce both to allow for
        // extra spaces that will be gbLayout->addWidgeted during concatenation
        int col1Width = w->getCharactersPerLine() / 2 - 3 - 5;
        int col2Width = w->getCharactersPerLine() / 2 - 3 + 5;

        try {
            //Create a string of spaces the width of the first column
            QString spaces;// = new StringBuilder();
            for (int i = 0; i < col1Width; i++) {
                spaces.append(" ");
            }
            // start with pane name in bold
            QString heading1 = tr("ColumnHeadingFunction");
            QString heading2 = tr("ColumnHeadingDescription");
            QString s;
            int interval = spaces.length() - heading1.length();
            w->getFontSize();
            w->setFontWeight( QFont::Bold);
            // write the section name and dividing line
            s = tr("HeadingFunctionLabels");
            w->write(s, 0, s.length());
            w->writeBorders();
            //Draw horizontal dividing line for each Pane section
            w->write(w->getCurrentLineNumber(), 0, w->getCurrentLineNumber(),
                    w->getCharactersPerLine() + 1);
            s = "\n";
            w->write(s, 0, s.length());

            w->setFontStyle(QFont::StyleItalic);
            w->setFontWeight(QFont::Bold);
            s = "   " + heading1 + spaces.mid(0, interval) + "   " + heading2;
            w->write(s, 0, s.length());
            w->writeBorders();
            s = "\n";
            w->write(s, 0, s.length());
            w->setFontStyle(QFont::StyleNormal);
            w->setFontWeight(QFont::Normal);

            // index over variables
            for (int i = 0; i <= maxfunction; i++) {
                QString name = "" + i;
                if (re->getFunctionLockable(i)) {
                    name = name + " (locked)";
                }
                QString value = re->getFunctionLabel(i);
                //Skip Blank functions
                if (value != NULL) {

                    //define index values for name and value substrings
                    int nameLeftIndex = 0;
                    int nameRightIndex = name.length();
                    int valueLeftIndex = 0;
                    int valueRightIndex = value.length();
                    QString trimmedName;
                    QString trimmedValue;

                    // Check the name length to see if it is wider than the column.
                    // If so, split it and do the same checks for the Value
                    // Then concatenate the name and value (or the split versions thereof)
                    // before writing - if split, repeat until all pieces have been output
                    while ((valueLeftIndex < value.length()) || (nameLeftIndex < name.length())) {
                        // name split code
                        if (name.mid(nameLeftIndex).length() > col1Width) {
                            for (int j = 0; j < col1Width; j++) {
                                QString delimiter = name.mid(nameLeftIndex + col1Width - j - 1,
                                        nameLeftIndex + col1Width - j);
                                if (delimiter == (" ") || delimiter == (";") || delimiter == (",")) {
                                    nameRightIndex = nameLeftIndex + col1Width - j;
                                    break;
                                }
                            }
                            trimmedName = name.mid(nameLeftIndex, nameRightIndex);
                            nameLeftIndex = nameRightIndex;
                            int space = spaces.length() - trimmedName.length();
                            s = "   " + trimmedName + spaces.mid(0, space);
                        } else {
                            trimmedName = name.mid(nameLeftIndex);
                            int space = spaces.length() - trimmedName.length();
                            s = "   " + trimmedName + spaces.mid(0, space);
                            name = "";
                            nameLeftIndex = 0;
                        }
                        // value split code
                        if (value.mid(valueLeftIndex).length() > col2Width) {
                            for (int j = 0; j < col2Width; j++) {
                                QString delimiter = value.mid(valueLeftIndex + col2Width - j - 1, valueLeftIndex + col2Width - j);
                                if (delimiter == (" ") || delimiter == (";") || delimiter == (",")) {
                                    valueRightIndex = valueLeftIndex + col2Width - j;
                                    break;
                                }
                            }
                            trimmedValue = value.mid(valueLeftIndex, valueRightIndex);
                            valueLeftIndex = valueRightIndex;
                            s = s + "   " + trimmedValue;
                        } else {
                            trimmedValue = value.mid(valueLeftIndex);
                            s = s + "   " + trimmedValue;
                            valueLeftIndex = 0;
                            value = "";
                        }
                        w->write(s, 0, s.length());
                        w->writeBorders();
                        s = "\n";
                        w->write(s, 0, s.length());
                    }
                    // handle special cases
                }
            }
            s = "\n";
            w->writeBorders();
            w->write(s, 0, s.length());
            w->writeBorders();
            w->write(s, 0, s.length());
        } catch (IOException e) {
            log->warn("error during printing: " + e.getMessage());
        }

    }

    /*private*/ /*final*/ /*static*/ Logger* FunctionLabelPane::log = LoggerFactory::getLogger("FunctionLabelPane");
