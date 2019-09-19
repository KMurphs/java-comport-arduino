/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package FPRegister;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**
 *
 * @author johannesr
 */
// https://www.javatpoint.com/creating-thread
// https://medium.com/@ssaurel/create-a-simple-http-web-server-in-java-3fc12b29d5fd
//http://www.java2s.com/Code/Java/Network-Protocol/AverysimpleWebserverWhenitreceivesaHTTPrequestitsendstherequestbackasthereply.htm
public class webServerLauncher extends Thread{
	// port to listen connection
	static final int PORT = 8080;

      
        
    public void run(){  
        System.out.println("Java server thread is running...");  
try{
    ServerSocket ss = new ServerSocket(PORT);
    for(;;){
        // Wait for a client to connect. The method will block;
        // when it returns the socket will be connected to the client
        Socket client = ss.accept();

        // Get input and output streams to talk to the client
        BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
        PrintWriter out = new PrintWriter(client.getOutputStream());

        // Start sending our reply, using the HTTP 1.1 protocol
        out.print("HTTP/1.1 200 \r\n"); // Version & status code
        out.print("Content-Type: text/plain\r\n"); // The type of data
        out.print("Connection: close\r\n"); // Will close stream
        out.print("\r\n"); // End of headers

        // Now, read the HTTP request from the client, and send it
        // right back to the client as part of the body of our
        // response. The client doesn't disconnect, so we never get
        // an EOF. It does sends an empty line at the end of the
        // headers, though. So when we see the empty line, we stop
        // reading. This means we don't mirror the contents of POST
        // requests, for example. Note that the readLine() method
        // works with Unix, Windows, and Mac line terminators.
        String line;
        while ((line = in.readLine()) != null) {
          if (line.length() == 0)
            break;
          out.print(line + "\r\n");
        }
out.print("<h1>congatulations</h1>" + "\r\n");
        // Close socket, breaking the connection to the client, and
        // closing the input and output streams
        out.close(); // Flush and close the output stream
        in.close(); // Close the input stream
        client.close(); // Close the socket itself
    }
}catch (Exception e) {
 System.err.println(e);
      System.err.println("Usage: java HttpMirror <port>");   
}
     
    }  
    public void init(){  
        webServerLauncher t1=new webServerLauncher();  
        t1.start();  
    }  
}
/////___________________________________________________________________________________
