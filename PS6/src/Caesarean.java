import java.io.*;
import java.util.*;

// write your matric number here:A0098997U
// write your name here:Mitchelle 
// write list of collaborators here (reading someone's post in Facebook group and using the idea is counted as collaborating):Eugene 

class Caesarean {
	private int V; // number of vertices in the graph (steps of a Caesarean section surgery)
	private int E; // number of edges in the graph (dependency information between various steps of a Caesarean section surgery)
	private Vector < IntegerPair > EL; // the unweighted graph, an edge (u, v) in EL implies that step u must be performed before step v
	private Vector < Integer > estT; // the estimated time to complete each step
	private boolean[] visited; 
	private Vector<Vector<Integer>> AdjList;
	private LinkedList < Integer > sortList;
	private int[] vcount;
	// if needed, declare a private data structure here that
	// is accessible to all methods in this class
	// --------------------------------------------



	// --------------------------------------------

	public Caesarean() {}

	int Query() {
		int ans = 0;
		int u, v,size,currmax, newmax, fork,currvcount,newvcount;

		Vector<Integer> arr = new Vector<Integer>();

		// You have to report the quickest time to complete the whole Caesarean section surgery
		// (from vertex 0 to vertex V-1)
		//
		// write your answer here
		vcount[0]=1;
		fork=1;
		dfs(0);

		for(int i=0;i<estT.size();i++){
			arr.add(0);
		}

		//		for(int i=0;i<EL.size();i++){
		//			int u=EL.get(i).first();
		//			int v=EL.get(i).second();
		//			int max=Math.max(estT.get(u)+arr.get(u), arr.get(v));
		//			arr.set(v, max);
		//		}		
		//		ans=arr.lastElement();

		while(!sortList.isEmpty()){
			
			u = sortList.pollLast();
			size=AdjList.get(u).size();
			
			if(size>1){ 
				fork= vcount[u]; 
			}

			for(int i=0;i<size;i++){
				v=AdjList.get(u).get(i);
				currvcount=vcount[v];
				newvcount=vcount[u]+1;
				currmax=arr.get(v);
				newmax=estT.get(u)+arr.get(u);

				if(newmax>currmax){

					arr.set(v, newmax);
					vcount[v]=newvcount;

				}
				else if (newmax==currmax)
				{
					arr.set(v, currmax);
					vcount[v]=currvcount+newvcount-fork-1;
				}
				else {
					arr.set(v, currmax);
				}

			}
		}
		//ans=arr.lastElement();

		ans=V-vcount[V-1];

		return ans;
	}

	// You can add extra function if needed
	// --------------------------------------------

	public void dfs(int u){

		visited[u]=true;

		Vector<Integer> N = AdjList.get(u);
		for(int i=0; i<N.size(); i++){
			int v = N.get(i); 

			if(visited[v] !=true){
				dfs(v);
			}
		}

		sortList.addLast(u);
	}
	// --------------------------------------------

	void run() throws Exception {
		IntegerScanner sc = new IntegerScanner(System.in);
		PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		int u, v;

		int TC = sc.nextInt(); // there will be several test cases
		while (TC-- > 0) {
			V = sc.nextInt(); E = sc.nextInt(); // read V and then E
			visited = new boolean[V];
			AdjList = new Vector<Vector<Integer>>();
			sortList = new LinkedList<Integer>();
			vcount = new int[V];

			estT = new Vector < Integer > ();
			for (int i = 0; i < V; i++){
				estT.add(sc.nextInt());
				AdjList.add(new Vector<Integer>());
			}

			// clear the graph and read in a new graph as an unweighted Edge List (only using IntegerPair, not IntegerTriple)
			EL = new Vector < IntegerPair > ();
			for (int i = 0; i < E; i++){
				u=sc.nextInt(); v=sc.nextInt();
				EL.add(new IntegerPair(u, v)); // just directed edge (u -> v)
				AdjList.get(u).add(v); //add new edge to v to a[u] in AdjList
			}
			pr.println(Query());
		}

		pr.close();
	}

	public static void main(String[] args) throws Exception {
		// do not alter this method
		Caesarean ps6 = new Caesarean();
		ps6.run();
	}
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
	int _first, _second;

	public IntegerPair(int f, int s) {
		_first = f;
		_second = s;
	}

	public int compareTo(IntegerPair o) {
		if (this.first() != o.first())
			return this.first() - o.first();
		else
			return this.second() - o.second();
	}

	int first() { return _first; }
	int second() { return _second; }
}
