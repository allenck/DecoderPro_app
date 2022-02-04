#include "beanselectpanel.h"

/**
 * Create a JPanel* containing a NamedBeanComboBox.  The default display option is
 * DISPLAYNAME.  JComboBoxUtil.setupComboBoxMaxRows() will be invoked.
 *
 * @author Dave Sand Copyright 2021
 */
///*public*/  class BeanSelectPanel<E extends NamedBean> extends JPanel* {


    /*public*/  BeanSelectPanel::BeanSelectPanel(/*@Nonnull*/ Manager/*<E>*/* manager, NamedBean* selection, QWidget* parent) {
        common(manager, selection, NamedBean::DisplayOptions::DISPLAYNAME, false);
    }

    /*public*/  BeanSelectPanel::BeanSelectPanel(/*@Nonnull*/ Manager/*<E>*/* manager, NamedBean* selection,NamedBean:: DisplayOptions display,  QWidget* parent) {
        common(manager, selection, display, true);
    }

    /**
     * Create a JPanel* that contains a named bean combo box.
     *
     * @param manager    The bean manager
     * @param selection  The bean that is selected, null for no selection.
     * @param display    The bean display option, null for default DISPLAYNAME.
     * @param maxRows    Should max rows be enabled; if false the JComboBox default of 8 will be used.
     */
    /*public*/  BeanSelectPanel::BeanSelectPanel(/*@Nonnull*/ Manager/*<E>*/* manager,NamedBean* selection, NamedBean::DisplayOptions display, bool maxRows)
    {
     common(manager, selection, display, false);
    }

    void BeanSelectPanel::common(Manager* manager, NamedBean* selection, NamedBean::DisplayOptions display, bool maxRows)
    {
        _selection = selection;
        _display = display; //== null ? DisplayOptions::DISPLAYNAME : display;

        _beanComboBox = new NamedBeanComboBox/*<>*/(manager, selection, _display);
        _beanComboBox->setAllowNull(true);
//        if (maxRows) JComboBoxUtil.setupComboBoxMaxRows(_beanComboBox);

        JPanel* bean = new JPanel();
        bean->setLayout(new FlowLayout());//FlowLayout.CENTER, 5, 0));
        bean->layout()->addWidget(_beanComboBox);
        JPanel::setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
        JPanel::layout()->addWidget(bean);
    }

    /*
     * Provide the actual combo box object to provide direct access, such as adding listeners.
     * @return the combo box
     */
    /*public*/  NamedBeanComboBox* BeanSelectPanel::getBeanCombo() {
        return _beanComboBox;
    }

    /**
     * Get the named bean that has been selected.
     * @return the selected bean which may be null if the first row is selected.
     */
    /*public*/ NamedBean* BeanSelectPanel::getNamedBean() {
            return _beanComboBox->getSelectedItem();
    }

    /**
     * Set the default selected item in the combo box.
     * @param nBean the bean that is selected by default
     */
    /*public*/  void BeanSelectPanel::setDefaultNamedBean(NamedBean* nBean) {
        _selection = nBean;
        _beanComboBox->setSelectedItem(_selection);
    }

    /**
     * Check that the user selected something in this BeanSelectCreatePanel.
     * @return true if nothing selected
     */
    /*public*/  bool BeanSelectPanel::isEmpty() {
        return _beanComboBox->getSelectedIndex() < 1;
    }

    /*public*/  void BeanSelectPanel::dispose() {
        _beanComboBox->dispose();
    }

    //initialize logging
//     private static final org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(BeanSelectPanel.class);
//}
