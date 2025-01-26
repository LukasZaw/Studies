public class zad2 {

    private static final int N = 1000000;
    private static final int NUM_THREADS = 4;

    private static double sum = 0.0;

    public static void main(String[] args) {

        long tBegin = System.currentTimeMillis();
        double piSequential = calculatePiSequential();
        long tEnd = System.currentTimeMillis();
        System.out.println("Sekwencyjnie: " + piSequential);
        System.out.println("Czas dzialania sekwencyjnego: " + (double) (tEnd - tBegin) / 1000 + " sekundy");

        tBegin = System.currentTimeMillis();
        double piParallel = calculatePiParallel();
        tEnd = System.currentTimeMillis();
        System.out.println("Rownolegle: " + piParallel);
        System.out.println("Czas dzialania rownoleglego: " + (double) (tEnd - tBegin) / 1000 + " sekundy");
    }

    public static double calculatePiSequential() {
        double sum = 0.0;
        double h = 2.0 / N;

        for (int i = 0; i < N; i++) {
            double x = -1 + i * h;
            sum += Math.sqrt(1 - x * x);
        }
        return 2 * h * sum;
    }

    public static double calculatePiParallel() {
        double h = 2.0 / N;
        int chunkSize = N / NUM_THREADS;

        for (int i = 0; i < NUM_THREADS; i++) {
            final int index = i;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    double localSum = 0.0;
                    int start = index * chunkSize;
                    int end = (index + 1) * chunkSize;
                    if (index == NUM_THREADS - 1) {
                        end = N;
                    }

                    for (int j = start; j < end; j++) {
                        double x = -1 + j * h;
                        localSum += Math.sqrt(1 - x * x);
                    }

                    synchronized (zad2.class) {
                        sum += localSum;
                    }
                }
            }).start();
        }

        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return 2 * h * sum;
    }
}