import java.rmi.Naming;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

//klient
public class Klient {
    public static void main(String[] args) {
        try {
            ZdalnyInterfejs zObiekt = (ZdalnyInterfejs) Naming.lookup("stats");
            System.out.println(zObiekt.srednia(1, 3));
        } catch (Exception e) {
        }

    }
}

// serwer
public class Serwer {
    public static void main(String[] args) {
        try {
            ZdalnyObiekt zObiekt = new ZdalnyObiekt();
            UnicastRemoteObject.exportObject(zObiekt, 0);
            Naming.rebind("stats", zObiekt);
        } catch (Exception e) {
        }

    }
}

// interface
public interface ZdalnyInterfejs extends Remote {
    public String srednia(double a, double b) throws RemoteException;
}

class ZdalnyObiekt implements ZdalnyInterfejs {

    public String srednia(double a, double b) throws RemoteException {
        return "Srednia: " + (a + b);
    }
}