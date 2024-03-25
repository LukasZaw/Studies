#include <GLFW/glfw3.h> 
#include<iostream> 
#include<fstream>
#include<stdlib.h>

using namespace std;

int lw;
int lk;

const int w = 1339;
const int k = 2000;

int m[3][3] = { 1,1,1,1,1,1,1,1,1 };

int Rs[w][k];
int Gs[w][k];
int Bs[w][k];

int Rn[w][k];
int Gn[w][k];
int Bn[w][k];

void display(float size) {
    /*glColor3d(1.0, 0.0, 0.0);

    glBegin(GL_QUADS);
    glVertex3f(-20.0, -20.0, 0.0);
    glVertex3f(20.0, -20.0, 0.0);
    glVertex3f(20.0, 20.0, 0.0);
    glVertex3f(-20.0, 20.0, 0.0);
    glEnd();*/

    glPushMatrix();
    glTranslated(0, 0, -6);

    glBegin(GL_POINTS);
    for (int i = 0; i < lw; ++i)
        for (int j = 0; j < lk; ++j)
        {
            glColor3d(Rn[i][j] / 255., Gn[i][j] / 255., Bn[i][j] / 255.);
            glVertex3d(j, i, 0);
        }


    glEnd();
    glPopMatrix();
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        //Powrot do pierwotnego zdjecia
        case GLFW_KEY_Q:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    Rn[i][j] = Rs[i][j];
                    Gn[i][j] = Gs[i][j];
                    Bn[i][j] = Bs[i][j];
                }
            break;

        //W - Inwersja kolorów : Zamiana kolorów na ich negatywy.
        case GLFW_KEY_W:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    Rn[i][j] = 255 - Rs[i][j];
                    Gn[i][j] = 255 - Gs[i][j];
                    Bn[i][j] = 255 - Bs[i][j];
                }
            break;

        //E - Zwiększenie kontrastu - mnożenie wartości pikseli przez stałą
        case GLFW_KEY_E:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    Rn[i][j] = 0.5 * Rs[i][j];
                    Gn[i][j] = 0.5 * Gs[i][j];
                    Bn[i][j] = 0.5 * Bs[i][j];
                }
            break;

        //R - Odcienie szarości - ITU-R BT.601, Luminancja
        case GLFW_KEY_R:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    int szarosc = 0.299 * Rs[i][j] + 0.587 * Gs[i][j] + 0.114 * Bs[i][j];
                    Rn[i][j] = szarosc;
                    Gn[i][j] = szarosc;
                    Bn[i][j] = szarosc;
                }
            break;

            //T - Binaryzacja (progowanie) obrazu
        case GLFW_KEY_T:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    int x = (Rs[i][j] + Gs[i][j] + Bs[i][j]) / 3;
                    if (x > 120) {
                        Rn[i][j] = 255;
                        Gn[i][j] = 255;
                        Bn[i][j] = 255;
                    }
                    else {
                        Rn[i][j] = 0;
                        Gn[i][j] = 0;
                        Bn[i][j] = 0;
                    }
                }
            break;


        //Z - Zmniejszenie jasnosci (-10)
        case GLFW_KEY_Z:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    Rn[i][j] = Rn[i][j] - 10;
                    Gn[i][j] = Gn[i][j] - 10;
                    Bn[i][j] = Bn[i][j] - 10;
                }
            break;
        //X - Zwiększenie jasnosci (+10)
        case GLFW_KEY_X:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    Rn[i][j] = Rn[i][j] + 10;
                    Gn[i][j] = Gn[i][j] + 10;
                    Bn[i][j] = Bn[i][j] + 10;
                }
            break;

        case GLFW_KEY_C:
            for (int i = 1; i < lw - 1; ++i)
                for (int j = 1; j < lk - 1; ++j)
                {
                    Rn[i][j] = (Rs[i - 1][j - 1] * m[0][0] +
                        Rs[i - 1][j] * m[0][1] +
                        Rs[i - 1][j + 1] * m[0][2] +
                        Rs[i][j - 1] * m[1][0] +
                        Rs[i][j] * m[1][1] +
                        Rs[i][j + 1] * m[1][2] +
                        Rs[i + 1][j - 1] * m[2][0] +
                        Rs[i + 1][j] * m[2][1] +
                        Rs[i + 1][j + 1] * m[2][2])
                        / (m[0][0]) + (m[0][1]) + (m[0][2]) + (m[1][0]) + (m[1][1]) + (m[1][2]) + (m[2][0]) + (m[2][1]) + (m[2][2]);

                    Gn[i][j] = (Gs[i - 1][j - 1] * m[0][0] +
                        Gs[i - 1][j] * m[0][1] +
                        Gs[i - 1][j + 1] * m[0][2] +
                        Gs[i][j - 1] * m[1][0] +
                        Gs[i][j] * m[1][1] +
                        Gs[i][j + 1] * m[1][2] +
                        Gs[i + 1][j - 1] * m[2][0] +
                        Gs[i + 1][j] * m[2][1] +
                        Gs[i + 1][j + 1] * m[2][2])
                        / (m[0][0]) + (m[0][1]) + (m[0][2]) + (m[1][0]) + (m[1][1]) + (m[1][2]) + (m[2][0]) + (m[2][1]) + (m[2][2]);

                    Bn[i][j] = (Bs[i - 1][j - 1] * m[0][0] +
                        Bs[i - 1][j] * m[0][1] +
                        Bs[i - 1][j + 1] * m[0][2] +
                        Bs[i][j - 1] * m[1][0] +
                        Bs[i][j] * m[1][1] +
                        Bs[i][j + 1] * m[1][2] +
                        Bs[i + 1][j - 1] * m[2][0] +
                        Bs[i + 1][j] * m[2][1] +
                        Bs[i + 1][j + 1] * m[2][2])
                        / (m[0][0] + m[0][1] + m[0][2] + m[1][0] + m[1][1] + m[1][2] + m[2][0] + m[2][1] + m[2][2]);
                }
            break;
        }
    }
}


const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



int main(void)
{


    ifstream plik("C:/glfw-3.4.bin.WIN64/zd5.txt");
    plik >> lw >> lk;
    cout << "wiersze=" << lw << " kolumny=" << lk << endl;
    for (int i = 0; i < lw; ++i)
        for (int j = 0; j < lk; ++j)
        {
            plik >> Rs[i][j];
            plik >> Gs[i][j];
            plik >> Bs[i][j];
        }
    plik.close();

    for (int i = 0; i < lw; ++i)
        for (int j = 0; j < lk; ++j)
        {
            Rn[i][j] = Rs[i][j];
            Gn[i][j] = Gs[i][j];
            Bn[i][j] = Bs[i][j];
        }


    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(800, 600, "Przykladowe Okno GLFW", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, -10.0, 10.0);
        glOrtho(0, k, 0, w, 2, 100.0);
        glMatrixMode(GL_MODELVIEW);

        glfwSetKeyCallback(window, key_callback);

        float squareSize = static_cast<float>(std::min(width, height)) * 0.2f;

        display(squareSize);

        glEnable(GL_CULL_FACE);
        glClearColor(1, 1, 1, 1);
        glfwSwapBuffers(window);

        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHTING);

        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
