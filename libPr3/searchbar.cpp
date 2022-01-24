#include "searchbar.h"
#include "loggerfactory.h"
#include "box.h"
#include "jrootpane.h"

/**
 * Provides a standard "search bar" for addition to
 * other panels.  Actual search is via call-back.
 *
 * @author Bob Jacobsen
 */
///*public*/ class SearchBar extends javax.swing.JPanel {


/*public*/ SearchBar::SearchBar(Runnable* forward, Runnable* backward, Runnable* done, QWidget* parent) : JPanel(parent){
    //super();
    this->forward = forward;
    this->backward = backward;
    this->done = done;

    // create GUI
    setLayout(new QHBoxLayout());//this, BoxLayout.X_AXIS));
    layout()->addWidget(textField);
    layout()->addWidget(Box::createHorizontalGlue());
    layout()->addWidget(leftButton);
    layout()->addWidget(rightButton);
    layout()->addWidget(doneButton);

    leftButton->setToolTip("Search backwards");
    rightButton->setToolTip("Search forwards");
    doneButton->setToolTip("Close search bar");

    // add actions
//    doneButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(doneButton, &JButton::clicked, [=]{
            if (done != nullptr) {
                log->debug("firing done");
                done->run();
            } else {
                log->warn("no search done defined, setting invisible");
                this->setVisible(false);
            }
//        }
    });

//    leftButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(leftButton, &JButton::clicked, [=]{
            if (backward != nullptr) {
                log->debug("firing backward");
                backward->run();
            } else {
                log->warn("no backward search defined");
            }
//        }
    });

//    rightButton.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(rightButton, &JButton::clicked, [=]{
            if (forward != nullptr) {
                log->debug("firing forward");
                forward->run();
            } else {
                log->warn("no forward search defined");
            }
//        }
    });

    // Enter in the text field does a forward search
    // and then leaves forward search selected for the next one
//    textField.addActionListener(new java.awt.event.ActionListener() {
//        @Override
//        /*public*/ void actionPerformed(ActionEvent e) {
    connect(textField, &JTextField::editingFinished, [=]{
            if (forward != nullptr) {
                log->debug("firing forward");
                forward->run();
            } else {
                log->warn("no forward search defined");
            }
//            rightButton->requestFocusInWindow();
//        }
    });

}

/*public*/ QString SearchBar::getSearchString() {
    return textField->text();
}

/**
 * A service routine to connect the SearchBar to
 * the usual modifier keys
 * @param frame JFrame containing this search bar; used to set key maps
 */
/*public*/ void SearchBar::configureKeyModifiers(JFrame* frame) {
#if 0
    JRootPane* rootPane = frame->getRootPane();

    rootPane.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(
        KeyStroke.getKeyStroke(KeyEvent.VK_F, Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()), "openSearch");

    rootPane.getActionMap().put("openSearch", new AbstractAction() {
        /*public*/ void actionPerformed(ActionEvent e) {

            // don't retain last text?
            textField.setText("");

            // alternate visible
            SearchBar.this.setVisible(! SearchBar.this.isVisible());

            // if visible, move focus
            if (SearchBar.this.isVisible()) {
                SearchBar.this.textField.requestFocusInWindow();
            }
        }
    });

    rootPane.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(
        KeyStroke.getKeyStroke(KeyEvent.VK_G, Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()|java.awt.event.InputEvent.SHIFT_DOWN_MASK), "forwardSearch");

    rootPane.getActionMap().put("forwardSearch", new AbstractAction() {
        /*public*/ void actionPerformed(ActionEvent e) {

            // same as button
            leftButton.doClick();
            }
    });

    rootPane.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(
        KeyStroke.getKeyStroke(KeyEvent.VK_G, Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()), "backwardSearch");

    rootPane.getActionMap().put("backwardSearch", new AbstractAction() {
        /*public*/ void actionPerformed(ActionEvent e) {

            // same as button
            rightButton.doClick();
            }
    });
#endif
}

/*private*/ /*final*/ /*static*/ Logger* SearchBar::log = LoggerFactory::getLogger("SearchBar");
