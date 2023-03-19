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

class Kattio extends PrintWriter {
    public Kattio(InputStream i) {
        super(new BufferedOutputStream(System.out));
        r = new BufferedReader(new InputStreamReader(i));
    }
    public Kattio(InputStream i, OutputStream o) {
        super(new BufferedOutputStream(o));
        r = new BufferedReader(new InputStreamReader(i));
    }

    public boolean hasMoreTokens() {
        return peekToken() != null;
    }

    public int getInt() {
        return Integer.parseInt(nextToken());
    }

    public double getDouble() {
        return Double.parseDouble(nextToken());
    }

    public long getLong() {
        return Long.parseLong(nextToken());
    }

    public String getWord() {
        return nextToken();
    }

    private BufferedReader r;
    private String line;
    private StringTokenizer st;
    private String token;

    private String peekToken() {
        if (token == null)
            try {
                while (st == null || !st.hasMoreTokens()) {
                    line = r.readLine();
                    if (line == null) return null;
                    st = new StringTokenizer(line);
                }
                token = st.nextToken();
            } catch (IOException e) { }
        return token;
    }

    private String nextToken() {
        String ans = peekToken();
        token = null;
        return ans;
    }
}

public class arnar_five_machines_35 {
    static int customerCount = 0, flavorCount = 0, machineCount = 0;
    static HashMap<State, Integer> mem;
    static ArrayList<Integer> choices;
    static Kattio io;
    
    static int dp(State state) {
        int index = state.index;
        int using = state.using;
        if (index == customerCount) {
            return 0;
        }
        if (mem.containsKey(state)) {
            return mem.get(state);
        }
        int result = 1000000000;
        int choice = choices.get(index);
        if (((using >> choice) & 1) == 1) {
            result = dp(new State(index + 1, using));
        }
        else if (Integer.bitCount(using) < machineCount) {
            result = dp(new State(index + 1, using | (1 << choice))) + 1;
        }
        else {
            for (int i = 0; i < flavorCount; i++) {
                if (((using >> i) & 1) == 1) {
                    State next = new State(index + 1, (using & ~(1 << i)) | (1 << choice));
                    result = Math.min(result, dp(next) + 1);
                }
            }
        }
        mem.put(state, result);
        return result;
    }
    
    public static void main(String[] args) throws Exception {
        io = new Kattio(System.in, System.out);
        
        customerCount = io.getInt();
        flavorCount = io.getInt();
        machineCount = io.getInt();

        mem = new HashMap<State, Integer>(customerCount, 0.5f);
        choices = new ArrayList<Integer>();

        for (int i = 0; i < customerCount; i++) {
            choices.add(io.getInt()-1);
        }

        for(int i = customerCount - 1; i > 0; i-=10) {
            dp(new State(i, 0));
        }

        io.println(dp(new State(0, 0)));
        io.flush(); 
    }
}
