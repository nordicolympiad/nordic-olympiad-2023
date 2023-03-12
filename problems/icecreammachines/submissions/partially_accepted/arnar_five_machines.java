import java.util.*;
import java.math.*;
import java.io.*;
class State {
    public int index;
    public int using;

    public State(int _index, int _using) {
        index = _index;
        using = _using;
    }

    @Override
    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }

        if (!(o instanceof State)) {
            return false;
        }

        State s = (State) o;

        return this.index == s.index && this.using == s.using;
    }

    @Override
    public int hashCode() {
        return Objects.hash(index, using);
    }

    public String toString() {
        return String.format("%d %d", index, using);
    }

}


public class arnar_five_machines {
    static int customerCount = 0, flavorCount = 0, machineCount = 0;
    static HashMap<State, Integer> mem;
    static ArrayList<Integer> choices;
    static PrintWriter out;
    
    public static ArrayList<State> switchOptions(State s, int flavor) {
        int index = s.index;
        int using = s.using;
        ArrayList<State> result = new ArrayList<State>();
        if (((using >> flavor) & 1) == 1) {
            result.add(new State(index + 1, using));
            return result;
        }
        ArrayList<Integer> setBits = new ArrayList<Integer>();
        for (int i = 0; i < flavorCount; i++) {
            if (((using >> i) & 1) == 1) {
                setBits.add(i);
            }
        }
        if (setBits.size() < machineCount) {
            result.add(new State(index + 1, using | (1 << flavor)));
            return result;
        }
        for (int i : setBits) {
            result.add(new State(index + 1, (using & ~(1 << i)) | (1 << flavor)));
        }
        return result;
    }
    
    static int dp(State state) {
        if (state.index == customerCount) {
            return 0;
        }
        if (mem.containsKey(state)) {
            return mem.get(state);
        }
        int result = 1000000000;
        int choice = choices.get(state.index);
        for (State next : switchOptions(state, choice)) {
            int cost = dp(next);
            if (state.using != next.using) {
                cost++;
            }
            result = Math.min(result, cost);
        }
        mem.put(state, result);
        return result;
    }
    
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        out = new PrintWriter(System.out, false);
        
        customerCount = in.nextInt();
        flavorCount = in.nextInt();
        machineCount = in.nextInt();

        mem = new HashMap<State, Integer>();
        choices = new ArrayList<Integer>();

        for (int i = 0; i < customerCount; i++) {
            choices.add(in.nextInt()-1);
        }

        out.println(dp(new State(0, 0)));
        out.flush(); 
    }
}
