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


#ifdef MASTER
I2cCommunication::I2cCommunication(int adress,ReceivedI2cMessage *receivedMessage, WriteI2cMessage *writeMessage) : 
                                            pReceivedMessage(receivedMessage),
                                            pWriteMessage(writeMessage),
                                            pAdress(adress)
{
    DBFUNCCALLln("I2cCommunication::I2cCommunication(int, ReceivedI2cMessage, WriteI2cMessage, size_t, size_t)");
    Wire.begin(21,22,16000000); // change!
}

void I2cCommunication::writeMessage()
{
    DBFUNCCALLln("I2cCommunication::writeMessage()");
    Wire.beginTransmission(pAdress);
    Wire.write((uint8_t *) pWriteMessage, sizeof(WriteI2cMessage));
    Wire.endTransmission();
    delay(50);
}

void I2cCommunication::readMessage()
{
    DBFUNCCALLln("I2cCommunication::readMessage()");
    Wire.requestFrom(pAdress, sizeof(ReceivedI2cMessage));
    
    // TEST
    // Serial.println(" request sended ");
    // TEST

    unsigned long currentMillis = millis();
    unsigned long previousMillis = currentMillis;
    while(Wire.available() < sizeof(ReceivedI2cMessage))
    {
        DBINFO2ln(" Wait till data available ");
        delay(5);
        currentMillis = millis();
        // TEST
        // Serial.print("Time: ");
        // Serial.println((currentMillis - previousMillis));
        // TEST
        if ((currentMillis - previousMillis) > 50)
        {
            // Throw exception here!
                // TODO
            DBERROR("Request failed");
            return;
        }
    }

    // TEST
    //Serial.println(" copy data ");
    
    Wire.readBytes((char *) pReceivedMessage, sizeof(ReceivedI2cMessage));

    //TEST
    /*
    //Serial.println(" copy data finish ");
    
    for (int i = 0; i < 12; i++)
    {
        Serial.print(pReceivedMessage->event[i]);
    }
    Serial.println();
    Serial.println(pReceivedMessage->packageId);
    Serial.println(pReceivedMessage->targetDest);
    Serial.println(pReceivedMessage->position);
    Serial.println(pReceivedMessage->state);
    Serial.println(pReceivedMessage->error);
    Serial.println(pReceivedMessage->token);
    */
    // TEST
    
}
#else

I2cCommunication::I2cCommunication(int adress, void (*receiveCallback)(int bytes), void (*requestCallback)()) : 
                                                            receiveCallbackFuncPointer(receiveCallback), 
                                                            requestCallbackFuncPointer(requestCallback),
                                                            pAdress(adress)
{
    DBFUNCCALLln("I2cCommunication::I2cCommunication(int adress)");
    Wire.begin(7);
    Wire.onRequest(requestCallbackFuncPointer);
    Wire.onReceive(receiveCallbackFuncPointer);
}
#endif


