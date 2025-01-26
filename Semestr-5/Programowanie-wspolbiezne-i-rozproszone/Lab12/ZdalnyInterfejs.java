import java.rmi.Remote;
import java.rmi.RemoteException;


public interface ZdalnyInterfejs extends Remote { 
    public String zdalnyKal(double a, double b) throws RemoteException;
}

class zdalnyKalkulator implements ZdalnyInterfejs
{
    public String zdalnyKal(double a, double b) throws RemoteException {
        return "Wynik Kalulatora dodawanie = " + (a + b);
    }
}
