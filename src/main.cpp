#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include "GL/glew.h"

#include "GLFW/glfw3.h"
GLFWwindow* window;

#include "glm/glm.hpp"

using namespace std;


void display(float& counter){
    // OpenGL space is from -1 to +1


    // Triangle 1
    // Reset the rotation metrics to Identity so as to reset the rotation of last draw call present in the OpenGL state machine
    glLoadIdentity();
    // NOTE: Translate first then rotate, otherwise it will move in an orbital path around the axis.
    // -z brings triangle inside the frustum so that it becomes visible
    glTranslatef(counter/200.0, -0.8, -2.0);
    glRotatef(counter, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
        // Set color for all upcoming draw calls
        glColor3f(0.0, 1.0, 0.0);
        //            x    y     z
        glVertex3f(-0.5, -0.5, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f( 0.5, -0.5, 0.0);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f( 0.0,  0.5, 0.0);
    glEnd();
    counter+=1.0;

    if(counter > 220.0){
        counter = -220;
    }



    // Triangle 2
    glLoadIdentity();
    glTranslatef(-0.5, -0.8, -2.0);
    glRotatef(75, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f( 0.5, -0.5, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f( 0.0,  0.5, 0.0);
    glEnd();


    /*
    // Triangle 3
    glLoadIdentity();
    //glRotatef(75, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -2.0);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-0.9, -0.1, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f( 0.1, -0.1, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f( -0.5,  0.9, 0.0);
    glEnd();
     */

}

void setWindowSizeCallbackHandler(GLFWwindow* window, int width, int height){
	cout << "Window width:" << width << " height:" << height << endl;

	// Draw inside window defined by below parameters (origin at bottom-left)
    // Tell OpenGL how to convert from coordinates to pixel values
	//glViewport(0, 0, width/2, height/2);
    glViewport(0, 0, width, height);

	// Perspective projection of scene
	glMatrixMode(GL_PROJECTION);

	// Reset projection matrix / camera view
	glLoadIdentity();

	// Define Frustum i.e. 3D visible volume as seen from camera
    // Our world is for 1 to 10 i.e. 9 units of view; {{We are no longer in -1 to 1 space}}
    // Note: Camera watches along -z axis
    gluPerspective( 60.0f,                           //camera angle; view angle of the world as seen though camera
                    (float)width/(float)height,      //The width to height ratio
                    1.0f,                            //The near z clipping coordinate; These are OpenGL units; They do not correspond to any real world metric unless we define it
                    10.0f );                         //The far z clipping coordinate

    // Reset mode
    glMatrixMode(GL_MODELVIEW);
}

int main(){
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


	glfwSetWindowSizeCallback(window, setWindowSizeCallbackHandler);

	// Init OpenGL
    // Set color in OpenGL state machine to be used for drawing background when glClear() is called
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

    // Enable depth testing in OpenGL. Test if something is behind something else
    glEnable(GL_DEPTH_TEST);
    // Anything which has <= Z-axis value will be in front i.e something closer to me will be visible
    glDepthFunc(GL_LEQUAL);


    float counter=1.0;

	do{

		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		// Update background with the color set by glClearColor()
        // Forget every depth information from the previous frame and start from scratch
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(counter);



		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;

}
