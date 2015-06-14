//
//  ofxKsmrParticleBasic.cpp
//  ofxKsmrParticleSample
//
//  Created by Ovis aries on 2015/05/25.
//
//

#include "ofxKsmrParticleBasic.h"

void ofxKsmrParticleBasic::update()
{
	age++;
	acc -= vec * friction;
	vec += acc;
	posTmp += vec;
	pos.set(posTmp.interpolate(posDef, powf(approachDef,4.0)));
	acc.set(0, 0);
	
	if (age > life) isLive = false;
}

void ofxKsmrParticleBasic::setPhysics(float mas, float frc)
{
	mass = mas;
	friction = frc;
}

void ofxKsmrParticleBasic::addForce(ofVec3f f){
	acc += f / mass;
}

void ofxKsmrParticleBasic::repel(ofVec3f pt, float radius, float amount)
{
	atract(pt, radius, amount * -1.0);
}

void ofxKsmrParticleBasic::atract(ofVec3f pt, float radius, float amount)
{
	ofVec3f posOfForce;
	posOfForce = pt;
	ofVec3f diff = posTmp - posOfForce;
	float length = diff.length();
	bool bAmCloseEnough = true;
	
	if (radius > 0)
		if (length > radius) bAmCloseEnough = false;
	
	if (bAmCloseEnough)
	{
		float pct = 1 - (length / radius);
		diff.normalize();
		acc = acc - diff * amount * pct / mass;
	}
}