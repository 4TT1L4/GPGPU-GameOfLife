#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>

#include "framebuffer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "quad.hpp"
#include <sstream>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

int windowWidth = 600;
int windowHeight = 600;

Quad* fullscreenQuad;
Texture2D* texture;
Shader* initShader;
Shader* lifeShader;
Shader* PutLifeShader;
Shader* visualize;

int example = 1;
bool paused = false;
int zoom = 1;
int left = 0;
int top = 0;
int sleepMs = 0;

long time = 0;
long frames;

Framebuffer* computeBuffer[2];
int inputBuffer = 0;
int npasses = 15;

void init(){

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)	{
		std::cerr << "Error: "<< glewGetErrorString(err) << std::endl;
	} 
	else 
	{
		if (GLEW_VERSION_3_3)
		{
			std::cout << "Driver supports OpenGL 3.3\nDetails:"<< std::endl;
			std::cout << "Using GLEW: " << glewGetString(GLEW_VERSION)<< std::endl;
			std::cout << "Vendor: " << glGetString (GL_VENDOR)<< std::endl;
			std::cout << "Renderer: " << glGetString (GL_RENDERER)<< std::endl;
			std::cout << "Version: " << glGetString (GL_VERSION)<< std::endl;
			std::cout << "GLSL: " << glGetString (GL_SHADING_LANGUAGE_VERSION)<< std::endl;
		}
	}

	fullscreenQuad = new Quad();
	
	computeBuffer[0] = new Framebuffer(600, 600, 1);
	computeBuffer[1] = new Framebuffer(600, 600, 1);

	computeBuffer[0]->clear();
	computeBuffer[1]->clear();	

    initShader = new Shader("passthrough.vert", "init.frag");
	lifeShader = new Shader("passthrough.vert", "life.frag");
	visualize = new Shader("passthrough.vert", "visualize.frag"); 
	PutLifeShader = new Shader("passthrough.vert", "PutLifeShader.frag"); 
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void Reset(int type = 0)
{	

		  computeBuffer[(inputBuffer) % 2]->setRenderTarget();
	      initShader->enable();
	      initShader->bindUniformTexture("inputMap", computeBuffer[(inputBuffer ) % 2]->getColorBuffer(0), 0);
		  initShader->bindUniformInt("type", type);
		  fullscreenQuad->render(initShader);
	      initShader->disable();
		  computeBuffer[(inputBuffer) % 2]->disableRenderTarget();
}

int i = 0;
void Render()
{	
	 if(i == 0)
	 {
		 inputBuffer = 0;
		 Reset();
	 }

	 frames++;
	 long currentTime = glutGet(GLUT_ELAPSED_TIME);
	 if(currentTime-time>1000)
	 {
		 std::ostringstream oss;
		 char str[100];
		 sprintf(str, "GP GPU - Homework - Attila Bujaki - Game of Life (FPS: %f)", 1000*frames/((float)currentTime-time));
        
		 glutSetWindowTitle(str);
		 frames = 0;
		 time = currentTime;
	 }
	 
     i++;

	 if(!paused)
     {
		 computeBuffer[(inputBuffer + 1) % 2]->setRenderTarget();
	     lifeShader->enable();
	     lifeShader->bindUniformTexture("inputMap", computeBuffer[inputBuffer]->getColorBuffer(0), 0);
	     fullscreenQuad->render(lifeShader);
	     lifeShader->disable();
	     computeBuffer[(inputBuffer + 1) % 2]->disableRenderTarget();
	     inputBuffer = (inputBuffer + 1) % 2;
		 Sleep(sleepMs);
	 }
	 
	 visualize->enable();
	 visualize->bindUniformTexture("inputMap", computeBuffer[inputBuffer]->getColorBuffer(0), 0);
	 visualize->bindUniformInt("zoom", zoom);
	 visualize->bindUniformInt("top", top/zoom);
	 visualize->bindUniformInt("left", left/zoom);
	 fullscreenQuad->render(visualize);
	 visualize->disable();
}

int lastRender = -1;
void display(){
	glClearColor(0.17f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutReshapeWindow(600, 600);
    Render();

	glutSwapBuffers();

	glutPostRedisplay();
}

void PrintHelp()
{
	std::cout << "\nClick anywhere to add a living cell.\n\n Keys:\n z - zoom in\n t - zoom out\n w - move up\n s - move - down\n a - move left\n d - move right\n u - speed up\n j - speed down\n h - print this help\n space - pause/resume\n\n\t HAVE FUN! :-) ";
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
	case 27:
		exit(0);
		break;
	case 'h':
		  PrintHelp();
		break;
	case 'u':
		if (sleepMs>5)
		{
		  sleepMs = sleepMs - 5;
		}
		else 
		{
			sleepMs = 0;
		}
		std::cout << "Wait each loop:" << sleepMs << "ms.\n";
	break;
	case 'j':
		if (sleepMs > 0)
		{
			sleepMs = sleepMs + 5;
		}
		else
		{
			sleepMs = 1;
		}
		std::cout << "Wait each loop:" << sleepMs << "ms.\n";
    break;
	case 'r':
		 Reset();
		break;
	case 'c':
		 Reset(1);
		break;
	case 'w':
		  top += 3 * zoom;
		  std::cout << "Top:" << top << "\n";
		break;
	case 's':
		   top -= 3 * zoom;
		  std::cout << "Top:" << top << "\n";
		break;
	case 'a':
		 left -= 3 * zoom;
		  std::cout << "Left:" << left << "\n";
		break;
	case 'd':
		 left += 3 * zoom;
		  std::cout << "Left:" << left << "\n";
		break;
	case 'z':
		  zoom++;
		  top += 600/zoom;
		  left += left/zoom;
		  std::cout << "Zoom:" << zoom << "\n";
		  std::cout << "Top:" << top << "\n";
		  std::cout << "Left:" << left << "\n";
		break;
	case 't':
		if(zoom>1)
		{
		  top -= top/zoom;
		  left -= left/zoom;
		  zoom--;
		  std::cout << "Zoom:" << zoom << "\n";
		  std::cout << "Top:" << top << "\n";
		  std::cout << "Left:" << left << "\n";
		}
		break;

	case ' ':
		paused = !paused;

		if(paused)
		{
		  std::cout << "Paused " << std::endl;		  
		}
		else
		{
			std::cout << "Started " << std::endl;		  
		}
		break;
	default:
		std::cout << "Unbinded key: " << (unsigned int)key << std::endl;

		PrintHelp();
	}

}

void PutLife(int x, int y, int button)
{		
	     int XCoord = left/zoom + x/zoom;
		 int YCoord =  (top/zoom + (590-y)/zoom );
		 std::cout << "Life put x: " << XCoord << " y:" << YCoord << "button:" << button << "\n"; 
		 computeBuffer[(inputBuffer + 1) % 2]->setRenderTarget();
	     PutLifeShader->enable();
	     PutLifeShader->bindUniformTexture("inputMap", computeBuffer[inputBuffer]->getColorBuffer(0), 0);
		 PutLifeShader->bindUniformInt2("Coord", XCoord, YCoord);
		 PutLifeShader->bindUniformInt("button", button);
	     fullscreenQuad->render(PutLifeShader);
	     PutLifeShader->disable();
	     computeBuffer[(inputBuffer + 1) % 2]->disableRenderTarget();
	     inputBuffer = (inputBuffer + 1) % 2;
}

void mouse(int button, int state, int x, int y)
{
   PutLife(x,y,button);
}

void reshape(int width, int height){
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitContextVersion (3, 3);
	glutInitContextFlags (GLUT_CORE_PROFILE | GLUT_DEBUG);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("GP GPU - Homework - Attila Bujaki - Game of Life");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	PrintHelp();

	glutMainLoop();

	return(0);
}
