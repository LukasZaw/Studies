
public class Main {

    public static void main(String[] args) {
        int ROZMIAR = 10;
        int tablica[] = new int[ROZMIAR];

        for (int i = 0; i < ROZMIAR; i++) {
            tablica[i] = i;
        }

        Watek w1 = new Watek(tablica, 0, ROZMIAR / 2);
        Watek w2 = new Watek(tablica, ROZMIAR / 2, ROZMIAR);

        w1.start();
        w2.start();

        try {
            w1.join();
            w2.join();
        } catch (InterruptedException e) {
            System.err.println(e);
        }

        System.err.println("Suma global: " + Watek.zwoc());
    }
}

class Watek extends Thread {
    private int[] tablica;
    private int start, koniec;
    static int suma_global = 0;

    public Watek(int[] tablica, int start, int koniec) {
        this.tablica = tablica;
        this.start = start;
        this.koniec = koniec;
    }

    public void run() {
        int suma = 0;
        for (int i = start; i < koniec; i++) {
            suma += tablica[i];
        }
        synchronized (Watek.currentThread()) {
            suma_global += suma;
        }
    }

    public static int zwoc() {
        return suma_global;
    }

}