#include "Camera.h"

Camera::Camera()
{
	m_camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, (float)800 / 600, 1.0f, 1000.0f);
}


void Camera::updateCamera()
{
	//Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	//Load it into a XMVECTOR structure.
	upVector = XMLoadFloat3(&up);

	//Setup the position of the camera in the world.
	position.x = camPosX;
	position.y = camPosY;
	position.z = camPosZ;

	//Load it into a XMVECTOR structure.
	positionVector = XMLoadFloat3(&position);

	//Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	//Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3(&lookAt);

	//Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = camYaw * 0.0174532925f;
	yaw = camPitch * 0.0174532925f;
	roll = camRoll * 0.0174532925f;

	//Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	//Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	//Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}