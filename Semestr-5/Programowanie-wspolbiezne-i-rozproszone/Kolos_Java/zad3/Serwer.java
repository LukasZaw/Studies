import java.rmi.Naming;
import java.rmi.server.UnicastRemoteObject;

public class Serwer {
    public static void main(String[] args) {
        try {
            ZdalnyObiekt zObiekt = new ZdalnyObiekt();
            UnicastRemoteObject.exportObject(zObiekt, 0);
            Naming.rebind("ZdalnyObiekt", zObiekt);
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}