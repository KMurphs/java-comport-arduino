/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package learn;
import com.google.gson.JsonObject;
import java.io.IOException;
import java.net.ProtocolException;
import java.sql.*;
import java.util.Dictionary;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;




/**
 *
 * @author johannesr
 */
public class Main extends javax.swing.JFrame {

    /**
     * Creates new form Main
     */
    public Main() {
        initComponents();
  
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        label1 = new java.awt.Label();
        Exit = new java.awt.Label();
        RegNewUser = new java.awt.Label();
        Settings = new java.awt.Label();
        jLabel1 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);
        getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

        label1.setAlignment(java.awt.Label.CENTER);
        label1.setBackground(new java.awt.Color(0, 176, 240));
        label1.setFont(new java.awt.Font("Calibri Light", 1, 14)); // NOI18N
        label1.setName(""); // NOI18N
        label1.setText("Run System");
        getContentPane().add(label1, new org.netbeans.lib.awtextra.AbsoluteConstraints(10, 80, 270, 120));
        Exit.setAlignment(java.awt.Label.CENTER);
        Exit.setBackground(new java.awt.Color(221, 131, 131));
        Exit.setFont(new java.awt.Font("Calibri Light", 1, 14)); // NOI18N
        Exit.setForeground(new java.awt.Color(255, 255, 255));
        Exit.setName(""); // NOI18N
        Exit.setText("EXIT");
        Exit.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                ExitMouseClicked(evt);
            }
        });
        getContentPane().add(Exit, new org.netbeans.lib.awtextra.AbsoluteConstraints(10, 380, 270, 30));

        RegNewUser.setAlignment(java.awt.Label.CENTER);
        RegNewUser.setBackground(new java.awt.Color(0, 0, 0));
        RegNewUser.setFont(new java.awt.Font("Calibri Light", 1, 14)); // NOI18N
        RegNewUser.setForeground(new java.awt.Color(255, 255, 255));
        RegNewUser.setName(""); // NOI18N
        RegNewUser.setText("Register New User");
        RegNewUser.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                RegNewUserMouseClicked(evt);
            }
        });
        getContentPane().add(RegNewUser, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 220, 280, 30));

        Settings.setAlignment(java.awt.Label.CENTER);
        Settings.setBackground(new java.awt.Color(0, 0, 0));
        Settings.setFont(new java.awt.Font("Calibri Light", 1, 14)); // NOI18N
        Settings.setForeground(new java.awt.Color(255, 255, 255));
        Settings.setName(""); // NOI18N
        Settings.setText("Settings");
        Settings.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                SettingsMouseClicked(evt);
            }
        });
        getContentPane().add(Settings, new org.netbeans.lib.awtextra.AbsoluteConstraints(10, 290, 270, 30));

        jLabel1.setBackground(new java.awt.Color(255, 153, 153));
        jLabel1.setForeground(new java.awt.Color(238, 0, 0));
        jLabel1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/Images/Picture3.png"))); // NOI18N
        jLabel1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jLabel1MouseClicked(evt);
            }
        });
        getContentPane().add(jLabel1, new org.netbeans.lib.awtextra.AbsoluteConstraints(-10, -30, -1, -1));

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void ExitMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_ExitMouseClicked
        // TODO add your handling code here:
        System.exit(0);
    }//GEN-LAST:event_ExitMouseClicked


      
    private void RegNewUserMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_RegNewUserMouseClicked

      //new main().setvisible(true);
       dispose();
      new RegisterNewUser().setVisible(true);

    }//GEN-LAST:event_RegNewUserMouseClicked

    private void SettingsMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_SettingsMouseClicked

    }//GEN-LAST:event_SettingsMouseClicked

    private void jLabel1MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jLabel1MouseClicked
        // TODO add your handling code here:
    }//GEN-LAST:event_jLabel1MouseClicked

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Main.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Main().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private java.awt.Label Exit;
    private java.awt.Label RegNewUser;
    private java.awt.Label Settings;
    private javax.swing.JLabel jLabel1;
    private java.awt.Label label1;
    // End of variables declaration//GEN-END:variables
}
