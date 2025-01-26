public class Main
{
    private static final int N = 1000000;
    private static double[] a = new double[N];

    public static void main(String[] args) {
        for (int i = 0; i < N; i++) {
            a[i] = i + 1;
        }

        long begin = System.currentTimeMillis();
        long end = System.currentTimeMillis();

        // Równolegle obliczanie bez sekcji krytycznej
        begin = System.currentTimeMillis();
        double resultParallelNoSync = calculateParallelNoSync();
        end = System.currentTimeMillis();
        System.out.println("Rownolegle bez sekcji krytycznej: " + resultParallelNoSync);
        System.out.println("Czas dzialania rownoleglego bez sekcji krytycznej: " + (end - begin));

        // Równolegle obliczanie z sekcją krytyczną w każdej iteracji
        begin = System.currentTimeMillis();
        double resultParallelWithSync = calculateParallelWithSync();
        end = System.currentTimeMillis();
        System.out.println("Rownolegle z sekcja krytyczna: " + Math.round(resultParallelWithSync));
        System.out.println("Czas dzialania rownoleglego z sekcja krytyczna: " + (end - begin));

        // Równolegle obliczanie z lokalną sumą i sekcją krytyczną na końcu
        begin = System.currentTimeMillis();
        double resultParallelWithLocalSum = calculateParallelWithLocalSum();
        end = System.currentTimeMillis();
        System.out.println("Rownolegle z lokalna suma i sekcja krytyczna: " + Math.round(resultParallelWithLocalSum));
        System.out.println("Czas dzialania rownoleglego z lokalna suma i sekcja krytyczna: " + (end - begin));
    }

    // Równolegle obliczanie bez sekcji krytycznej (błąd wyników oczekiwany)
    public static double calculateParallelNoSync() {
        final double[] sum = {0.0}; // Tablica sumy, aby była efektywnie finalna
        int chunkSize = N / 4;
        Thread[] threads = new Thread[4];

        for (int i = 0; i < 4; i++) {
            final int index = i;
            threads[i] = new Thread(() -> {
                int start = index * chunkSize;
                int end = (index + 1) * chunkSize;
                if (index == 3) end = N; // Ostatni wątek obejmuje resztę

                for (int j = start; j < end; j++) {
                    sum[0] += Math.sin(a[j]) + Math.log(a[j]);
                }
            });
            threads[i].start();
        }

        try {
            for (int i = 0; i < 4; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return sum[0];
    }

    // Równolegle obliczanie z sekcją krytyczną w każdej iteracji
    public static double calculateParallelWithSync() {
        final double[] sum = {0.0};
        int chunkSize = N / 4;
        Thread[] threads = new Thread[4];

        for (int i = 0; i < 4; i++) {
            final int index = i;
            threads[i] = new Thread(() -> {
                int start = index * chunkSize;
                int end = (index + 1) * chunkSize;
                if (index == 3) end = N;

                for (int j = start; j < end; j++) {
                    synchronized (Main.class) {
                        sum[0] += Math.sin(a[j]) + Math.log(a[j]);
                    }
                }
            });
            threads[i].start();
        }

        try {
            for (int i = 0; i < 4; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        return sum[0];
    }

    // Równolegle obliczanie z lokalną sumą i sekcją krytyczną na końcu
    public static double calculateParallelWithLocalSum() {
        final double[] sum = {0.0};
        int chunkSize = N / 4;
        Thread[] threads = new Thread[4];

        for (int i = 0; i < 4; i++) {
            final int index = i;
            threads[i] = new Thread(() -> {
                double localSum = 0.0;
                int start = index * chunkSize;
                int end = (index + 1) * chunkSize;
                if (index == 3) end = N;

                for (int j = start; j < end; j++) {
                    localSum += Math.sin(a[j]) + Math.log(a[j]);
                }

                synchronized (Main.class) {
                    sum[0] += localSum;
                }
            });
            threads[i].start();
        }

        try {
            for (int i = 0; i < 4; i++) {
                threads[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return sum[0];
    }
}