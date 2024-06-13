#include <Camera.h>

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      speed(SPEED),
	  sensitivity(SENSITIVITY),
	  zoom(ZOOM)
{
    Position = pos;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}

// processes input received from any keyboard-like input system. 
// Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = speed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;

	if (direction == BACKWARD)
		Position -= Front * velocity;

	if (direction == LEFT)
		Position -= Right * velocity;

	if (direction == RIGHT)
		Position += Right * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	Yaw   += xoffset;
	Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;

		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessScroll(float yoffset)
{
	zoom -= (float)yoffset;

	if (zoom < 1.0f)
		zoom = 1.0f;
		
	if (zoom > 45.0f)
		zoom = 45.0f;
}