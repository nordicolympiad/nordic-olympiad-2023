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

class UnionFind {
    ArrayList<Integer> p;
    ArrayList<HashSet<Integer>> adj;
    int n;
    public UnionFind(int n) {
        this.n = n;
        p = new ArrayList<Integer>();
        adj = new ArrayList<HashSet<Integer>>();
        for (int i = 0; i < n; i++) {
            p.add(-1);
            adj.add(new HashSet<Integer>());
        }
    }

    public void addEdge(int x, int y) {
        adj.get(x).add(y);
        adj.get(y).add(x);
    }

    public boolean distrusts(int x, int y) {
        return adj.get(find(x)).contains(find(y));
    }

    private void mergeAdj(int x, int y) {
        HashSet<Integer> xSet = adj.get(x), ySet = adj.get(y);
        for (int z : ySet) {
            adj.get(z).remove(y);
            adj.get(z).add(x);
            xSet.add(z);
        }
        ySet.clear();
    }

    public int find(int x) {
        if (p.get(x) < 0) {
            return x;
        }
        p.set(x, find(p.get(x)));
        return p.get(x);
    }

    public boolean unite(int x, int y) {
        int xp = find(x);
        int yp = find(y);
        if (xp == yp) {
            return false;
        }
        mergeAdj(xp, yp);
        p.set(xp, p.get(xp) + p.get(yp));
        p.set(yp, xp);
        return true; 
    }

    public boolean united(int x, int y) {
        return find(x) == find(y);
    }

    public int size(int x) {
        return -p.get(find(x)); 
    } 
}

public class arnar_uf_52 {
  public static void main(String[] args) throws Exception {
    Kattio io = new Kattio(System.in, System.out);
    
    int n = io.getInt();
    int m = io.getInt();
    int q = io.getInt();

    UnionFind uf = new UnionFind(n);

    for(int i = 0; i < m; i++) {
        int a = io.getInt() - 1;
        int b = io.getInt() - 1;
        uf.addEdge(a, b);
    }

    for(int query = 0; query < q; query++) {
        int a = io.getInt() - 1;
        int b = io.getInt() - 1;
        if(uf.distrusts(a, b)) {
            io.println("REFUSE");
        }
        else {
            io.println("APPROVE");
            uf.unite(a, b);
        }
    }
    io.flush(); 
  }
}
