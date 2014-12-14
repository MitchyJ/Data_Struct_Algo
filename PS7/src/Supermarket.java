import java.util.*;
import java.io.*;

// write your matric number here:A0098997
// write your name here:
// write list of collaborators here (reading someone's post in Facebook group/IVLE discussion forum and using the idea is counted as collaborating):

class Supermarket {
	private int N; // number of items in the supermarket. V = N+1 
	private int K; // the number of items that Steven has to buy
	private int[] shoppingList; // indices of items that Steven has to buy
	private int[][] T; // the complete weighted graph that measures the direct walking time to go from one point to another point in seconds

	private int[][] reduced ; 
	private int[][] memo; 
	private PriorityQueue<IntegerPair> pq; 

	private int INFI = 1000000; 

	public Supermarket() {}


	int Query() {
		memo = new int[K+1][(int)Math.pow(2,K+1)];
		for (int[] row: memo){
			Arrays.fill(row,-1);  
		}

		dijks(); 
		T = reduced ; 

		int ans = tsp(0,1);

		return ans;
	}
	
	public int tsp(int u, int t){
		if(t == (1<<(K+1))-1){//all 1 in binary, all vertices visited.
			return T[u][0];
		}

		if(memo[u][t] != -1){ 
			return memo[u][t];
		}

		//general case.
		int temp = INFI;
		for(int i=0; i<K+1; i++){
			if ((i!=u) && ( (t & (1<<i)) == 0)){
				temp = Math.min(temp, T[u][i] + tsp(i, t|(1<<i)) );
			}
		}
		memo[u][t] = temp;
		return temp;

	}
	public void dijks(){
		int V = K+1; 
		boolean[] visited = new boolean[N+1];
		int[] items = Arrays.copyOf(shoppingList, V);
		HashMap<Integer, Integer> hm = new HashMap<Integer, Integer>();
		int[] dist = new int[N+1];
		pq = new PriorityQueue<IntegerPair>(); 
		reduced  = new int[K+1][K+1];

		int next, u, weight;
		IntegerPair front;


		for(int i=0; i<V; i++){
			hm.put(items[i], i);
		}

		for(int i=0; i<V; i++){ 

			Arrays.fill(dist, INFI);
			Arrays.fill(visited,false);

			int item = items[i];
			reduced [i][i] = 0;
			pq.offer(new IntegerPair(item,0));
			dist[item]=0;

			while(!pq.isEmpty()){
				front=pq.poll();
				u=front.first(); 
				next=front.second();

				if(!visited[u]){
					visited[u]=true;

					for(int j=0; j<N+1; j++){ //find shortest path
						if(u!=j){
							weight = T[u][j] + next;

							if(weight<dist[j]){
								if(hm.containsKey(j)){
									reduced [i][hm.get(j)] = weight; //update shortest distance 
								}
								dist[j]=weight; 
								pq.offer(new IntegerPair(j, weight));
							}

						}
					}
				}
			}
		}


	}

	void run() throws Exception {
		// do not alter this method to standardize the I/O speed (this is already very fast)
		IntegerScanner sc = new IntegerScanner(System.in);
		PrintWriter pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

		int TC = sc.nextInt(); // there will be several test cases
		while (TC-- > 0) {
			// read the information of the complete graph with N+1 vertices
			N = sc.nextInt(); K = sc.nextInt(); // K is the number of items to be bought

			shoppingList = new int[K];
			for (int i = 0; i < K; i++)
				shoppingList[i] = sc.nextInt();

			T = new int[N+1][N+1];
			for (int i = 0; i <= N; i++)
				for (int j = 0; j <= N; j++)
					T[i][j] = sc.nextInt();

			pw.println(Query());
		}

		pw.close();
	}

	public static void main(String[] args) throws Exception {
		// do not alter this method
		Supermarket ps7 = new Supermarket();
		ps7.run();
	}
}


class IntegerPair implements Comparable<IntegerPair> {
	Integer _first, _second;

	public IntegerPair(Integer f, Integer s) {
		_first = f;
		_second = s;
	}

	public int compareTo(IntegerPair o) {
		if (!this._second.equals(o.second()))
			return this._second - o.second();
		else
			return this._first - o.first();
	}

	Integer first() { return _first; }
	Integer second() { return _second; }

}



class IntegerScanner { // coded by Ian Leow for PS4
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