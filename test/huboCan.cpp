/* 
    Conductor: High Degree of Freedom Robot Controller Framework
    Copyright (C) 2010, 2011 Robert Sherbert
    bob.sherbert@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    aint with this program.  If not, see <http://www.gnu.org/licenses/>.

    If you are interested in licensing this software for commercial purposes
    please contact the author. The software can be licensed to you under
    non-free license terms by the copyright holder.

    As a courtesy to the author, and in the spirit of fair attribution, you are
    asked to cite the following paper if any work based upon or utilizing this
    framework is published in the scientific literature: 
    Sherbert, Robert M. and Oh, Paul Y. "Conductor: A Controller Development
    Framework for High Degree of Freedom Systems." Intelligent Robots and
    Systems (IROS), 2011 IEEE/RSJ International Conference on. 
*/

#include "huboCan.h"

    canMsg::canMsg(): BNO(boardNum(0)), type(CAN_NONE), subType(CMD_NONE), r1(0), r2(0),
                      r3(0), r4(0), r5(0)
    {}

    canMsg::canMsg(boardNum BNO, messageType Type, cmdType st) :
        BNO(BNO), type(Type), subType(st), r1(0), r2(0), r3(0), r4(0), r5(0){}

    canMsg::canMsg(boardNum BNO, messageType Type, cmdType st,
                   int R1, int R2,
                   int R3, int R4,
                   int R5)
            : BNO(BNO), type(Type), subType(st), r1(R1), r2(R2), r3(R3), r4(R4),
              r5(R5){}

    boardNum canMsg::getBNO(){
        return BNO;
    }

    messageType canMsg::getType(){
        return type;
    }

    cmdType canMsg::getCmd(){
        return subType;
    }

    int canMsg::getR1(){
        return r1;
    }

    int canMsg::getR2(){
        return r2;
    }

    int canMsg::getR3(){
        return r3;
    }

    int canMsg::getR4(){
        return r4;
    }

    int canMsg::getR5(){
        return r5;
    }

    void canMsg::setR1(int r1){
        this->r1 = r1;
    }

    void canMsg::setR2(int r2){
        this->r2 = r2;
    }

    void canMsg::setR3(int r3){
        this->r3 = r3;
    }

    void canMsg::setR4(int r4){
        this->r4 = r4;
    }

    void canMsg::setR5(int r5){
        this->r5 = r5;
    }

    void canMsg::printme(){
        std::ostringstream s(std::ostringstream::out);

        s << "[" << std::setbase(16) << BNO << "]{"
                 << std::setbase(16) << type << "/"
                 << std::setbase(16) << subType
                 << "} "; 
        s << "R1 = 0x" << std::hex << r1 << ", ";
        s << "R2 = 0x" << std::hex << r2 << ", ";
        s << "R3 = 0x" << std::hex << r3 << ", ";
        s << "R4 = 0x" << std::hex << r4 << ", ";
        s << "R5 = 0x" << std::hex << r5;
        cout << s.str() << endl;
    }

    /* The bitStuffing algorithems are pulled directly from the original hubo
     * code base. They're wrong in that they use a sign bit instead of a two's
     * complement representation, but I'm maintaing them because they're needed
     * to ensure compatibility with the motor controllers */
    int canMsg::bitStuff15byte(int bs){
        if (bs < 0) return( (int)(((-bs) & 0x000007FF) | (1<<11)) );
        else	return( (int)(bs) );
    }

    int canMsg::bitStuff3byte(int bs){
        if (bs < 0) return( (int)(((-bs) & 0x007FFFFF) | (1<<23)) );
        else	return( (int)(bs) );
    }

    int canMsg::bitStuffCalibratePacket(int bs){
        if (bs < 0) return( (int)(((-bs) & 0x0007FFFF) | (1<<19)) );
        else	return( (int)(bs) );
    }

    unsigned char canMsg::bitStrip(int src, int byteNum){
        unsigned char retval;
//        retval = (unsigned char)( (src >> (8*byteNum)) & 0x000000FFu );
        int mask = (8 << byteNum) - 1;

        return retval;
    }

    unsigned char* ticksToArray(int src){
        unsigned char* retval = new unsigned char[3];

        int b0i = 255;
        int b1i = 65280;
        int b2i = 16711680;

        int a = abs(src); 

        unsigned char b0 = a & b0i;
        unsigned char b1 = (a & b1i) >> 8;
        unsigned char b2 = (a & b2i) >> 16;
        unsigned char t = 0;

        if (src < 0)
            t = 128;

        b2 = (b2 & 127) | t;

        retval[0] = b0;
        retval[1] = b1;
        retval[2] = b2;

        //printf("%d = %02X %02X %02X\n", src, b0, b1, b2);

        return retval;
    }


    canmsg_t* canMsg::toCAN(){
        return toLineType();
    }

    string canMsg::toSerial(){
        canmsg_t* cm = toLineType();
        char* buf = new char[3];
        string output = "t";
        sprintf(buf, "%03X", (unsigned int)cm->id);
        output += buf;
        sprintf(buf, "%d", cm->length);
        output += buf;
        buf = new char[2];
        for (int i = 0; i < cm->length; i++){
            sprintf(buf, "%02X", cm->data[i]);
            output += buf;
        }
        return output;
    }

    canmsg_t* canMsg::toLineType(){
        canmsg_t* cm = new canmsg_t;
        cm->flags = 0;
        cm->cob = 0;
        //cm->timestamp = 0;
        
        switch(type){
            //How to construct the outbound packets
            case TX_MOTOR_CMD:
		cm->id = (unsigned char) type;
                processCMD(cm);
                break;
            case TX_SENSOR_CMD:
		cm->id = (unsigned char) type;
                cm->length = 1;
                cm->data[0] = 0;
                break;
            case TX_REF:
		cm->id = BNO + (unsigned char) type;
                processREF(cm);
                break;
            //Inbound packet types are not allowed here, and represent an error
        /*    case SENSOR_FT_RXDF:
            case SENSOR_AD_RXDF:
            case ENC_RXDF:
            case CUR_RXDF:
            case PM_RXDF:
            case STAT_RXDF:
            case NAME_RXDF:
            case DAOFFSET_RXDF:
            case ADOFFSET_RXDF:
            case OFFSET_RXDF:
          */  default:
                assert(false);
        }
        return cm;
    }

    canmsg_t* canMsg::processCMD(canmsg_t* cm){
        cm->data[0] = (unsigned char)BNO;
        cm->data[1] = (unsigned char)subType;
        switch(subType){
            /*  Command messages are split into various register to byte combinations.  See
                comment above each block for mapping diagram. */

            /*******************************************************************
               |  B0  |  B1  |  B2  |  B3  |  B4  |  B5  |  B6  |  B7  |
                                                                   
               |  BNO |  sub |     r1      |     r2      |     r3      |
            *******************************************************************/

            case CMD_SET_POS_GAIN_0:
            case CMD_SET_POS_GAIN_1:
            case CMD_SET_CUR_GAIN_0:
            case CMD_SET_CUR_GAIN_1:
            case CMD_SET_ERR_BOUND:
            case CMD_SET_FT_0:
            case CMD_SET_FT_1:
            case CMD_SET_FT_2:
            case CMD_SET_INCLINO_SCALE:
                cm->data[2] = bitStrip(r1, 0);
                cm->data[3] = bitStrip(r1, 1);
                cm->data[4] = bitStrip(r2, 0);
                cm->data[5] = bitStrip(r2, 1);
                cm->data[6] = bitStrip(r3, 0);
                cm->data[7] = bitStrip(r3, 1);
                cm->length = 8;
            break;

            /*******************************************************************
               |  B0  |  B1  |  B2  |  B3  |  B4  |  B5  |  B6  |  B7  |
                                                                   
               |  BNO |  sub |  r1  |  --  |  --  |  --  |  --  |  --  |
            *******************************************************************/

            case CMD_SETREQ_BOARD_INFO:
            case CMD_REQ_ENC_POS:
            case CMD_RESET_ENC_ZERO:
            case CMD_HIP_ENABLE:
            case CMD_SET_CTRL_MODE:
            case CMD_SET_DEAD_ZONE:
            case CMD_REQ_BOARD_PARAM:
            case CMD_NULL:                //ALSO CMD_SET_SWITCH
            case CMD_REQ_ALARM:
            case CMD_REQ_BEEP:
                cm->data[2] = r1;
                cm->length = 3; 
            break;
          
            /*******************************************************************
               |  B0  |  B1  |  B2  |  B3  |  B4  |  B5  |  B6  |  B7  |
                                                                   
               |  BNO |  sub |  --  |  --  |  --  |  --  |  --  |  --  |
            *******************************************************************/
            
            case CMD_REQ_BOARD_STATUS:
            case CMD_REQ_CURR:
            case CMD_CONTROLLER_ON:
            case CMD_CONTROLLER_OFF:
            case CMD_INIT_BOARD:
            case CMD_REQ_VOLT_CUR:
            case CMD_REQ_TIME_STATUS:
            //case CMD_CALIBRATE: 
                cm->length = 2;
            break;


        }
        return cm;
    }

    canmsg_t* canMsg::processREF(canmsg_t* cm){
        cm->length = 6;
        unsigned char* first = new unsigned char[3];
        unsigned char* second = new unsigned char[3];
        switch((int)subType){
            case 2:
                // Dual motor boards (most joints)
                first = ticksToArray(r1);
                second = ticksToArray(r2);

                cm->data[0] = first[0];
                cm->data[1] = first[1];
                cm->data[2] = first[2];
                cm->data[3] = second[0];
                cm->data[4] = second[1];
                cm->data[5] = second[2];

                break;
            case 3:
                // Neck
                cm->data[0] = bitStrip(r1, 0);
                cm->data[1] = bitStrip(r1, 1);
                cm->data[2] = bitStrip(r2, 0);
                cm->data[3] = bitStrip(r2, 1);
                cm->data[4] = bitStrip(r3, 0);
                cm->data[5] = bitStrip(r3, 1);
                break;
            case 5:
                // Hands/Fingers
                cm->data[0] = bitStrip(r1,0);
                cm->data[1] = bitStrip(r2,0);
                cm->data[2] = bitStrip(r3,0);
                cm->data[3] = bitStrip(r4,0);
                cm->data[4] = bitStrip(r5,0);
            default:
                assert(false);
        }
        return cm;
    }
/*
int main(){
    
    canMsg test = canMsg(BNO_R_HIP_YAW_ROLL, TX_REF, cmdType(2), 1000, 2000, 0, 0, 0);
    cout << test.toSerial() << endl;
    return 0;
}
*/
