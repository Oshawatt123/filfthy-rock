#pragma once
#include "Box.h"

class ForceField : public Box
{
private:
	Vector3 forceDirection{ 1, 0, 0 };

protected:
	virtual void OnCollision(PhysicsObject* other) override;

public:
	ForceField(Vector3 pos, Vector3 force, float w, float h, float d);

	virtual void Draw3D() override;
};