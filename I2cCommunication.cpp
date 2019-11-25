/**
 * @file I2cCommunication.cpp
 * @author Philip Zellweger (philip.zellweger@hsr.ch)
 * @brief I2c communication library for master and slave
 * @version 0.1
 * @date 2019-11-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "I2cCommunicationSlave.h"


I2cCommunicationSlave::I2cCommunicationSlave() 
{
    #ifdef MASTER
    Wire.begin();
    #else
    Wire.begin(I2C_SLAVE_ADDRESS_ESP);
    Wire.onRequest(i2cRequestCallback);
    Wire.onReceive(i2cReadCallback);
    #endif
}

String I2cCommunicationSlave::getReceivedEvent()
{
    DBFUNCCALLln("I2cCommunicationSlave::getReceivedEvent()");
    return (pReceivedMessage.event);
}

bool I2cCommunicationSlave::getReadFlag_I2c()
{
    DBFUNCCALLln("I2cCommunicationSlave::getReadFlag_I2c()");
    return READFLAG_I2C;
}

void I2cCommunicationSlave::setWriteEvent(String s)
{
    DBFUNCCALLln("I2cCommunicationSlave::setWriteEvent()");
    (pWriteMessage.event) = s;
}

void I2cCommunicationSlave::setReadFlag_I2c(bool flag)
{
    DBFUNCCALLln("setReadFlag_I2c");
    READFLAG_I2C = flag;
}

#ifdef MASTER
void I2cCommunicationSlave::i2cWriteMessage()
{

}

void I2cCommunicationSlave::i2cReadMessage()
{

}

String I2cCommunicationSlave::getReceivedState()
{
    DBFUNCCALLln("I2cCommunicationSlave::getReceivedState()");
    return (pReceivedMessage.state);
}

String I2cCommunicationSlave::getReceivedPosition()
{
    DBFUNCCALLln("I2cCommunicationSlave::getReceivedPosition()");
    return (pReceivedMessage.position);
}

Package I2cCommunicationSlave::getReceivedPackageInformation()
{
    DBFUNCCALLln("I2cCommunicationSlave::getReceivedPackageInformation()");
    return (pReceivedMessage.packageInformation);
}

void I2cCommunicationSlave::setWriteInformation(String s)
{
    DBFUNCCALLln("I2cCommunicationSlave::setWriteInformation");
    (pWriteMessage.information) = s;
}

#else

void I2cCommunicationSlave::i2cReadCallback(int bytes)
{
    DBFUNCCALLln("receiveEvent()");
    READFLAG_I2C = true;
    //readData();
    while (0 < Wire.available())
    {
        Wire.readBytes( (char*) &pReceivedMessage, sizeof(ReceivedI2cMessage));
    }
    
}

void I2cCommunicationSlave::i2cRequestCallback()
{
    DBFUNCCALLln("I2cCommunicationSlave::i2cRequestCallback()");
    Wire.write( (char*) &pWriteMessage);
}

#endif

void I2cCommunicationSlave::resetReceivedMessages()
{
    DBFUNCCALLln("I2cCommunicationSlave::resetMessages()");
    pReceivedMessage.event = "null";
    #ifdef MASTER
    pReceivedMessage.information = "null";
    #else
    pReceivedMessage.state = "null";
    pReceivedMessage.position = "null";
    pReceivedMessage.packageInformation.id = "null";
    pReceivedMessage.packageInformation.cargo = "null";
    pReceivedMessage.packageInformation.targetDest = "null";
    pReceivedMessage.packageInformation.targetReg = "null";
    #endif
}

void I2cCommunicationSlave::resetWriteMessages()
{
    DBFUNCCALLln("I2cCommunicationSlave::resetWriteMessages()");
    pWriteMessage.event = "null";
    #ifdef MASTER
    pReceivedMessage.state = "null";
    pReceivedMessage.position = "null";
    pReceivedMessage.packageInformation.id = "null";
    pReceivedMessage.packageInformation.cargo = "null";
    pReceivedMessage.packageInformation.targetDest = "null";
    pReceivedMessage.packageInformation.targetReg = "null";
    #else
    pWriteMessage.information = "null";
    #endif
}