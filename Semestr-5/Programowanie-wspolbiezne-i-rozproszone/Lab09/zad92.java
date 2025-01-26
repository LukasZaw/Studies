public class zad92 {
    
    public static double funkcja(double x) {
        return Math.sqrt(1 - x * x);
    }

    public static double metodaTrapezow(double a, double b, int n) {
        double h = (b - a) / n;
        double suma = 0.5 * (funkcja(a) + funkcja(b));

        for (int i = 1; i < n; ++i) {
            suma += funkcja(a + i * h);
        }

        return suma * h;
    }

    public static double obliczPi(int n) {
        double a = -1;
        double b = 1;
        double pole = metodaTrapezow(a, b, n);
        return 2 * pole;
    }

    public static void main(String[] args) {
        int n = 1000000;

        Thread obliczaniePiWatek = new Thread(() -> {
            double pi = obliczPi(n);
            System.out.println("Pi: " + pi);
        });

        obliczaniePiWatek.start();

        try {
            obliczaniePiWatek.join();
        } catch (InterruptedException e) {
            System.err.println("error");
        }
    }
}
