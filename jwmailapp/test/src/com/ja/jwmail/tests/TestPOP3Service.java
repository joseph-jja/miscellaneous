package com.ja.jwmail.tests;

import com.ja.jwmail.services.POP3Service;

import junit.framework.*;
import junit.extensions.*;
import javax.mail.Folder;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import com.ja.jwmail.common.MailMessage;
import com.ja.jwmail.common.Pair;

public class TestPOP3Service extends TestCase {

   private String username; 
   private String passwd; 
   private String mailhost; 

   public TestPOP3Service (String name) {
        super (name);

        username = System.getProperty("username");
        passwd = System.getProperty("passwd");
        mailhost = System.getProperty("mailhost");
   }

   public void testpop3Service() throws Exception {

        POP3Service pservice = new POP3Service();

        System.out.println("POP3Service test started!");

        boolean con = pservice.connect(username, passwd, mailhost);

        assertEquals("true", Boolean.valueOf(con).toString());

        int count = pservice.getMessageCount();
        System.out.println("Message count =  " + count);

        // if there is a message then print the from, subject and sent date
        if ( count > 0 ) { 
            for ( int i = 0; i < count; i+=1 ) { 
                MailMessage msgs = pservice.getMessage(i);
                System.out.println("###############################################");
                System.out.println("From: " + msgs.getFrom() );
                System.out.println("Subject: " + msgs.getSubject() );
                System.out.println("Sent Date: " + msgs.getSentDate() );
                System.out.println("Message Type: " + msgs.getMessageType() );
                System.out.println("Message ID: " + msgs.getMessageID() );
                System.out.println("Message Content: " + msgs.getMessageText() );
                if ( msgs.getAttachments() != null && msgs.getAttachments().size() > 0 ) {
                	List<Pair<String, Object>> attachments = msgs.getAttachments();
                	System.out.println("Message Attachment Count: " + attachments.size() );
                }
                System.out.println("###############################################");
                
                // we dont always want to delete
                // until we have the SMTP service working we comment this out
                //pservice.deleteMessage(i);
            }
        }

        Folder[] folders = pservice.getAllFolders();
        if ( folders != null && folders.length > 0 ) {
        	for ( int i = 0; i < folders.length; i+=1 ) { 
        		System.out.println("###############################################");
        		System.out.println("Name = " + folders[i].getFullName());
        		System.out.println("###############################################");
        	}
        }
        pservice.disconnect(); 

        System.out.println("POP3Service test completed!");
    }
}
