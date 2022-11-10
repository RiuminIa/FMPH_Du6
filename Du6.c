#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

FILE *dfile;
float x=0;
float v=0;
float fvon=0;
float const krok=5;
float a=0;
float const MYU=0.05;
float const GI=9.81;
float mas=1.0;
float actualTime=0;


void keyboardUpSpecialKey(unsigned char key, int x, int y){
    switch (key)
    {
    case GLUT_KEY_LEFT:
        fvon=0;
        break;
    case GLUT_KEY_RIGHT:
        fvon=0;
        break;
    default:
        fvon=0.0;
        break;     
    }
}


void processSpecialKeys(unsigned char key, int x, int y){
switch (key)
    {
    case GLUT_KEY_LEFT:
        fvon=-1.0;
        break;
    case GLUT_KEY_RIGHT:
        fvon=1.0;
        break;
    case GLUT_KEY_UP:
        mas+=0.1;
        break;
    case GLUT_KEY_DOWN:             
        mas-=0.1;
        break;
    default:
        break;
    }
} 

void processNormalKeys(unsigned char key, int x, int y){
    switch (key)
    {
    case 27: { 
        fclose(dfile);
        exit(0);
    }                                     
    default:
        break;
    }
}

void changecoordinates(){
    actualTime+=krok/1000;
    if (fvon < 0.0){
        a=fabsf((fvon+MYU*fabsf(v)*GI)/mas);
        v=v+(-1*a*krok/1000);
    }
    else if(fvon > 0.0){
        a=fabsf((fvon-MYU*fabsf(v)*GI)/mas);
        v=v+(a*krok/1000);
    }
    else{
        a=fabsf((MYU*fabsf(v)*GI)/mas);
        if(v>0.0){
        v=v-(a*krok/1000);
        }
        else if (v<0.0){
        v=v+(a*krok/1000);    
        }
        else{
            v=0;
        }
    }
    x+=v*krok/1000+1/2*a*pow(krok/1000,2);
    if (x>=1 || x<=-1){
        v*=-1;
    }
    printf("%.2f %.2f %.2f \n",actualTime,x,v);
    fprintf(dfile,"%.2f %.2f %.2f\n",actualTime,x,v);

}

void refresh(const int ihod){
    changecoordinates();    
    glutPostRedisplay();  
    glutTimerFunc(krok, refresh, ihod+1);
}

void resizeWindow(int width, int heigth){

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2, 2, -2, 2);
}

void drawRect(){
    glLoadIdentity();
    glTranslatef(x,0,0);
    glBegin(GL_QUADS);
    glColor3f(0.1, 0.4, 0.9);
    glVertex2f ( 0,0);
    glVertex2f (0,0.1);
	glVertex2f (0.1,0.1);
    glVertex2f (0.1, 0);
	glEnd();
}

void draw(){
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    drawRect();
    glutSwapBuffers();
}
int main(int argc, char **argv)
{ 
    if((dfile= fopen("RiuminDU6.txt", "w"))==NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }
    fprintf(dfile,"t     x     v\n");
    printf("t     x     v\n");
    fprintf(dfile,"0.00  0.00 0.00");
    printf("0.00  0.00 0.00");

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL: Hmotni bod");
	glutDisplayFunc(draw);
	glClearColor(0.2, 0.2, 0.2, 0.3);
	glutReshapeFunc(resizeWindow);
	glutTimerFunc(krok, refresh, 0);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutSpecialUpFunc(keyboardUpSpecialKey);
	glutMainLoop();
    fclose(dfile);
	return 0;
}