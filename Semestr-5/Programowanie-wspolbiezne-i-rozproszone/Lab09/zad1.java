import java.util.Random;

class MyThread extends Thread {
    public void run() {
        try {
            Random random = new Random();
            int sleepTime = random.nextInt(5001);
            Thread.sleep(sleepTime);

            System.out.println("Watek MyThread - czas wstrzymania: " + sleepTime + " ms");
        } catch (InterruptedException e) {
            System.out.println("Wątek MyThread przerwany.");
        }
    }
}

class MyRunnable implements Runnable {
    public void run() {
        try {
            Random random = new Random();
            int sleepTime = random.nextInt(5001);
            Thread.sleep(sleepTime);

            System.out.println("Watek MyRunnable - czas wstrzymania: " + sleepTime + " ms");
        } catch (InterruptedException e) {
            System.out.println("Wątek MyRunnable przerwany.");
        }
    }
}

public class zad1 {
    public static void main(String[] args) {
        System.out.println("Glowny watek: START");
        MyThread thread1 = new MyThread();
        thread1.start();

        MyRunnable myRunnable = new MyRunnable();
        Thread thread2 = new Thread(myRunnable);
        thread2.start();

        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            System.out.println("Wątek główny przerwany.");
        }

        System.out.println("Koniec programu");
    }
}
