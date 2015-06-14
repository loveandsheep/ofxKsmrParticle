//
//  ofxKsmrParticleBasic.h
//  ofxKsmrParticleSample
//
//  Created by Ovis aries on 2015/05/25.
//
//

#ifndef __ofxKsmrParticleSample__ofxKsmrParticleBasic__
#define __ofxKsmrParticleSample__ofxKsmrParticleBasic__

#include "ofMain.h"

class ofxKsmrParticleBasic{
public:
	
	ofxKsmrParticleBasic(ofVec3f p = ofVec3f(0,0,0),
						 ofVec3f defPos = ofVec3f(0,0,0))
	{
		posDef.set(defPos);
		pos.set(p);
		posTmp.set(p);
		acc.set(0,0,0);
		vec.set(0,0,0);
		
		mass = 1.0 + ofRandomuf() * 10.0;
		approachDef = 0.0;
		friction = 0.01;
		age = 0;
		life = 60;
		isLive = false;
		seed = ofRandomuf();
	}
	
	~ofxKsmrParticleBasic()
	{
		
	}
	
	void setPhysics(float mas, float frc);
	void update();
	void atract(ofVec3f pt, float radius, float amount);
	void repel(ofVec3f pt, float radius, float amount);
	void addForce(ofVec3f f);

	float getApproach(){return approachDef;}
	const ofVec3f & getDefaultPos(){return posDef;}
	const ofVec3f & getPosition(){return pos;}
	const ofVec3f & getVector(){return vec;}
	
	void setApproach(float pct){approachDef = pct;}
	void setDefaultPos(ofVec3f v){posDef = v;}
	void setPosition(ofVec3f v){pos = v;posTmp = v;}
	void setVec(ofVec3f v){vec = v;}
	void setAcc(ofVec3f a){acc = a;}
	float getSeed(){return seed;}
	
	bool	isLive;
	int		age;
	int		life;

protected:
	
	ofVec3f posDef;
	ofVec3f posTmp;
	ofVec3f pos;
	ofVec3f acc;
	ofVec3f vec;
	
	float seed;
	float approachDef;
	float mass;
	float friction;
};

#endif /* defined(__ofxKsmrParticleSample__ofxKsmrParticleBasic__) */
