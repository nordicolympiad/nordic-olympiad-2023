import java.util.*;
import java.math.*;
import java.io.*;
public class arnar_slow_fif_55 {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out, false);

        int customerCount = in.nextInt();
        int flavorCount = in.nextInt();
        int machineCount = in.nextInt();
        
        int switches = 0;
        ArrayList<Integer> choices = new ArrayList<Integer>();
        for (int i = 0; i < customerCount; i++) {
            choices.add(in.nextInt()-1);
        }

        ArrayList<Integer> machines = new ArrayList<Integer>();
        for (int i = 0; i < machineCount; i++) {
            machines.add(-1);
        }
        for (int i = 0; i < customerCount; i++) {
            int choice = choices.get(i);
            int bestMachine = machines.indexOf(choice);
            if (bestMachine != -1) {
                continue;
            }
            bestMachine = 0;
            int bestIndex = 0;
            int startIndex = i+1;
            for (int machine = 0; machine < machineCount; machine++) {
                int flavor = machines.get(machine);
                int flavorIndex = choices.subList(startIndex, customerCount).indexOf(flavor);
                if (flavorIndex == -1) {
                    flavorIndex = customerCount;
                }
                flavorIndex += startIndex;
                if (flavorIndex > bestIndex) {
                    bestIndex = flavorIndex;
                    bestMachine = machine;
                }
            }
            machines.set(bestMachine, choice);
            switches++;
        }
        out.println(switches);
        out.flush(); 
    }
}
