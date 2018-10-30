import java.net.*; 
import java.util.*; 

public class IPDemo 
{ 
	public static String host,ipaddress; 
	public static Scanner input;
	public IPDemo(){
		host = new String();
		ipaddress = new String();
	}

	public static void main(String[] args){
		IPDemo ipdemo = new IPDemo(); 
		input = new Scanner(System.in); 
		int options;
		System.out.println("1.URL to IP");
		System.out.println("2.IP to URL");
		System.out.println("3.Exit");
		System.out.println("Enter Options");
		options = input.nextInt();

		switch (options) {
			case 1:
					ipdemo.URLtoIp();
					break;
			case 2:
					ipdemo.IPtoURL();
					break;
			case 3:
					System.exit(0);
		}


	} 

	public  void URLtoIp(){
		System.out.print("\n Enter host name: ");
		input.nextLine(); 
		host = input.nextLine(); 
		try { 
			InetAddress address = InetAddress.getByName(host);
			System.out.println("IP address: " + address.getHostAddress());
		} 
		catch (UnknownHostException ex) {
		     System.out.println("Could not find "); 
		}
	}

	public void IPtoURL(){
		System.out.print("\n Enter IPadress: ");
		input.nextLine();
		ipaddress = input.nextLine(); 
		try { 
			InetAddress host1 = InetAddress.getByName(ipaddress);
			System.out.println(host1.getHostName());
		} 
		catch (UnknownHostException ex) {
		     System.out.println("Could not find " ); 
		}

	}

}
