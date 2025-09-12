#include "ForceField.h"

#include "FilthyUtil.h"

void ForceField::OnCollision(PhysicsObject* other)
{
	other->ApplyAcceleration(forceDirection * FilthyUtil::GetFrameTime());
}

ForceField::ForceField(Vector3 pos, Vector3 force, float w, float h, float d)
{
	Position = pos;
	forceDirection = force;
	Width = w;
	Height = h;
	Depth = d;


	isSolid = false;
}

void ForceField::Draw3D()
{
	if (drawDebug)
	{
		DrawCubeWires(Position, Width, Height, Depth, RED);
		DrawCylinderWiresEx(Position, Position + Vector3Normalize(forceDirection) * 5, 0.5, 0, 6, GREEN);
	}
	else
	{
		DrawCubeWires(Position, Width, Height, Depth, GREEN);
	}
}
