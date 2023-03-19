import java.util.*;
import java.math.*;
import java.io.*;
class State {
    public int index, machine1, machine2;

    public State() {
        index = 0;
        machine1 = 0;
        machine2 = 0;
    }

    public State(int _index, int _machine1, int _machine2) {
        index = _index;
        machine1 = _machine1;
        machine2 = _machine2;
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

        return this.index == s.index && this.machine1 == s.machine1 && this.machine2 == s.machine2;
    }

    @Override
    public int hashCode() {
        return Objects.hash(index, machine1, machine2);
    }

    public String toString() {
        return String.format("%d %d %d", index, machine1, machine2);
    }

}


public class arnar_two_machines_15 {
    static int customerCount = 0, flavorCount = 0, machineCount = 0;
    static HashMap<State, Integer> mem;
    static ArrayList<Integer> choices;
    static int dp(State state) {
        if (state.index == customerCount) {
            return 0;
        }
        if (mem.containsKey(state)) {
            return mem.get(state);
        }
        int choice = choices.get(state.index);
        int use1 = dp(new State(state.index + 1, choice, state.machine2));
        if (choice != state.machine1) use1++;
        int use2 = dp(new State(state.index + 1, state.machine1, choice));
        if (choice != state.machine2) use2++;
        int result = Math.min(use1, use2);
        mem.put(state, result);
        return result;
    }
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out, false);

        customerCount = in.nextInt();
        flavorCount = in.nextInt();
        machineCount = in.nextInt();

        mem = new HashMap<State, Integer>();
        choices = new ArrayList<Integer>();

        for (int i = 0; i < customerCount; i++) {
            choices.add(in.nextInt());
        }

        Stack<State> stack = new Stack<State>();
        State initialState = new State(0, -1, -1);
        stack.add(initialState);
        while(!stack.empty()) {
            State state = stack.peek();
            
            if (state.index == customerCount) {
                mem.put(state, 0);
                stack.pop();
                continue;
            }

            int choice = choices.get(state.index);

            State next1 = new State(state.index + 1, choice, state.machine2);
            State next2 = new State(state.index + 1, state.machine1, choice);
            if (!mem.containsKey(next1)) {
                stack.add(next1);
            }
            else if (!mem.containsKey(next2)) {
                stack.add(next2);
            }
            else {
                int use1 = mem.get(next1);
                if (choice != state.machine1) use1++;
                int use2 = mem.get(next2);
                if (choice != state.machine2) use2++;
                int result = Math.min(use1, use2);
                mem.put(state, result);
                stack.pop();
            }
        }

        out.println(mem.get(initialState));
        out.flush(); 
    }
}
