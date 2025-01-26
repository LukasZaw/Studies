import java.util.Scanner;

class Bufor {
    private Integer liczbaWejsciowa;
    private Integer wynikObliczen;

    public synchronized void ustawLiczbe(int liczba) throws InterruptedException {
        while (liczbaWejsciowa != null) {
            wait();
        }
        this.liczbaWejsciowa = liczba;
        notify();
    }

    public synchronized int pobierzLiczbe() throws InterruptedException {
        while (liczbaWejsciowa == null) {
            wait();
        }
        int liczba = liczbaWejsciowa;
        liczbaWejsciowa = null;
        notify();
        return liczba;
    }

    public synchronized void ustawWynik(int wynik) throws InterruptedException {
        while (wynikObliczen != null) {
            wait();
        }
        this.wynikObliczen = wynik;
        notify();
    }

    public synchronized int pobierzWynik() throws InterruptedException {
        while (wynikObliczen == null) {
            wait();
        }
        int wynik = wynikObliczen;
        wynikObliczen = null;
        notify();
        return wynik;
    }
}

class WatekWejscia extends Thread {
    private Bufor bufor;

    public WatekWejscia(Bufor bufor) {
        this.bufor = bufor;
    }

    @Override
    public void run() {
        Scanner scanner = new Scanner(System.in);
        for (int i = 0; i < 5; i++) {
            try {
                System.out.print("Podaj liczbe: ");
                int liczba = scanner.nextInt();
                bufor.ustawLiczbe(liczba);
                int wynik = bufor.pobierzWynik();
                System.out.println("Silnia: " + wynik);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        scanner.close();
    }
}

class WatekObliczen extends Thread {
    private Bufor bufor;

    public WatekObliczen(Bufor bufor) {
        this.bufor = bufor;
    }

    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            try {
                int liczba = bufor.pobierzLiczbe();
                int wynik = silnia(liczba);
                bufor.ustawWynik(wynik);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    private int silnia(int n) {
        int wynik = 1;
        for (int i = 1; i <= n; i++) {
            wynik *= i;
        }
        return wynik;
    }
}

public class Main {
    public static void main(String[] args) {
        Bufor bufor = new Bufor();

        WatekWejscia wejscie = new WatekWejscia(bufor);
        WatekObliczen obliczenia = new WatekObliczen(bufor);

        wejscie.start();
        obliczenia.start();
    }
}
