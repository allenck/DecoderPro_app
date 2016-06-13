#include "language.h"
#include <QTranslator>
#include <QApplication>
#include <QDebug>

language::language(QObject *parent) :
    QObject(parent)
{
}
void language::loadLanguage(QString s_locale)
{
 if (s_locale != "")
 {
  QTranslator this_translator;
  if (this_translator.load(":languages/libPr3_"+s_locale+".qm"))
  {
   qApp->installTranslator(&this_translator);
   qDebug()<< tr("-I-> language::on_init_control_text : translation file for ")+"'"+s_locale+"'"+tr(" loaded");
  }
 }
}
