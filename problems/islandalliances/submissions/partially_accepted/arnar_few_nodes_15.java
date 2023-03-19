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

public class arnar_few_nodes_15 {
  public static void main(String[] args) throws Exception {
    Kattio io = new Kattio(System.in, System.out);
    
    int n = io.getInt();
    int m = io.getInt();
    int q = io.getInt();

    int[][] adj = new int[n][n];

    ArrayList<HashSet<Integer>> states = new ArrayList<>();
    for (int i = 0; i < n; i++) {
        states.add(new HashSet<Integer>());
        states.get(i).add(i);
    }

    for(int i = 0; i < m; i++) {
        int a = io.getInt() - 1;
        int b = io.getInt() - 1;
        adj[a][b] = 1;
        adj[b][a] = 1;
    }

    for(int query = 0; query < q; query++) {
        int a = io.getInt() - 1;
        int b = io.getInt() - 1;
        if(adj[a][b] == 1) {
            io.println("REFUSE");
        }
        else {
            io.println("APPROVE");
            HashSet<Integer> aSet = null, bSet = null;
            int[] overwrite = new int[n];
            for (HashSet<Integer> s : states) {
                if (s.contains(a)) {
                    aSet = s;
                }
                if (s.contains(b)) {
                    bSet = s;
                }
            }
            aSet.addAll(bSet);
            states.remove(bSet);
            for (int x : aSet) {
                for (int y = 0; y < n; y++) {
                    overwrite[y] |= adj[x][y];
                }
            }
            for (int x : aSet) {
                for (int y = 0; y < n; y++) {
                    adj[x][y] |= overwrite[y];
                    adj[y][x] |= overwrite[y];
                }
            }
        }
    }
    io.flush(); 
  }
}
