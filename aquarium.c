//gcc aquarium.c -o aquarium -lGL -lGLU -lglut -lm
 // ./aquarium

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define FISH_COUNT 5
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
    float x, y;
    float dx, dy;
    float speed;
    float size;
    float r, g, b;
    int direction;
    int userControlled;
} Fish;

Fish fishes[FISH_COUNT];
int windowWidth = WINDOW_WIDTH;
int windowHeight = WINDOW_HEIGHT;
int selectedFish = -1;

void initFish(Fish *fish, int index) {
    fish->x = (float)(rand() % windowWidth);
    fish->y = (float)(rand() % windowHeight);
    fish->speed = 1.0f + (float)(rand() % 3);
    fish->size = 15.0f + (float)(rand() % 20);
    
    switch(index) {
        case 0: fish->r = 1.0f; fish->g = 0.0f; fish->b = 0.0f; break;
        case 1: fish->r = 0.0f; fish->g = 1.0f; fish->b = 0.0f; break;
        case 2: fish->r = 0.0f; fish->g = 0.0f; fish->b = 1.0f; break;
        case 3: fish->r = 1.0f; fish->g = 1.0f; fish->b = 0.0f; break;
        case 4: fish->r = 0.5f; fish->g = 0.0f; fish->b = 0.5f; break;
    }
    
    fish->direction = (rand() % 2) ? 1 : -1;
    fish->dx = fish->direction * fish->speed;
    fish->dy = (float)(rand() % 3 - 1) * 0.5f;
    fish->userControlled = 0;
}

void initFishes() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < FISH_COUNT; i++) {
        initFish(&fishes[i], i);
    }
}

void drawFish(Fish *fish, int index) {
    glPushMatrix();
    glTranslatef(fish->x, fish->y, 0.0f);
    
    if (fish->direction == -1) {
        glScalef(-1.0f, 1.0f, 1.0f);
    }
    
    glColor3f(fish->r, fish->g, fish->b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int angle = 0; angle <= 360; angle += 10) {
        float rad = angle * 3.14159f / 180.0f;
        float x = cos(rad) * fish->size;
        float y = sin(rad) * fish->size * 0.4f;
        glVertex2f(x, y);
    }
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex2f(-fish->size, 0.0f);
    glVertex2f(-fish->size * 1.8f, -fish->size * 0.7f);
    glVertex2f(-fish->size * 1.8f, fish->size * 0.7f);
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glVertex2f(fish->size * 0.3f, fish->size * 0.4f);
    glVertex2f(0, fish->size * 0.8f);
    glVertex2f(-fish->size * 0.3f, fish->size * 0.4f);
    glEnd();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(fish->size * 0.6f, fish->size * 0.15f);
    glEnd();
    
    // Fixed number display
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-fish->size/2, fish->size + 5);
    char numText[12]; // Increased buffer size
    snprintf(numText, sizeof(numText), "%d", index + 1);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, numText[0]);
    
    glPopMatrix();
}

void updateFish(Fish *fish) {
    if (!fish->userControlled) {
        if (rand() % 100 < 2) {
            fish->dy = (float)(rand() % 3 - 1) * 0.5f;
        }
        
        if (fish->y < fish->size || fish->y > windowHeight - fish->size) {
            fish->dy = -fish->dy;
        }
        
        if ((fish->direction == 1 && fish->x > windowWidth + fish->size) ||
            (fish->direction == -1 && fish->x < -fish->size)) {
            fish->x = (fish->direction == 1) ? -fish->size : windowWidth + fish->size;
            fish->y = (float)(rand() % windowHeight);
        }
    }
    
    fish->x += fish->dx;
    fish->y += fish->dy;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.4f);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glColor3f(0.2f, 0.2f, 0.8f);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0, windowHeight);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.76f, 0.70f, 0.50f);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight * 0.1f);
    glVertex2f(0, windowHeight * 0.1f);
    glEnd();
    
    for (int i = 0; i < FISH_COUNT; i++) {
        drawFish(&fishes[i], i);
    }
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10, windowHeight - 20);
    char* msg = "Press 1-5 to select fish, SPACE to toggle control, ARROWS to move";
    for (char* c = msg; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
    
    glRasterPos2f(10, windowHeight - 40);
    char* colorGuide = "Fish Colors: 1-Red, 2-Green, 3-Blue, 4-Yellow, 5-Purple";
    for (char* c = colorGuide; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
    
    if (selectedFish >= 0) {
        char info[50];
        snprintf(info, sizeof(info), "Controlling fish %d (Direction: %s)", 
                selectedFish + 1, 
                fishes[selectedFish].direction == 1 ? "Right" : "Left");
        glRasterPos2f(10, windowHeight - 60);
        for (char* c = info; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
        }
    }
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    for (int i = 0; i < FISH_COUNT; i++) {
        updateFish(&fishes[i]);
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1': case '2': case '3': case '4': case '5':
            selectedFish = key - '1';
            break;
        case ' ':
            if (selectedFish >= 0) {
                fishes[selectedFish].userControlled = !fishes[selectedFish].userControlled;
                if (fishes[selectedFish].userControlled) {
                    fishes[selectedFish].dy = 0;
                }
            }
            break;
        case 27:
            exit(0);
            break;
    }
}

void specialKeys(int key, int x, int y) {
    if (selectedFish >= 0 && fishes[selectedFish].userControlled) {
        switch (key) {
            case GLUT_KEY_LEFT:
                fishes[selectedFish].direction = -1;
                fishes[selectedFish].dx = -fishes[selectedFish].speed;
                break;
            case GLUT_KEY_RIGHT:
                fishes[selectedFish].direction = 1;
                fishes[selectedFish].dx = fishes[selectedFish].speed;
                break;
            case GLUT_KEY_UP:
                fishes[selectedFish].dy = fishes[selectedFish].speed * 0.5f;
                break;
            case GLUT_KEY_DOWN:
                fishes[selectedFish].dy = -fishes[selectedFish].speed * 0.5f;
                break;
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("OpenGL Aquarium");
    
    initFishes();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, timer, 0);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glutMainLoop();
    return 0;
}