#include <GLFW/glfw3.h> // Dołączenie nagłówka biblioteki GLFW do obsługi okien,

#include<iostream> 
using namespace std;

void display(float size) {



	/*
	glBegin(GL_QUADS); // Rozpoczęcie definiowania prymitywu GL_QUADS (czworokąta).
	glVertex3f(-20.0, -20.0, 0.0); // Dolny lewy wierzchołek
	glVertex3f(20.0, -20.0, 0.0); // Dolny prawy wierzchołek
	glVertex3f(20.0, 20.0, 0.0); // Górny prawy wierzchołek
	glVertex3f(-20.0, 20.0, 0.0); // Górny lewy wierzchołek
	glEnd();

	//punkt
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex3d(10, 0, 0);
	glEnd();


	glColor3d(0.0, 1.0, 1.0);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex3d(-10, 20, 0);
	glVertex3d(-10, 0, 0);
	glEnd();

	//trojkat
	glColor3d(1.0, 1.0, 0);
	glLineWidth(5);
	glBegin(GL_TRIANGLES);
	glVertex3d(-25, -25, 0);
	glVertex3d(-5, -25, 0);
	glVertex3d(-15, -5, 0);
	glEnd();

	//kwadrat
	glColor3d(1.0, 1.0, 0);
	glBegin(GL_QUADS);
	glVertex3d(5, -20, 0);
	glVertex3d(20, -20, 0);
	glVertex3d(20, -5, 0);
	glVertex3d(5, -5, 0);
	glEnd();

	//poligon
	glColor3d(0, 0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3d(5, 0, 0);
	glVertex3d(20, 0, 0);
	glVertex3d(25, 15, 0);
	glVertex3d(25, 20, 0);
	glVertex3d(5, 0, 0);
	glEnd();
	*/
	//0,1,0 zielony
	//0,0,1 niebieski
	//0,1,1 turkus
	//1,0,1 fiolet
	//1,1,0 zolty
	//0.5, 1,0
	 // Ustawienie koloru rysowania na czerwony.

	//punkty
	glColor3d(1, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3d(15, 0, 0);

	glVertex3d(-15, 0, 0);
	glEnd();

	glColor3d(0, 0, 1);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3d(0, -30, 0);
	glEnd();



	//linia
	glColor3d(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex3d(-30, -2, 0);
	glVertex3d(-30, 8, 0);

	glVertex3d(30, -2, 0);
	glVertex3d(30, 8, 0);
	glEnd();

	glColor3d(0, 1, 1);
	glLineWidth(7);
	glBegin(GL_LINES);
	glVertex3d(0, 15, 0);
	glVertex3d(0, 30, 0);
	glEnd();


	//trojkat
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
	glColor3d(1, 0, 0);  glVertex3d(0, 10, 0);
	glColor3d(0, 1, 0);  glVertex3d(-5, 0, 0);
	glColor3d(0, 0, 1);  glVertex3d(5, 0, 0);
	glEnd();


	//trojkat
	glColor3d(1.0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3d(-30, -20, 0);
	glVertex3d(-30, -30, 0);
	glVertex3d(-20, -30, 0);
	glEnd();

	//trojkat
	glColor3d(1.0, 0.5, 0);
	glBegin(GL_TRIANGLES);
	glVertex3d(30, -20, 0);
	glVertex3d(20, -30, 0);
	glVertex3d(30, -30, 0);
	glEnd();

	//kwadrat
	glColor3d(0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3d(-30, 30, 0);
	glVertex3d(-30, 20, 0);
	glVertex3d(-20, 20, 0);
	glVertex3d(-20, 30, 0);
	glEnd();

	//kwadrat
	glColor3d(0, 0, 1.0);
	glBegin(GL_QUADS);
	glVertex3d(20, 30, 0);
	glVertex3d(20, 20, 0);
	glVertex3d(30, 20, 0);
	glVertex3d(30, 30, 0);
	glEnd();

	//poligon
	glColor3d(0, 1.0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0, -7, 0);
	glVertex3d(-5, -10, 0);
	glVertex3d(-5, -15, 0);
	glVertex3d(0, -18, 0);
	glVertex3d(5, -15, 0);
	glVertex3d(5, -10, 0);
	glEnd();
}

// Definiowanie stałych dla właściwości światła
const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

// Definiowanie stałych dla właściwości materiału
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


int main(void)
{
	GLFWwindow* window; // Deklaracja wskaźnika na obiekt okna GLFW.

	if (!glfwInit()) // Inicjalizacja biblioteki GLFW. Jeśli inicjalizacja się nie powiedzie, program zakończy działanie z kodem - 1.
		return -1;
	// Utworzenie okna o rozmiarach 800x600 pikseli i tytule "Przykladowe Okno GLFW".
	// Ostatnie dwa argumenty dotyczą okna dzielonego i atrybutów kontekstu OpenGL, które są tutaj ustawione na NULL.
	window = glfwCreateWindow(800, 600, "Przykladowe Okno GLFW", NULL, NULL);

	if (!window) // Jeśli utworzenie okna się nie powiedzie, zakończenie działania GLFW i zwolnienie zasobów.
	{
		glfwTerminate();
		return -1;
	}

	// Ustawienie bieżącego kontekstu renderowania na utworzone okno.
	glfwMakeContextCurrent(window);
	// Pętla renderowania, wykonuje się dopóki okno nie zostanie zamknięte.
	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);// Pobranie rozmiaru bufora ramki dla bieżącego okna.
		
		glViewport(0, 0, width, height); // Ustawienie widoku portu do rozmiaru bufora ramki.
		
		glClear(GL_COLOR_BUFFER_BIT); // Czyszczenie bufora kolorów.
		
		glMatrixMode(GL_PROJECTION); // Ustawienie macierzy projekcji.
		glLoadIdentity(); // Zresetowanie macierzy projekcji do macierzy jednostkowej.

		// Ustawienie ortogonalnego widoku z proporcjami zależnymi od rozmiaru okna.
		glOrtho(-width / 20.0, width / 20.0, -height / 20.0, height / 20.0, -10.0, 10.0);

		
		glMatrixMode(GL_MODELVIEW); // Powrót do modelowania transformacji macierzy.

		// Obliczenie proporcjonalnego rozmiaru kwadratu.
		float squareSize = static_cast<float>(std::min(width, height)) * 0.2f;


		display(squareSize);// Wywołanie funkcji rysującej obiekty.

		glEnable(GL_CULL_FACE);
		
		glClearColor(1, 1, 1, 1); // Ustawienie koloru tła.
		
		glfwSwapBuffers(window); // Zamiana buforów w oknie.

		// Włączenie światła, normalizacji normalnych i materiałów koloru
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);

		// Ustawienie właściwości światła
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);

		// Ustawienie właściwości materiału
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		
		glfwPollEvents();// Przetwarzanie zdarzeń w kolejce zdarzeń.
	}

	
	glfwTerminate(); // Zakończenie działania GLFW i zwolnienie przydzielonych zasobów.
	return 0;
}