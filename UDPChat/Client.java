import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Client{
public static void main (String args[])
{
Scanner sc=new Scanner(System.in);
String send,receive;
try{

DatagramSocket dsoc=new DatagramSocket(9099);
byte sbuf[]=new byte[1024];
byte rbuf[]=new byte[1024];

while(true){
System.out.print("Client: ");
send=sc.nextLine();
sbuf=send.getBytes();
DatagramPacket spkg = new DatagramPacket(sbuf,sbuf.length,InetAddress.getByName("127.0.0.1"),10000);
dsoc.send(spkg);

DatagramPacket rpkg = new DatagramPacket(rbuf,rbuf.length);
dsoc.receive(rpkg);
System.out.print("\nServer: "+new String(rpkg.getData())+"\n");
for(int i=0;i<1024;i++){
    rbuf[i] = '\0';
}
}
}

catch(Exception e){System.out.println(e);}
}
}
