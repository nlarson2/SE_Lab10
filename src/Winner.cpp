
/*
Created By: Nickolas Larson
Date: 10/28/2019

Modified By:
Modified Date:


*/

#ifndef WINNER_CPP
#define WINNER_CPP

#include "Winner.h"


Winner::Winner(int _xres, int _yres) {
    exitClicked = 0;
    xres = _xres;
    yres = _yres;
    img = new Image("images/WIN.png");
    //position start button on the bottom middle of the screen
    exit.center[0] = xres/2.0f;
    exit.center[1] = yres/4.0f;
    //wider than it is tall
    exit.w = xres/8.0f;
    exit.h = yres/15.0f;

    exit.rgb[0] = 1.0f;
    exit.rgb[1] = 0;
    exit.rgb[2] = 0;

    img->GenerateGLTexture(winnerTexture);
}
Winner::~Winner()
{
    delete img;
}
void Winner::Draw()
{
        
    glLoadIdentity();

    float w;
    float h;
    float * rgb;
    /*Title*/
    glPushMatrix();
    w = 250;
    h = 150;
    glTranslatef(xres/2, yres/2 + 200, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, winnerTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(0.00, 0.99);glVertex2f(-w, -h);
        glTexCoord2f(0.00, 0.00);glVertex2f(-w,  h);
        glTexCoord2f(1.00, 0.00);glVertex2f( w,  h);
        glTexCoord2f(1.00, 0.99);glVertex2f( w, -h);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    /*Start Button*/
    glPushMatrix();
    w = exit.w;
    h = exit.h;
    rgb = exit.rgb;
    glTranslatef(exit.center[0], exit.center[1], 0.0f);
    /*Border*/
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_QUADS);

        glVertex2f(-w, -h);
        glVertex2f(-w,  h);
        glVertex2f( w,  h);
        glVertex2f( w, -h);
    glEnd();

    /*Fill*/
    glColor3f(0,0,0);
    glBegin(GL_QUADS);

        glVertex2f(-w + 4,-h + 4);
        glVertex2f(-w + 4, h - 4);
        glVertex2f( w - 4, h - 4);
        glVertex2f( w - 4,-h + 4);
    glEnd();
    glPopMatrix();
    Rect r;
    r.bot = (int)exit.center[1] - 5;
    r.left = (int)exit.center[0];;
    ggprint16(&r, 16, 0xFFFFFFFF, "RETURN TO MENU");
};
GameScene * Winner::CheckMouse(int x, int y) 
{
    if (x > exit.center[0] - exit.w && x < exit.center[0] + exit.w ) {
        if (yres - y > exit.center[1] - exit.h && yres - y < exit.center[1] + exit.h ) {
            //return to menu  on update
            exitClicked = true;
        }
    }
    return nullptr;
}
GameScene * Winner::CheckKey(int key) 
{
    if(key == XK_Return)
        return this;
    return nullptr;
}
GameScene * Winner::Update() {
    
    if(exitClicked)
        return this;
    return nullptr;
}
 


#endif
