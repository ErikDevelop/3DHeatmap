#include "TriangleScene.h"

Scene* TriangleScene::getInstance() {
	if (!instanceFlag) {
		scene = new TriangleScene();
		instanceFlag = true;
		return scene;
	}

	return scene;
};

void TriangleScene::start() {
	/*
	 * Normally, this code Would be put away inside the gameComponent's own update functions.
	 * This function has yet to be fixed.
	 */

	//Triangle A Rotates in the center
	triangleA = gameComponent(&vp);								// passing the VP, so the component can complete it's personal MVP matrix.
	components.push_back(&triangleA);							// Adds the Triangle to the components list, so the scene can call all it's components update functions.
	triangleAPostionVector = glm::vec3(-5.5f, 4.0f, -5.0f);
	triangleA.setPosition(&triangleAPostionVector);				// From here on: see gamecomponent.cpp.
	triangleARotationAngle = 0.0f;

	triangleARotationVector = glm::vec3(0.0f, 0.0f, 1.0f);
	triangleA.setOrientation(&glm::angleAxis(					// glm::angleAxis returns a quaternion.
		glm::radians(triangleARotationAngle),
		triangleARotationVector)
	);
	
	//Triangle B Rotates around Triangle A and faces it.
	triangleB = gameComponent(&vp);
	components.push_back(&triangleB);

	triangleBDirectionVector = glm::vec3(						// Creates a directional vector based on triangleA's rotation.
		glm::cos(glm::radians(triangleARotationAngle + 90.0f)),
		glm::sin(glm::radians(triangleARotationAngle + 90.0f)),
		0.0f
	);

	/*
	 * Linear Algebra, triangleB's position is determined by adding it's directional vector, multiplied by it's magnitude,
	 * before adding it to triangleA's position to find it's relative position.
	 */
	triangleBDistance = 2.1f;
	triangleBPositionVector = triangleAPostionVector + (triangleBDirectionVector * triangleBDistance);
	triangleB.setPosition(&triangleBPositionVector);

	//Triangle C bounces off it's angles, happily dancing across the screen.
	triangleC = gameComponent(&vp);
	components.push_back(&triangleC);
	triangleCPositionVector = glm::vec3(0.0f, -2.0f, -5.0f);
	triangleC.setPosition(&triangleCPositionVector);

	triangleCDirectionVector = glm::vec3(-1.0f, 0.0f, 0.0f);
	triangleCSineVector = glm::vec3(0.0f, 0.03f, 0.0f);
	triangleCSpeed = 0.05f;
	Scene::start();
};

/*
 * The update function gets called during the window loop
 */
void TriangleScene::update() {
	// First execute checks and reset variables so we can power through the update logic afterwards.
	if (triangleARotationAngle >= 360.0f) triangleARotationAngle = 0.0f;
	if (triangleC.getPostition().x <= -12.0f) triangleC.setPosition(&(triangleCPositionVector + glm::vec3(12.0f, 0.0f, 0.0f)));

	// update trinagleA's rotation and update it's Orientation through a quaternion.
	triangleARotationAngle++;
	triangleA.setOrientation(&glm::angleAxis(glm::radians(triangleARotationAngle), triangleARotationVector));

	// regenerate triangleB's directional vector based on triangleA's new rotation.
	triangleBDirectionVector = glm::vec3(
		glm::cos(glm::radians(triangleARotationAngle + 90.0f)),
		glm::sin(glm::radians(triangleARotationAngle + 90.0f)),
		0.0f);

	// regenerate triangleB's position.
	triangleBPositionVector = triangleAPostionVector + (triangleBDirectionVector * triangleBDistance);
	triangleB.setPosition(&triangleBPositionVector);

	//give it an orientation that's directly the opposite of triangleA's, so they'll always be touching tips.
	triangleB.setOrientation(&glm::angleAxis(glm::radians(triangleARotationAngle - 180.0f), triangleARotationVector));

	triangleC.setOrientation(&glm::angleAxis(glm::radians(triangleARotationAngle), triangleARotationVector));

	/*
	 * triangleC's position is determined by adding it's directional vector multiplied by it's magnitude to it's position,
	 * and then adding it's sine directional vector to the sine of it's own X position. making y = (0, 0.3, 0) * sin(x)
	 */
	triangleC.setPosition(&(
		triangleC.getPostition() + (triangleCDirectionVector * triangleCSpeed) +
		(triangleCSineVector * glm::sin(triangleC.getPostition().x))
	));
	Scene::update();
};

void TriangleScene::destroy() {
	Scene::destroy();
};