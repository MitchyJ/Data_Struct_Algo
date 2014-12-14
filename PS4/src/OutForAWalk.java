import java.util.*;
import java.io.*;

// write your matric number here:A0098997	
// write your name here:Mitchelle 
// write list of collaborators here (reading someone's post in Facebook Group/IVLE discussion forum and using the idea is counted as collaborating):Harry


class OutForAWalk {
	
	private int V; // number of vertices in the graph (number of rooms in the building)
	private Vector < Vector < IntegerPair > > AdjList;
	int curr, currW, start, neighbour;
	LinkedList < IntegerTriple > LL;
	
	boolean[] visited;
	int[][] maxW;
	
	

	public OutForAWalk() {}


	int Query(int source, int destination) {
		
		
		return maxW[source][destination];
	}

	public int findMax(int a, int b){
		if (a>b)
			return a;
		else 
			return b;
	}

	public void dfs(int t, int max){

		visited[t] = true;
		int x;

		for(int i=0; i<AdjList.get(t).size(); i++){
			neighbour = AdjList.get(t).get(i).first();
			currW = AdjList.get(t).get(i).second();

			if (visited[neighbour]==false){//not visited 
				x=findMax(currW,max); //return max value 

				maxW[curr][neighbour]=x;
				dfs(neighbour,x);
			}
		} 
	}

	public void preprocess(){

		Collections.sort(LL);

		UnionFind uf = new UnionFind(V); 

		while(uf.ufSize()>1 &&  LL.size()>0  ) { 
			IntegerTriple trp = LL.poll();
			
			int x = trp.second(), y = trp.third(), z = trp.first(); 
			
			if (!uf.isSameSet(x, y)) {
				AdjList.get(x).add(new IntegerPair(y,z));
				AdjList.get(y).add(new IntegerPair(x,z));
				uf.unionSet(x, y); 
			}
		}


		if(V<10){
			start = V;
		}
		else { 
			start = 10;
		}
		maxW = new int[start][V];

		for (int i=0;i<start;i++){
			curr=i;
			visited = new boolean[V];
			dfs(i,0);
		}

	}



	void run() throws Exception {

		IntegerScanner sc = new IntegerScanner(System.in);
		PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		

		int TC = sc.nextInt();
		while (TC-- > 0) {
			V = sc.nextInt();
			LL = new LinkedList < IntegerTriple >();
			
			 AdjList = new Vector < Vector < IntegerPair > >();
			for (int i = 0; i < V; i++) {
				  AdjList.add(new Vector<IntegerPair>());
				  
				   int k = sc.nextInt();
			        while (k-- > 0) {
			          int j = sc.nextInt(), w = sc.nextInt();
			          //AdjList.get(i).add(new IntegerPair(j, w)); // edge (corridor) weight (effort rating) is stored here
			          LL.add(new IntegerTriple(w,i,j));
			        }
			}

			preprocess();

			int Q = sc.nextInt();
			while (Q-- > 0)
				pr.println(Query(sc.nextInt(), sc.nextInt()));
			pr.println();
		}
		pr.close();
	}
	public static void main(String[] args) throws Exception {
		// do not alter this method
		OutForAWalk ps4 = new OutForAWalk();
		ps4.run();
	}
}

class UnionFind {                                              // OOP style
	  private Vector<Integer> p, rank, setSize;
	  private int numSets;

	  public UnionFind(int N) {
	    p = new Vector<Integer>(N);
	    rank = new Vector<Integer>(N);
	    setSize = new Vector<Integer>(N);
	    numSets = N;
	    for (int i = 0; i < N; i++) {
	      p.add(i);
	      rank.add(0);
	      setSize.add(1);
	    }
	  }

	  public int findSet(int i) { 
	    if (p.get(i) == i) return i;
	    else {
	      int ret = findSet(p.get(i)); p.set(i, ret);
	      return ret; } }

	  public Boolean isSameSet(int i, int j) { return findSet(i) == findSet(j); }

	  public void unionSet(int i, int j) { 
	    if (!isSameSet(i, j)) { numSets--; 
	    int x = findSet(i), y = findSet(j);
	    // rank is used to keep the tree short
	    if (rank.get(x) > rank.get(y)) { p.set(y, x); setSize.set(x, setSize.get(x) + setSize.get(y)); }
	    else                           { p.set(x, y); setSize.set(y, setSize.get(y) + setSize.get(x));
	                                     if (rank.get(x) == rank.get(y)) rank.set(y, rank.get(y) + 1); } } }
	  public int numDisjointSets() { return numSets; }
	  public int sizeOfSet(int i) { return setSize.get(findSet(i)); }
	  public int ufSize(){return numSets;}
	}



class IntegerScanner { // coded by Ian Leow, using any other I/O method is not recommended
	BufferedInputStream bis;
	IntegerScanner(InputStream is) {
		bis = new BufferedInputStream(is, 1000000);
	}

	public int nextInt() {
		int result = 0;
		try {
			int cur = bis.read();
			if (cur == -1)
				return -1;

			while ((cur < 48 || cur > 57) && cur != 45) {
				cur = bis.read();
			}

			boolean negate = false;
			if (cur == 45) {
				negate = true;
				cur = bis.read();
			}

			while (cur >= 48 && cur <= 57) {
				result = result * 10 + (cur - 48);
				cur = bis.read();
			}

			if (negate) {
				return -result;
			}
			return result;
		}
		catch (IOException ioe) {
			return -1;
		}
	}
}

class IntegerPair implements Comparable<IntegerPair> {
	Integer _first, _second;

	public IntegerPair(Integer f, Integer s) {
		_first = f;
		_second = s;
	}

	public int compareTo(IntegerPair o) {
		if (!this.first().equals(o.first()))
			return this.first() - o.first();
		else
			return this.second() - o.second();
	}

	Integer first() { return _first; }
	Integer second() { return _second; }
}



class IntegerTriple implements Comparable<IntegerTriple> {
	Integer _first, _second, _third;

	public IntegerTriple(Integer f, Integer s, Integer t) {
		_first = f;
		_second = s;
		_third = t;
	}

	public int compareTo(IntegerTriple o) {
		if (!this.first().equals(o.first()))
			return this.first() - o.first();
		else if (!this.second().equals(o.second()))
			return this.second() - o.second();
		else
			return this.third() - o.third();
	}

	Integer first() { return _first; }
	Integer second() { return _second; }
	Integer third() { return _third; }

	
}
