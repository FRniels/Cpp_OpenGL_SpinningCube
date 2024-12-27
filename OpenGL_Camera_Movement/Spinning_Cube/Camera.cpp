#include "Camera.h"

Camera::Camera(float FOV, float near_field, float far_field, float window_aspect_ratio, RenderContext& render_context) 
	: FOV(FOV), near_field(near_field), far_field(far_field)
{
	UpdateProjectionMatrix(FOV, near_field, far_field, window_aspect_ratio);
	render_context.matrix_view       = &view_matrix;
	render_context.matrix_projection = &projection_mat;
}

//void Camera::SetPosition(vec3f position)
//{
//	memcpy(this->position, position, sizeof(vec3f));
//	view_matrix.SetWorldTranslation(position);
//};

void Camera::UpdateProjectionMatrix(float FOV, float near_field, float far_field, float window_aspect_ratio)
{
	projection_mat.SetProjectionMatrix(FOV, near_field, far_field, window_aspect_ratio);
}

void Camera::Callback_Key(int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT) 
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			std::cout << "Up key pressed or held down" << std::endl;
			position[1] += 0.03f;
			break;
		case GLFW_KEY_DOWN:
			std::cout << "Down key pressed or held down" << std::endl;
			position[1] -= 0.03f;
			break;
		case GLFW_KEY_LEFT:
			std::cout << "Left key pressed or held down" << std::endl;
			position[0] -= 0.03f;
			break;
		case GLFW_KEY_RIGHT:
			std::cout << "Right key pressed or held down" << std::endl;
			position[0] += 0.03f;
			break;
		case GLFW_KEY_I: // ZOOM IN
			std::cout << "I key pressed or held down" << std::endl;
			position[2] += 0.03f;
			break;
		case GLFW_KEY_O: // ZOOM OUT
			std::cout << "O key pressed or held down" << std::endl;
			position[2] -= 0.03f;
			break;
		default:
			break;
		}

		view_matrix.SetWorldTranslation(position);
	}
}
