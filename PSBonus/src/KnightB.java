import java.util.*;
import java.io.*;
import java.math.BigInteger;

//Name of collaborator: Eugene

class KnightB{

	public static void main(String[] args) throws Exception {
		Scanner sc = new Scanner(System.in); 
		while (sc.hasNextBigInteger()) {
			long val=4,val1=7,val2=1;
			BigInteger a = sc.nextBigInteger();	

			BigInteger bi1= BigInteger.valueOf(val);
			BigInteger bi2= BigInteger.valueOf(val1);
			BigInteger bi3= BigInteger.valueOf(val2);

			if(a.toString().equals("1"))
			{
				System.out.println(8);
			}//break;
			else if(a.toString().equals("2"))
			{
				System.out.println(33);
			}//break;
			else{
				BigInteger ans = bi3.add(bi1.multiply(a).add(bi2.multiply(a).multiply(a)));
				System.out.println(ans);
			}//break;


		}
		sc.close();
	}

}


