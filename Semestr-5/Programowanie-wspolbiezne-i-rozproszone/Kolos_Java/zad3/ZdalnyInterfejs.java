import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ZdalnyInterfejs extends Remote {
    public String zdalnaMetoda(int a, int b) throws RemoteException;
}

class ZdalnyObiekt implements ZdalnyInterfejs {
    public String zdalnaMetoda(int a, int b) throws RemoteException {
        return "Wynik dodawania " + (a + b);
    }
}