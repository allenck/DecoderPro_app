#include "exceptions.h"

//Exception::Exception(QString msg)
//{
// this->msg = msg;
//}
//QString Exception::getMessage() {return msg;}

//QString Exception::getLocalizedMessage() { return "default localized message!";}

LocoNetException::LocoNetException(QString m) : JmriException(m)
{
 msg = m;
}
/**
 *  LocoNet-specific exception
 *
 * @author			Bob Jacobsen  Copyright (C) 2001
 * @version	$Revision: 17977 $
 */
QString LocoNetException::getText() {return msg;}

EOFException::EOFException(QString msg)
{
this->msg = msg;
}

IOException::IOException(QString msg)
{
this->msg = msg;
}
QString IOException::getMessage() {return msg;}

IIOException::IIOException(QString msg)
{
this->msg = msg;
}
QString IIOException::getMessage() {return msg;}


LocoNetMessageException::LocoNetMessageException(QString s)
{
 msg = s;
}

JmriException::JmriException(QString s)
{
 msg = s;
}

QString JmriException::toString()
{
 return msg;
}

NoSuchElementException::NoSuchElementException(QString s) {msg = s;}

InterruptedException::InterruptedException()
{
}
IllegalArgumentException::IllegalArgumentException(QString s)
{
 msg = s;
}

NumberFormatException::NumberFormatException(QString s)
{
    msg=s;
}
ProgrammerException::ProgrammerException(QString s)
{
    msg=s;
}
TimebaseRateException::TimebaseRateException(QString s)
{
    msg=s;
}

UnsupportedCommOperationException::UnsupportedCommOperationException(QString s)
{
 msg = s;
}
UnsupportedOperationException::UnsupportedOperationException(QString s)
{
 msg = s;
}
NoSuchPortException::NoSuchPortException(QString s)
{
 msg = s;
}
NullPointerException::NullPointerException(QString s)
{
 msg = s;
}
DataConversionException::DataConversionException(QString s)
{
 msg = s;
}
TurnoutOperatorException::TurnoutOperatorException(QString s)
{
 msg = s;
}
//Throwable::Throwable(QString s) {msg = s;}
JDOMException::JDOMException(QString s){msg = s;}
FileNotFoundException::FileNotFoundException(QString s){msg=s;}
ParseException::ParseException(QString s){msg=s;}
PortInUseException::PortInUseException(QString s) {msg=s;}
JmriConfigureXmlException::JmriConfigureXmlException(QString s) : JmriException(s) {msg =s;}
ClassNotFoundException::ClassNotFoundException(QString s) {msg=s;}
NoClassDefFoundError::NoClassDefFoundError(QString s) {msg=s;}
IllegalAccessException::IllegalAccessException(QString s) {msg=s;}
InstantiationException::InstantiationException(QString s) {msg=s;}
MalformedURLException::MalformedURLException(QString s) {msg=s;}
IndexOutOfBoundsException::IndexOutOfBoundsException(QString s) {msg = s;}
MissingResourceException::MissingResourceException(QString s) {msg = s;}
IllegalStateException::IllegalStateException(QString s) {msg = s;}
ArrayIndexOutOfBoundsException::ArrayIndexOutOfBoundsException(QString s) {msg = s;}
EmptyStackException::EmptyStackException(QString s) {msg = s;}
Error::Error(QString s) {msg = s;}
CloneNotSupportedException::CloneNotSupportedException(QString s) {msg = s;}
NegativeArraySizeException::NegativeArraySizeException(QString s) {msg = s;}
UnsupportedFlavorException::UnsupportedFlavorException(QString s) {msg = s;}
MimeTypeParseException::MimeTypeParseException(QString s) {msg = s;}
InvalidDnDOperationException::InvalidDnDOperationException(QString s) {msg = s;}
HeadlessException::HeadlessException(QString s) {msg = s;}
TooManyListenersException::TooManyListenersException(QString s) {msg = s;}
PrinterException::PrinterException(QString s) {msg = s;}
AudioException::AudioException(QString s) {msg = s;}
SAXException::SAXException(QString s) {msg = s;}
UnsatisfiedLinkError::UnsatisfiedLinkError(QString s) {msg = s;}
BackingStoreException::BackingStoreException(QString s) {msg = s;}
NoSuchMethodException::NoSuchMethodException(QString s) {msg = s;}
InvocationTargetException::InvocationTargetException(QString s) {msg = s;}
TransformerFactoryConfigurationError::TransformerFactoryConfigurationError(QString s) {msg = s;}
