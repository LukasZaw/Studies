import java.rmi.Naming;

public class Klient
{
public static void main(String args[]) {
    try {
        ZdalnyInterfejs zObiekt = (ZdalnyInterfejs)Naming.lookup("ZdalnyObiekt");
        System.out.println(zObiekt.zdalnyKal(1, 3));
    }
        catch (Exception e){ System.out.println(e); }
    }
}