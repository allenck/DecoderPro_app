#include "sproghexfile.h"
#include "loggerfactory.h"
#include "joptionpane.h"

using namespace Sprog;

/**
 * Class to encapsulate an intel format hex file and methods to manipulate it.
 * Intended use is as an input format for new program code to be sent to a
 * hardware device via some bootloading process.
 *
 * @author	Andrew Crosland Copyright (C) 2010
 */
///*public*/ class SprogHexFile extends jmri.util.JmriJFrame {


// Hex file record types
/*static*/ /*final*/ char SprogHexFile::EXT_ADDR = 4;
/*static*/ /*final*/ char SprogHexFile::DATA = 0;
/*static*/ /*final*/ char SprogHexFile::END = 1;
// Maximum record length
/*private*/ /*static*/ /*final*/ int SprogHexFile::MAX_LEN = (255 + 1 + 2 + 1 + 1) * 2;
// Offsets of fields within the record
/*private*/ /*static*/ /*final*/ int SprogHexFile::LEN = 0;
/*private*/ /*static*/ /*final*/ int SprogHexFile::ADDRH = 1;
/*private*/ /*static*/ /*final*/ int SprogHexFile::ADDRL = 2;
/*private*/ /*static*/ /*final*/ int SprogHexFile::TYPE = 3;

/*public*/ SprogHexFile::SprogHexFile(QString fileName, QWidget* parent) : JmriJFrame(parent) {
    name = fileName;
    file = new File(fileName);
}

/**
 * @return name of the open file
 */
//@Override
/*public*/ QString SprogHexFile::getName() {
    return name;
}

/**
 * Open hex file for reading.
 *
 * @return bool true if successful
 */
/*public*/ bool SprogHexFile::openRd()
{
 _read = true;
 try
 {
  // Create an input reader based on the file, so we can read its data.
  //in = new FileInputStream(file);
  QFile f(file->getPath());
  if(!f.open(QIODevice::ReadOnly)) throw new IOException();
  in = new QDataStream(&f);
  //buffIn = new BufferedInputStream(in);
  address = 999999;
  //line = new StringBuffer("");
  return true;
 } catch (IOException e) {
     return false;
 }
}

/**
 * Open file for writing.
 *
 * @return bool true if successful
 */
/*public*/ bool SprogHexFile::openWr() {
    _read = false;
    try {
        // Create an output writer based on the file, so we can write.
//        out = new FileOutputStream(file);
//        buffOut = new BufferedOutputStream(out);
     QFile f(file->getPath());
     if(!f.open(QIODevice::WriteOnly)) throw new IOException();
     out = new QDataStream(&f);
        return true;
    } catch (IOException e) {
        return false;
    }
}

/**
 * Close the currently open file.
 */
/*public*/ void SprogHexFile::close() {
    try {
        if (_read) {
            //buffIn.close();
            in->device()->close();
        } else {
            //buffOut.flush();
            //buffOut.close();

            out->device()->close();
        }
        name = "";
    } catch (IOException e) {

    }
}

/**
 * Read a record (line) from the hex file.
 * <p>
 * If it's an extended address record then update the address
 * and read the next line. Returns the data length.
 *
 * @return int the data length of the record, or 0 if no data
 */
//@SuppressFBWarnings(value = "DLS_DEAD_LOCAL_STORE")
// False positive
/*public*/ int SprogHexFile::read() {
    // Make space for the the maximum size record to be read
    QVector<int> record = QVector<int>(MAX_LEN);
    do {
        record = readLine();
        if (type == EXT_ADDR) {
            // Get new extended address and read next line
            address = address & 0xffff
                    + record[4] * 256 * 65536 + record[5] * 65536;
            record = readLine();
        }
    } while ((type != DATA) && (type != END));
    if (type == END) {
        return 0;
    }
    data = QVector<int>(len);
    for (int i = 0; i < len; i++) {
        data[i] = record[TYPE + 1 + i];
    }
    return len;
}

/**
 * Read a line from the hex file and verify the checksum.
 *
 * @return int[] the array of bytes read from the file
 */
/*public*/ QVector<int> SprogHexFile::readLine() {
    // Make space for the the maximum size record to be read
    QVector<int> record = QVector<int>(MAX_LEN);
    int checksum = 0;
    // Read ":"
    try {
//        //while (((charIn = in->read()) == 0xd)
//                || (charIn == 0xa)) {
     while(true)
     {
      quint8 inchar;
      *in >> inchar;
      charIn = inchar;
      if(charIn == 0xd || charIn == 0xa)
       continue;
      break;
            // skip
        }
        if (charIn != ':') {
            if (log->isDebugEnabled()) {
                log->debug("HexFile.readLine no colon at start of line " + QString::number(lineNo));
            }
            //return new int[]{-1};
            return QVector<int>(0,-1);
        }
    } catch (IOException e) {
        JOptionPane::showMessageDialog(this, tr("I/O Error reading hex file!"),
                tr("Error"), JOptionPane::ERROR_MESSAGE);
        if (log->isDebugEnabled()) {
            log->debug("I/O Error reading hex file!" + e.getMessage());
        }
    }
    // length of data
    record[LEN] = rdHexByte();
    checksum += record[LEN];
    // High address
    record[ADDRH] = rdHexByte();
    checksum += record[ADDRH];
    // Low address
    record[ADDRL] = rdHexByte();
    checksum += record[ADDRL];
    // record type
    record[TYPE] = rdHexByte();
    checksum += record[TYPE];
    // update address
    address = (address & 0xffff0000) + record[ADDRH] * 256 + record[ADDRL];
    type = record[TYPE];
    if (type != END) {
        len = record[LEN];
        for (int i = 1; i <= len; i++) {
            record[TYPE + i] = rdHexByte();
            checksum += record[TYPE + i];
        }
    }
    int fileCheck = rdHexByte();
    if (((checksum + fileCheck) & 0xff) != 0) {
        log->error("HexFile.readLine bad checksum at line " + lineNo);
    }
    lineNo++;
    return record;
}

/**
 * Read a hex byte.
 *
 * @return byte the byte that was read
 */
/*private*/ int SprogHexFile::rdHexByte() {
    int hi = rdHexDigit();
    int lo = rdHexDigit();
    if ((hi < 16) && (lo < 16)) {
        return (hi * 16 + lo);
    } else {
        return 0;
    }
}

/**
 * Read a single hex digit.
 *
 * @return 16 if digit is invalid. byte low nibble contains the hex digit read.
 * high nibble set if error.
 */
/*private*/ int SprogHexFile::rdHexDigit() {
    quint8 b = 0;
    try {
      *in >> b;
        if ((b >= '0') && (b <= '9')) {
            b = b - '0';
        } else if ((b >= 'A') && (b <= 'F')) {
            b = b - 'A' + 10;
        } else if ((b >= 'a') && (b <= 'f')) {
            b = b - 'a' + 10;
        } else {
            JOptionPane::showMessageDialog(this, tr("Invalid hex digit at line %1").arg(lineNo),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
            log->error(tr("Format Error! Invalid hex digit at line %1").arg(lineNo));
            b = 16;
        }
    } catch (IOException e) {
        JOptionPane::showMessageDialog(this, tr("I/O Error reading hex file!"),
                tr("Error"), JOptionPane::ERROR_MESSAGE);
        log->error("I/O Error reading hex file!"+ e.getMessage());
    }
    return (char) b;
}

/**
 * Write a line to the hex file.
 *
 * @param addr int the starting address of the data
 * @param type byte the type of data record being written
 * @param data QByteArray the array of bytes to be written
 */
/*public*/ void SprogHexFile::write(int addr, char type, QByteArray data) {
    // Make space for the record to be written
    QByteArray record = QByteArray(data.length() + 1 + 2 + 1,0);
    if (addr / 0x10000 != address / 0x10000) {
        // write an extended address record
//        QByteArray extAddr = {
//            2, 0, 0, EXT_ADDR, 0, (char) (addr / 0x10000)};
     const char cart[] = { 2, 0, 0, EXT_ADDR, 0, (char) (addr / 0x10000)};
     QByteArray extAddr(QByteArray::fromRawData(cart, 6));
        writeLine(extAddr);
    }
    // update current address
    address = addr;
    // save length, address and record type
    record[LEN] = (char) (data.length());
    record[ADDRH] = (char) (address / 0x100);
    record[ADDRL] = (char) (address & 0xff);
    record[TYPE] = type;
    // copy the data
    for (int i = 0; i < data.length(); i++) {
        record[TYPE + 1 + i] = data[i];
    }
    // write the record
    writeLine(record);
}

/**
 * Write an extended address record.
 *
 * @param addr the extended address
 */
/*public*/ void SprogHexFile::wrExtAddr(int addr) {
    write(0, EXT_ADDR, QByteArray{(char) (addr / 256), (char) (addr & 0xff)});
}

/**
 * Write an end of file record.
 *
 */
/*public*/ void SprogHexFile::wrEof() {
    //writeLine(new QByteArray{0, 0, 0, END});
 const char cart[] = {0, 0, 0, END};
 QByteArray a(QByteArray::fromRawData(cart, 4));
 writeLine(a);
}

/**
 * Get the type of the last record read from the hex file.
 *
 * @return byte the record type
 */
/*public*/ int SprogHexFile::getRecordType() {
    return type;
}

/**
 * Get the length of the last record read from the hex file.
 *
 * @return byte the length
 */
/*public*/ int SprogHexFile::getLen() {
    return len;
}

/**
 * Get current address.
 *
 * @return int the current address
 */
/*public*/ int SprogHexFile::getAddress() {
    return address;
}

/**
 * Get lower byte of current address.
 *
 * @return byte the lower byte of the address
 */
/*public*/ char SprogHexFile::getAddressL() {
    return (char) (address & 0xff);
}

/**
 * Get high (middle) byte of current address.
 *
 * @return byte the high (middle) byte of the address
 */
/*public*/ char SprogHexFile::getAddressH() {
    return (char) ((address / 0x100) & 0xff);
}

/**
 * Get upper byte of current address.
 *
 * @return byte the upper byte of the address
 */
/*public*/ char SprogHexFile::getAddressU() {
    return (char) (address / 0x10000);
}

/**
 * Get data from last record read.
 *
 * @return QByteArray array of data bytes
 */
/*public*/ QVector<int> SprogHexFile::getData() {
    //return Arrays.copyOf(data, data.length);
 return QVector<int>(data);
}

/**
 * Write a byte array to the hex file, prepending ":" and appending checksum
 * and carriage return.
 *
 * @param data QByteArray array of data bytes top be written
 */
/*private*/ void SprogHexFile::writeLine(QByteArray data) {
    int checksum = 0;
    try {
        //buffOut.write(':');
     *out << ':';
        for (int i = 0; i < data.length(); i++) {
            writeHexByte(data[i]);
            checksum += data[i];
        }
        checksum = checksum & 0xff;
        if (checksum > 0) {
            checksum = 256 - checksum;
        }
        writeHexByte((char) checksum);
        //buffOut.write('\n');
        *out << '\n';
    } catch (IOException e) {

    }
}

/**
 * Write a byte as two hex characters.
 *
 * @param b byte the byte to be written
 */
/*private*/ void SprogHexFile::writeHexByte(char b) {
    int i = b;
    // correct for byte being -128 to +127
    if (b < 0) {
        i = 256 + b;
    }
    writeHexDigit((char) (i / 16));
    writeHexDigit((char) (i & 0xf));
}

/**
 * Write a single hex digit.
 *
 * @param b byte low nibble contains the hex digit to be written
 */
/*private*/ void SprogHexFile::writeHexDigit(char b) {
    try {
        if (b > 9) {
            //out->write(b - 9 + 0x40);
         *out << (quint8)(b - 9 + 0x40);
        } else {
            //out->write(b + 0x30);
         *out << (quint8)(b + 0x30);
        }
    } catch (IOException e) {
    }
}
/*public*/ QString SprogHexFile::getClassName()
{
 return "jmri.jmrix.sprog.update.SprogHexFile";
}

/*private*/ /*final*/ /*static*/ Logger* SprogHexFile::log = LoggerFactory
        ::getLogger("SprogHexFile");
