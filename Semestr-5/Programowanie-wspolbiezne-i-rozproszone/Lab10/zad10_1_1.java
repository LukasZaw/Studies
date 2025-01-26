public class zad10_1_1 {
    private static final int ARRAY_SIZE = 1000000;
    private static final double P = 2.0; // Przykładowa wartość P

    public static double calculateSequentially(int[] array) {
        double result = 0.0;
        for (int i = 0; i < ARRAY_SIZE; i++) {
            result += P * Math.sin(i) + Math.log(i + 1);
        }
        return result;
    }

    public static void main(String[] args) {
        int[] array = new int[ARRAY_SIZE];
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = i + 1;
        }

        double result = calculateSequentially(array);
        System.out.println("Wynik sekwencyjny: " + result);
    }
}