#ifndef SPROGTYPE_H
#define SPROGTYPE_H

#include <QObject>

class Logger;
namespace Sprog
{

 class SprogType : public QObject
 {
  Q_OBJECT
 public:
  explicit SprogType(int type, QObject *parent = nullptr);
  // NOTE the numerical order of thes constants is used in the bootloader
  // to test for various SPROG types
  enum SPROGTYPES
  {
   UNKNOWN = 0,
   NO_PROMPT_FOUND = 1,
   NOT_A_SPROG = 2,
   NOT_RECOGNISED = 3,
   TIMEOUT = 4,
   SPROGV4 = 10,
   SPROGII = 20,
   SPROGIIUSB = 21,
   SPROGIIv3 = 23,
   SPROGIIv4 = 24,
   SPROG3 = 30,
   SPROGIV = 40,
   SPROG5 = 50,
   PISPROGONE = 60,
   NANO = 1000,
   PISPROGNANO = 1001,
   SNIFFER = 2000
  };
  /*public*/ int _sprogType;// = UNKNOWN;
  /*public*/ bool isSprog();
  /*public*/ bool isSprogII();
  /*public*/ double getCurrentMultiplier();
  /*public*/ int getBlockLen();
  static /*public*/ int getBlockLen(int bootVer);
  /*public*/ bool isValidFlashAddress(int addr);
  /*public*/ int getEraseStart();
  /*public*/ QString toString();
  /*public*/ QString toString(int t);

 signals:

 public slots:
 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(SprogType.class);

 };
}
#endif // SPROGTYPE_H
