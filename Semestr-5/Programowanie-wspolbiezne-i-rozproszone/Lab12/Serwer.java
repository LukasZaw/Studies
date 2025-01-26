
import java.rmi.server.*;
import java.rmi.Naming;


public class Serwer {
    

    public static void main(String[] args) {
    try {
        zdalnyKalkulator zObiekt = new zdalnyKalkulator();
        UnicastRemoteObject.exportObject(zObiekt, 0);
        Naming.rebind("ZdalnyObiekt", zObiekt);
    }
        catch (Exception e) { System.out.println(e); }
    }
}