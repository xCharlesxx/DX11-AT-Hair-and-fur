#include "Camera.h"

Camera::Camera(float _fieldOfView, float _aspectRatio, float _nearPlaneDistance, float _farPlaneDistance)
{
	m_fieldOfView = _fieldOfView;
	m_aspectRatio = _aspectRatio;
	m_nearPlaneDistance = _nearPlaneDistance;
	m_farPlaneDistance = _farPlaneDistance;

	m_lookAt = XMFLOAT3(0, 0, 1);
	m_up = XMFLOAT3(0, 1, 0);
}


void Camera::updateCamera()
{
	//Load it into a XMVECTOR structure.
	upVector = XMLoadFloat3(&m_up);

	//Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3(&m_lookAt);

	//Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, m_rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, m_rotationMatrix);

	//Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(getPos(), lookAtVector);

	//Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(getPos(), lookAtVector, upVector);

	return;
}

void Camera::draw(DrawData * _DD)
{
}
