#ifndef QUICKPROMPTUTIL_H
#define QUICKPROMPTUTIL_H

#include <QObject>
#include "predicate.h"
#include <QPushButton>

class QIntValidator;
class Component;
class QuickPromptUtil : public QObject
{
 Q_OBJECT
protected:
 explicit QuickPromptUtil(QObject *parent = nullptr);
public:
 static /*public*/ QString promptForString(Component* parentComponent, QString message, QString title, QString oldValue);
 static /*public*/ int promptForInt(Component* parentComponent, QString message, QString title, int oldValue);
 /*public*/ static int promptForInteger(Component* parentComponent, /*@Nonnull*/ QString message, /*@Nonnull*/ QString title,
                                        int oldValue, /*@CheckForNull*/ QIntValidator* validator);
 /*public*/ static int promptForInteger(Component* parentComponent, /*@Nonnull*/ QString message, /*@Nonnull*/ QString title,
                                        int oldValue, /*@CheckForNull*/ Predicate<int> validator);
 /*public*/ static QIntValidator* checkIntRange(int min, int max, QString valueLabel);

private:
#if 0
 template<class T>
 /*private*/ static  T promptForData(Component* parentComponent,
             /*@Nonnull*/ QString message, /*@Nonnull*/ QString title, T oldValue,
             /*@CheckForNull*/ QIntValidator validator,
             /*@CheckForNull*/ Function<String, T> converter) {
         QString result = oldValue == null ? "" : oldValue.toString(); // NOI18N
         QPushButton* okOption = new QPushButton(tr("OK")); // NOI18N
         QPushButton* cancelOption = new QPushButton(tr("Cancel")); // NOI18N
         //okOption.setDefaultCapable(true);

         ValidatingInputPane<T> validating = new ValidatingInputPane<T>(converter)
                 .message(message)
                 .validator(validator)
                 .attachConfirmUI(okOption);
         validating.setText(result);
         JOptionPane pane = new JOptionPane(validating, JOptionPane.PLAIN_MESSAGE,
                 OK_CANCEL_OPTION, null, new Object[]{okOption, cancelOption});

         pane.putClientProperty("OptionPane.buttonOrientation", SwingConstants.RIGHT); // NOI18N
         JDialog dialog = pane.createDialog(parentComponent, title);
         dialog.getRootPane().setDefaultButton(okOption);
         dialog.setResizable(true);

         class AL implements ActionListener {

             boolean confirmed;

             @Override
             public void actionPerformed(ActionEvent e) {
                 Object s = e.getSource();
                 if (s == okOption) {
                     confirmed = true;
                     dialog.setVisible(false);
                 }
                 if (s == cancelOption) {
                     dialog.setVisible(false);
                 }
             }
         }

         AL al = new AL();
         okOption.addActionListener(al);
         cancelOption.addActionListener(al);

         dialog.setVisible(true);
         dialog
           return oldValue;
       }.dispose();

         if (al.confirmed) {
             T res = validating.getValue();
             if (res != null) {
                 return res;
             }
         }
#endif
};

#endif // QUICKPROMPTUTIL_H
