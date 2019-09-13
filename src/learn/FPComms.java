/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package learn;

import java.util.ArrayList;
import java.util.Dictionary;
import java.util.Hashtable;

/**
 *
 * @author johannesr
 */
public class FPComms {
    private static TxRx txRx;
    private static Dictionary inMsg;
    
    public static void init(String portName) throws Exception{
        txRx = new TxRx();
        txRx.connect(portName);
        
        inMsg = new Hashtable();
        inMsg.put("Command", ""); 
        inMsg.put("Data", ""); 
        inMsg.put("DataLength", 0);
    }
    public static void close(){
        txRx.close();
    }
    public static void send(String command, String data) throws Exception{
        String msg = ":" + command + ":" + data;
        txRx.send("$" + msg.length() + msg);
    }
    public static Dictionary receive(int timeoutms) throws Exception{
        
        inMsg.put("Command", ""); 
        inMsg.put("Data", ""); 
        inMsg.put("DataLength", 0);
        
        long start = System.currentTimeMillis(); 
        Boolean isMsgReceived = false;

        while((System.currentTimeMillis() - start < timeoutms) && (isMsgReceived == false)){
            // Receiving data
            ArrayList<String> msgs = txRx.receive(10);
            
            // Process Data to find valid msg
            for(String tempMsg : msgs) 
            { 
                //Found Valid Data
                if('$' == tempMsg.charAt(0)){
                    //System.out.println(tempMsg);
                    String[] tempMsgParts = tempMsg.split(":");
                    
                    inMsg.put("Command", tempMsgParts[1]); 
                    inMsg.put("Data", tempMsgParts[2]); 
                    inMsg.put("DataLength", tempMsgParts[2].length());
                    
                    isMsgReceived = true;
                    break;
                }
            }
        }
        return inMsg;
    }
    
}
