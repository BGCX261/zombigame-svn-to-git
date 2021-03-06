//----------------------------------------------------------------------------------
// CPhysicSphericalJoint class
// Author: Enric Vergara
//
// Description:
// Esta clase representa joint de tipo esferico
//----------------------------------------------------------------------------------
#pragma once
#ifndef INC_PHYSIC_SPHERICAL_JOINT_H_
#define INC_PHYSIC_SPHERICAL_JOINT_H_

#include "Math/MathUtils.h"
#include "Math/Vector3.h"

//---Forward Declarations---
class NxJoint;
class NxSphericalJointDesc;
class CPhysicActor;
//--------------------------

class CPhysicSphericalJoint
{
public:
	CPhysicSphericalJoint();
	~CPhysicSphericalJoint();

	void									CreateJoint			(NxJoint* joint);
	void									SetInfo					(const Vect3f& anchor, CPhysicActor* actorA,  CPhysicActor* actorB =0);


	//---Get PhsX Info---
	NxJoint*							GetPhXJoint			() {return m_pJoint;}
	NxSphericalJointDesc*	GetPhXDescJoint	() {return m_pSphericalDesc;}

private:
	NxJoint*							m_pJoint;
	NxSphericalJointDesc* m_pSphericalDesc;

};

#endif //INC_PHYSIC_SPHERICAL_JOINT_H_