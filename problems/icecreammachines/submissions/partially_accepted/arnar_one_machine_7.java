import java.util.*;
import java.math.*;
import java.io.*;
public class arnar_one_machine_7 {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out, false);

        int customerCount = in.nextInt();
        int flavorCount = in.nextInt();
        int machineCount = in.nextInt();

        int lastChoice = -1, switches = 0;
        for (int i = 0; i < customerCount; i++) {
            int customerChoice = in.nextInt();
            if (lastChoice != customerChoice) {
                switches++;
            }
            lastChoice = customerChoice;
        }
        out.println(switches);
        out.flush(); 
    }
}
