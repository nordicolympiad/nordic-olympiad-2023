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
    int n;
    public UnionFind(int n) {
        this.n = n;
        p = new ArrayList<Integer>();
        for (int i = 0; i < n; i++) {
            p.add(-1);
        }
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

class Edge {
    public int u, v;
    public Edge(int _u, int _v) {
        u = _u;
        v = _v;
    }
}

public class arnar_bs_23 {
  public static void main(String[] args) throws Exception {
    Kattio io = new Kattio(System.in, System.out);
    
    int n = io.getInt();
    int m = io.getInt();
    int q = io.getInt();

    ArrayList<Edge> edges = new ArrayList<Edge>();
    ArrayList<Edge> queries = new ArrayList<Edge>();

    for(int i = 0; i < m; i++) {
        int a = io.getInt() - 1;
        int b = io.getInt() - 1;
        edges.add(new Edge(a, b));
    }

    for(int query = 0; query < q; query++) {
        int a = io.getInt() - 1;
        int b = io.getInt() - 1;
        queries.add(new Edge(a, b));
    }

    int lo = 0, hi = q;
    int best = 0;
    while (lo <= hi) {
        int mid = (lo + hi)/2;
        UnionFind uf = new UnionFind(n);
        for (int i = 0; i < mid; i++) {
            Edge query = queries.get(i);
            uf.unite(query.u, query.v);
        }
        boolean distrust = false;
        for (Edge e : edges) {
            distrust |= uf.united(e.u, e.v);
        }
        if (distrust) {
            hi = mid - 1;
        }
        else {
            best = mid;
            lo = mid + 1;
        }
    }


    for(int i = 0; i < best; i++) {
        io.println("APPROVE");
    }
    q -= best;
    if (q > 0) {
        io.println("REFUSE");
        q--;

    }
    for(int i = 0; i < q; i++) {
        io.println("APPROVE");
    }

    io.flush(); 
  }
}
