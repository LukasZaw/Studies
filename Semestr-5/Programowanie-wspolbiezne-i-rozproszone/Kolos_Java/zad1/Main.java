class Skrzynka {
    private String wiadomosc;
    private boolean pusta = true;

    // Metoda do wysyłania wiadomości
    public synchronized void wyslijWiadomosc(String wiadomosc) throws InterruptedException {
        while (!pusta) {
            wait(); // Czekaj, aż wiadomość zostanie odebrana
        }
        this.wiadomosc = wiadomosc;
        pusta = false;
        notifyAll(); // Powiadom odbiorcę
    }

    // Metoda do odbierania wiadomości
    public synchronized String odbierzWiadomosc() throws InterruptedException {
        while (pusta) {
            wait(); // Czekaj, aż wiadomość zostanie wysłana
        }
        String wiadomoscOdebrana = wiadomosc;
        pusta = true;
        notifyAll(); // Powiadom nadawcę
        return wiadomoscOdebrana;
    }
}

class Nadawca implements Runnable {
    private Skrzynka skrzynka;

    public Nadawca(Skrzynka skrzynka) {
        this.skrzynka = skrzynka;
    }

    @Override
    public void run() {
        try {
            for (int i = 1; i <= 20; i++) {
                String wiadomosc = "Nadawca A, wiadomość " + i;
                System.out.println("Nadawca wysyła: " + wiadomosc);
                skrzynka.wyslijWiadomosc(wiadomosc);
                Thread.sleep((int) (Math.random() * 1000)); // Czas nadawcy (0-1000 ms)
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

class Odbiorca implements Runnable {
    private Skrzynka skrzynka;

    public Odbiorca(Skrzynka skrzynka) {
        this.skrzynka = skrzynka;
    }

    @Override
    public void run() {
        try {
            for (int i = 1; i <= 20; i++) {
                String wiadomosc = skrzynka.odbierzWiadomosc();
                System.out.println("Odbiorca odebrał: " + wiadomosc);
                Thread.sleep((int) (Math.random() * 300)); // Czas odbiorcy (0-300 ms)
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Skrzynka skrzynka = new Skrzynka();
        Thread nadawca = new Thread(new Nadawca(skrzynka));
        Thread odbiorca = new Thread(new Odbiorca(skrzynka));

        nadawca.start();
        odbiorca.start();
    }
}
