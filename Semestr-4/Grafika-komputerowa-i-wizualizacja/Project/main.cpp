#include <GLFW/glfw3.h> 
#include<iostream> 
#include <math.h>
#include<cmath>
#include<string>
#include<fstream>
#include<stdlib.h>

using namespace std;

# define M_PI 3.141592653589793
# define GL_PI 3.141592653589793

enum
{
    FULL_WINDOW,
    ASPECT_1_1,
    ORTO,
    FRUST
};

//setting start values
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

int width = 1024; //initial window size
int height = 768; 

//Setting the parameters of the projection ranges
GLfloat zakresOrto = 20.0f;
GLfloat zakres = 0.5f;
GLfloat blisko = 1.0f;
GLfloat daleko = 80.0f;

//camera settings and moving
double Rot_x = 0.0;
double Rot_y = 0.0;
double Rot_z = 0.0;

double Tra_x = -6.0;
double Tra_y = -5.0;
double Tra_z = -18.0;

float sensitivity = 100.0f; //ustawienia kamery
bool firstClick = true;
float speed = 0.13f;

struct Vec3 {
    float x, y, z;

    Vec3(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

    Vec3 normalize() {
        float length = sqrt(x * x + y * y + z * z);
        return Vec3(x / length, y / length, z / length);
    }

    Vec3 cross(const Vec3& other) {
        return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
};

float degreesToRadians(float degrees) {
    return degrees * (GL_PI/ 180.0f);
}

//lighting
float angle_ref = 15.0f;
float mocne_val = 0.9f;
float slabe_val = 0.25f;

GLfloat fPozycja_swiatla[4] = { -8.0f, 9.0f, 5.0f, 1.0f };
GLfloat fSlabe_swiatlo[] = { slabe_val, slabe_val, slabe_val, 1.0f };
GLfloat fMocne_swiatlo[] = { mocne_val, mocne_val, mocne_val, 1.0f };

GLfloat fKierunek_reflektora[4] = { 0.0f, 0.0f, -2.0f, 1.0f }; //direction in which the reflector is to shine

const GLfloat ambient_materials[] = { 0.329412, 0.223529, 0.027451, 1.0 };
const GLfloat diffuse_materials[] = { 0.780392, 0.568627, 0.113725, 1.0 };
const GLfloat specular_materials[] = { 0.992157, 0.941176, 0.807843, 1.0 };
const GLfloat shininess_materials[] = { 27.8974 };

void displayConsoleInfo() {
    system("cls");
    cout << "======== Lista funkcjonalnosci ========" << endl;
    cout << "\tH - wyswietlenie listy\n\n\n";

    cout << "------- Ruch obiektu -------" << endl;
    cout << "          W A S D" << endl << endl;

    cout << "------- Obrot kamery -------" << endl;
    cout << "   Ruch myszy + LPM, Q R" << endl << endl;

    cout << "-------- Rzutowanie --------" << endl;
    cout << " 1 - Perspektywiczne / Ortogonalne" << endl;
    cout << " 2 - Skalowanie" << endl << endl;

    cout << "------ Zmiana ustawien -----" << endl;
    cout << " 5 - Ukrywanie niewidocznych powierzchni" << endl;
    cout << " 6 - Wypelniania rysowania obiektow" << endl;
    cout << " 7 - Sprawdzania glebi" << endl;
    cout << " 8 - Nawijania rysowania trojkatow" << endl;
    cout << " 9 - Zmiana wypelniania kolorem" << endl << endl;

    cout << "--- Poruszanie oswietleniem ---" << endl;
    cout << "         Strzalki Z X" << endl << endl;

    cout << "----- Zmiana oswietlenia -----" << endl;
    cout << " Y - Swiatlo oglone" << endl;
    cout << " U - Materialy" << endl;
    cout << " I - Swiatlo 1 (ogolne)" << endl;
    cout << " O - Swiatlo 2 (reflektor)" << endl;
    cout << " P - Swiatlo 3 (punktowe)" << endl << endl;

    cout << "----- Parametry swiatla -----" << endl;
    cout << " K L   - Zmiana rozwarcia reflektora" << endl;
    cout << " C V   - Intensywnosc swiatla" << endl;
    cout << " B N M - Zmiana koloru swiatla" << endl;
    cout << " J - Przywracanie ustawien poczatkowych" << endl;

    cout << " \t================" << endl << endl;


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



void drawCube(float width, float height, float depth) {
    glBegin(GL_QUADS);

    // Przód
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, depth);
    glVertex3f(width, 0.0f, depth);
    glVertex3f(width, height, depth);
    glVertex3f(0.0f, height, depth);

    // Tył
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(width, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, height, 0.0f);
    glVertex3f(width, height, 0.0f);

    // Lewa strona
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, depth);
    glVertex3f(0.0f, height, depth);
    glVertex3f(0.0f, height, 0.0f);

    // Prawa strona
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(width, 0.0f, depth);
    glVertex3f(width, 0.0f, 0.0f);
    glVertex3f(width, height, 0.0f);
    glVertex3f(width, height, depth);

    // Góra
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, height, depth);
    glVertex3f(width, height, depth);
    glVertex3f(width, height, 0.0f);
    glVertex3f(0.0f, height, 0.0f);

    // Dół
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(width, 0.0f, depth);
    glVertex3f(0.0f, 0.0f, depth);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(width, 0.0f, 0.0f);

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

void drawPyramid(float width, float height, float depth) {
    glBegin(GL_TRIANGLES);

    // Podstawa
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(width, 0.0f, 0.0f);
    glVertex3f(width, 0.0f, depth);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(width, 0.0f, depth);
    glVertex3f(0.0f, 0.0f, depth);

    // Boczne ściany
    // Lewa
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, depth);
    glVertex3f(width / 2.0f, height, depth / 2.0f);

    // Przod
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, depth);
    glVertex3f(width, 0.0f, depth);
    glVertex3f(width / 2.0f, height, depth / 2.0f);

    // Prawa
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(width, 0.0f, depth);
    glVertex3f(width, 0.0f, 0.0f);
    glVertex3f(width / 2.0f, height, depth / 2.0f);

    // Tyl
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(width / 2.0f, height, depth / 2.0f);
    glVertex3f(width, 0.0f, 0.0f);

    glEnd();
}

void sklejane(float wsp_1, float wsp_2, float z_1, float z_2) {
    GLfloat x1, y1, x2, y2, angle;
    glBegin(GL_TRIANGLE_STRIP);
    for (angle = 0.0f; angle < (2.0f * GL_PI); angle += (GL_PI / 16.01f))
    {
        x2 = wsp_2 * sin(angle);
        y2 = wsp_2 * cos(angle);
        x1 = wsp_1 * sin(angle);
        y1 = wsp_1 * cos(angle);

        glVertex3f(x2, y2, z_2);
        glVertex3f(x1, y1, z_1);
    }
    glEnd();

}

void drawCone(float height, float radius, int sides, int slices) {
    glNormal3f(0.0f, 0.0f, 1.0f);

    // Rysowanie stożka
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, height);
    for (int i = 0; i <= sides; ++i) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(sides);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0.0f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= sides; ++i) {
        float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(sides);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
    }
    glEnd();
}

void drawGrid(int size, float spacing) {
    float halfSize = size * spacing * 0.5f;

    // Rysowanie siatki
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5f);

    // Linie poziome
    for (int i = -size / 2; i <= size / 2; ++i) {
        glVertex3f(-halfSize, 0.0f, i * spacing);
        glVertex3f(halfSize, 0.0f, i * spacing);
    }

    // Linie pionowe
    for (int i = -size / 2; i <= size / 2; ++i) {
        glVertex3f(i * spacing, 0.0f, -halfSize);
        glVertex3f(i * spacing, 0.0f, halfSize);
    }

    glEnd();
}

void drawWindow() {
    glColor3f(0.2, 0.1, 0);

    glTranslated(0, 0, 0.1);

    drawCube(1.8, 0.03, 0.06);
    glTranslated(1.77, 0, 0);

    drawCube(0.03, 1.5, 0.06);
    glTranslated(0, 1.47, 0);

    drawCube(-1.77, 0.03, 0.06);
    glTranslated(-1.77, 0, 0);

    drawCube(0.03, -1.5, 0.06);
    glTranslated(0.03, -1.44, 0.01);

    glColor4f(0.8, 0.9, 0.9, 0.35);
    drawCube(1.74, 1.44, 0.02);
    glTranslated(-0.03, 0, -0.01);

    glTranslated(0.9, 0, 0);
    glColor3f(0.2, 0.1, 0);
    drawCube(0.06, 1.47, 0.06);

    glTranslated(-0.9, -0.03, -0.1);
}

void drawDoor() {
    glColor3f(0.42, 0.32, 0.2);

    glTranslated(-0.03, 0, -0.03);

    drawCube(0.08, 2, 0.36);
    glTranslated(0, 1.97, 0);

    drawCube(1.2, 0.08, 0.36);
    glTranslated(1.17, -1.97, 0);

    drawCube(0.08, 2.05, 0.36);

    glColor3f(0.6, 0.6, 0.6);
    drawCube(-1.1, 0.03, 0.36);

    glColor3f(0.34, 0.25, 0.12);

    glTranslated(0, 0, 0.1);
    drawCube(-1.1, 2, 0.1);

    glColor3f(0.4, 0.4, 0.4);
    glTranslated(-0.2, 1.1, 0.14);
    
    drawSphere(0.07, 20, 15);
    glTranslated(0, 0, -0.16);

    drawSphere(0.07, 20, 15);
    glTranslated(-0.94, -1.1, -0.05);


}

void drawTree() {
    glColor3f(0.4, 0.3, 0.1);
    glRotated(-90, 1, 0, 0);
    sklejane(0.2, 0.2, 0, 1);

    glColor3f(0, 0.3, 0.1);

    glTranslated(0, 0, 1);
    drawCone(2, 1.8, 10, 10);
    glTranslated(0, 0, 1);
    drawCone(1.8, 1.5, 10, 10);
    glTranslated(0, 0, 1.2);
    drawCone(1.6, 1.2, 10, 10);

    glTranslated(0, 0, -3.2);


    glRotated(90, 1, 0, 0);
}


//Main drawing function
void display(float size) {
    displaySettings();

    glPushMatrix();
        glRotated(Rot_x, 1, 0, 0);
        glRotated(Rot_y, 0, 1, 0);
        glRotated(Rot_z, 0, 0, 1);
        glTranslated(Tra_x, Tra_y, Tra_z);

        glLightfv(GL_LIGHT0, GL_POSITION, fPozycja_swiatla); // pozycja światła
        glLightfv(GL_LIGHT1, GL_POSITION, fPozycja_swiatla);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, fKierunek_reflektora);
        glLightfv(GL_LIGHT2, GL_POSITION, fPozycja_swiatla);

        glTranslated(fPozycja_swiatla[0], fPozycja_swiatla[1], fPozycja_swiatla[2]);
        glColor3d(1.0f, 1.0f, 1.0f);
        drawCube(0.2f, 0.2f, 0.2f);
        glTranslated(-fPozycja_swiatla[0], -fPozycja_swiatla[1], -fPozycja_swiatla[2]);

        //grid
        //drawGrid(60, 1);
        glTranslated(-14, -0.1, -15);
        glColor3f(0.5, 0.9, 0.3);
        drawCube(40, 0.1, 40);
        glTranslated(14, 0, 15);

        glTranslated(0.3, 0.1, 0.3);

        //podłoga
        glColor3f(0.6, 0.6, 0.6);
        drawCube(11.4, 0.02, 7.4);
        glTranslated(-0.3, 0, -0.3);

        //sciana tył
        glColor3f(0.8, 0.85, 1);

        drawCube(2, 3.1, 0.3);
        glTranslated(2, 0, 0);

        drawCube(1.8, 0.9, 0.3);//okno
        glTranslated(0, 2.4, 0);

        drawCube(1.8, 0.7, 0.3);//okno
        glTranslated(1.8, -2.4, 0);

        drawCube(4, 3.1, 0.3);
        glTranslated(4, 0, 0);

        drawCube(1.8, 0.9, 0.3);
        glTranslated(0, 2.4, 0);

        drawCube(1.8, 0.7, 0.3);
        glTranslated(1.8, -2.4, 0);

        drawCube(2.4, 3.1, 0.3);
        glTranslated(2.1, 0, 0.3);

        //sciana bok prawa
        drawCube(0.3, 3.1, 3);
        glTranslated(0, 0, 3);

        drawCube(0.3, 0.9, 1.8);
        glTranslated(0, 2.4, 0);

        drawCube(0.3, 0.7, 1.8);
        glTranslated(0, -2.4, 1.8);

        drawCube(0.3, 3.1, 2.9);
        glTranslated(0, 0, 2.6);

        //sciana przód
        drawCube(-1.8, 3.1, 0.3);
        glTranslated(-1.8, 0, 0);

        drawCube(-1.8, 0.9, 0.3);//okno
        glTranslated(0, 2.4, 0);

        drawCube(-1.8, 0.7, 0.3);//okno
        glTranslated(-1.8, -2.4, 0);

        drawCube(-1.4, 3.1, 0.3);
        glTranslated(-1.4, 2, 0);

        drawCube(-1.2, 1.1, 0.3); //drzwi
        glTranslated(-1.2, -2, 0);

        drawCube(-1.4, 3.1, 0.3);
        glTranslated(-1.4, 0, 0);

        drawCube(-1.8, 0.9, 0.3);//okno
        glTranslated(0, 2.4, 0);

        drawCube(-1.8, 0.7, 0.3);//okno
        glTranslated(-1.8, -2.4, 0);

        drawCube(-2.3, 3.1, 0.3);
        glTranslated(-2.3, 0, 0);

        //sciana bok lewa
        drawCube(0.3, 3.1, -2.7);
        glTranslated(0, 0, -2.7);

        drawCube(0.3, 0.9, -1.8);
        glTranslated(0, 2.4, 0);

        drawCube(0.3, 0.7, -1.8);
        glTranslated(0, -2.4, -1.8);

        drawCube(0.3, 3.1, -2.9);
        glTranslated(0, 0, -2.9);

       

        //okna
        glTranslated(2, 0.9, -0.3);
        drawWindow();

        glTranslated(5.8, 0, 0);
        drawWindow();

        glTranslated(4.2, 0, 3.3);
        glRotatef(-90, 0, 1, 0);
        drawWindow();
        glRotatef(90, 0, 1, 0);

        glTranslated(-2.1, 0, 4.7);
        glRotatef(180, 0, 1, 0);
        drawWindow();

        glTranslated(5.8, 0, 0);
        drawWindow();
        glRotatef(-180, 0, 1, 0);

        glTranslated(-4.1, 0, -3);
        glRotatef(90, 0, 1, 0);
        drawWindow();
        glRotatef(-90, 0, 1, 0);

        
        glColor3f(0.52, 0.1, 0);

        glTranslated(-0.6, 2.2, -5.6); //dach
        drawPyramid(13.2, 4, 9.2);

        glTranslated(6.1, -3.1, 8.3);

        drawDoor();

        glTranslated(-13, 0, -10);
        drawTree();

        glTranslated(26, 0, 0);
        drawTree();

        glColor3f(0.4, 0.4, 0.4);
        glTranslated(-12.9, 0, 10.6);

        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);

        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);

        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(-1.1, 0, 0);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(-1.1, 0, 0);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(-1.1, 0, 0);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);
        drawCube(0.95, 0.02, 0.95);
        glTranslated(0, 0, 1.1);
        drawCube(0.95, 0.02, 0.95);

        //glColor3f(1, 0, 0.6);
        //drawSphere(0.1, 15, 10);
        

    glPopMatrix();
}


void CameraInputs(GLFWwindow* window) {
    //Obsługa ruchu myszy
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (firstClick) {
            glfwSetCursorPos(window, (width / 2), (height / 2));
            firstClick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        Rot_x += sensitivity * (float)(mouseY - (height / 2)) / height;
        Rot_y += sensitivity * (float)(mouseX - (width / 2)) / width;

        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }

    //Poruszanie obserwatora
    Vec3 front;
    front.x = cos(degreesToRadians(Rot_y)) * cos(degreesToRadians(Rot_x));
    front.y = sin(degreesToRadians(Rot_x));
    front.z = sin(degreesToRadians(Rot_y)) * cos(degreesToRadians(Rot_x));
    front = front.normalize();

    Vec3 right = front.cross(Vec3(0, 1, 0)).normalize();
    Vec3 up = right.cross(front).normalize();

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        Tra_z -= speed * front.z;
        Tra_x -= speed * front.x;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        Tra_z += speed * front.z;
        Tra_x += speed * front.x;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Tra_z += speed * right.z;
        Tra_x += speed * right.x;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Tra_z -= speed * right.z;
        Tra_x -= speed * right.x;
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

        case GLFW_KEY_Q:
            Rot_z -= 2;
            break;

        case GLFW_KEY_E:
            Rot_z += 2;
            break;

        //Zmiana wyswietlania
        case GLFW_KEY_1:
            if (rzut == FRUST) {
                rzut = ORTO;
                cout << "ORTO  | Zmiana rzutowania" << endl;
            }
            else {
                rzut = FRUST;
                cout << "FRUST | Zmiana rzutowania" << endl;
            }
            break;

        case GLFW_KEY_2:
            if (skala == ASPECT_1_1) {
                skala = FULL_WINDOW;
                cout << "FULL  | Zmiana skali rysowania" << endl;
            }
            else {
                skala = ASPECT_1_1;
                cout << "ASPECT| Zmiana skali rysowania" << endl;
            }
            break;

        case GLFW_KEY_5:
            iCull = !iCull;
            if (iCull) {
                cout << "ON    | Ukrywanie niewidocznych powierzchni" << endl;
            }
            else {
                cout << "OFF   | Ukrywanie niewidocznych powierzchni" << endl;
            }
            break;
        case GLFW_KEY_6:
            iOutline = !iOutline;
            if (iOutline) {
                cout << "ON    | Zmiana wypelniania rysowania obiektow - linia" << endl;
            }
            else {
                cout << "OFF   | Zmiana wypelniania rysowania obiektow - wypelnienie" << endl;
            }
            break;
        case GLFW_KEY_7:
            iDepth = !iDepth;
            if (iDepth) {
                cout << "ON    | Mechanizm sprawdzania glebi" << endl; 
            }
            else {
                cout << "OFF   | Mechanizm sprawdzania glebi" << endl;
            }
            break;
        case GLFW_KEY_8:
            iClock = !iClock;
            if (iClock) {
                cout << "ON    | Zmiana nawijania rysowania trojkatow" << endl;
            }
            else {
                cout << "OFF   | Zmiana nawijania rysowania trojkatow" << endl;
            }
            break;
        case GLFW_KEY_9:
            iFill = !iFill;
            if (iFill) {
                cout << "ON    | Zmiana wypelniania kolorem - jednolite" << endl;
            }
            else {
                cout << "OFF   | Zmiana wypelniania kolorem - gladkie" << endl;
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

        case GLFW_KEY_B:
            fMocne_swiatlo[0] = 1.0f;
            fMocne_swiatlo[1] = 0.2f;
            fMocne_swiatlo[2] = 0.2f;

            fSlabe_swiatlo[0] = 0.2f;
            fSlabe_swiatlo[1] = 0.1f;
            fSlabe_swiatlo[2] = 0.1f;
            cout << "Swiatlo Czerwone" << endl;
            break;
        case GLFW_KEY_N:
            fMocne_swiatlo[0] = 0.2f;
            fMocne_swiatlo[1] = 1.0f;
            fMocne_swiatlo[2] = 0.2f;

            fSlabe_swiatlo[0] = 0.1f;
            fSlabe_swiatlo[1] = 0.2f;
            fSlabe_swiatlo[2] = 0.1f;
            cout << "Swiatlo Zielone" << endl;
            break;
        case GLFW_KEY_M:
            fMocne_swiatlo[0] = 0.2f;
            fMocne_swiatlo[1] = 0.2f;
            fMocne_swiatlo[2] = 1.0f;

            fSlabe_swiatlo[0] = 0.1f;
            fSlabe_swiatlo[1] = 0.1f;
            fSlabe_swiatlo[2] = 0.2f;
            cout << "Swiatlo Niebieskie" << endl;
            break;
        case GLFW_KEY_J:
            fMocne_swiatlo[0] = mocne_val;
            fMocne_swiatlo[1] = mocne_val;
            fMocne_swiatlo[2] = mocne_val;

            fSlabe_swiatlo[0] = slabe_val;
            fSlabe_swiatlo[1] = slabe_val;
            fSlabe_swiatlo[2] = slabe_val;
            cout << "Wartosci domyslne swiatla" << endl;

            break;

        case GLFW_KEY_C:
            fMocne_swiatlo[0] += 0.1f;
            fMocne_swiatlo[1] += 0.1f;
            fMocne_swiatlo[2] += 0.1f;
            fSlabe_swiatlo[0] += 0.04f;
            fSlabe_swiatlo[1] += 0.04f;
            fSlabe_swiatlo[2] += 0.04f;
            cout << "Mocne swiatlo: " << fMocne_swiatlo[0] << " " << fMocne_swiatlo[1] << " " << fMocne_swiatlo[2] << endl;
            cout << "Slabe swiatlo: " << fSlabe_swiatlo[0] << " " << fSlabe_swiatlo[1] << " " << fSlabe_swiatlo[2] << endl;
            cout << "------" << endl;

            break;
        case GLFW_KEY_V:
            fMocne_swiatlo[0] -= 0.1f;
            fMocne_swiatlo[1] -= 0.1f;
            fMocne_swiatlo[2] -= 0.1f;
            fSlabe_swiatlo[0] -= 0.04f;
            fSlabe_swiatlo[1] -= 0.04f;
            fSlabe_swiatlo[2] -= 0.04f;
            cout << "Mocne swiatlo: " << fMocne_swiatlo[0] << "\t" << fMocne_swiatlo[1] << "\t" << fMocne_swiatlo[2] << endl; 
            cout << "Slabe swiatlo: " << fSlabe_swiatlo[0] << "\t" << fSlabe_swiatlo[1] << "\t" << fSlabe_swiatlo[2] << endl;
            cout << "------" << endl;
            break;

        case GLFW_KEY_H:
            displayConsoleInfo();
            break;

        }
    }
}


int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(width, height, "Projekt GLFW - Dom", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    displayConsoleInfo();

    glfwMakeContextCurrent(window);

    //FPS counter
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
            string FPS = to_string( int((1.0 / timeDiff) * counter));
            string ms = to_string( (timeDiff / counter) * 1000);
            string newTitle = "Projekt GLFW - Dom \t" + FPS + " FPS, " + ms + "ms";
            glfwSetWindowTitle(window, newTitle.c_str());
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

        //przerzroczystosc
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //changing light settings
        if (lighting)
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

        //general light
        glLightfv(GL_LIGHT0, GL_AMBIENT, fSlabe_swiatlo); // światło otoczenia
        glLightfv(GL_LIGHT0, GL_DIFFUSE, fMocne_swiatlo); // światło rozproszenia
        glLightfv(GL_LIGHT0, GL_SPECULAR, fSlabe_swiatlo); // światło odbite

        //spotlight
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, angle_ref); // reflektor o kącie rozwarcia
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 30.0f); // stopień skupienia reflektora
        glLightfv(GL_LIGHT1, GL_AMBIENT, fSlabe_swiatlo); // światło otoczenia
        glLightfv(GL_LIGHT1, GL_DIFFUSE, fMocne_swiatlo); // światło rozproszenia
        glLightfv(GL_LIGHT1, GL_SPECULAR, fMocne_swiatlo); // światło odbite

        //fading light
        glLightfv(GL_LIGHT2, GL_AMBIENT, fSlabe_swiatlo); // światło otoczenia
        glLightfv(GL_LIGHT2, GL_DIFFUSE, fMocne_swiatlo); // światło rozproszenia
        glLightfv(GL_LIGHT2, GL_SPECULAR, fMocne_swiatlo); // światło odbite
        //glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 2.0f);
        glLighti(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.0f);
        //glLighti(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.03f);

        //materials
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_materials);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_materials);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular_materials);
        glMaterialfv(GL_FRONT, GL_SHININESS, shininess_materials);


        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}