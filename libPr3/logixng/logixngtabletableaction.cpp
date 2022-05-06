#include "logixngtabletableaction.h"
#include "loggerfactory.h"
#include "defaultnamedtablemanager.h"
#include "tableeditor.h"
#include "runtimeexception.h"
#include "fileutil.h"
#include "jfilechooser.h"
#include "filenameextensionfilter.h"
#include "gridbaglayout.h"

/**
 * Swing action to create and register a LogixNG Table.
 * <p>
 Also contains the panes to create, edit, and delete a LogixNG.
 <p>
 * Most of the text used in this GUI is in BeanTableBundle.properties, accessed
 * via Bundle.getMessage().
 * <p>
 *
 * @author Dave Duchamp Copyright (C) 2007 (LogixTableAction)
 * @author Pete Cressman Copyright (C) 2009, 2010, 2011 (LogixTableAction)
 * @author Matthew Harris copyright (c) 2009 (LogixTableAction)
 * @author Dave Sand copyright (c) 2017 (LogixTableAction)
 * @author Daniel Bergqvist copyright (c) 2019
 * @author Dave Sand copyright (c) 2021
 */
// /*public*/  class LogixNGTableTableAction extends AbstractLogixNGTableAction<NamedTable> {


    /**
     * Create a LogixNGTableAction instance.
     *
     * @param s the Action title, not the title of the resulting frame. Perhaps
     *          this should be changed?
     */
    /*public*/  LogixNGTableTableAction::LogixNGTableTableAction(QString s, QObject* parent)
      : AbstractLogixNGTableAction(s, parent){
        //super(s);
    }

    /**
     * Create a LogixNGTableAction instance with default title.
     */
    /*public*/  LogixNGTableTableAction::LogixNGTableTableAction(QObject* parent)
      : AbstractLogixNGTableAction(tr("LogixNGTableTable"),parent)
    {
        //this(Bundle.getMessage("TitleLogixNGTableTable"));
    }

    //@Override
    /*protected*/ void LogixNGTableTableAction::setTitle() {
        f->setTitle(tr("LogixNGTableTable"));
    }

    //@Override
    /*public*/  QString LogixNGTableTableAction::getClassDescription() {
        return tr("LogixNGTableTable");        // NOI18N
    }

    //@Override
    /*protected*/ AbstractLogixNGEditor/*<NamedTable>*/* LogixNGTableTableAction::getEditor(BeanTableFrame/*<NamedTable>*/* f, BeanTableDataModel/*<NamedTable>*/* m, QString sName) {
        return new TableEditor(m, sName);
    }

    //@Override
    /*protected*/ Manager/*<NamedTable>*/* LogixNGTableTableAction::getManager() {
        return (DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager");
    }

    //@Override
    /*protected*/ void LogixNGTableTableAction::enableAll(bool enable) {
        // Not used by the tables table
    }

    //@Override
    /*protected*/ void LogixNGTableTableAction::setEnabled(NamedBean* bean, bool enable) {
        // Not used by the tables table
    }

    //@Override
    /*protected*/ bool LogixNGTableTableAction::isEnabled(NamedBean* bean) {
        return true;
    }

    //@Override
    /*protected*/ /*NamedTable**/NamedBean* LogixNGTableTableAction::createBean(QString userName) {
        QString systemName = ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->AbstractManager::getAutoSystemName();
        return createBean(systemName, userName);
    }

    //@Override
    /*protected*/ /*NamedTable**/NamedBean* LogixNGTableTableAction::createBean(QString systemName, QString userName) {
        if (_typeExternalTable->isChecked()) {
            QString fileName = _csvFileName->text();
            if (fileName == "" || fileName.isEmpty()) {
                JOptionPane::showMessageDialog(addLogixNGFrame,
                        tr("A CSV file was not selected."), tr("Error"), // NOI18N
                        JOptionPane::ERROR_MESSAGE);
                return nullptr;
            }
            return (NamedBean*)((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))
                    ->newCSVTable(systemName, userName, fileName);
        } else if (_typeInternalTable->isChecked()) {
            // Open table editor
        } else {
            log->error("No table type selected");
            throw new RuntimeException("No table type selected");
        }

//        InstanceManager.getDefault(NamedTableManager.class).loadTableFromCSV(file, systemName, userName);
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    //@Override
    /*protected*/ void LogixNGTableTableAction::deleteBean(NamedBean* bean) {
        try {
            ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->deleteBean((NamedTable*)bean->self(), "DoDelete");
        } catch (PropertyVetoException* e) {
            //At this stage the DoDelete shouldn't fail, as we have already done a can delete, which would trigger a veto
            log->error(e->getMessage());
        }
    }

    //@Override
    /*protected*/ bool LogixNGTableTableAction::browseMonoSpace() {
        return true;
    }

    //@Override
    /*protected*/ QString LogixNGTableTableAction::getBeanText(NamedBean* b) {
     NamedTable* bean = (NamedTable*)b->self();
        int maxColumnWidth = 0;
        QVector<int> columnWidth =  QVector<int>(bean->numColumns()+1);
        //QString[][] cells = new QString[bean->numRows()+1][];
        QVector<QVector<QString> > cells = QVector<QVector<QString> >(bean->numRows()+1);
        for (int row=0; row <= bean->numRows(); row++) {
            cells[row] = QVector<QString> (bean->numColumns()+1);
            for (int col=0; col <= bean->numColumns(); col++) {
                QVariant value = bean->getCell(row, col);
                cells[row][col] = value != QVariant() ? value.toString() : "<null>";
                columnWidth[col] = qMax(columnWidth[col], cells[row][col].length());
                maxColumnWidth = qMax(maxColumnWidth, columnWidth[col]);
            }
        }
        QString columnLine;// = new StringBuilder();
        while (columnLine.length()+2 < maxColumnWidth) {
            columnLine.append("----------------------");
        }
        //QString columnPadding = asprintf(QString("%")+QString::number(maxColumnWidth)+"s", "");
        QString columnPadding;
        if(columnPadding.length()< maxColumnWidth) columnPadding.append(" ");
        QString sb;// = new StringBuilder();
        sb.append("+");
        for (int col=0; col <= bean->numColumns(); col++) {
            sb.append(columnLine.mid(0,columnWidth[col]+2));
            sb.append("+");
            if (col == bean->numColumns()) sb.append("%n");
        }
        for (int row=0; row <= bean->numRows(); row++) {
            sb.append("|");
            for (int col=0; col <= bean->numColumns(); col++) {
                sb.append(" ");
                sb.append((cells[row][col]+columnPadding).mid(0,columnWidth[col]));
                sb.append(" |");
                if (col == bean->numColumns()) sb.append(QString("%n"));
            }
            sb.append("+");
            for (int col=0; col <= bean->numColumns(); col++) {
                sb.append(columnLine.mid(0,columnWidth[col]+2));
                sb.append("+");
                if (col == bean->numColumns()) sb.append(QString("%n"));
            }
        }
        return sb/*.toString()*/;
    }

    //@Override
    /*protected*/ QString LogixNGTableTableAction::getAddTitleKey() {
        return "LogixNGTable Table";
    }

    //@Override
    /*protected*/ QString LogixNGTableTableAction::getCreateButtonHintKey() {
        return "LogixNGTableCreateButtonHint";
    }

    //@Override
    /*protected*/ QString LogixNGTableTableAction::helpTarget() {
        return "package.jmri.jmrit.beantable.LogixNGTableTable";  // NOI18N
    }

    /*private*/ JButton* LogixNGTableTableAction::createFileChooser() {
        JButton* selectFileButton = new JButton("..."); // "File" replaced by ...
        selectFileButton->setMaximumSize(selectFileButton->sizeHint());
        selectFileButton->setToolTip(tr("Click to select a file from disk"));  // NOI18N
        connect(selectFileButton, &JButton::clicked, [=] {
            JFileChooser* csvFileChooser = new JFileChooser(FileUtil::getUserFilesPath());
            csvFileChooser->setFileFilter(QString("CSV files (*.csv, *.txt")); // NOI18N
//            csvFileChooser.rescanCurrentDirectory();
            int retVal = csvFileChooser->showOpenDialog(nullptr);
            // handle selection or cancel
            if (retVal == JFileChooser::APPROVE_OPTION) {
                // set selected file location
                try {
                    _csvFileName->setText(FileUtil::getPortableFilename(csvFileChooser->getSelectedFile()->getCanonicalPath()));
                } catch (IOException* ex) {
                    log->error(tr("exception setting file location: %1").arg(ex->toString()));  // NOI18N
                    _csvFileName->setText("");
                }
            }
        });
        return selectFileButton;
    }

    /**
     * Create or copy bean frame.
     *
     * @param titleId   property key to fetch as title of the frame (using Bundle)
     * @param startMessageId part 1 of property key to fetch as user instruction on
     *                  pane, either 1 or 2 is added to form the whole key
     * @return the button JPanel
     */
    //@Override
    /*protected*/ JPanel* LogixNGTableTableAction::makeAddFrame(QString titleId, QString startMessageId) {
        addLogixNGFrame = new JmriJFrame((titleId));
        addLogixNGFrame->addHelpMenu(
                "package.jmri.jmrit.beantable.LogixNGTableTable", true);     // NOI18N
        addLogixNGFrame->setLocation(50, 30);
        QWidget* contentPane = addLogixNGFrame->getContentPane();
        contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

        JPanel* p;
        p = new JPanel();
        //p->setLayout(new FlowLayout());
        GridBagLayout* pLayout;
        p->setLayout(pLayout = new GridBagLayout());
        GridBagConstraints c = GridBagConstraints();
        c.gridwidth = 1;
        c.gridheight = 1;

        c.gridx = 0;
        c.gridy = 0;
        c.anchor = GridBagConstraints::EAST;

        pLayout->addWidget(_sysNameLabel, c);
        _sysNameLabel->setLabelFor(_systemName);
        c.gridy = 1;
        pLayout->addWidget(_userNameLabel, c);
        _userNameLabel->setLabelFor(_addUserName);
        c.gridy = 2;
        pLayout->addWidget(new JLabel(tr("CSV file name")), c);

        c.gridx = 1;
        c.gridy = 0;
        c.anchor = GridBagConstraints::WEST;
        c.weightx = 1.0;
        c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
        pLayout->addWidget(_systemName, c);
        c.gridy = 1;
        pLayout->addWidget(_addUserName, c);

        c.gridy = 2;
        createFileChooser();
        pLayout->addWidget(createFileChooser(), c);

        c.gridx = 2;        // make room for file selector
        c.gridwidth = GridBagConstraints::REMAINDER;
        pLayout->addWidget(_csvFileName, c);

        c.gridwidth = 1;
        c.gridx = 2;
        c.gridy = 1;
        c.anchor = GridBagConstraints::WEST;
        c.weightx = 1.0;
        c.fill = GridBagConstraints::HORIZONTAL;  // text field will expand
        c.gridy = 0;
        pLayout->addWidget(_autoSystemName, c);


        _buttonGroup->addButton(_typeExternalTable);
        _buttonGroup->addButton(_typeInternalTable);
        _typeExternalTable->setChecked(true);
        _typeInternalTable->setEnabled(false);

        _addUserName->setToolTip(tr("Enter user name for new LogixNG, e.g. Signal 2 Control"));    // NOI18N
        _systemName->setToolTip(tr("Enter system name for new LogixNG, e.g. IQ13"));   // NOI18N
        contentPane->layout()->addWidget(p);

        JPanel* panel98 = new JPanel();
        panel98->setLayout(new FlowLayout());
        JPanel* panel99 = new JPanel();
        panel99->setLayout(new QVBoxLayout());//panel99, BoxLayout.Y_AXIS));
        panel99->layout()->addWidget(_typeExternalTable/*, c)*/);
        panel99->layout()->addWidget(_typeInternalTable/*, c*/);
        panel98->layout()->addWidget(panel99);
        contentPane->layout()->addWidget(panel98);

        // set up message
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new QVBoxLayout());//panel3, BoxLayout.Y_AXIS));
        JPanel* panel31 = new JPanel();
        panel31->setLayout(new FlowLayout());
        //JLabel* message1 = new JLabel(QString(startMessageId) + tr("LogixNGTableMessage1"));  // NOI18N
        JLabel* message1 = new JLabel(startMessageId==tr("Add")? tr("Please enter system name and user name, then") :
                  tr("Please enter System Name and User Name\n "));
        panel31->layout()->addWidget(message1);
        JPanel* panel32 = new JPanel(new FlowLayout());
        //JLabel* message2 = new JLabel(QString(startMessageId) + tr("LogixNGTableMessage2"));  // NOI18N
        JLabel* message2= new JLabel(startMessageId==tr("Add")? tr("click [Create].") : tr("of target LogixNG Table, then click [Copy]"));
        panel32->layout()->addWidget(message2);
        panel3->layout()->addWidget(panel31);
        panel3->layout()->addWidget(panel32);
        contentPane->layout()->addWidget(panel3);

        // set up create and cancel buttons
        JPanel* panel5 = new JPanel();
        panel5->setLayout(new FlowLayout());
        // Cancel
        JButton* cancel = new JButton(tr("Cancel"));    // NOI18N
        panel5->layout()->addWidget(cancel);
        connect(cancel, SIGNAL(clicked()), this, SLOT(cancelAddPressed()));
        cancel->setToolTip(tr("CancelLogixNGButtonHint"));      // NOI18N
#if 0
        addLogixNGFrame.addWindowListener(new java.awt.event.WindowAdapter() {
            @Override
            /*public*/  void windowClosing(java.awt.event.WindowEvent e) {
                cancelAddPressed(null);
            }
        });
#endif
        contentPane->layout()->addWidget(panel5);

        connect(_autoSystemName, &JButton::clicked, [=] {
            autoSystemName();
        });
        return panel5;
    }

    //@Override
    /*protected*/ void LogixNGTableTableAction::getListenerRefsIncludingChildren(NamedBean* table, QList<QString> list) {
        // Do nothing
    }

    //@Override
    /*protected*/ bool LogixNGTableTableAction::hasChildren(NamedBean* /*table*/) {
        // Tables doesn't have children
        return false;
    }

    /*private*/ /*final*/ /*static*/ Logger* LogixNGTableTableAction::log = LoggerFactory::getLogger("LogixNGTableTableAction");
