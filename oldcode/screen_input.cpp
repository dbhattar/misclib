# include <iostream>
# include <string>
# include <GL\glut.h>
# include <GL\glu.h>

# define WINDOW_W 900
# define WINDOW_H 900

# define FROM_X	0
# define FROM_Y	1
# define TO_X	2
# define TO_Y	3

# define MIN_X 0
# define MIN_Y 0
# define MAX_X 237
# define MAX_Y 224

# define V_W 160
# define V_H 20

using namespace std;

typedef struct coord{
	int x, y;
} coord;

typedef struct {
	bool isSelected;
	coord offset;
	coord start, size, curRasterPosition;
	string content, label;
	GLfloat curColor[3];
} VIEWPORT;

const GLfloat defaultColor[3] = {0.0, 0.0, 0.0};

coord curRasterPos;
VIEWPORT v[4];

int fromX = 0, fromY = 0, toX = 0, toY = 0;
int activeViewport = -1;

bool inputWait = false;

int Clamp(int mx, int mn, int data);

void DrawAllViewports(void);
void InitializeViewports(void);
int GetViewport(int x, int y);
void PrintViewportContents(void);

void GLUTInit(int argc, char **argv);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void reshape(int w, int h);

int main(int argc, char **argv) {
	curRasterPos.x = 0;
	curRasterPos.y = 0;
	InitializeViewports();
	GLUTInit(argc, argv);
	glutMainLoop();
}

void GLUTInit(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize (WINDOW_W, WINDOW_H);
	glutInitWindowPosition (0, 0);
	glutCreateWindow (argv[0]);
	glClearColor(0.7, 0.7, 0.7, 0.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
}
//vector<unsigned char> enteredText;

//Plots the data
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		DrawAllViewports();
		PrintViewportContents();
	glPopMatrix();
	glutSwapBuffers();
}

//Handles keyboard events
void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 27: exit(0);
		case 13:
			fromX = Clamp(MIN_X, MAX_X, atoi(v[FROM_X].content.c_str()));
			fromY = Clamp(MIN_Y, MAX_Y, atoi(v[FROM_Y].content.c_str()));
			toX = Clamp(MIN_X, MAX_X, atoi(v[TO_X].content.c_str()));
			toY = Clamp(MIN_Y, MAX_Y, atoi(v[TO_Y].content.c_str()));
			cout << "From X: " << fromX << " From Y: " << fromY << endl;
			cout << "To X: " << toX << " To Y: " << toY << endl;
			break;
		default:
			if(inputWait) {
				if((key >= '0' && key <= '9')) {
					if(v[activeViewport].content.length() <= 3) {
							v[activeViewport].content.push_back(key);
					}
				}
				else if(key == 8 && !v[activeViewport].content.empty())
					v[activeViewport].content.erase(v[activeViewport].content.length()-1);
				glutPostRedisplay();
			}
			break;
	}
}

void mouse(int button, int state, int x, int y) {
	switch(button) {
		case GLUT_LEFT_BUTTON:
			switch(state) {
				case GLUT_UP:
					x = x;
					y = WINDOW_H-y;
					activeViewport = GetViewport(x, y);
					for(int i = FROM_X; i <= TO_Y; ++i)
						memcpy(v[i].curColor, defaultColor, sizeof(GLfloat) * 3);
					if(activeViewport == -1) inputWait = false;
					else {
						inputWait = true;
						v[activeViewport].curColor[0] = 1.0;
						v[activeViewport].curColor[1] = 0.0;
						v[activeViewport].curColor[2] = 0.0;
					}
					glutPostRedisplay();
					break;
			}
			break;
	}
//	cout << "Active Viewport: " << activeViewport << endl;
}

//Handles reshape events
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0, (GLfloat) w, 0.0, (GLfloat) h);
   glMatrixMode(GL_MODELVIEW);
}

void InitializeViewports(void) {
	v[FROM_X].isSelected = true;
	v[FROM_X].content.clear();
	v[FROM_X].label = "From X: ";
	memcpy(v[FROM_X].curColor, defaultColor, sizeof(GLfloat) * 3);
	v[FROM_X].start.x = 32; v[FROM_X].start.y = 10;
	v[FROM_X].size.x = V_W; v[FROM_X].size.y = V_H;
	unsigned int i, j;
	coord offset;
	v[FROM_Y].label = "From Y: ";
	v[TO_X].label = "To X: ";
	v[TO_Y].label = "To Y: ";

	for(i = FROM_X+1; i <= TO_Y; ++i) {
		v[i].content.clear();
		v[i].start.x = v[FROM_X].start.x + i * (V_W + 65); 
		v[i].start.y = 10;
		v[i].size.x = V_W; v[i].size.y = V_H;
		memcpy(v[i].curColor, defaultColor, sizeof(GLfloat) * 3);
		v[i].isSelected = false;
	}

	for(i = FROM_X; i <= TO_Y; ++i) {
		v[i].content.push_back('0');
		offset.x = 0;
		for(j = 0; j < v[i].label.length(); ++j)
			offset.x += glutBitmapWidth(GLUT_BITMAP_9_BY_15, v[i].label.at(j));
		offset.y = 5;
		v[i].offset.x = offset.x; v[i].offset.y = offset.y;
	}
}

void DrawAllViewports(void) {
	GLfloat curPos[4];
	glPushMatrix();
		glLoadIdentity();
		glBegin(GL_LINES);
			glColor3f(0.0, 1.0, 0.0);
			glVertex2i(0, 40);
			glVertex2i(WINDOW_W, 40);
		glEnd();
		for(int i = FROM_X; i <= TO_Y; ++i) {
			glColor3f(v[i].curColor[0], v[i].curColor[1], v[i].curColor[2]);
			glRasterPos2i(v[i].start.x + 2, v[i].start.y + 2);
			for(unsigned int j = 0; j < v[i].label.length(); ++j)
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, v[i].label.at(j));
			glBegin(GL_LINE_LOOP);
				glVertex2i(v[i].start.x+v[i].offset.x, v[i].start.y);
				glVertex2i(v[i].start.x + v[i].size.x, v[i].start.y);
				glVertex2i(v[i].start.x + v[i].size.x, v[i].start.y + v[i].size.y);
				glVertex2i(v[i].start.x + v[i].offset.x, v[i].start.y + v[i].size.y);
			glEnd();
		}
	glPopMatrix();
}

int GetViewport(int x, int y) {
	for(int i = FROM_X; i <= TO_Y; ++i) {
		if((x >= v[i].start.x && x <= v[i].start.x + v[i].size.x) &&
			(y >= v[i].start.y && y <= v[i].start.y + v[i].size.y) )
			return i;
	}
	return -1;
}

void PrintViewportContents(void) {
	for(int i = FROM_X; i <= TO_Y; ++i) {
		glColor3f(v[i].curColor[0], v[i].curColor[1], v[i].curColor[2]);
		glRasterPos2i(v[i].start.x + v[i].offset.x + 5, v[i].start.y + v[i].offset.y);
		for(unsigned int j = 0; j < v[i].content.length(); ++j)
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, v[i].content.at(j));
	}
}

int Clamp(int mn, int mx, int data) {
	return data > mx? mx: data < mn? mn: data;
}