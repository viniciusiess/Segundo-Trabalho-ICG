#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

float pi = 3.14159265358979323846;
int clique = 0;
float corR = 0.0f, corG = 0.5f, corB = 1.0f;
float anguloRotacao = 0.0f;
float solX = -0.9, solY = 0.1f, luaX = -0.9, luaY = 0.1f;
float escalaSolX, escalaSolY, escalaLuaX, escalaLuaY;
float velocidadeRotacao = 1.0f;

float carroX = -0.9f;
float carroY = -0.90f;
float velocidadeCarro = 0.4f;


void Chao()
{
    glBegin(GL_QUADS);
    glColor3f(0.32f, 0.49f, 0.46f);
    glVertex2f(-1.0f, -0.95f);
    glVertex2f(1.0f, -0.95f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void TorreGerador()
{
    glColor3f(0.8f, 0.8f, 0.8f);

    glBegin(GL_QUADS);
    glVertex2f(-0.761f, -0.6f);
    glVertex2f(-0.755f, -0.6f);
    glVertex2f(-0.75f, -0.95f);
    glVertex2f(-0.765f, -0.95f);
    glEnd();
}

void Carro()
{
    glColor3f(1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(carroX, carroY, 0.0f);

    glBegin(GL_QUADS);
    glVertex2f(-0.1f, -0.05f);
    glVertex2f(0.1f, -0.05f);
    glVertex2f(0.08f, 0.02f);
    glVertex2f(-0.08f, 0.02f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i += 10)
    {
        float angulo = i * pi / 180.0;
        float x = -0.08f + 0.02f * cos(angulo);
        float y = -0.05f + 0.02f * sin(angulo);
        glVertex2f(x, y);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i += 10)
    {
        float angulo = i * pi / 180.0;
        float x = 0.08f + 0.02f * cos(angulo);
        float y = -0.05f + 0.02f * sin(angulo);
        glVertex2f(x, y);
    }
    glEnd();

    glPopMatrix();
}


void Gerador()
{
    glPushMatrix();
    glTranslatef(-0.7595f, -0.625f, 0.0f);
    glRotatef(anguloRotacao, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.0095f, -0.15f);
    glVertex2f(0.0095f, -0.15f);
    glEnd();
    glPopMatrix();
    glutPostRedisplay();
}

void Sol()
{
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glScalef(escalaSolX, escalaSolY, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10)
    {
        float angulo = i * pi / 180.0;
        float x = solX + sin(angulo) * solY;
        float y = 0.8f + cos(angulo) * solY;
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glFlush();
}

void Lua()
{
    if (clique >= 14)
    {
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glScalef(escalaLuaX, escalaLuaY, 1);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 10)
        {
            float angulo = i * pi / 180.0;
            float x = luaX + sin(angulo) * luaY;
            float y = 0.8f + cos(angulo) * luaY;
            glVertex2f(x, y);
        }
        glEnd();
        glPopMatrix();
    }
    glFlush();
}

void TeclaMais(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
        case '+':
            clique++;

            float movimentoSol = solY < 0.5f ? 0.05f : -0.05f;
            solX += movimentoSol;
            solY = movimentoSol;
            escalaSolX += 0.1;
            escalaSolY += 0.1;

            float escurecendo = clique / 6.0;
            corR = 0.0f + escurecendo * (0.0f - 0.0f);
            corG = 0.5f + escurecendo * (0.0f - 0.5f);
            corB = 1.0f + escurecendo * (0.0f - 0.3f);

            carroX += velocidadeCarro;

            if (clique >= 14)
            {
                float movimentoLua = luaY < 0.5f ? 0.05f : -0.05f;
                luaX += movimentoLua;
                luaY = movimentoLua;
                escalaLuaX += 0.1;
                escalaLuaY += 0.1;
            }
            break;
    }
}

void Estrela()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    glPointSize(1.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++)
    {
        float x = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;
        float y = (rand() / (float)RAND_MAX) * 2.0f - 1.0f;
        glVertex2f(x, y);
    }
    glEnd();
}

void Cenario()
{
    glClearColor(corR, corG, corB, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Chao();
    TorreGerador();
    Gerador();
    Sol();
    Lua();

    if (clique > 13)
    {
        Estrela();
    }

    if (clique > 27)
    {
        exit(0);
    }

    Carro();

    anguloRotacao += velocidadeRotacao;

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Trabalho ICG - Vinicius Siess");
    glutDisplayFunc(Cenario);
    glutKeyboardFunc(TeclaMais);
    glutMainLoop();
    return 0;
}
