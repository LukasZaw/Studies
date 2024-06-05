#include <GLFW/glfw3.h> 
#include<iostream> 
#include <math.h>
#include<cmath>
#include<string>
using namespace std;

# define M_PI 3.14159265358979323846 
# define GL_PI 3.14159265358979323846 

enum
{
    FULL_WINDOW,
    ASPECT_1_1,
    ORTO,
    FRUST
};

// ustawienie wartości startowych
bool iCull = false;
bool iOutline = false;
bool iDepth = true;
bool iClock = false;
bool iFill = false;

bool lighting = true;
bool material = true;
bool light0 = true;
bool light1 = false;
bool light2 = false;

GLint skala = ASPECT_1_1;
GLint rzut = FRUST;

int width = 1024; //poczatkowy rozmiar okna
int height = 768;

float sensitivity = 120.0f; //ustawienia kamery
bool firstClick = true;
float speed = 0.1f;

// ustawienie parametrow zakresów rzutowania
GLfloat zakresOrto = 20.0f;
GLfloat zakres = 0.5f;
GLfloat blisko = 1.0f;
GLfloat daleko = 50.0f;

double Rot_x = 0.0;
double Rot_y = -10.0;
double Rot_z = 0.0;

double Tra_x = -1.5;
double Tra_y = -0.5;
double Tra_z = -6.0;

float angle_ref = 15.0f;

GLfloat fPozycja_swiatla[4] = { 4.0f, 4.0f, 3.0f, 1.0f };
GLfloat fSlabe_swiatlo[] = { 0.25f, 0.25f, 0.25f, 1.0f };
GLfloat fMocne_swiatlo[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat fKierunek_reflektora[4] = { 0.0f, 0.0f, -2.0f, 1.0f }; // kierunek w którym ma świecić reflektor

const GLfloat ambient_materials[] = { 0.329412, 0.223529, 0.027451, 1.0 };
const GLfloat diffuse_materials[] = { 0.780392, 0.568627, 0.113725, 1.0 };
const GLfloat specular_materials[] = { 0.992157, 0.941176, 0.807843, 1.0 };
const GLfloat shininess_materials[] = { 27.8974 };

void drawCubeColorSize(float width, float height, float depth) {
    glBegin(GL_QUADS);
    // Front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-width, -height, depth);
    glVertex3f(width, -height, depth);
    glVertex3f(width, height, depth);
    glVertex3f(-width, height, depth);

    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-width, -height, -depth);
    glVertex3f(-width, height, -depth);
    glVertex3f(width, height, -depth);
    glVertex3f(width, -height, -depth);

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-width, height, -depth);
    glVertex3f(-width, height, depth);
    glVertex3f(width, height, depth);
    glVertex3f(width, height, -depth);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-width, -height, -depth);
    glVertex3f(width, -height, -depth);
    glVertex3f(width, -height, depth);
    glVertex3f(-width, -height, depth);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(width, -height, -depth);
    glVertex3f(width, height, -depth);
    glVertex3f(width, height, depth);
    glVertex3f(width, -height, depth);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-width, -height, -depth);
    glVertex3f(-width, -height, depth);
    glVertex3f(-width, height, depth);
    glVertex3f(-width, height, -depth);

    glEnd();
}

void drawSphere(float R, int numTheta, int numPhi) {
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < numTheta; ++i) {
        float theta1 = (i * 2.0 * GL_PI) / numTheta;
        float theta2 = ((i + 1) * 2.0 * GL_PI) / numTheta;
        for (int j = 0; j < numPhi; ++j) {
            float phi1 = (j * GL_PI) / numPhi;
            float phi2 = ((j + 1) * GL_PI) / numPhi;
            float x1 = R * sin(phi1) * cos(theta1);
            float y1 = R * sin(phi1) * sin(theta1);
            float z1 = R * cos(phi1);
            float x2 = R * sin(phi2) * cos(theta1);
            float y2 = R * sin(phi2) * sin(theta1);
            float z2 = R * cos(phi2);
            float x3 = R * sin(phi2) * cos(theta2);
            float y3 = R * sin(phi2) * sin(theta2);
            float z3 = R * cos(phi2);
            float x4 = R * sin(phi1) * cos(theta2);
            float y4 = R * sin(phi1) * sin(theta2);
            float z4 = R * cos(phi1);
            // Pierwszy trójkąt
            glNormal3f(x1, y1, z1);
            glVertex3f(x1, y1, z1);
            glNormal3f(x2, y2, z2);
            glVertex3f(x2, y2, z2);
            glNormal3f(x3, y3, z3);
            glVertex3f(x3, y3, z3);
            // Drugi trójkąt
            glNormal3f(x1, y1, z1);
            glVertex3f(x1, y1, z1);
            glNormal3f(x3, y3, z3);
            glVertex3f(x3, y3, z3);
            glNormal3f(x4, y4, z4);
            glVertex3f(x4, y4, z4);
        }
    }
    glEnd();
}

void drawPyramid(float baseWidth, float height, float baseDepth) {
    // Wysokość piramidy
    float halfWidth = baseWidth / 2.0f;
    float halfDepth = baseDepth / 2.0f;

    glBegin(GL_TRIANGLES);

    // Podstawa
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-halfWidth, 0.0f, -halfDepth);
    glVertex3f(halfWidth, 0.0f, -halfDepth);
    glVertex3f(halfWidth, 0.0f, halfDepth);

    glVertex3f(-halfWidth, 0.0f, -halfDepth);
    glVertex3f(halfWidth, 0.0f, halfDepth);
    glVertex3f(-halfWidth, 0.0f, halfDepth);

    // Boczne ściany
    // Lewa
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-halfWidth, 0.0f, -halfDepth);
    glVertex3f(-halfWidth, 0.0f, halfDepth);
    glVertex3f(0.0f, height, 0.0f);

    // Górna
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-halfWidth, 0.0f, halfDepth);
    glVertex3f(halfWidth, 0.0f, halfDepth);
    glVertex3f(0.0f, height, 0.0f);

    // Prawa
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(halfWidth, 0.0f, halfDepth);
    glVertex3f(halfWidth, 0.0f, -halfDepth);
    glVertex3f(0.0f, height, 0.0f);

    // Dolna
    // Obliczanie normalnej dla dolnej ściany piramidy
    float crossX = -halfWidth;
    float crossZ = halfDepth;
    float crossProductLength = sqrt(crossX * crossX + crossZ * crossZ);
    crossX /= crossProductLength;
    crossZ /= crossProductLength;

    //glNormal3f(crossX, 0.0f, crossZ);
    glVertex3f(-halfWidth, 0.0f, -halfDepth);
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(halfWidth, 0.0f, -halfDepth);

    glEnd();
}

void displaySettings() {
    if (iCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
    if (iDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    if (iOutline)
        glPolygonMode(GL_BACK, GL_LINE);
    else
        glPolygonMode(GL_BACK, GL_FILL);
    if (iFill)
        glShadeModel(GL_FLAT);
    else
        glShadeModel(GL_SMOOTH);
    if (iClock)
        glFrontFace(GL_CW);
    else
        glFrontFace(GL_CCW);
}


void display(float size) {
    displaySettings();

    glPushMatrix();

        glTranslated(Tra_x, Tra_y, Tra_z);
        glRotated(Rot_x, 1, 0, 0);
        glRotated(Rot_y, 0, 1, 0);
        glRotated(Rot_z, 0, 0, 1);

        glLightfv(GL_LIGHT0, GL_POSITION, fPozycja_swiatla); // pozycja światła
        glLightfv(GL_LIGHT1, GL_POSITION, fPozycja_swiatla); // pozycja światła
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, fKierunek_reflektora); // kierunek w który odwrócony jest reflektor
        glLightfv(GL_LIGHT2, GL_POSITION, fPozycja_swiatla); // pozycja światła

        glTranslated(fPozycja_swiatla[0], fPozycja_swiatla[1], fPozycja_swiatla[2]);
        glColor3d(1.0f, 1.0f, 1.0f);
        drawCubeColorSize(0.2f, 0.2f, 0.2f);
        glTranslated(-fPozycja_swiatla[0], -fPozycja_swiatla[1], -fPozycja_swiatla[2]);

        glTranslated(2.5f, 0, 0);
        glColor3d(0.4f, 0.6f, 0.0f);
        drawSphere(0.8f, 150, 100);

        glTranslated(-2.5f, -1.0f, 0);
        glColor3d(0.4f, 0.6f, 0.9f);
        drawPyramid(1.5f, 2.0f, 1.5f);

    glPopMatrix();
}


void CameraInputs(GLFWwindow* window) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Zmiana rotacji kamery
        Rot_x += sensitivity * (float)(mouseY - (height / 2)) / height;;
        Rot_y += sensitivity * (float)(mouseX - (width / 2)) / width;
        //cout << Rot_y << " " << Rot_x << endl;

        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Tra_x -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Tra_x += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Tra_z += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Tra_z -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        Tra_y += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Tra_y -= speed;
    }

    //poruszanie oswietleniem
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        fPozycja_swiatla[0] -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        fPozycja_swiatla[0] += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        fPozycja_swiatla[1] += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        fPozycja_swiatla[1] -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        fPozycja_swiatla[2] -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        fPozycja_swiatla[2] += speed;
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (action == GLFW_PRESS) {

        switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;

            //Zmiana wyswietlania
        case GLFW_KEY_1:
            rzut = FRUST;
            break;

        case GLFW_KEY_0:
            rzut = ORTO;
            break;

        case GLFW_KEY_2:
            skala = ASPECT_1_1;
            break;

        case GLFW_KEY_3:
            skala = FULL_WINDOW;
            break;

        case GLFW_KEY_5:
            iCull = !iCull;
            if (iCull) {
                cout << "ON  | Ukrywanie niewidocznych powierzchni" << endl;
            }
            else {
                cout << "OFF | Ukrywanie niewidocznych powierzchni" << endl;
            }
            break;
        case GLFW_KEY_6:
            iOutline = !iOutline;
            if (iOutline) {
                cout << "ON  | Zmiana wypelniania rysowania obiektow - linia" << endl;
            }
            else {
                cout << "OFF | Zmiana wypelniania rysowania obiektow - wypelnienie" << endl;
            }
            break;
        case GLFW_KEY_7:
            iDepth = !iDepth;
            if (iDepth) {
                cout << "ON  | Mechanizm sprawdzania glebi" << endl;
            }
            else {
                cout << "OFF | Mechanizm sprawdzania glebi" << endl;
            }
            break;
        case GLFW_KEY_8:
            iClock = !iClock;
            if (iClock) {
                cout << "ON  | Zmiana nawijania rysowania trojkatow" << endl;
            }
            else {
                cout << "OFF | Zmiana nawijania rysowania trojkatow" << endl;
            }
            break;
        case GLFW_KEY_9:
            iFill = !iFill;
            if (iFill) {
                cout << "ON  | Zmiana wypelniania kolorem - jednolite" << endl;
            }
            else {
                cout << "OFF | Zmiana wypelniania kolorem - gladkie" << endl;
            }
            break;

            //oswietlenie
        case GLFW_KEY_Y:
            lighting = !lighting;
            if (lighting) {
                cout << "Swiatlo ogolne ON" << endl;
            }
            else {
                cout << "Swiatlo ogolne OFF" << endl;
            }
            break;
        case GLFW_KEY_U:
            material = !material;
            if (material) {
                cout << "Materialy ON" << endl;
            }
            else {
                cout << "Materialy OFF" << endl;
            }
            break;
        case GLFW_KEY_I:
            light0 = !light0;
            if (light0) {
                cout << "Swiatlo 1 ON" << endl;
            }
            else {
                cout << "Swiatlo 1 OFF" << endl;
            }
            break;
        case GLFW_KEY_O:
            light1 = !light1;
            if (light1) {
                cout << "Swiatlo 2 ON" << endl;
            }
            else {
                cout << "Swiatlo 2 OFF" << endl;
            }
            break;
        case GLFW_KEY_P:
            light2 = !light2;
            if (light2) {
                cout << "Swiatlo 3 ON" << endl;
            }
            else {
                cout << "Swiatlo 3 OFF" << endl;
            }
            break;

        case GLFW_KEY_K:
            angle_ref += 1.0f;
            break;
        case GLFW_KEY_L:
            angle_ref -= 1.0f;
            break;
        }
    }
}


int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(width, height, "Projekt GLFW - Oswietlenie", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);

    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    unsigned int counter = 0;

    glfwSwapInterval(0); //Vsync disabled

    while (!glfwWindowShouldClose(window))
    {
        crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        counter++;
        if (timeDiff >= 1.0 / 60.0)
        {
            prevTime = crntTime;
            counter = 0;
            CameraInputs(window);

        }

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glShadeModel(GL_SMOOTH);
        glfwSetKeyCallback(window, key_callback);

        if (rzut == ORTO)
        {
            if (skala == ASPECT_1_1)
            {
                if (width < height && width > 0)
                    glOrtho(-zakresOrto, zakresOrto, -zakresOrto * height / width, zakresOrto * height / width, -zakresOrto, zakresOrto);
                else
                    if (width >= height && height > 0)
                        glOrtho(-zakresOrto * width / height, zakresOrto * width / height, -zakresOrto, zakresOrto, -zakresOrto, zakresOrto);
            }
            else
                glOrtho(-zakresOrto, zakresOrto, -zakresOrto, zakresOrto, -zakresOrto, zakresOrto);
        }

        if (rzut == FRUST)
        {
            if (skala == ASPECT_1_1)
            {
                if (width < height && width > 0)
                    glFrustum(-zakres, zakres, -zakres * height / width, zakres * height / width, blisko, daleko);
                else
                    glFrustum(-zakres * width / height, zakres * width / height, -zakres, zakres, blisko, daleko);
            }
            else
                //glFrustum(.5, -.5, -.5 * height / width, .5 * height / width, 1, 50);
                glFrustum(-zakres, zakres, -zakres, zakres, blisko, daleko);
        }

        glMatrixMode(GL_MODELVIEW);

        float squareSize = static_cast<float>(std::min(width, height)) * 0.2f;

        display(squareSize);

        //glEnable(GL_CULL_FACE);
        glClearColor(1, 1, 1, 1);
        glfwSwapBuffers(window);

        glDepthFunc(GL_LESS);

        //zmiana ustawin swiatla
        if(lighting)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);
        if (material)
            glEnable(GL_COLOR_MATERIAL);
        else
            glDisable(GL_COLOR_MATERIAL);

        if (light0)
            glEnable(GL_LIGHT0);
        else
            glDisable(GL_LIGHT0);
        if (light1)
            glEnable(GL_LIGHT1);
        else
            glDisable(GL_LIGHT1);
        if (light2)
            glEnable(GL_LIGHT2);
        else
            glDisable(GL_LIGHT2);
       

        //swiatlo ogolne
        glLightfv(GL_LIGHT0, GL_AMBIENT, fSlabe_swiatlo); // światło otoczenia
        glLightfv(GL_LIGHT0, GL_DIFFUSE, fMocne_swiatlo); // światło rozproszenia
        glLightfv(GL_LIGHT0, GL_SPECULAR, fMocne_swiatlo); // światło odbite


        //swiatlo reflektora
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, angle_ref); // reflektor o kącie rozwarcia
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 30.0f); // stopień skupienia reflektora

        glLightfv(GL_LIGHT1, GL_AMBIENT, fSlabe_swiatlo); // światło otoczenia
        glLightfv(GL_LIGHT1, GL_DIFFUSE, fMocne_swiatlo); // światło rozproszenia
        glLightfv(GL_LIGHT1, GL_SPECULAR, fMocne_swiatlo); // światło odbite

        //swiatlo zanikajace
        glLightfv(GL_LIGHT2, GL_AMBIENT, fSlabe_swiatlo); // światło otoczenia
        glLightfv(GL_LIGHT2, GL_DIFFUSE, fMocne_swiatlo); // światło rozproszenia
        glLightfv(GL_LIGHT2, GL_SPECULAR, fMocne_swiatlo); // światło odbite
        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 2.0f);
        glLighti(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.0f);
        glLighti(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.5f);
        
        //materiały
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_materials);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_materials);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular_materials);
        glMaterialfv(GL_FRONT, GL_SHININESS, shininess_materials);


        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}