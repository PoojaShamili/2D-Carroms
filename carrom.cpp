#include<stdio.h>
#include<iostream>
#include<cmath>
#include<GL/glut.h>
using namespace std;

#define DEG2RAD(deg) (deg * PI / 180)
#define PI 3.141592653589
#define E 0.5
class Striker
{
  public:
    double s_x = -1.5f;
    double s_y = -1.65f;
    double sv_x = 1.0f;
    double sv_y = 1.0f;
    double r = 0.15f;
    double theta = 0;
    double mass = 2.0f;
};

class Initial_Striker
{
  public:
    double s_x = -1.5f;
    double s_y = -1.65f;
    double sv_x = 1.0f;
    double sv_y = 1.0f;
    double r = 0.15f;
    double theta = 0;
    double mass = 2.0f;
};

class Coin
{
  public:
    double c_x;
    double c_y;
    double cv_x = 0.0f;
    double cv_y = 0.0f;
    double r = 0.12f;
    double mass = 1.0f;
};

class Box
{
  public:
    double box_len1 = 4.0f;
    double box_len = 5.0f;
};

class Hole
{
  public:
    double h_x;
    double h_y;
    double r = 0.15f;
};

Striker striker;
Box box;
Coin coins[8];
Hole holes[4];
//striker.s_x = -2.0f;
//striker.s_y = -2.08f;
//striker.r = 0.2f;

int flag = 0;
int speed = 0;

void initRendering() {
    glEnable(GL_DEPTH_TEST);        
    glEnable(GL_COLOR_MATERIAL);    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   
}

void drawBall(double rad)
{
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
    }
    glEnd();
}

void drawCircles()
{
    double r;
    r = 0.6f;
    glBegin(GL_POINTS);
    for(int i=0;i<1000;++i)
    {
        glVertex3f(r*cos(2*PI*i/1000.0),r*sin(2*PI*i/1000.0),0);
    }
    glEnd(); 
}

void setHoles()
{
    double l = box.box_len;
    holes[0].h_x = -(l-0.5)/2;
    holes[0].h_y = (l-0.5)/2;
    holes[1].h_x = (l-0.5)/2;
    holes[1].h_y = (l-0.5)/2;
    holes[2].h_x = -(l-0.5)/2;
    holes[2].h_y = -(l-0.5)/2;
    holes[3].h_x = (l-0.5)/2;
    holes[3].h_y = -(l-0.5)/2;
}

void setCoods()
{
    double r;
    r = 0.5;
    int i, theta = 45;
    for(i=0;i<8;i++)
    {
        coins[i].c_x = r*cos(DEG2RAD(theta*i));
	coins[i].c_y = r*sin(DEG2RAD(theta*i));
    }
}

void drawHoles()
{
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0 ; i<360 ; i++) {
       glVertex2f(0.15f * cos(DEG2RAD(i)), 0.15f * sin(DEG2RAD(i)));
    }
    glEnd();
}

void drawCoins()
{
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0 ; i<360 ; i++) {
       glVertex2f(coins[1].r * cos(DEG2RAD(i)), coins[1].r * sin(DEG2RAD(i)));
    }
    glEnd();
    
}

void drawBox(double len)
{
    float len1 = 5.0f;
    glColor3f(0.34f, 0.15f, 0.13f);
    glBegin(GL_QUADS);
    glVertex2f(-(len1+1) / 2, -(len1+1)/ 2);
    glVertex2f((len1+1)/ 2, -(len1+1)/ 2);
    glVertex2f((len1+1)/ 2, (len1+1)/ 2);
    glVertex2f(-(len1+1)/ 2, (len1+1)/ 2);
    glEnd();
    glColor3f(0.65f, 0.50f, 0.39f);
    glBegin(GL_QUADS);
    glVertex2f(-len1 / 2, -len1 / 2);
    glVertex2f(len1 / 2, -len1 / 2);
    glVertex2f(len1 / 2, len1 / 2);
    glVertex2f(-len1 / 2, len1 / 2);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-(len-0.4)/ 2, -(len-0.4)/ 2);
    glVertex2f((len-0.4)/ 2, -(len-0.4)/ 2);
    glVertex2f((len-0.4)/ 2, (len-0.4)/ 2);
    glVertex2f(-(len-0.4)/ 2, (len-0.4)/ 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawIndicator()
{
    if(speed == 0)
	    return;
    int len = 0.5f;
    len += striker.sv_x*10 - 1.0f;
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, len);
    glEnd();
    //glutTimerFunc(10, drawIndicator, 0);

}

void drawLines(double theta)
{
    if(flag == 0)
	    return;
    int len = 1.0f;
    len += striker.sv_x*2 - 1.0f;
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(len * cos(theta), len * sin(theta));
    //glRotatef(theta,0,len,0);
    glEnd();
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, -8.0f);
    drawBox(box.box_len1);
    
    for(int i=0; i<4; i++)
    {
    glPushMatrix();
    glTranslatef(holes[i].h_x, holes[i].h_y, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHoles();
    glPopMatrix();
    }


    glPushMatrix();
    glTranslatef(striker.s_x, striker.s_y, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawBall(striker.r);
    glPopMatrix();

    /*glPushMatrix();
    glTranslatef(ball_x1, ball_y1, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();*/

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawCircles();
    glPopMatrix();

    int i;
    for(i=0;i<8;i++)
    {
    	glPushMatrix();
    	glColor3f(1.0f, 1.0f, 0.0f);
    	glTranslatef(coins[i].c_x, coins[i].c_y, 0.0f);
    	drawCoins();
    	glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(striker.s_x, striker.s_y, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawLines(striker.theta);
    glPopMatrix();
    
    /*glPushMatrix();
    glTranslatef(striker.s_x, striker.s_y, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    drawIndicator();
    glPopMatrix();*/

    glPopMatrix();
    glutSwapBuffers();
}

int checkHoles(int i)
{
	for(int j=0; j<4; j++)
	{
	    double z_x = coins[i].c_x - holes[j].h_x;
	    double z_y = coins[i].c_y - holes[j].h_y;
	    double z = sqrt(z_x*z_x + z_y*z_y);
	    if(z <= coins[i].r + holes[i].r)
		    return 1;
	}
	return 0;

}

void make_coin_move(int i)
{
	double v_x = coins[i].cv_x;
	double v_y = coins[i].cv_y;
	double a_x, a_y;

	if(v_x < 0)
		a_x = -v_x;
	else
		a_x = v_x;
	if(v_y < 0)
		a_y = -v_y;
	else
		a_y = v_y;
        
	a_x -= 0.01;
        a_y -= 0.01;

	if(a_x < 0 && a_y < 0)
	{
	      return;
	}
	if(a_x < 0)
		a_x = 0;
	if(a_y < 0)
		a_y = 0;

        if(v_x < 0)
		v_x = -a_x;
	else
		v_x = a_x;
	if(v_y < 0)
		v_y = -a_y;
	else
		v_y = a_y;

	coins[i].cv_x = v_x;
	coins[i].cv_y = v_y;


	if(coins[i].c_x + coins[i].r >= box.box_len/2 || coins[i].c_x - coins[i].r <= -box.box_len/2)
		coins[i].cv_x *= -1;
	if(coins[i].c_y + coins[i].r >= box.box_len/2 || coins[i].c_y - coins[i].r <= -box.box_len/2)
		coins[i].cv_y *= -1;

	coins[i].c_x += coins[i].cv_x*0.1;
	//striker.s_x *= striker.theta;
	coins[i].c_y += coins[i].cv_y*0.1;
	//make_striker_move(start);
        int flag = checkHoles(i);
	if(flag == 1)
	{
		coins[i].c_x = 1000.0f;
		coins[i].c_y = 1000.0f;
	}

        glutTimerFunc(10, make_coin_move, i);
}
void checkStrikerCollision(int i)
{
	double z_x = coins[i].c_x - striker.s_x;
	double z_y = coins[i].c_y - striker.s_y;
	double z = sqrt(z_x*z_x + z_y*z_y);
	if(z<= striker.r + coins[i].r)
	{
		//printf("%d\n", i);
		double cvf_x = (z_x* coins[i].cv_x + z_y* coins[i].cv_y)/z;
		double cvf_y = (z_x* striker.sv_x + z_y* striker.sv_y)/z;
		if(striker.mass > 1.5f)
		{
			double temp_x = (4*cvf_y - cvf_x)/3;
			double temp_y = (cvf_x + 2*cvf_y)/3;
			cvf_y = temp_x;
			cvf_x = temp_y;
		}

		double svf_x = (z_y* coins[i].cv_x - z_x* coins[i].cv_y)/z;
		double svf_y = (z_y* striker.sv_x - z_x* striker.sv_y)/z;

		coins[i].cv_x = (z_x* cvf_y + z_y* svf_x)/z;
		coins[i].cv_y = (cvf_y* z_y - svf_x* z_x)/z;

		striker.sv_x = (z_x* cvf_x + z_y* svf_y)/z;
		striker.sv_y = (z_y* cvf_x - svf_y* z_x)/z;

		make_coin_move(i);
	}
}


void make_striker_move(int start)
{
	double v_x = striker.sv_x;
	double v_y = striker.sv_y;
	double a_x, a_y;

	if(v_x < 0)
		a_x = -v_x;
	else
		a_x = v_x;
	if(v_y < 0)
		a_y = -v_y;
	else
		a_y = v_y;
        
	a_x -= 0.01;
        a_y -= 0.01;

	if(a_x < 0 && a_y < 0)
	{
	      Initial_Striker initial_striker;
	      striker.s_x = initial_striker.s_x;
	      striker.s_y = initial_striker.s_y;
	      striker.sv_x = initial_striker.sv_x;
	      striker.sv_y = initial_striker.sv_y;
	      striker.r = initial_striker.r;
	      striker.theta = initial_striker.theta;
	      return;
	}
	if(a_x < 0)
		a_x = 0;
	if(a_y < 0)
		a_y = 0;

        if(v_x < 0)
		v_x = -a_x;
	else
		v_x = a_x;
	if(v_y < 0)
		v_y = -a_y;
	else
		v_y = a_y;

	striker.sv_x = v_x;
	striker.sv_y = v_y;


	if(striker.s_x + striker.r >= box.box_len/2 || striker.s_x - striker.r <= -box.box_len/2)
		striker.sv_x *= -1;
	if(striker.s_y + striker.r >= box.box_len/2 || striker.s_y - striker.r <= -box.box_len/2)
		striker.sv_y *= -1;
        for(int i=0; i<8; i++)
	{
		checkStrikerCollision(i);
		//checkCoinCollision(i);
	}

	striker.s_x += striker.sv_x*0.1*cos(striker.theta);
	//striker.s_x *= striker.theta;
	striker.s_y += striker.sv_y*0.1*sin(striker.theta);
	//make_striker_move(start);

        glutTimerFunc(10, make_striker_move, start);
}

void update(int value)
{
    
    glutTimerFunc(10, update, 0);
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFlush();
}

void handleKeypress(int key, int x, int y)
{
  if (key == GLUT_KEY_LEFT)
        striker.s_x -= 0.1;
  if (key == GLUT_KEY_RIGHT)
        striker.s_x += 0.1;

  if (key == GLUT_KEY_UP)
  {
	striker.sv_x += 0.1;
	striker.sv_y += 0.1;
  }
  if (key == GLUT_KEY_DOWN)
  {
        if(striker.sv_x > 0)
	     striker.sv_x -= 0.1;
	if(striker.sv_y > 0)
	     striker.sv_y -= 0.1;
  }
}

void handleNKeypress(unsigned char key, int x, int y)
{
  if(key == 'a')
  {
	  striker.theta -= 0.1;
	  flag = 1;
  }

  if(key == 'c')
  {
	  striker.theta += 0.1;
	  flag = 2;
  }

  int c = key;
  if(c == 32)
  {
	  Initial_Striker initial_striker;
          flag = 0;
	  time_t start;
	  time(&start);
	  int star = start;
          glutTimerFunc(10, make_striker_move, star);
	  /*striker.s_x = initial_striker.s_x;
	  striker.s_y = initial_striker.s_y;
	  striker.sv_x = initial_striker.sv_x;
	  striker.sv_y = initial_striker.sv_y;
	  striker.r = initial_striker.r;
	  striker.theta = initial_striker.theta;*/
  }
}

int main(int argc, char **argv)
{
    setCoods();
    setHoles();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);

    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;
     
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
     
    glutCreateWindow("Carroms!!");  
     
    initRendering();

    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutDisplayFunc(display);
    glutKeyboardFunc(handleNKeypress);
    glutSpecialFunc(handleKeypress);
    glutReshapeFunc(handleResize);
//    glutTimerFunc(10, update, 0);
    glutMainLoop();
    return 0;

}
