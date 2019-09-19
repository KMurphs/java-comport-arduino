package learn;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;
/**
 *
 * @author johannesr
 */
public class httpRequest {
    private static HttpURLConnection con;
    
    public static JsonObject get(String url, HashMap<String, String> data) throws MalformedURLException,
            ProtocolException, IOException {
        
        JsonObject getResponse;

        try {
            URL myurl = new URL(url);
            con = (HttpURLConnection) myurl.openConnection();

            con.setRequestMethod("GET");
            con.setRequestProperty("User-Agent", "Java client");
            con.setRequestProperty("Content-Type", "application/json");
            
            StringBuilder content;

            try (BufferedReader in = new BufferedReader(
                    new InputStreamReader(con.getInputStream()))) {

                String line;
                content = new StringBuilder();

                while ((line = in.readLine()) != null) {
                    content.append(line);
                    content.append(System.lineSeparator());
                }
            }
            
            JsonParser jsonParser = new JsonParser();
            getResponse = jsonParser.parse(content.toString()).getAsJsonObject();

        } finally {
            
            con.disconnect();
        }
        
        return getResponse;
    }    
    
    public static JsonObject post(String url, HashMap<String, String> data) throws MalformedURLException,
            ProtocolException, IOException {
        
        JsonObject postResponse;
        
        JsonObject postDataJSON = new JsonObject();
        for(Map.Entry<String, String> entry : data.entrySet()) {
            postDataJSON.addProperty(entry.getKey(), entry.getValue()); 
        }

        
        byte[] postData = postDataJSON.toString().getBytes(StandardCharsets.UTF_8);

        try {

            URL myurl = new URL(url);
            con = (HttpURLConnection) myurl.openConnection();

            con.setDoOutput(true);
            con.setRequestMethod("POST");
            con.setRequestProperty("User-Agent", "Java client");
            con.setRequestProperty("Content-Type", "application/json");

            try (DataOutputStream wr = new DataOutputStream(con.getOutputStream())) {
                wr.write(postData);
            }

            StringBuilder content;

            try (BufferedReader in = new BufferedReader(
                    new InputStreamReader(con.getInputStream()))) {

                String line;
                content = new StringBuilder();

                while ((line = in.readLine()) != null) {
                    content.append(line);
                    content.append(System.lineSeparator());
                }
            }

            JsonParser jsonParser = new JsonParser();
            postResponse = jsonParser.parse(content.toString()).getAsJsonObject();

        } finally {
            
            con.disconnect();
        }
        
        return postResponse;
    }    
}
