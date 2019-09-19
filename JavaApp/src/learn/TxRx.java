/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author johannesr
 */

package learn;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;

/**
 * This version of the TwoWaySerialComm example makes use of the 
 * SerialPortEventListener to avoid polling.
 *
 */
// http://rxtx.qbang.org/wiki/index.php/Event_Based_Two_Way_Communication
public class TxRx
{
    private static CommPort commPort;
    private static SerialPort serialPort;
    private static InputStream in;
    private static OutputStream out;
    private static Boolean hasReceivedMsg;
    private static ArrayList<String> rxMsgBuffer;
    private static Integer rxTimeout;
    
    public TxRx(){
        super();
    }
    
    void connect (String portName) throws Exception
    {
        rxMsgBuffer = new ArrayList<String>();
        CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
        
        if(portIdentifier.isCurrentlyOwned()){
            System.out.println("Error: Port is currently in use");
        } else {
            commPort = portIdentifier.open(this.getClass().getName(),2000);
            
            if(commPort instanceof SerialPort){
                serialPort = (SerialPort) commPort;
                serialPort.setSerialPortParams(9600,SerialPort.DATABITS_8,SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);
                
                in = serialPort.getInputStream();
                out = serialPort.getOutputStream();
                
                serialPort.addEventListener(new SerialReader(in));
                serialPort.notifyOnDataAvailable(true);
        
            } else {
                System.out.println("Error: Only serial ports are handled by this example.");
            }
        }     
    }
    
    public static synchronized void close() {
        System.out.println("Closing Serial Port");
        if (serialPort != null) {
            serialPort.removeEventListener();
            serialPort.close();
        }
        System.out.println("Serial Port Closed");
    }
    public void send(String myMsg )throws Exception{
        try {      
            System.out.println("Sending Message");
            out.write(myMsg.getBytes());
            System.out.println("----> " + myMsg);
            
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(-1);
        } 
    }        
    public ArrayList<String> receive(Integer rxTimeout_mSec)throws Exception{
  
//        System.out.println("Waiting for Reply");
        rxTimeout = rxTimeout_mSec;
        hasReceivedMsg = false;
                
        long start = System.currentTimeMillis();
        long now = System.currentTimeMillis();
        while(hasReceivedMsg == false && ((now - start) < rxTimeout)){
//            System.out.println("Waiting...");
            Thread.sleep(10);
            now = System.currentTimeMillis();
        }
        ArrayList<String> temp = rxMsgBuffer;
        rxMsgBuffer = new ArrayList<String>();
        return temp;
    }
    /**
     * Handles the input coming from the serial port. A new line character
     * is treated as the end of a block in this example. 
     */
    public static class SerialReader implements SerialPortEventListener 
    {
        private InputStream in;
        private byte[] buffer = new byte[1024];
        
        public SerialReader (InputStream in){
            this.in = in;
        }
        
        public void serialEvent(SerialPortEvent arg0) {
            int data;
            
          
            try {
                hasReceivedMsg = false;
                Boolean isReceiving = false;
                int len = 0;
                while ( ( data = in.read()) > -1 ){
                    isReceiving = true;
                    if ( data == '\n' ||  data == '\r') {
                        break;
                    }
                    buffer[len++] = (byte) data;
                }

                String temp = new String(buffer,0,len);
//                System.out.println("<----" + temp);
                if(isReceiving){
                    if(!"".equals(temp) && !"".equals(temp.replaceAll(" ",""))){
                        rxMsgBuffer.add(temp);
                    }
                    hasReceivedMsg = true;
                }                
                
                
            }
            catch (IOException e){
                e.printStackTrace();
                System.exit(-1);
            }             
        }
    }
}