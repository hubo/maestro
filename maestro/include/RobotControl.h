#ifndef ROBOTCONTROL_H
#define ROBOTCONTROL_H

#define CONFIG_PATH "/opt/ros/fuerte/stacks/maestro/test/config.txt"
#define HARDWARE true
#define SIMULATION false

#include <rtt/TaskContext.hpp>
#include <rtt/Port.hpp>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <rtt/Component.hpp>
#include <rtt/scripting/Scripting.hpp>
#include <rtt/scripting/ProgramInterface.hpp>
#include <rtt/scripting/ScriptingService.hpp>
#include <hubomsg/typekit/HuboCmd.h>
#include <hubomsg/typekit/CanMessage.h>
#include <hubomsg/typekit/HuboState.h>
#include <hubomsg/typekit/HuboJointState.h>
#include <hubomsg/typekit/HuboCommand.h>
#include <hubomsg/typekit/HuboJointCommand.h>
#include <hubomsg/typekit/AchCommand.h>
#include <hubomsg/typekit/HuboIMU.h>
#include <hubomsg/typekit/HuboFT.h>
#include <vector>
#include <queue>
#include <map>
#include "huboCan.h"
#include "CommHandler.h"
#include "HuboState.h"
#include "HuboMotor.h"
#include "MotorBoard.h"
#include "IMUBoard.h"
#include "FTSensorBoard.h"
#include "Names.h"
#include <fstream>

using std::queue;
using std::vector;
using namespace RTT;

class RobotControl : public RTT::TaskContext{

public:
    RobotControl(const std::string&);
    ~RobotControl();

    void updateHook(); 
    hubomsg::CanMessage buildCanMessage(canMsg* msg);
    void buildHuboCommandMessage(hubomsg::HuboJointCommand& state, hubomsg::HuboCommand& message);
    void initRobot(string path);

    //JOINT MOVEMENT API
    void set(string name, string property, double value);
    void setProperties(string names, string properties, string values);

    // Control Commands
    void debugControl(int board, int operation);
	void setDelay(int us);
	void runGesture(string name);
	void command(string name, string target);

    // Feedback Commands
    bool requiresMotion(string name);
    double get(string name, string property);
    void updateState();

    // Parameter Commands
    void setMode(string mode, bool value);

    // Configuration Commands
    bool getRunType(string path);
    bool setAlias(string name, string alias);
    vector<string> getGestureScripts(string path);
    vector<string> splitFields(string input);
    string getDefaultInitPath(string path);


private:


    //SUBSCRIBE
    InputPort<hubomsg::CanMessage>* canUpPort;
    InputPort<hubomsg::HuboCmd>* orOutPort;
    InputPort<hubomsg::HuboState>* huboUpPort;
    CommHandler* commHandler;

    //PUBLISH
    OutputPort<hubomsg::CanMessage>* canDownPort;
    OutputPort<hubomsg::HuboCmd>* orInPort;
    OutputPort<hubomsg::HuboCommand>* huboDownPort;
    OutputPort<hubomsg::AchCommand>* achDownPort;

    HuboState* state;

    queue<hubomsg::CanMessage>* inputQueue;
    queue<hubomsg::HuboState>*	huboInputQueue;
    queue<hubomsg::HuboCommand>* huboOutputQueue;
    queue<hubomsg::AchCommand>* achOutputQueue;

    map< string, vector<float> > gestures;
    map<string, COMMAND> commands;
    ofstream tempOutput;

    int written;
    bool printNow, enableControl;
    int delay;
    bool interpolation, override;
    bool RUN_TYPE;
};

#endif
