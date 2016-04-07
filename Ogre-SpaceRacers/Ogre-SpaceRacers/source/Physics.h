#pragma once
#include "BaseApplication.h"

struct SphereCollider {
	bool trigger;
	Ogre::Sphere sphere;
	Ogre::Vector3 position;	//Should be constant
	SphereCollider(bool t, Ogre::Sphere s) {
		trigger = t;
		sphere = s;
		position = s.getCenter();
	}
	void setPositionToParentPosition(Ogre::Vector3 p) {
		sphere.setCenter(p + position);
	}
};
struct BoxCollider {
	bool trigger;
	Ogre::Box box;
	Ogre::Vector3 startPosition;
	BoxCollider(bool t, Ogre::Box b) {
		trigger = t;
		box = b;
		//startPosition = b.getCenter;
	}
};

struct RigidBody {
	float mass;
	float inverseMass;
	Ogre::Vector3 velocity;
	Ogre::Vector3 acceleration;
	Ogre::Vector3 force;
	Ogre::Real drag;
	RigidBody() {
		mass = 1;
		inverseMass = mass / 1;
		velocity = (0, 0, 0);
		acceleration = (0, 0, 0);
		force = (0, 0, 0);
		drag = 1;
	}

	void AddForce(Ogre::Vector3 f) {
		force += f;
	}

	void IntergrateForce(float dt) {
		if (inverseMass <= 0.0f) return;

		Ogre::Vector3 resultingAcc = acceleration;
		resultingAcc += force * inverseMass;

		velocity += resultingAcc * dt;
		velocity *= pow(drag, dt);
		//force = (0, 0, 0);
	}
};

class Physics
{
public:

};