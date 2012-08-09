#include "RobotControl.h"
#include <iostream>
using namespace std;

RobotControl::RobotControl(const std::string& name):
    TaskContext(name)
  {
    this->canUpPort = new InputPort<hubomsg::CanMessage>("can_up");
    this->canDownPort = new OutputPort<hubomsg::CanMessage>("can_down");
    this->orOutPort = new InputPort<hubomsg::HuboCmd>("or_out");
    this->orInPort = new OutputPort<hubomsg::HuboCmd>("or_in");

    //CAN PORTS 
    this->addEventPort(*canUpPort);
    this->addPort(*canDownPort);

    //OPENRAVE PORTS
    this->addEventPort(*orOutPort);
    this->addPort(*orInPort);

    this->addOperation("setWaist", &RobotControl::setWaist, this, RTT::OwnThread)
            .doc("Set Torso Yaw")
            .arg("Value", "New ticks for torso yaw.");
    
    this->addOperation("setLeftShoulderRoll", &RobotControl::setLeftShoulderRoll, this, RTT::OwnThread)
            .doc("Set Left Shoulder Roll")
            .arg("Value", "New ticks for left shoulder roll.");
    
    this->addOperation("setLeftShoulderPitch", &RobotControl::setLeftShoulderPitch, this, RTT::OwnThread)
            .doc("Set Left Shoulder Pitch")
            .arg("Value", "New ticks for left shoulder pitch.");
   
    this->addOperation("setLeftShoulderYaw", &RobotControl::setLeftShoulderYaw, this, RTT::OwnThread)
            .doc("Set Left Shoulder Yaw")
            .arg("Value", "New ticks for left shoulder yaw.");
   
    this->addOperation("setLeftElbow", &RobotControl::setLeftElbow, this, RTT::OwnThread)
            .doc("Set Left Elbow")
            .arg("Value", "New ticks for left elbow.");

    this->addOperation("setLeftWristPitch", &RobotControl::setLeftWristPitch, this, RTT::OwnThread)
            .doc("Set Left Wrist Pitch")
            .arg("Value", "New ticks for left wrist pitch.");

    this->addOperation("setLeftWristYaw", &RobotControl::setLeftWristYaw, this, RTT::OwnThread)
            .doc("Set Left Wrist Yaw")
            .arg("Value", "New ticks for left Wrist Yaw.");

    this->addOperation("setRightShoulderRoll", &RobotControl::setRightShoulderRoll, this, RTT::OwnThread)
            .doc("Set Right Shoulder Roll")
            .arg("Value", "New ticks for right shoulder roll.");

    this->addOperation("setRightShoulderPitch", &RobotControl::setRightShoulderPitch, this, RTT::OwnThread)
            .doc("Set Right Shoulder Pitch")
            .arg("Value", "New ticks for right shoulder pitch.");

    this->addOperation("setRightShoulderYaw", &RobotControl::setRightShoulderYaw, this, RTT::OwnThread)
            .doc("Set Right Shoulder Yaw")
            .arg("Value", "New ticks for right shoulder yaw.");			
			
    this->addOperation("setRightElbow", &RobotControl::setRightElbow, this, RTT::OwnThread)
            .doc("Set Right Elbow")
            .arg("Value", "New ticks for right elbow.");

    this->addOperation("setRightWristPitch", &RobotControl::setRightWristPitch, this, RTT::OwnThread)
            .doc("Set Right Wrist Pitch")
            .arg("Value", "New ticks for right wrist pitch.");

    this->addOperation("setRightWristYaw", &RobotControl::setRightWristYaw, this, RTT::OwnThread)
            .doc("Set Right Wrist Yaw")
            .arg("Value", "New ticks for right wrist yaw.");

    this->addOperation("setLeftHipYaw", &RobotControl::setLeftHipYaw, this, RTT::OwnThread)
            .doc("Set Left Hip Yaw")
            .arg("Value", "New ticks for left hip yaw.");

    this->addOperation("setLeftHipRoll", &RobotControl::setLeftHipRoll, this, RTT::OwnThread)
            .doc("Set Left Hip Roll")
            .arg("Value", "New ticks for left hip roll.");

    this->addOperation("setLeftHipPitch", &RobotControl::setLeftHipPitch, this, RTT::OwnThread)
            .doc("Set Left Hip Pitch")
            .arg("Value", "New ticks for left hip pitch.");

    this->addOperation("setLeftKnee", &RobotControl::setLeftKnee, this, RTT::OwnThread)
            .doc("Set Left Knee")
            .arg("Value", "New ticks for left knee.");

    this->addOperation("setLeftAnklePitch", &RobotControl::setLeftAnklePitch, this, RTT::OwnThread)
            .doc("Set Left Ankle Pitch")
            .arg("Value", "New ticks for left ankle pitch.");

    this->addOperation("setLeftAnkleRoll", &RobotControl::setLeftAnkleRoll, this, RTT::OwnThread)
            .doc("Set Left Ankle Roll")
            .arg("Value", "New ticks for left ankle roll.");

    this->addOperation("setRightHipYaw", &RobotControl::setRightHipYaw, this, RTT::OwnThread)
            .doc("Set Right Hip Yaw")
            .arg("Value", "New ticks for right hip yaw.");

    this->addOperation("setRightHipRoll", &RobotControl::setRightHipRoll, this, RTT::OwnThread)
            .doc("Set Right Hip Roll")
            .arg("Value", "New ticks for right hip roll.");

    this->addOperation("setRightHipPitch", &RobotControl::setRightHipPitch, this, RTT::OwnThread)
            .doc("Set Right Hip Pitch")
            .arg("Value", "New ticks for right hip pitch.");

    this->addOperation("setRightKnee", &RobotControl::setRightKnee, this, RTT::OwnThread)
            .doc("Set Right Knee")
            .arg("Value", "New ticks for right knee.");

    this->addOperation("setRightAnklePitch", &RobotControl::setRightAnklePitch, this, RTT::OwnThread)
            .doc("Set Right Ankle Pitch")
            .arg("Value", "New ticks for right ankle pitch.");

    this->addOperation("setRightAnkleRoll", &RobotControl::setRightAnkleRoll, this, RTT::OwnThread)
            .doc("Set Right Ankle Roll")
            .arg("Value", "New ticks for right ankle roll.");

  }
  
  RobotControl::~RobotControl(){}

  void RobotControl::updateHook(){
    hubomsg::HuboCmd huboCmd = hubomsg::HuboCmd();
    hubomsg::CanMessage canMessage = hubomsg::CanMessage();
    if (NewData == this->canUpPort->read(canMessage)){
        //Received update from CanGateway
    }
    if (NewData == this->orOutPort->read(huboCmd)){
        //Recieved update from openRAVE
    }
  }

  hubomsg::CanMessage RobotControl::buildCanMessage(canMsg* msg){
      hubomsg::CanMessage canMessage;

      canMessage.bno = msg->getBNO();
      canMessage.mType = msg->getType();
      canMessage.cmdType = msg->getCmd();
      canMessage.r1 = msg->getR1();
      canMessage.r2 = msg->getR2();
      canMessage.r3 = msg->getR3();
      canMessage.r4 = msg->getR4();
      canMessage.r5 = msg->getR5();

      return canMessage;
  }

  void RobotControl::setWaist(int ticks){
      //ros_gateway->transmit(0,ticks);

      canMsg* out = new canMsg(BNO_WAIST, TX_REF, CMD_NONE,
                               ticks, 0, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
  }

  void RobotControl::setNeck(int ticks, int one, int two){

      canMsg* out = new canMsg(BNO_NECK_YAW_1_2, TX_REF, CMD_NONE,
                               ticks, one, two, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
     //ros_gateway->transmit(1,ticks);
  }

  void RobotControl::setLeftShoulderRoll(int ticks){
      canMsg* out = new canMsg(BNO_L_SHOULDER_PITCH_ROLL, TX_REF, CMD_NONE,
                               state.getMotorByName(LSP)->getTicksPosition(), ticks, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
     //ros_gateway->transmit(3,ticks);
  }

  void RobotControl::setLeftShoulderPitch(int ticks){
      canMsg* out = new canMsg(BNO_L_SHOULDER_PITCH_ROLL, TX_REF, CMD_NONE,
                               ticks, state.getMotorByName(LSR)->getTicksPosition(), 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
     //ros_gateway->transmit(4,ticks);
  }
  
  void RobotControl::setLeftShoulderYaw(int ticks){
      canMsg* out = new canMsg(BNO_L_SHOULDER_YAW_ELBOW, TX_REF, CMD_NONE,
                               ticks, state.getMotorByName(LEB)->getTicksPosition(), 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
     //ros_gateway->transmit(6,ticks);
  }

  void RobotControl::setLeftElbow(int ticks){
      canMsg* out = new canMsg(BNO_L_SHOULDER_YAW_ELBOW, TX_REF, CMD_NONE,
                               state.getMotorByName(LSY)->getTicksPosition(), ticks, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
     //ros_gateway->transmit(6,ticks);
  }

  void RobotControl::setLeftWristPitch(int ticks){
      canMsg* out = new canMsg(BNO_L_WRIST_YAW_PITCH, TX_REF, CMD_NONE,
                               state.getMotorByName(LWY)->getTicksPosition(), ticks, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
     //ros_gateway->transmit(8,ticks);
  }

  void RobotControl::setLeftWristYaw(int ticks){
      canMsg* out = new canMsg(BNO_L_WRIST_YAW_PITCH, TX_REF, CMD_NONE,
                               ticks, state.getMotorByName(LWP)->getTicksPosition(), 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(9,ticks);
  }

  void RobotControl::setRightShoulderRoll(int ticks){
      canMsg* out = new canMsg(BNO_R_SHOULDER_PITCH_ROLL, TX_REF, CMD_NONE,
                               state.getMotorByName(RSP)->getTicksPosition(), ticks, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(11,ticks);
  }

  void RobotControl::setRightShoulderPitch(int ticks){
      canMsg* out = new canMsg(BNO_R_SHOULDER_PITCH_ROLL, TX_REF, CMD_NONE,
                               ticks, state.getMotorByName(RSR)->getTicksPosition(), 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(12,ticks);
  }

  void RobotControl::setRightShoulderYaw(int ticks){
      canMsg* out = new canMsg(BNO_R_SHOULDER_YAW_ELBOW, TX_REF, CMD_NONE,
                               ticks, state.getMotorByName(REB)->getTicksPosition(), 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
  }
  
  void RobotControl::setRightElbow(int ticks){
      canMsg* out = new canMsg(BNO_R_SHOULDER_YAW_ELBOW, TX_REF, CMD_NONE,
                               state.getMotorByName(RSY)->getTicksPosition(), ticks, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(14,ticks);
  }

  void RobotControl::setRightWristPitch(int ticks){
      canMsg* out = new canMsg(BNO_R_WRIST_YAW_PITCH, TX_REF, CMD_NONE,
                               state.getMotorByName(RWY)->getTicksPosition(), ticks, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(16,ticks);
  }

  void RobotControl::setRightWristYaw(int ticks){
      canMsg* out = new canMsg(BNO_R_WRIST_YAW_PITCH, TX_REF, CMD_NONE,
                               ticks, state.getMotorByName(RWP)->getTicksPosition(), 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(17,ticks);
  }

  void RobotControl::setLeftHipYaw(int ticks){
      canMsg* out = new canMsg(BNO_L_HIP_YAW_ROLL, TX_REF, CMD_NONE,
                               ticks, state.getMotorByName(LHR)->getTicksPosition(), 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(19,ticks);
  }

  void RobotControl::setLeftHipRoll(int ticks){
      canMsg* out = new canMsg(BNO_L_HIP_YAW_ROLL, TX_REF, CMD_NONE,
                               state.getMotorByName(LHY)->getTicksPosition(), ticks, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(20,ticks);
  }

  void RobotControl::setLeftHipPitch(int ticks){
      canMsg* out = new canMsg(BNO_L_HIP_PITCH, TX_REF, CMD_NONE,
                               ticks, 0, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(21,ticks);
  }

  void RobotControl::setLeftKnee(int ticks){
      canMsg* out = new canMsg(BNO_L_KNEE, TX_REF, CMD_NONE,
                               ticks, 0, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(22,ticks);
  }

  void RobotControl::setLeftAnklePitch(int ticks){
      canMsg* out = new canMsg(BNO_L_ANKLE_PITCH_ROLL, TX_REF, CMD_NONE,
                               ticks, state.getMotorByName(LAR)->getTicksPosition(), 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(23,ticks);
  }

  void RobotControl::setLeftAnkleRoll(int ticks){
      canMsg* out = new canMsg(BNO_L_ANKLE_PITCH_ROLL, TX_REF, CMD_NONE,
                               state.getMotorByName(LAP)->getTicksPosition(), ticks, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(24,ticks);
  }

  void RobotControl::setRightHipYaw(int ticks){
      canMsg* out = new canMsg(BNO_R_HIP_YAW_ROLL, TX_REF, CMD_NONE,
                               ticks, state.getMotorByName(RHR)->getTicksPosition(), 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(26,ticks);
  }

  void RobotControl::setRightHipRoll(int ticks){
      canMsg* out = new canMsg(BNO_R_HIP_YAW_ROLL, TX_REF, CMD_NONE,
                               state.getMotorByName(RHY)->getTicksPosition(), ticks, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(27,ticks);
  }

  void RobotControl::setRightHipPitch(int ticks){
      canMsg* out = new canMsg(BNO_R_HIP_PITCH, TX_REF, CMD_NONE,
                               ticks, 0, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(28,ticks);
  }

  void RobotControl::setRightKnee(int ticks){
      canMsg* out = new canMsg(BNO_R_KNEE, TX_REF, CMD_NONE,
                               ticks, 0, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(29,ticks);
  }

  void RobotControl::setRightAnklePitch(int ticks){
      canMsg* out = new canMsg(BNO_R_ANKLE_PITCH_ROLL, TX_REF, CMD_NONE,
                               ticks, state.getMotorByName(RAR)->getTicksPosition(), 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(30,ticks);
  }

  void RobotControl::setRightAnkleRoll(int ticks){
      canMsg* out = new canMsg(BNO_R_ANKLE_PITCH_ROLL, TX_REF, CMD_NONE,
                               state.getMotorByName(RAP)->getTicksPosition(), ticks, 0, 0, 0);
      this->canDownPort->write(buildCanMessage(out));
      //ros_gateway->transmit(31,ticks);
  }

  void RobotControl::setRightHand(int f0, int f1, int f2, int f3, int f4){
      canMsg* out = new canMsg(BNO_R_HAND, TX_REF, CMD_NONE,
                               f0, f1, f2, f3, f4);
      this->canDownPort->write(buildCanMessage(out));
  }

  void RobotControl::setLeftHand(int f0, int f1, int f2, int f3, int f4){
      canMsg* out = new canMsg(BNO_L_HAND, TX_REF, CMD_NONE,
                               f0, f1, f2, f3, f4);
      this->canDownPort->write(buildCanMessage(out));
  }

ORO_CREATE_COMPONENT_LIBRARY()
ORO_LIST_COMPONENT_TYPE(RobotControl)
