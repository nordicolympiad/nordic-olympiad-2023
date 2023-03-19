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

    private int find(int x) {
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
        if (p.get(xp) > p.get(yp)) {
            int tmp = yp;
            yp = xp;
            xp = tmp;
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

class Edge implements Comparable<Edge> {
    int u, v;
    public Edge(int u, int v) {
        this.u = u;
        this.v = v;
    }
    @Override
    public int compareTo(Edge other) {
        int res = Integer.compare(u, other.u);
        if(res == 0) {
            return Integer.compare(v, other.v);
        }
        return res;
    }
}


public class arnar_few_edges_17 {
  public static void main(String[] args) throws Exception {
    Kattio io = new Kattio(System.in, System.out);
    
    int n = io.getInt();
    int m = io.getInt();
    int q = io.getInt();

    UnionFind uf = new UnionFind(n);
    ArrayList<Edge> edges = new ArrayList<Edge>();

    for(int i = 0; i < m; i++) {
        int a = io.getInt() - 1;
        int b = io.getInt() - 1;
        edges.add(new Edge(a, b));
        edges.add(new Edge(b, a));
    }

    for(int query = 0; query < q; query++) {
        int a = io.getInt() - 1;
        int b = io.getInt() - 1;
        boolean ok = true;
        for (Edge e : edges) {
            if (uf.united(e.u, a) && uf.united(e.v, b)) {
                ok = false;
            }
        }
        if(!ok) {
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
