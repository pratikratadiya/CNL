import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Server{
public static void main (String args[])
{
Scanner sc=new Scanner(System.in);
String send,receive;
try{

DatagramSocket dsoc=new DatagramSocket(10000);
byte sbuf[]=new byte[1024];
byte rbuf[]=new byte[1024];


while(true){

DatagramPacket rpkg = new DatagramPacket(rbuf,rbuf.length);
dsoc.receive(rpkg);
System.out.print("Client: "+new String(rpkg.getData())+"\n");
for(int i=0;i<1024;i++){
    rbuf[i] = '\0';
}

System.out.print("\nServer: ");
send=sc.nextLine();
sbuf=send.getBytes();
DatagramPacket spkg = new DatagramPacket(sbuf,sbuf.length,InetAddress.getByName("127.0.0.1"),9099);
dsoc.send(spkg);

}
}

catch(Exception e){System.out.println(e);}
}
}
