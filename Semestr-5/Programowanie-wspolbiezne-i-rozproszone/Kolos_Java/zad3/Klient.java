import java.rmi.Naming;

public class Klient {
    public static void main(String args[]) {
        try {
            ZdalnyInterfejs zObiekt = (ZdalnyInterfejs) Naming.lookup("ZdalnyObiekt");
            System.out.println(zObiekt.zdalnaMetoda(1, 5));
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}