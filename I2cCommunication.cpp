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
#include "I2cCommunication.h"


I2cCommunication::I2cCommunication() 
{
    #ifdef MASTER
    Wire.begin();
    #else
    Wire.begin(I2CSLAVEADDRESSESP);
    Wire.onRequest(i2cRequestCallback);
    Wire.onReceive(i2cReadCallback);
    #endif
}

/*
String I2cCommunication::getReceivedEvent()
{
    DBFUNCCALLln("I2cCommunication::getReceivedEvent()");
    return (pReceivedMessage.event);
}

bool I2cCommunication::getReadFlag_I2c()
{
    DBFUNCCALLln("I2cCommunication::getReadFlag_I2c()");
    return READFLAG_I2C;
}

void I2cCommunication::setWriteEvent(String s)
{
    DBFUNCCALLln("I2cCommunication::setWriteEvent()");
    (pWriteMessage.event) = s;
}

void I2cCommunication::setReadFlag_I2c(bool flag)
{
    DBFUNCCALLln("setReadFlag_I2c");
    READFLAG_I2C = flag;
}
*/

#ifdef MASTER
void I2cCommunication::writeMessage(WriteI2cMessage &message)
{
    Wire.beginTransmission(I2CSLAVEADDRESP);
    Wire.write((uint8_t *) &message, (size_t)sizeof(message));
    Wire.endTransmission();
    delay(50);
}

ReceivedI2cMessage I2cCommunication::readMessage()
{
    Wire.requestFrom(I2CSLAVEADDRESP, sizeof(ReceivedI2cMessage));
    while(Wire.available() < sizeof(ReceivedI2cMessage))
    {
        delay(5);
    }
    ReceivedI2cMessage tempMessage;
    Wire.readBytes((char *) &tempMessage, sizeof(tempMessage));
    return tempMessage;
}

/*
String I2cCommunication::getReceivedState()
{
    DBFUNCCALLln("I2cCommunication::getReceivedState()");
    return (pReceivedMessage.state);
}

String I2cCommunication::getReceivedPosition()
{
    DBFUNCCALLln("I2cCommunication::getReceivedPosition()");
    return (pReceivedMessage.position);
}

Package I2cCommunication::getReceivedPackageInformation()
{
    DBFUNCCALLln("I2cCommunication::getReceivedPackageInformation()");
    return (pReceivedMessage.packageInformation);
}

void I2cCommunication::setWriteInformation(String s)
{
    DBFUNCCALLln("I2cCommunication::setWriteInformation");
    (pWriteMessage.information) = s;
}
*/
#else

void I2cCommunication::ReadCallback(int bytes)
{
    DBFUNCCALLln("receiveEvent()");
    READFLAG_I2C = true;
    //readData();
    while (0 < Wire.available())
    {
        Wire.readBytes( (char*) &pReceivedMessage, sizeof(ReceivedI2cMessage));
    }
}

void I2cCommunication::RequestCallback()
{
    DBFUNCCALLln("I2cCommunication::i2cRequestCallback()");
    Wire.write((char*) &pWriteMessage, sizeof(WriteI2cMessage);
}
#endif

void I2cCommunication::resetReceivedMessages()
{
    DBFUNCCALLln("I2cCommunication::resetMessages()");
    pReceivedI2cMessage[0].event = "null";
    #ifdef MASTER
    pReceivedI2cMessage[0].state = "null";
    pReceivedI2cMessage[0].position = -1;
    pReceivedI2cMessage[0].packageId = 0;
    pReceivedI2cMessage[0].cargo = "null";
    pReceivedI2cMessage[0].targetDest = "null";
    #else
    pReceivedI2cMessage[0].information = "null";
    #endif
}

/*
void I2cCommunication::resetWriteMessages()
{
    DBFUNCCALLln("I2cCommunication::resetWriteMessages()");
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
*/