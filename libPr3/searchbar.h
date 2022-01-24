#ifndef SEARCHBAR_H
#define SEARCHBAR_H
#include "jpanel.h"
#include "runnable.h"
#include "jtextfield.h"
#include "jbutton.h"
#include "jframe.h"

class Logger;
class SearchBar : public JPanel
{
 public:
  SearchBar(Runnable* forward, Runnable* backward, Runnable* done, QWidget* parent=nullptr);
  /*public*/ QString getSearchString();
  /*public*/ void configureKeyModifiers(JFrame* frame);
 private:
  static Logger* log;
  Runnable* forward;
  Runnable* backward;
  Runnable* done;

  JTextField* textField = new JTextField();
  JButton* rightButton = new JButton(">");
  JButton* leftButton = new JButton("<");
  JButton* doneButton = new JButton(tr("Done"));

};

#endif // SEARCHBAR_H
