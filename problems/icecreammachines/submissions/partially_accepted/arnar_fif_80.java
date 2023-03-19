import java.util.*;
import java.math.*;
import java.io.*;

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

class FlavorTracker implements Comparable<FlavorTracker> {
    public int flavor;
    public LinkedList<Integer> indices;

    public FlavorTracker(int _flavor) {
        flavor = _flavor;
        indices = new LinkedList<Integer>();
    }

    @Override
    public boolean equals(Object o) {

        // If the object is compared with itself then return true  
        if (o == this) {
            return true;
        }

        /* Check if o is an instance of Complex or not
           "null instanceof [type]" also returns false */
        if (!(o instanceof FlavorTracker)) {
            return false;
        }

        // typecast o to Complex so that we can compare data members 
        FlavorTracker p = (FlavorTracker) o;

        // Compare the data members and return accordingly 
        return this.compareTo(p) == 0;
    }

    public int nextIndex() {
        if (indices.size() == 0) {
            return 10000000;
        }
        return indices.peekFirst();
    }

    public void advance() {
        indices.removeFirst();
    }

    public void add(int index) {
        indices.add(index);
    }

    @Override
    public int compareTo(FlavorTracker other) {
        int a = this.nextIndex();
        int b = other.nextIndex();
        return a == b ? Integer.compare(this.flavor, other.flavor) : Integer.compare(a, b);
    }

    @Override
    public int hashCode() {
        return Objects.hash(flavor, indices);
    }

    public String toString() {
        return String.format("%d %s", flavor, indices);
    }

}

public class arnar_fif_80 {
    public static void main(String[] args) throws Exception {
        Kattio io = new Kattio(System.in, System.out);

        int customerCount = io.getInt();
        int flavorCount = io.getInt();
        int machineCount = io.getInt();
        
        int switches = 0;
        ArrayList<Integer> choices = new ArrayList<Integer>();
        ArrayList<FlavorTracker> trackers = new ArrayList<FlavorTracker>();
        for (int i = 0; i < flavorCount; i++) {
            trackers.add(new FlavorTracker(i));
        }

        for (int i = 0; i < customerCount; i++) {
            int choice = io.getInt()-1;
            choices.add(choice);
            trackers.get(choice).add(i);
        }

        ArrayList<Integer> machines = new ArrayList<Integer>();
        for (int i = 0; i < machineCount; i++) {
            machines.add(-1);
        }

        for (int i = 0; i < customerCount; i++) {
            int choice = choices.get(i);
            trackers.get(choice).advance();
            int bestMachine = machines.indexOf(choice);
            if (bestMachine != -1) {
                continue;
            }
            bestMachine = 0;
            int bestIndex = 0;
            int startIndex = i+1;
            for (int machine = 0; machine < machineCount; machine++) {
                int flavor = machines.get(machine);
                int flavorIndex = flavor == -1 ? 10000000 : trackers.get(flavor).nextIndex();
                if (flavorIndex > bestIndex) {
                    bestIndex = flavorIndex;
                    bestMachine = machine;
                }
            }
            machines.set(bestMachine, choice);
            switches++;
        }

        io.println(switches);
        io.flush(); 
    }
}
