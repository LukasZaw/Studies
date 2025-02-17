class Skrzynka {
    private String wiadomosc = null;

    public synchronized void wyslijWiadomosc(String msg) throws InterruptedException {
        while (wiadomosc != null) {
            wait();
        }
        wiadomosc = msg;
        notify();
    }

    public synchronized String odbierzWiadomosc() throws InterruptedException {
        while (wiadomosc == null) {
            wait();
        }
        String msg = wiadomosc;
        wiadomosc = null;
        notify();
        return msg;
    }
}

class Nadawca extends Thread {
    private Skrzynka s;

    Nadawca(Skrzynka s) {
        this.s = s;
    }

    public void run() {
        int czas = (int) (Math.random() * 2000);
        try {
            for (int i = 0; i < 10; i++) {
                Thread.sleep(czas);
                s.wyslijWiadomosc("Nadawca N, wiadomosc " + i);
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}

class Odbiorca extends Thread {
    private Skrzynka s;

    Odbiorca(Skrzynka s) {
        this.s = s;
    }

    public void run() {
        int czas = (int) (Math.random() * 500);
        try {
            for (int i = 0; i < 10; i++) {
                Thread.sleep(czas);
                System.out.println(s.odbierzWiadomosc());
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Skrzynka s = new Skrzynka();
        Nadawca n = new Nadawca(s);
        Odbiorca o = new Odbiorca(s);

        n.start();
        o.start();

        try {
            n.join();
            o.join();
        } catch (InterruptedException ex) {
            System.out.println(ex);
        }

    }
}
