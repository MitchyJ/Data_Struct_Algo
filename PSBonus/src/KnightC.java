import java.util.*;
import java.io.*;
import java.math.*;

//Name of collaborator: Eugene

class KnightC{
	private static int[] container;

	public static void main(String[] args) throws Exception {
		//Scanner sc1 = new Scanner(System.in);

		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter pr = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
		int TC = Integer.parseInt(br.readLine()); // there will be several test cases
		while (TC-- > 0) {
			br.readLine(); // ignore dummy blank line
			int N = Integer.parseInt(br.readLine());
			int Q = Integer.parseInt(br.readLine());
			container = new int[Q];
			for (int i = 0; i < Q; i++){
				container[i] = Integer.parseInt(br.readLine());
			}

		}
		
	//int a= Dist(container[0],container[1],container[2],container[3] );	
	//System.out.println(a);
	}

	static //Infinite chessboard distance between 2 cells.
	int Dist(int x1, int y1, int x2, int y2)
	{

		int dx= Math.abs(x2-x1);
		int dy= Math.abs(y2-y1);
		int lb=(dx+1)/2;


		if(lb>((dy+1)/2)){
			lb=(dy+1)/2;
		}

		if(lb>(dx+dy+2)/3){
			lb=(dx+dy+2)/3;
		}

		while ((lb%2)!=(dx+dy)%2) lb++;
		if (Math.abs(dx)==1 && dy==0) return 3;
		if (Math.abs(dy)==1 && dx==0) return 3;
		if (Math.abs(dx)==2 && Math.abs(dy)==2) return 4;
		return lb;
	}

}




