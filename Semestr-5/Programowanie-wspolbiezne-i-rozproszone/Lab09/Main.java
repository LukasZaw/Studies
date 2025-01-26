class MyThread extends Thread {
    public void run() {
        try {
            int czekaj =(int)(Math.random()*5000+0);
            Thread.sleep(czekaj);
            System.out.println("Numer 1: " + czekaj + " milisekund");
        }
        catch(InterruptedException e) {}
    }
}

class MySecondThreat implements Runnable {
    public void run() {
        try {
            int czekaj =(int)(Math.random()*5000+0);
            Thread.sleep(czekaj);
            System.out.println("Numer 2: " + czekaj + " milisekund");
        }
        catch(InterruptedException e) {}
    }
}

class Main {
    public static void main(String args[]) {

        Thread thread1 = new MyThread();
        MySecondThreat object = new MySecondThreat();
        Thread thread2 = new Thread(object);

        thread1.start();
        try {
            thread1.join();
        }
        catch(InterruptedException e) {}
        
        thread2.run();
        try {
            thread2.join();
        }
        catch(InterruptedException e) {}

        System.out.println("Koniec programu");
    }
}