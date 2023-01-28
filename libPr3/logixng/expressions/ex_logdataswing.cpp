#include "ex_logdataswing.h"
#include "ex_logdata.h"
#include "QBoxLayout"
#include "jlabel.h"
#include "jtextfield.h"
#include "ex_logdatatablemodel.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "../parserexception.h"
#include "instancemanager.h"
#include "../defaultdigitalexpressionmanager.h"

/**
 * Configures an LogData object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
namespace Expressions {
///*public*/  class LogDataSwing extends AbstractDigitalActionSwing {


    //@Override
    /*protected*/ void LogDataSwing::createPanel(/*@CheckForNull */Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && (!qobject_cast<LogData*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object is not a LogData: ") +  QString(object->bself()->metaObject()->className()));
        }
        LogData* logData = nullptr;
        if(object) logData =(LogData*)object->bself();

        panel = new JPanel();

        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));


        _logToLogCheckBox = new JCheckBox(tr("Log to the log"));
        panel->layout()->addWidget(_logToLogCheckBox);

        _logToScriptOutputCheckBox = new JCheckBox(tr("Log to the Script Output"));
        panel->layout()->addWidget(_logToScriptOutputCheckBox);


        JPanel* formatTypePanel = new JPanel(new FlowLayout);
        _formatType = new JComboBox();
        for (LogData::FormatType::FORMATTYPE formatType : LogData::FormatType::values()) {
            _formatType->addItem(LogData::FormatType::toString(formatType), formatType);
        }
        formatTypePanel->layout()->addWidget(new JLabel(tr("Format type")));
        formatTypePanel->layout()->addWidget(_formatType);
        panel->layout()->addWidget(formatTypePanel);

        JPanel* formatPanel = new JPanel(new FlowLayout);
        _format = new JTextField(20);
        formatPanel->layout()->addWidget(new JLabel(tr("Format")));
        formatPanel->layout()->addWidget(_format);
        panel->layout()->addWidget(formatPanel);


        if (logData != nullptr) {
            _logToLogCheckBox->setSelected(logData->getLogToLog());
            _logToScriptOutputCheckBox->setSelected(logData->getLogToScriptOutput());
            _formatType->setSelectedItem(logData->getFormatType());
            _format->setText(logData->getFormat());
        }


        JPanel* tablePanel = new JPanel(new QVBoxLayout);
        _logDataTable = new JTable();

        if (logData != nullptr) {
            QList<LogData::Data>* dataList
                    = new QList<LogData::Data>(logData->getDataList());

            _logDataTableModel = new LogDataTableModel(dataList);
        } else {
            _logDataTableModel = new LogDataTableModel(nullptr);
        }

        _logDataTable->setModel(_logDataTableModel);
#if 0
        _logDataTable.setDefaultRenderer(LogData.DataType.class,
                new LogDataTableModel.CellRenderer());
        _logDataTable.setDefaultEditor(LogData.DataType.class,
                new LogDataTableModel.DataTypeCellEditor());
#endif
        _logDataTableModel->setColumnsForComboBoxes(_logDataTable);
#if 0
        _logDataTable.setDefaultRenderer(JButton.class, new ButtonRenderer());
        _logDataTable.setDefaultEditor(JButton.class, new ButtonEditor(new JButton()));
#endif
        JButton* testButton = new JButton("XXXXXX");  // NOI18N
        _logDataTable->setRowHeight(testButton->sizeHint().height());
        TableColumn* deleteColumn = _logDataTable->getColumnModel()
                ->getColumn(LogDataTableModel::COLUMN_DUMMY);
        deleteColumn->setMinWidth(testButton->sizeHint().width());
        deleteColumn->setMaxWidth(testButton->sizeHint().width());
        deleteColumn->setResizable(false);

        // The dummy column is used to be able to force update of the
        // other columns when the panel is closed.
        TableColumn* dummyColumn = _logDataTable->getColumnModel()
                ->getColumn(LogDataTableModel::COLUMN_DUMMY);
        dummyColumn->setMinWidth(0);
        dummyColumn->setPreferredWidth(0);
        dummyColumn->setMaxWidth(0);

        //JScrollPane scrollpane = new JScrollPane(_logDataTable);
//        scrollpane.setPreferredSize(new Dimension(400, 200));
        ((QVBoxLayout*)tablePanel->layout())->addWidget(/*scrollpane*/_logDataTable, 1, Qt::AlignHCenter/*BorderLayout.CENTER*/);
        panel->layout()->addWidget(tablePanel);

        // Add parameter
        JButton* add = new JButton(tr("Add"));
        buttonPanel->layout()->addWidget(add);
        //add.addActionListener((ActionEvent e) -> {
        connect(add, &JButton::clicked, [=]{
            _logDataTableModel->add();
        });
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool LogDataSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        for (LogData::Data data : _logDataTableModel->getDataList()) {
            if (data.getDataType() == LogData::DataType::Formula) {
                try {
                    QMap<QString, Variable*> variables = QMap<QString, Variable*>();
                    RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
                    parser->parseExpression(data.getData());
                } catch (ParserException* e) {
                    errorMessages->append(e->getLocalizedMessage());
                }
            }
        }
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* LogDataSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        LogData* action = new LogData(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void LogDataSwing::updateObject(/*@Nonnull*/ Base* object) {
     if(!object) throw new NullPointerException();
        if (! (qobject_cast<LogData*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object is not a LogData: ") + QString(object->bself()->metaObject()->className()));
        }
        LogData* logData = (LogData*)object->bself();


        logData->setLogToLog(_logToLogCheckBox->isSelected());
        logData->setLogToScriptOutput(_logToScriptOutputCheckBox->isSelected());

        logData->setFormatType((LogData::FormatType::FORMATTYPE)_formatType->getItemAt(_formatType->getSelectedIndex()).toUInt());
        logData->setFormat(_format->text());


        // Do this to force update of the table
//        _logDataTable.editCellAt(0, 2);

        logData->getDataList().clear();

        for (LogData::Data data : _logDataTableModel->getDataList()) {
            logData->getDataList().append(data);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString LogDataSwing::toString() {
        return tr("Log data");
    }

    //@Override
    /*public*/  void LogDataSwing::dispose() {
    }

}
