//package Kolos_Java;
//Do podanego powyżej kodu programu dodać następującą funcjonalność: jeżeli wylosowana liczba (number) jest większa niż 1000 to przypisz tą wylosowaną wartośc do pola value w zmiennej buffer i poinformuj o tym tylko jeden z oczekujących wątków. Zakładamy że wątki zdafiniowane przez klasę Workr zostały utworzone i jest ich więcej niż jeden oraz korzystają one z tego samego obiektu klasy Buffer, razem z wątkami oczekującymi na wystąpienie zdarzenia.

import java.io.*;

public class zad2 {
    
    class Buffer{
        public int value = 0;
    }

    class Worker extends Thread{
        private Buffer buffer;
        public Worker(Buffer b){
            buffer = b;
        }

        public void run(){
            int number = (int)(2000* Math.random());
            System.out.println("Wylosowana liczba: "+ number);

            synchronized (buffer){
                if(number > 1000){
                    buffer.value = number;
                    buffer.notify();
                }
            }

            synchronized (buffer){
                while (buffer.value <= 1000) {
                    try{
                        buffer.wait();
                    }
                    catch(InterruptedException e) {
                        e.printStackTrace();
                    }
                    
                }
            }
            System.out.println("Wartosc w buffer zmienila sie na: " + buffer.value);
        }
    }


    public static void main(String[] args) {
        System.out.println("Zad 2");
        zad2 program = new zad2();

        Buffer buffer = program.new Buffer();

        Thread t1 = program.new Worker(buffer);
        Thread t2 = program.new Worker(buffer);
        Thread t3 = program.new Worker(buffer);

        t1.start();
        t2.start();
        t3.start();
    }
}
