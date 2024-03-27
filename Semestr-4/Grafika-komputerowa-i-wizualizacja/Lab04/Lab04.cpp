#include <GLFW/glfw3.h> 
#include<iostream> 
#include<fstream>
#include<stdlib.h>
#include <algorithm>
using namespace std;

int lw;
int lk;

const int w = 1339;
const int k = 2000;

double mA[3][3] = { 0.0625, 0.125, 0.0625,
                 0.125, 0.25, 0.125,
                 0.0625, 0.125, 0.0625 };

int mS[3][3] = { 0,-1,0,
                -1,5,-1,
               0,-1,0 };

int mD[3][3] = { -1,-1,-1,
                -1,8,-1,
                -1,-1,-1 };

int mF[3][3] = { -2,-1,0,
                -1,1,1,
                0,1,2 };

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

            //Przekształcenia bezkontekstowe
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

            //E - Zmniejszenie kontrastu - mnożenie wartości pikseli przez stałą
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


            //Przekształcenia kontekstowe
        //A - Filtr uśredniający
        case GLFW_KEY_A:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    float sumR = 0.0f;
                    float sumG = 0.0f;
                    float sumB = 0.0f;
                    
                    for (int k = -1; k <= 1; ++k) {
                        for (int l = -1; l <= 1; ++l) {
                            if (i + k >= 0 && i + k < lw && j + l >= 0 && j + l < lk) {
                                sumR += Rs[i + k][j + l] * mA[k + 1][l + 1];
                                sumG += Gs[i + k][j + l] * mA[k + 1][l + 1];
                                sumB += Bs[i + k][j + l] * mA[k + 1][l + 1];
                            }
                        }
                    }
                    
                    Rn[i][j] = sumR;
                    Gn[i][j] = sumG;
                    Bn[i][j] = sumB;
                }
                
            break;

        //S - Filtr wyostrzający
        case GLFW_KEY_S:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    float sumR = 0.0f;
                    float sumG = 0.0f;
                    float sumB = 0.0f;

                    for (int k = -1; k <= 1; ++k) {
                        for (int l = -1; l <= 1; ++l) {
                            if (i + k >= 0 && i + k < lw && j + l >= 0 && j + l < lk) {
                                sumR += Rs[i + k][j + l] * mS[k + 1][l + 1];
                                sumG += Gs[i + k][j + l] * mS[k + 1][l + 1];
                                sumB += Bs[i + k][j + l] * mS[k + 1][l + 1];
                            }
                        }
                    }

                    Rn[i][j] = sumR;
                    Gn[i][j] = sumG;
                    Bn[i][j] = sumB;
                }

            break;
        
        //D - Filtr krawędziowy (outline)
        case GLFW_KEY_D:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    float sumR = 0.0f;
                    float sumG = 0.0f;
                    float sumB = 0.0f;

                    for (int k = -1; k <= 1; ++k) {
                        for (int l = -1; l <= 1; ++l) {
                            if (i + k >= 0 && i + k < lw && j + l >= 0 && j + l < lk) {
                                sumR += Rs[i + k][j + l] * mD[k + 1][l + 1];
                                sumG += Gs[i + k][j + l] * mD[k + 1][l + 1];
                                sumB += Bs[i + k][j + l] * mD[k + 1][l + 1];
                            }
                        }
                    }

                    Rn[i][j] = sumR;
                    Gn[i][j] = sumG;
                    Bn[i][j] = sumB;
                }

            break;

            //F - Filtr (emboss)
        case GLFW_KEY_F:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    float sumR = 0.0f;
                    float sumG = 0.0f;
                    float sumB = 0.0f;

                    for (int k = -1; k <= 1; ++k) {
                        for (int l = -1; l <= 1; ++l) {
                            if (i + k >= 0 && i + k < lw && j + l >= 0 && j + l < lk) {
                                sumR += Rs[i + k][j + l] * mF[k + 1][l + 1];
                                sumG += Gs[i + k][j + l] * mF[k + 1][l + 1];
                                sumB += Bs[i + k][j + l] * mF[k + 1][l + 1];
                            }
                        }
                    }

                    Rn[i][j] = sumR;
                    Gn[i][j] = sumG;
                    Bn[i][j] = sumB;
                }

            break;

            //G - Filtr maksimum
        case GLFW_KEY_G:
            for (int i = 0; i < lw; ++i)
                for (int j = 0; j < lk; ++j)
                {
                    int minR = 0;
                    int minG = 0;
                    int minB = 0;

                    for (int k = -1; k <= 1; ++k) {
                        for (int l = -1; l <= 1; ++l) {
                            if (i + k >= 0 && i + k < lw && j + l >= 0 && j + l < lk) {
                                minR = max(minR, Rs[i + k][j + l]);
                                minG = max(minG, Gs[i + k][j + l]);
                                minB = max(minB, Bs[i + k][j + l]);
                            }
                        }
                    }
                    Rn[i][j] = minR;
                    Gn[i][j] = minG;
                    Bn[i][j] = minB;
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

    window = glfwCreateWindow(800, 600, "Lukasz Zawodzinski - grafika komputerowa", NULL, NULL);

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
