#include <GL/glfw.h>
#define MAX_SIZE 101 //max size
#include<stdio.h>
#include<stdlib.h>
#include<iostream>

class Stack
{
public:
    int A[MAX_SIZE];  // array to store the stack
	int top;

	Stack(){ top = -1; }

	void Push(int x){
	  if(top == MAX_SIZE -1)
			return;

		A[++top] = x;
	}

	void Pop(){
		if(top == -1) // If tower is empty
			return;
		top--;
		}

	int Top(){
		return A[top];}

	int Size(){
        return top+1;}
};

    Stack A; //peg A
    Stack B;//peg B
    Stack C;//peg C

int width=1500, height=800;
int totaldisk = 3;
float diskwidth = 0.05;
float diskgap = 0.01;
//int disk=0;//disk number chosen = 0 means no disk
double timelimit = 0.5; //animation time for every move

void rectangle(){
    glBegin(GL_POLYGON);
        glVertex2f(0.9,0.0);
        glVertex2f(-0.9,0.0);
        glVertex2f(-0.9,-0.07);
        glVertex2f(0.9,-0.07);
    glEnd();
}

void diskSC(int n,Stack peg){
    glPushMatrix();
        glColor3f(1.0f-peg.A[n]/10,peg.A[n]/10.0f,peg.A[n]/10.0f);
        glScalef(peg.A[n]/25.0,0.7,0.0);
        rectangle();
    glPopMatrix();
}
void pegAdisks(){ //n=A.size()

    for(int i=0; i<A.Size(); i++){
        glPushMatrix();
            glTranslatef(-0.6,-0.8+(1+i)*(diskwidth+diskgap),0.0);
            diskSC(i,A);
        glPopMatrix();

        }
}
void pegBdisks(){
    for(int i=0; i<B.Size(); i++){
        glPushMatrix();
            glTranslatef(0.015,-0.8+(1+i)*(diskwidth+diskgap),0.0);
            diskSC(i,B);
//            level = level + 0.001;
        glPopMatrix();

        }
}
void pegCdisks(){
    for(int i=0; i<C.Size(); i++){//start from 0 so we can give args to diskSC to access array
        glPushMatrix();
            glTranslatef(0.615,-0.8+(1+i)*(diskwidth+diskgap),0.0);
            diskSC(i,C);
//            level = level + 0.001;
        glPopMatrix();

        }
}

void base(){
    glPushMatrix();
        glColor3f(0.258824,0.258824,0.435294);//0.13f,0.54f,0.13f
        glTranslatef(0.0,-0.8,0.0);
        rectangle();
    glPopMatrix();
}

void pegB(){
    glPushMatrix();
    glColor3f(1.0f,0.0f,0.0f);
        glRotatef(90,0.0,0.0,1.0);
        glScalef(0.5,0.4,0.0);
        glTranslatef(-0.8,0.0,0.0);
        rectangle();
    glPopMatrix();
}

void pegA(){
    glPushMatrix();
    glColor3f(0.0f,0.0f,1.0f);
        glRotatef(90,0.0,0.0,1.0);
        glScalef(0.5,0.4,0.0);
        glTranslatef(-0.8,1.535,0.0);
        rectangle();
    glPopMatrix();
}
void pegC(){
    glPushMatrix();
    glColor3f(0.137255,0.556863,0.137255);
        glRotatef(90,0.0,0.0,1.0);
        glScalef(0.5,0.4,0.0);
        glTranslatef(-0.8,-1.5,0.0);
        rectangle();
    glPopMatrix();
}

void display(){

glfwSetTime(0.0);//otherwise time is set to init() time of the glfw

    while(glfwGetTime() < timelimit){
        glClear(GL_COLOR_BUFFER_BIT);
            glPushMatrix();
                base();
                pegA();
                pegB();
                pegC();
                pegAdisks();
                pegBdisks();
                pegCdisks();
            glPopMatrix();
        glfwSwapBuffers();
    }
}

void moveDisk(int disk,Stack* source,Stack* dest){
    display();
    dest->Push(disk);
    source->Pop();
}

//ALGORITHM FOR TOH
void moveTower(int disk,Stack* source, Stack* dest, Stack* temp){
    if(disk == 0)//disk = 0 means tower is empty means stop the pop operation
        return;
    moveTower(disk -1,source,temp,dest);
    moveDisk(disk,source,dest);
    moveTower(disk-1,temp,dest,source);
}

int main()
{
    for(int i=totaldisk; i>=1; i--){//initial tower values are also inserted in the array
            A.Push(i);          //can change the source peg** using B.push() or C.Push()
        }

    glfwInit();


    if( !glfwOpenWindow( width, height, 0, 0, 0, 0, 0, 0, GLFW_WINDOW ) )
    {
        glfwTerminate();
        return 0;
    }
    glfwSetWindowTitle("TOWER OF HANOI(Swarit Sharma)");

    moveTower(totaldisk,&A,&B,&C);//function to start recursive calls & source,dest,temp

    while(true)
    {
        display();//solved

        if(glfwGetKey(GLFW_KEY_ESC)== GLFW_PRESS)
            break;
    }

    return 0;
}
