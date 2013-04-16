#include "HuboMotor.h"
#include <string>
#include <iostream>

HuboMotor::HuboMotor(){
    this->ticks_position = 0;
    this->desired_position = 0;
    this->omega = MAX_ANGULAR_VELOCITY;

    //NEW_DATA
    currGoal = 0;
	interStep = 0;
	interVel = 0;

	currVel = 0;
	currPos = 0;
	currCurrent = 0;
	currTemp = 0;

	enabled = false;
	homed = false;
	zeroed = false;
}

HuboMotor::HuboMotor(long mpos1, long mpos2, long kp, long kd, long ki,
                     long dz, long off, long hlim, long hld, long hv1,
                     long hv2, long hma, long sm, long ers, long as, long md,
                     long v_max, long a_max, long jam_lim, long jamd,
                     long pwm_lim, long i_err, long b_err){
    this->mpos1 = mpos1;
    this->mpos2 = mpos2;
    this->Kp = kp;
    this->Kd = kd;
    this->Ki = ki;
    this->dz = dz;
    this->off = off;
    this->hlim = hlim;
    this->hld = hld;
    this->hv1 = hv1;
    this->hv2 = hv2;
    this->hma = hma;
    this->sm = sm;
    this->ers = ers;
    this->as = as;
    this->md = md;
    this->v_max = v_max;
    this->a_max = a_max;
    this->jam_lim = jam_lim;
    this->jamd = jamd;
    this->pwm_lim = pwm_lim;
    this->i_err = i_err;
    this->b_err = b_err;
    this->ticks_position = 0;
    this->desired_position = 0;
    this->omega = MAX_ANGULAR_VELOCITY;

    currGoal = 0;
	interStep = 0;
	interVel = 0;

	currVel = 0;
	currPos = 0;
	currCurrent = 0;
	currTemp = 0;

	enabled = false;
	homed = false;
	zeroed = false;
}

HuboMotor::HuboMotor(const HuboMotor& rhs){
    this->mpos1 = rhs.mpos1;
    this->mpos2 = rhs.mpos2;
    this->Kp = rhs.Kp;
    this->Kd = rhs.Kd;
    this->Ki = rhs.Ki;
    this->dz = rhs.dz;
    this->off = rhs.off;
    this->hlim = rhs.hlim;
    this->hld = rhs.hld;
    this->hv1 = rhs.hv1;
    this->hv2 = rhs.hv2;
    this->hma = rhs.hma;
    this->sm = rhs.sm;
    this->ers = rhs.ers;
    this->as = rhs.as;
    this->md = rhs.md;
    this->v_max = rhs.v_max;
    this->a_max = rhs.a_max;
    this->jam_lim = rhs.jam_lim;
    this->jamd = rhs.jamd;
    this->pwm_lim = rhs.pwm_lim;
    this->i_err = rhs.i_err;
    this->b_err = rhs.b_err;
    this->ticks_position = rhs.ticks_position;
    this->desired_position = rhs.desired_position;
    this->omega = rhs.omega;

    //NEW_DATA
    this->name = rhs.name;
    this->currGoal = rhs.currGoal;
    this->interStep = rhs.interStep;
    this->interVel = rhs.interVel;

    this->currVel = rhs.currVel;
    this->currPos = rhs.currPos;
    this->currCurrent = rhs.currCurrent;
    this->currTemp = rhs.currTemp;

    this->enabled = rhs.enabled;
    this->homed = rhs.homed;
    this->zeroed = rhs.zeroed;
}

void HuboMotor::setUpperLimit(long limit){
    this->mpos2 = limit;
}

void HuboMotor::setLowerLimit(long limit){
    this->mpos1 = limit;
}

void HuboMotor::setPositionGain(long kp, long kd, long ki){
    this->Kp = kp;
    this->Kd = kd;
    this->Ki = ki;
}

void HuboMotor::setCurrentGain(long kpt, long kdt, long kf){
    this->Kpt = kpt;
    this->Kdt = kdt;
    this->Kf = kf;
}

void HuboMotor::setDeadZone(int dz){
    this->dz = dz;
}

void HuboMotor::setHomeset1(long off, long hlim, long hld){
    this->off = off;
    this->hlim = hlim;
    this->hld = hld;
}

void HuboMotor::setHomeset2(long hv1, long hv2, long hma, long sm){
    this->hv1 = hv1;
    this->hv2 = hv2;
    this->hma = hma;
    this->sm = sm;
}

void HuboMotor::setEncoderResolution(long ers, long as, long md){
    this->ers = ers;
    this->as = as;
    this->md = md;
}

void HuboMotor::setSpeedLimit(long vel, long acc){
    this->v_max = vel;
    this->a_max = acc;
}

void HuboMotor::setJamPowerLimit(long jam_lim, long jamd, long pwm_lim){
    this->jam_lim = jam_lim;
    this->jamd = jamd;
    this->pwm_lim = pwm_lim;
}

void HuboMotor::setErrorLimit(long i_err, long b_err){
    this->i_err = i_err;
    this->b_err = b_err;
}

void HuboMotor::setGearRatios(long drive, long driven, long harm, long enc){
	this->drive = drive;
	this->driven = driven;
	this->harm = harm;
	this->enc = enc;
}

void HuboMotor::setTicksPosition(long ticks){
    this->ticks_position = ticks;
}

void HuboMotor::setDesiredPosition(long ticks){
	this->desired_position = ticks;
}

void HuboMotor::setAngularVelocity(double omega){
	this->omega = omega;
}

long HuboMotor::getUpperLimit(){
    return this->mpos2;
}

long HuboMotor::getLowerLimit(){
    return this->mpos1;
}

long HuboMotor::getKp(){
    return this->Kp;
}

long HuboMotor::getKi(){
    return this->Ki;
}

long HuboMotor::getKd(){
    return this->Kd;
}

long HuboMotor::getKpt(){
    return this->Kpt;
}

long HuboMotor::getKdt(){
    return this->Kdt;
}

long HuboMotor::getKf(){
    return this->Kf;
}

long HuboMotor::getDz(){
    return this->dz;
}

long HuboMotor::getOff(){
    return this->off;
}

long HuboMotor::getHlim(){
    return this->hlim;
}

long HuboMotor::getHld(){
    return this->hld;
}

long HuboMotor::getHv1(){
    return this->hv1;
}

long HuboMotor::getHv2(){
    return this->hv2;
}

long HuboMotor::getHma(){
    return this->hma;
}

long HuboMotor::getSm(){
    return this->sm;
}

long HuboMotor::getErs(){
    return this->ers;
}

long HuboMotor::getAs(){
    return this->as;
}

long HuboMotor::getMd(){
    return this->md;
}

long HuboMotor::getVmax(){
    return this->v_max;
}

long HuboMotor::getAmax(){
    return this->a_max;
}

long HuboMotor::getJamLim(){
    return this->jam_lim;
}

long HuboMotor::getJamd(){
    return this->jamd;
}

long HuboMotor::getPwmLim(){
    return this->pwm_lim;
}

long HuboMotor::getIerr(){
    return i_err;
}

long HuboMotor::getBerr(){
    return b_err;
}

long HuboMotor::getTicksPosition(){
    return this->ticks_position;
}

long HuboMotor::getDesiredPosition(){
	return this->desired_position;
}

bool HuboMotor::requiresMotion(){
	return desired_position - ticks_position != 0;
}

double HuboMotor::ticksToRadians(long ticks){
	return (ticks * (double)(this->drive * 2 * M_PI))/(this->driven * this->harm * this->enc);
}

long HuboMotor::radiansToTicks(double rad){
	return (long)(rad * ((double)(this->driven * this->harm * this->enc))/(this->drive * 2 * M_PI));
}

long HuboMotor::interpolate(int MAX_STEP, int MIN_STEP){
	const float LEAP_PERCENTAGE = .5;
	const int FREQUENCY = 100; //Hertz
	if (MAX_STEP == 0)
		MAX_STEP = radiansToTicks(omega) / 100;

	int error = desired_position - ticks_position;
	int output = desired_position;

	if((abs(error) > MIN_STEP)){
		output = (int)(LEAP_PERCENTAGE * error);

		if(abs(output) > MAX_STEP)
			output = output < 0 ? -MAX_STEP : MAX_STEP;

	} else
		output = error;

	output += ticks_position;
	ticks_position = output;
	return output;
}

double HuboMotor::interpolate(){
	const float LEAP_PERCENTAGE = .5;
	const double MIN_STEP = .00000001;
	const double MAX_STEP = interVel/100; //Radians per second, divided by our operating frequency.

	double error = currGoal - interStep;
	if (error == 0) return currGoal;
	std::cout << error;
	double output = currGoal;

	if((abs(error) > MIN_STEP)){
		output = (LEAP_PERCENTAGE * error);

		if(abs(output) > MAX_STEP)
			output = output < 0 ? -MAX_STEP : MAX_STEP;

	} else
		output = error;

	output += interStep;
	interStep = output;
	return interStep;
}


void HuboMotor::setName(string name){
	this->name = name;
}

void HuboMotor::setGoalPosition(double rads){
	currGoal = rads;
}

void HuboMotor::setInterVelocity(double omega){
	interVel = omega;
}

void HuboMotor::update(double position, double velocity, double temperature, double current){
	currPos = position;
	currVel = velocity;
	currTemp = temperature;
	currCurrent = current;
}

void HuboMotor::setEnabled(bool enabled){
	this->enabled = enabled;
	interStep = currPos; //If we have recently changed from non-interpolation to interpolation, the step MUST be updated.
}

void HuboMotor::setHomed(bool homed){
	this->homed = homed;
}

void HuboMotor::setZeroed(bool zeroed){
	this->zeroed = zeroed;
}


string HuboMotor::getName(){
	return name;
}

double HuboMotor::getGoalPosition(){
	return currGoal;
}

double HuboMotor::getPosition(){
	return currPos;
}

double HuboMotor::getVelocity(){
	return currVel;
}

double HuboMotor::getTemperature(){
	return currTemp;
}

double HuboMotor::getCurrent(){
	return currCurrent;
}

bool HuboMotor::isEnabled(){
	return enabled;
}

bool HuboMotor::isHomed(){
	return homed;
}

bool HuboMotor::isZeroed(){
	return zeroed;
}

