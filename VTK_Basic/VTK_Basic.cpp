// VTK_Basic.cpp : Defines the entry point for the application.
//

#include "VTK_Basic.h"
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCylinderSource.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRenderingExternalModule.h>
#include <vtkExternalOpenGLCamera.h>
#include <vtkMatrix4x4.h>
#include <vtkLight.h>
#include <vtkLightCollection.h>

#include <array>

using namespace std;

float convertScale(float originalValue, float originalMin, float originalMax, float newMin, float newMax) {
	double originalRange = originalMax - originalMin;
	double newRange = newMax - newMin;
	return (((originalValue - originalMin) * newRange) / originalRange) + newMin;
}

int main(int argc, char* argv[])
{
	vtkNew<vtkNamedColors> colors;

	std::array<unsigned char, 4> bkg{ {26, 51, 102, 255} };
	colors->SetColor("BkgColor", bkg.data());

	vtkNew<vtkCylinderSource> cylinder;
	cylinder->SetResolution(8);

	vtkNew<vtkPolyDataMapper> cylinderMapper;
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

	vtkNew<vtkActor> cylinderActor;
	cylinderActor->SetMapper(cylinderMapper);
	cylinderActor->GetProperty()->SetColor(
		colors->GetColor4d("Tomato").GetData());
	cylinderActor->SetPosition(0.0, 0.0, 0.0);

	vtkNew<vtkRenderer> renderer;
	renderer->AddActor(cylinderActor);
	renderer->SetBackground(colors->GetColor3d("BkgColor").GetData());

	float sceneWidth = std::stof(argv[1]), sceneHeight = std::stof(argv[2]);
	float instanceWidth = std::stof(argv[3]), instanceHeight = std::stof(argv[4]);
	float instancePositionX = std::stof(argv[5]), instancePositionY = std::stof(argv[6]);
	float physicalHeight = std::stof(argv[7]), physicalDistance = std::stof(argv[8]);

	vtkNew<vtkRenderWindow> renderWindow;
	renderWindow->SetSize(instanceWidth,instanceHeight);
	renderWindow->SetPosition(instancePositionX, instancePositionY);
	renderWindow->BordersOff();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetWindowName("Cylinder");

	vtkNew<vtkExternalOpenGLCamera> camera;
	renderer->SetActiveCamera(camera);

	float aspectRatio = (float)sceneWidth / (float)sceneHeight;
	float fov = 2 * atan(physicalHeight / (2 * -physicalDistance));

	float near = std::max(physicalDistance - 1.0f, 0.1f);
	float far = 1000.0f;

	float halfHeight = tan(fov / 2) * near;
	float halfWidth = halfHeight * aspectRatio;

	float left = convertScale(instancePositionX, 0, sceneWidth, -halfWidth, halfWidth);
	float right = convertScale(instancePositionX + instanceWidth, 0, sceneWidth, -halfWidth, halfWidth);
	float top = convertScale(sceneHeight - instancePositionY, 0, sceneHeight, -halfHeight, halfHeight);
	float bottom = convertScale(sceneHeight - (instancePositionY + instanceHeight), 0, sceneHeight, -halfHeight, halfHeight);

	vtkNew<vtkMatrix4x4> projectionMatrix;
	projectionMatrix->Zero();
	projectionMatrix->SetElement(0, 0, (2 * near) / (right - left));
	projectionMatrix->SetElement(0, 2, (right + left) / (right - left));
	projectionMatrix->SetElement(1, 1, (2 * near) / (top - bottom));
	projectionMatrix->SetElement(1, 2, (top + bottom) / (top - bottom));
	projectionMatrix->SetElement(2, 2, -(far + near) / (far - near));
	projectionMatrix->SetElement(2, 3, -2 * far * near / (far - near));
	projectionMatrix->SetElement(3, 2, -1.0);

	camera->SetUseExplicitProjectionTransformMatrix(true);
	camera->SetExplicitProjectionTransformMatrix(projectionMatrix);
	camera->SetPosition(0.0, 0.0, 5.0);

	vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;
}
